#include <unistd.h>
#include <iostream>
#include <string>
#include "server.hpp"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "Too few arguments" << std::endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        Server server(8888, argv[1]);
        server.run();
    }
    catch(const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
