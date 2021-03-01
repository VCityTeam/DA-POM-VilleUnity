#include "CLI/CLI.hpp"

int main(int argc, char* argv[]) 
{
    CLI cli(argc, argv);
	cli.run();

	std::cin.get();

    return 0;
}