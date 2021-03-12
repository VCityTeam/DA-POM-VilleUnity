#ifndef CITYGMLTOOL_HPP
#define CITYGMLTOOL_HPP

#include <iostream>
#include <vector>
#include "../Modules/Module.hpp"
#include "../Modules/XMLParser/XMLParser.hpp"
#include "../Modules/GMLtoOBJ/GMLtoOBJ.hpp"

class CityGMLTool
{
public:
	CityGMLTool();
	~CityGMLTool();

	Module* findModuleByName(const std::string name);
	void parse();
	void createOBJ();
	void setFileName(std::string& filename);

private:
	std::vector<Module*> modules;
	CityModel* cityModel;
	std::string filename;

};

#endif // !CITYGMLTOOLKIT_HPP

