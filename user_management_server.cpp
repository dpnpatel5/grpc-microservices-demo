#include <iostream>
#include <unordered_map>
#include <string>
#include <grpcpp/grpcpp.h>
#include "user_management.pb.h"
#include "user_management.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerContext;
using usermanagement::CreateUserRequest;
using usermanagement::CreateUserResponse;
using usermanagement::GetUserRequest;
using usermanagement::GetUserResponse;
using usermanagement::UserService;

struct User {
    std::string name;
    std::string email;
};

class UserServiceImpl final : public UserService::Service {
public:
    Status CreateUser(ServerContext* context, const CreateUserRequest* request, CreateUserResponse* reply) override {
        try {
            // Simulate user creation
            std::cout << "Creating user: " << request->user_id() << ", " << request->name() << ", " << request->email() << std::endl;
            const std::string& user_id = request->user_id();
            const std::string& name = request->name();
            const std::string& email = request->email();

            // Create user in the map
            users_[user_id] = User{name, email};
            reply->set_success(true);
            return Status::OK;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation error: " << e.what() << std::endl;
            return Status(grpc::RESOURCE_EXHAUSTED, "Memory allocation failed");
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            return Status(grpc::INTERNAL, "An unexpected error occurred");
        }
    }

    Status GetUser(ServerContext* context, const GetUserRequest* request, GetUserResponse* reply) override {
        try {
            // Simulate user retrieval
            std::cout << "Getting user: " << request->user_id() << std::endl;
            const std::string& user_id = request->user_id();

            // Find user in the map
            auto it = users_.find(user_id);
            if (it != users_.end()) {
                const User& user = it->second;
                reply->set_user_id(user_id);
                reply->set_name(user.name);
                reply->set_email(user.email);
                return Status::OK;
            } else {
                return Status(grpc::NOT_FOUND, "User not found");
            }
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation error: " << e.what() << std::endl;
            return Status(grpc::RESOURCE_EXHAUSTED, "Memory allocation failed");
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            return Status(grpc::INTERNAL, "An unexpected error occurred");
        }
    }

private:
    std::unordered_map<std::string, User> users_;
};

void RunServer() {
    std::string server_address("0.0.0.0:50052");
    UserServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    printf("Server listening on %s\n", server_address.c_str());

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}

