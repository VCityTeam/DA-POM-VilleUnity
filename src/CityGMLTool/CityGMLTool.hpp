#ifndef CITYGMLTOOL_HPP
#define CITYGMLTOOL_HPP

#include <iostream>
#include <vector>
#include "../Modules/Module.hpp"
#include "../Modules/XMLParser/XMLParser.hpp"

class CityGMLTool
{
public:
	CityGMLTool();
	~CityGMLTool();

	Module* findModuleByName(const std::string name);
	void parse(std::string& filename);

private:
	std::vector<Module*> modules;
	CityModel* cityModel;

};

#endif // !CITYGMLTOOLKIT_HPP

