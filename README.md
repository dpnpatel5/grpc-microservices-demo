# gRPC Microservices Demo

This repository demonstrates a microservice-based architecture using gRPC for communication between services. The project includes both C++ and Python implementations to showcase interaction between microservices.

## Project Structure

- **`user_management.proto`**: Protocol Buffers definition file for the User Management service.
- **`Makefile`**: Build script for compiling the C++ server and generating code from `.proto` files.
- **`user_management_server.cpp`**: C++ implementation of the gRPC User Management service.
- **`user_management_client.py`**: Python client for interacting with the gRPC User Management service.

## Features

- **gRPC-based User Management Service**: Provides RPC methods to create and retrieve user information.
- **Multi-language Clients**: Includes C++ server and Python client to demonstrate cross-language gRPC communication.
- **Dynamic User Management**: Supports dynamic creation and retrieval of user data.

## Getting Started

### Prerequisites

- [gRPC](https://grpc.io/docs/languages/cpp/quickstart/) and [Protocol Buffers](https://developers.google.com/protocol-buffers/docs/cpptutorial) installed.
- [Python](https://www.python.org/downloads/) and [grpcio-tools](https://pypi.org/project/grpcio-tools/) installed.
```bash
pip install grpcio grpcio-tools
```

### Build the Server

1. **Generate gRPC Code and Build the Server**:
   ```bash
   make
   ```

### Generate Python code required to interact with the gRPC service defined in user_management.proto.

```bash
python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. user_management.proto
```
