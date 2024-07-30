import grpc
import user_management_pb2
import user_management_pb2_grpc

def create_user(stub):
    user_id = input("Enter user id: ")
    name = input("Enter user name: ")
    email = input("Enter user email: ")
    
    user = user_management_pb2.CreateUserRequest(user_id=user_id,name=name, email=email)
    response = stub.CreateUser(user)

def get_user(stub):
    user_id = input("Enter user id: ")
    try:
        request = user_management_pb2.GetUserRequest(user_id=user_id)
        response = stub.GetUser(request)
        print(f"User ID: {response.user_id}")
        print(f"Name: {response.name}")
        print(f"Email: {response.email}")
    except grpc.RpcError as e:
        # Handle different types of RPC errors
        if e.code() == grpc.StatusCode.NOT_FOUND:
            print("User not found.")
        else:
            print(f"gRPC Error: {e.code()} - {e.details()}")

def run():
    with grpc.insecure_channel('localhost:50052') as channel:
        stub = user_management_pb2_grpc.UserServiceStub(channel)
        
        while True:
            print("1. Create User")
            print("2. Get User")
            print("3. Exit")
            choice = input("Enter choice: ")
            
            if choice == '1':
                create_user(stub)
            elif choice == '2':
                get_user(stub)
            elif choice == '3':
                break
            else:
                print("Invalid choice. Please try again.")

if __name__ == '__main__':
    run()


