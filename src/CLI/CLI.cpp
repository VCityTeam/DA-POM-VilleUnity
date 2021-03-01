#include "CLI.hpp"

CLI::CLI(int argc, char* argv[])
{
    this->_argc = argc;

    for (int i = 0 ; i < argc; i++)
    {
		std::string str(argv[i]);
		this->_argv.push_back(str);
    }

	_citygmltool = new CityGMLTool();
}

void CLI::run()
{
	checkParams();

	delete _citygmltool;
}

void CLI::checkParams()
{
	// If no parameters : print usage
	if (this->_argc < 2)
	{
		usage();
		return;
	}

	for (int i = 0; i < _argc; i++)
	{
		std::cout << this->_argv.at(i) << " ";
	}

	// Check if the ext is ".gml"
	//TODO: implements a better way to handle file extension detection
	std::string toMatch = ".gml";
	if (this->_argv[1].size() >= toMatch.size() && this->_argv[1].compare(this->_argv[1].size() - toMatch.size(), toMatch.size(), toMatch) == 0)
	{
		std::cout << std::endl;
		std::cout << "..:: CityGML file found ::.." << std::endl;

		this->_citygmltool->parse(this->_argv[1]);
	}
}

void CLI::usage()
{
	std::cout << "Usage: " << std::endl;
	std::cout << "\t citygmltool [options] <gitygmlfile>" << std::endl;

	std::cout << "Options: " << std::endl;
	std::cout << "\t --exemple <exemple>" << std::endl;	// Exemple
}