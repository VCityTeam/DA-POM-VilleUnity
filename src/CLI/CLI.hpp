#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../CityGMLTool/CityGMLTool.hpp"

class CLI
{
public:
    CLI(int argc, char* argv[]);

	// main function
	void run();

	void checkParams();
    void usage();
private:
    int _argc;
    std::vector<std::string> _argv;

	CityGMLTool* _citygmltool;
};

#endif