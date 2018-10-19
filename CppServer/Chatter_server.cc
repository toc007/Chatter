/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "Chatter.grpc.pb.h"
#endif

using Chatter::ChatMessage;
using Chatter::Empty;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Chatter::ServerServices::Service
{
public:
  explicit GreeterServiceImpl(std::string s) : serverName(s){};

  Status Ping(ServerContext *context,
              const Empty *request,
              Empty *response) override
  {
    return Status::OK;
  }

  Status Echo(ServerContext *context,
              const ChatMessage *request,
              ChatMessage *response) override
  {
    *response = *request;
    return Status::OK;
  }

  Status nEcho(ServerContext *context,
               const ChatMessage *request,
               ServerWriter<ChatMessage> *writer) override
  {
    for (int i = 0; i < request->timesrepeated(); i++)
    {
      writer->Write(*request);
    }
    return Status::OK;
  }

  Status PingPong(ServerContext *context,
                  ServerReaderWriter<ChatMessage, ChatMessage> *stream) override
  {
    ChatMessage msg;
    ChatMessage pingResponse;
    ChatMessage pongResponse;
    pingResponse.set_payload("Ping");
    pongResponse.set_payload("Pong");
    static int count = 0;
    while (stream->Read(&msg)) {
      if(count % 2 == 0) {
        stream->Write(pingResponse);
      }
      else {
        stream->Write(pongResponse);
      }
      count++;
    }
    return Status::OK;
  }

private:
  const std::string serverName;
  // Status SayHello(ServerContext* context, const HelloRequest* request,
  //                 HelloReply* reply) override {
  //   std::string prefix("Hello ");
  //   reply->set_message(prefix + request->name());
  //   return Status::OK;
  // }
};

void RunServer()
{
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service("I is dumb server");

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char **argv)
{
  RunServer();

  return 0;
}
