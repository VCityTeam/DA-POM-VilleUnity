#include "GMLSplit.hpp"

GMLSplit::GMLSplit(std::string name) : Module(name)
{
}

void GMLSplit::splitGMLFile(std::string & filename, int nbSplit, std::string outputLocation)
{
	std::cout << "[SPLIT GML FILE]...............................[START]" << std::endl;
	std::cout << "\t [GML FILENAME]....................[" << filename << "]" << std::endl;
	std::cout << "\t [SPLIT NUMBER]....................[" << nbSplit << "]" << std::endl;
	std::cout << "\t [OUTPUT LOCATION]....................[" << outputLocation << "]" << std::endl;

	//TODO: process output location

	


	std::cout << "[SPLIT GML FILE]...............................[END]" << std::endl;
}
