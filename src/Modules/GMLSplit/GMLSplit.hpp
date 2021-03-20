#ifndef GMLSPLIT_HPP
#define GMLSPLIT_HPP

#include <iostream>
#include "../Module.hpp"

class GMLSplit : public Module
{
public:
	GMLSplit(std::string name);

	void splitGMLFile(std::string & filename, int nbSplit, std::string outputLocation);

private:

};

#endif // !GMLSPLIT_HPP
