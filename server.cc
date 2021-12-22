#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"

#include <iostream>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class CalculatorServiceImpl final : public Calculator::Service
{
    Status AddOne( ServerContext* context, const Number* request, Number* response ) override
    {
        response->set_n( request->n() + 1 );
        return Status::OK;
    }
};

void RunServer()
{
    ServerBuilder builder;

    builder.AddListeningPort( "localhost:2000", grpc::InsecureServerCredentials() );

    CalculatorServiceImpl service;
    builder.RegisterService( &service );

    std::unique_ptr<Server> server = builder.BuildAndStart();
    std::cout << "Server is listening on localhost:2000" << std::endl;

    server->Wait();
}

int main( int argc, char** argv )
{
    RunServer();
    return 0;
}

