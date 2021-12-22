#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"

#include <iostream>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using Calculator::Stub;

class Client
{
public:
    Client( std::shared_ptr<Channel> channel ) : mStub{Calculator::NewStub( channel )}
    {
    }

    // Wrapper around the RPC
    void AddOne( int n )
    {
        ClientContext context;

        Number request;
        request.set_n( n );

        Number response;

        Status status = mStub->AddOne( &context, request, &response );

        if( status == Status::OK )
            std::cout << "Output: " << response.n() << std::endl;
        else
            std::cout << "Error occured." << std::endl;
    }

private:
   std::unique_ptr<Stub> mStub;
};

int main( int argc, char **argv )
{
    std::shared_ptr<Channel> channel = grpc::CreateChannel( "localhost:2000", grpc::InsecureChannelCredentials() );

    Client client{ channel };

    std::cout << "Enter input: ";
    int n;
    std::cin >> n;

    client.AddOne( n );

    return 0;
}

