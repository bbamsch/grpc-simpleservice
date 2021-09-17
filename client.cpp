#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "service.pb.h"
#include "service.grpc.pb.h"

using test::SimpleService;
using test::TestMethodRequest;
using test::TestMethodResponse;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

int main(int argc, char *argv[]) {
  std::cout << "Hello, World!" << std::endl;

  std::shared_ptr<Channel> channel(grpc::CreateChannel("localhost:8080", grpc::InsecureChannelCredentials()));
  std::unique_ptr<SimpleService::Stub> stub(SimpleService::NewStub(channel));

  TestMethodRequest request;
  request.set_echo("Hello, World!");

  ClientContext context;
  TestMethodResponse response;
  Status status = stub->TestMethod(&context, request, &response);

  if (status.ok()) {
    std::cout << "TestMethod rpc response: " << response.DebugString() << std::endl;
  } else {
    std::cout << "TestMethod rpc failed: " << status.error_message() << std::endl;
  }
}


