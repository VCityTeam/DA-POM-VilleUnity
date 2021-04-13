#include "GMLtoOBJ.hpp"

GMLtoOBJ::GMLtoOBJ(std::string name) : Module(name)
{
}

void GMLtoOBJ::processOutputLocation(std::string & arg)
{
	std::string toMatch = ".obj";

	// 1. Test if arg is empty
	if (arg.empty()) {
		// Default procedure, output location : "output/obj/<filename>.obj"

		// Create output directory
		int cmdResult = system("mkdir output");
		if (cmdResult == 0) {
			std::cout << "[DIRECTORY CREATED] : 'output'." << std::endl;
		}

		// Create obj directory
		cmdResult = system("cd output && mkdir obj");
		if (cmdResult == 0) {
			std::cout << "[DIRECTORY CREATED] : 'output/obj'." << std::endl;

			outputLocation = "output/obj/" + eraseExtension(this->gmlFilename) + ".obj";
		}
		else { // already exist
			outputLocation = "output/obj/" + eraseExtension(this->gmlFilename) + ".obj";
		}
	}
	// 2. Test if arg is filename (.obj)
	else if (arg.size() >= toMatch.size() && arg.compare(arg.size() - toMatch.size(), toMatch.size(), toMatch) == 0) {
		// Output location is simply the argument provided
		outputLocation = arg;
	}
	// 3. Test if it's a directory and test if it exists
	else {
		std::string cmd;
		if (arg.back() == '/' || arg.back() == '\\') {
			cmd = "mkdir " + arg.substr(0, arg.size() - 1);
		}
		else {
			cmd = "mkdir " + arg;
			arg.append("/");
		}

		std::cout << "[COMMAND]: " << cmd << std::endl;

		int cmdResult = system(cmd.c_str());
		outputLocation = arg.append(eraseExtension(this->gmlFilename).append(".obj"));

		/* DEBUG LOG */
		if (cmdResult == 0) { // Directory created
			std::cout << "[DIRECTORY CREATED]: '" << arg << "'." << std::endl;
		}
		else { // Directory exists
			std::cout << "[DIRECTORY FOUND] '" << arg << "'" << std::endl;
		}
	}
}

 void GMLtoOBJ::createMyOBJ(const citygml::CityModel& cityModel, std::string argOutputLoc) {

	processOutputLocation(argOutputLoc);
	std::cout << "[OUTPUT LOCATION]: '" << outputLocation << "'" << std::endl;

	file = std::ofstream(outputLocation);
		
	if(file){
		file.clear();
		file << "# Generated OBJ object from DA-POM project 2020 " << std::endl;
		file << "# " << std::endl;
		file << "mtllib " << eraseExtension(gmlFilename) << ".mtl" << std::endl << std::endl;
		file << "o " << eraseExtension(gmlFilename) << std::endl << std::endl;
		file << "usemtl Murs" << std::endl;
		vertexCounter = 0;

		boundingX = cityModel.getEnvelope().getLowerBound().x;
		boundingY = cityModel.getEnvelope().getLowerBound().y;
		boundingZ = cityModel.getEnvelope().getLowerBound().z;

		processCityModel(cityModel);

		file.close();

		std::cout << "OBJconverter:.............................:[OK]" << std::endl;
	}else {
	 	std::cout << "OBJconverter:.............................:[FAILED]: Problem with filepath: '" << outputLocation << "'" << std::endl;
		return;
	}
 }

std::string GMLtoOBJ::eraseExtension(const std::string& filename) {
	std::string res = filename;
	const size_t last_slash_idx = res.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		res.erase(0, last_slash_idx + 1);
	}

	const size_t period_idx = res.rfind('.');
	if (std::string::npos != period_idx)
	{
		res.erase(period_idx);
	}
	return res;
}



void GMLtoOBJ::processCityModel(const citygml::CityModel & cityModel)
{
	std::cout << "CityModel:[ROOT] " << cityModel.getCityObjectsRoots().size() << " children" << std::endl;

	for (int childIdx = 0; childIdx < cityModel.getCityObjectsRoots().size(); childIdx++) {
		file << "g " << childIdx << std::endl;
		processCityObject(*cityModel.getCityObjectsRoots()[childIdx]);
	}
}

void GMLtoOBJ::processCityObject(const citygml::CityObject & cityObject)
{
	std::cout << cityObject.getTypeAsString() << " - " << cityObject.getChildCount() << " children - " << cityObject.getGeometries().size() << " geometries" << std::endl;

	// Check if the current CityObject has any children
	if (cityObject.getChildCount() == 0) {
		// We are at the end of the tree
		// Process geometries if the CityObject has any
		if (cityObject.getGeometries().size() > 0) {
			processGeometries(cityObject);
		}
	}
	else {
		// The current CityObject has children
		// So we need to go deeper to process CityObject's children
		for (int childIdx = 0; childIdx < cityObject.getChildCount(); childIdx++) {
			processCityObject(*cityObject.getChild(childIdx));
		}
	}
}

void GMLtoOBJ::processGeometries(const citygml::CityObject & cityObject)
{
	for (int geoIdx = 0; geoIdx < cityObject.getGeometries().size(); geoIdx++) {
		//std::cout << "\t\t" << *cityObject.getGeometry(geoIdx) << std::endl;

		for (int polygonIdx = 0; polygonIdx < cityObject.getGeometry(geoIdx)->getPolygons().size(); polygonIdx++) { //faces

			//std::cout << "TEXTURES" << cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getTexCoords().front() << std::endl;
			int size = cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices().size();
			for (int n = 0; n < size; n++) {
				double mX = (cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices()[n].x) - boundingX;
				double mY = (cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices()[n].y) - boundingY;
				double mZ = (cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices()[n].z) - boundingZ;
				//std::cout << "v " << mX << " " << mY << " " << mZ << std::endl;

				file << std::fixed << "v " << mY << " ";
				file << std::fixed << mZ << " ";
				file << std::fixed << mX << std::endl;
			}
			for (int coords = 0; coords < cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getTexCoords().size(); coords++) { // cordonnées de textures
				float vtX = cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getTexCoords()[coords].x;
				float vtY = cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getTexCoords()[coords].y;
				file << "vt " << vtX << " " << vtY << std::endl;
				std::cout << "TEXTURES " << vtX << " " << vtY << std::endl;
			}
			vertexCounter += size;
			file << "f";
			for (int m = 0; m < size; m++) {
				int temp = (vertexCounter - ((size - 1) - m));
				file << " " << temp;
			}
			file << std::endl << std::endl;
		}
	}
}

void GMLtoOBJ::setGMLFilename(const std::string & filename)
{
	this->gmlFilename = filename;
}
