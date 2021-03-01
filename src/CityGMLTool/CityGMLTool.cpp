#include "CityGMLTool.hpp"

CityGMLTool::CityGMLTool()
{
	this->modules.push_back(new XMLParser("xmlparser"));
}

CityGMLTool::~CityGMLTool()
{
	//std::cout << "Destructeur CityGMLTool" << std::endl;

	for (int i = 0; i < this->modules.size(); i++)
	{
		delete this->modules[i];
	}

	this->modules.clear();

	delete this->cityModel;
}

Module* CityGMLTool::findModuleByName(const std::string name)
{
	for (int i = 0; i < this->modules.size(); i++)
	{
		if (this->modules[i]->getName() == name)
		{
			//std::cout << "::[MODULE FOUND]::[NAME=" << this->modules[i].getName() << "]" << std::endl;
			return this->modules[i];
		}
	}
}

void CityGMLTool::parse(std::string& filename)
{
	XMLParser* xmlparser = static_cast<XMLParser*>(this->findModuleByName("xmlparser"));
	int initError = xmlparser->init(filename);
	//int runError = xmlparser->run();

	citygml::ParserParams params = citygml::ParserParams();
	cityModel = xmlparser->load(filename, params);

	// == 0 if the parsing failed, file name/location may be wrong
	if (cityModel == 0)
	{
		std::cout << "PARSING:.............................:[FAILED]" << std::endl;
		return;
	}

	std::cout << "PARSING:.............................:[OK]" << std::endl;
	//std::cout << model->getroot()->getid() << std::endl;

	std::cout << "city objects roots - size : " << cityModel->getCityObjectsRoots().size() << std::endl;
	for (int i = 0; i < cityModel->getCityObjectsRoots().size(); i++)
	{
		std::cout << cityModel->getCityObjectsRoots()[i]->getTypeAsString() << std::endl;
	}
}
