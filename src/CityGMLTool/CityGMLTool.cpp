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
		// Send the lowerBound of CityModel to the GMLtoOBJ module
		mOBJconverter->setLowerBoundCoord(
			this->cityModel->getEnvelope().getLowerBound().x,
			this->cityModel->getEnvelope().getLowerBound().y,
			this->cityModel->getEnvelope().getLowerBound().z
		);

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
	GMLtoOBJ* mOBJconverter = static_cast<GMLtoOBJ*>(this->findModuleByName("objcreator"));

	// Send the lowerBound of CityModel to the GMLtoOBJ module
	mOBJconverter->setLowerBoundCoord(
		this->cityModel->getEnvelope().getLowerBound().x,
		this->cityModel->getEnvelope().getLowerBound().y,
		this->cityModel->getEnvelope().getLowerBound().z
	);

	if (assignOrCut) {

		TVec3d Lower = this->cityModel->getEnvelope().getLowerBound();
		TVec3d Upper = this->cityModel->getEnvelope().getUpperBound();

		TVec2d MinTile((int)(Lower.x / xmax) * xmax, (int)(Lower.y / ymax) * ymax);
		TVec2d MaxTile((int)(Upper.x / xmax) * xmax, (int)(Upper.y / ymax) * ymax);

		std::cout << Lower << std::endl;
		std::cout << Upper << std::endl;

		std::cout << MinTile << std::endl;
		std::cout << MaxTile << std::endl;

		for (int x = (int)MinTile.x; x <= (int)MaxTile.x; x += xmax)
		{
			for (int y = (int)MinTile.y; y <= (int)MaxTile.y; y += ymax)
			{
				std::vector<TextureCityGML*> texturesList;
				CityModel* tile = gmlcut->assign(this->cityModel, &texturesList, TVec2d(x, y), TVec2d(x + xmax, y + ymax), gmlFilename);

				if (tile->getCityObjectsRoots().size() > 0) {
					//std::cout << "[GMLCUT - ASSIGN]..................[TILE OK]" << std::endl;
					std::string outputFolder = "cut_output_obj";
					std::string filename = outputFolder + "/" + std::to_string((int)(x / xmax)) + "_" + std::to_string((int)(y / ymax)) + ".gml";

					mOBJconverter->setGMLFilename(filename);
					mOBJconverter->createMyOBJ(*tile, outputFolder);
				}
				else {
					//std::cout << "[GMLCUT - ASSIGN]..................[TILE EMPTY] " << TVec2d(x, y) << " " << TVec2d(x + xmax, y + ymax) << std::endl;
				}
				
			}
		}

		std::cout << "[GMLCUT -- ASSIGN]...............................[DONE]" << std::endl;
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
