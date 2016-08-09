// ChatServer.cpp : Defines the entry point for the console application.
//

#include <iostream>

#define ASIO_STANDALONE
#include "asio.hpp"
#include "aprpc.h"

int main(int argc, char* argv[])
{
	asio::io_service a;
	std::cout << "client: test asio........" << std::endl;
	aprpc *b = new aprpc();
	b->aprpc_output();
	std::cout << "new line ..!" << std::endl;
	delete b;
	return 0;
}

