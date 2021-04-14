#include "CityGMLTool.hpp"

CityGMLTool::CityGMLTool()
{
	this->modules.push_back(new XMLParser("xmlparser"));
	this->modules.push_back(new GMLtoOBJ("objcreator"));
	this->modules.push_back(new GMLCut("gmlcut"));
	this->modules.push_back(new GMLSplit("gmlsplit"));
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

void CityGMLTool::parse(std::string & filename)
{	
	XMLParser* xmlparser = static_cast<XMLParser*>(this->findModuleByName("xmlparser"));

	citygml::ParserParams params = citygml::ParserParams();
	cityModel = xmlparser->load(filename, params);

	// == 0 if the parsing failed, file name/location may be wrong
	if (cityModel == 0)
	{
		std::cout << "PARSING:.............................:[FAILED]" << std::endl;
		exit(1);
		return;
	}

	std::cout << "PARSING:.............................:[OK]" << std::endl;


	/*
		==============================================
		::::::::::::::::: DEBUG PART :::::::::::::::::
		==============================================
	*/

	//std::cout << "city objects roots - size : " << cityModel->getCityObjectsRoots().size() << std::endl;
	//for (int i = 0; i < cityModel->getCityObjectsRoots().size(); i++)
	//{
	//	std::cout << (cityModel->getCityObjectsRoots()[i]->getTypeAsString()) << " ";
	//	std::cout << cityModel->getCityObjectsRoots()[i]->getChildCount() << " children ";
	//	std::cout << cityModel->getCityObjectsRoots()[i]->getGeometries().size() << " geometries" << std::endl;

	//	// If CityObject type is "Bridge", they have no children so we don't need to go deeper
	//	if (cityModel->getCityObjectsRoots()[i]->getType() == CityObjectsType::COT_Bridge) {
	//		for (int geo = 0; geo < cityModel->getCityObjectsRoots()[i]->getGeometries().size(); geo++) {

	//			const Geometry* geometry = cityModel->getCityObjectsRoots()[i]->getGeometry(geo);
	//			std::cout << "\t " << *geometry << std::endl;
	//		}
	//	}
	//	// If CityObject type is "Building", we need to go deeper
	//	else if (cityModel->getCityObjectsRoots()[i]->getType() == CityObjectsType::COT_Building) {
	//		for (int j = 0; j < cityModel->getCityObjectsRoots()[i]->getChildCount(); j++)
	//		{
	//			const CityObject* obj = cityModel->getCityObjectsRoots()[i]->getChild(j);

	//			std::cout << "\t" << (obj->getTypeAsString()) << " - ";
	//			std::cout << obj->getChildCount() << " children ";
	//			std::cout << obj->getGeometries().size() << " geometries" << std::endl;

	//			// If CityObject type is "BuildingPart", we need to go deeper
	//			if (obj->getType() == CityObjectsType::COT_BuildingPart) {
	//				for (int k = 0; k < obj->getChildren().size(); k++) {
	//					std::cout << "\t\t" << obj->getChild(k)->getTypeAsString() << " - ";
	//					std::cout << obj->getChild(k)->getChildCount() << " children ";
	//					std::cout << obj->getChild(k)->getGeometries().size() << " geometries" << std::endl;
	//				}
	//			}
	//		}
	//	}
	//}
}

void CityGMLTool::createOBJ(std::string & gmlFilename, std::string output) {
	 GMLtoOBJ* mOBJconverter = static_cast<GMLtoOBJ*>(this->findModuleByName("objcreator"));
	 if(cityModel){
		 mOBJconverter->setGMLFilename(gmlFilename);
	 	mOBJconverter->createMyOBJ(*cityModel, output);
	 }else {
	 	std::cout << "OBJconverter:.............................:[FAILED]: CityModel NULL" << std::endl;
	 	return;
	 }
}

void CityGMLTool::gmlCut(std::string & gmlFilename, double xmin, double ymin, double xmax, double ymax, bool assignOrCut, std::string output)
{
	GMLCut* gmlcut = static_cast<GMLCut*>(this->findModuleByName("gmlcut"));

	if (assignOrCut) {
		std::vector<TextureCityGML*> texturesList;
		CityModel* tile = gmlcut->assign(this->cityModel, &texturesList, TVec2d(xmin, ymin), TVec2d(xmax, ymax), gmlFilename);

		std::cout << "[GMLCUT -- ASSIGN]...............................[DONE]" << std::endl;

		/*
		==============================================
		::::::::::::::::: DEBUG PART :::::::::::::::::
		==============================================
		*/

		std::cout << "city objects roots - size : " << tile->getCityObjectsRoots().size() << std::endl;
		for (int i = 0; i < tile->getCityObjectsRoots().size(); i++)
		{
			std::cout << (tile->getCityObjectsRoots()[i]->getTypeAsString()) << " ";
			std::cout << tile->getCityObjectsRoots()[i]->getChildCount() << " children ";
			std::cout << tile->getCityObjectsRoots()[i]->getGeometries().size() << " geometries" << std::endl;

			// If CityObject type is "Bridge", they have no children so we don't need to go deeper
			if (tile->getCityObjectsRoots()[i]->getType() == CityObjectsType::COT_Bridge) {
				for (int geo = 0; geo < tile->getCityObjectsRoots()[i]->getGeometries().size(); geo++) {

					const Geometry* geometry = tile->getCityObjectsRoots()[i]->getGeometry(geo);
					std::cout << "\t " << *geometry << std::endl;
				}
			}
			// If CityObject type is "Building", we need to go deeper
			else if (tile->getCityObjectsRoots()[i]->getType() == CityObjectsType::COT_Building) {
				for (int j = 0; j < tile->getCityObjectsRoots()[i]->getChildCount(); j++)
				{
					const CityObject* obj = tile->getCityObjectsRoots()[i]->getChild(j);

					std::cout << "\t" << (obj->getTypeAsString()) << " - ";
					std::cout << obj->getChildCount() << " children ";
					std::cout << obj->getGeometries().size() << " geometries" << std::endl;

					// If CityObject type is "BuildingPart", we need to go deeper
					if (obj->getType() == CityObjectsType::COT_BuildingPart) {
						for (int k = 0; k < obj->getChildren().size(); k++) {
							std::cout << "\t\t" << obj->getChild(k)->getTypeAsString() << " - ";
							std::cout << obj->getChild(k)->getChildCount() << " children ";
							std::cout << obj->getChild(k)->getGeometries().size() << " geometries" << std::endl;
						}
					}
				}
			}
		}
	}
	else {
		gmlcut->cut(gmlFilename, xmin, ymin, xmax, ymax, output);
	}
}

void CityGMLTool::gmlSplit(std::string & gmlFilename, int nbSplit, std::string output)
{
	GMLSplit* gmlsplit = static_cast<GMLSplit*>(this->findModuleByName("gmlsplit"));

	gmlsplit->splitGMLFile(gmlFilename, nbSplit, output);
}

void CityGMLTool::setFileName(std::string& filename) {
	this->filename = filename;
}
