#include "GMLtoOBJ.hpp"

GMLtoOBJ::GMLtoOBJ(std::string name) : Module(name)
{
}

 void GMLtoOBJ::createMyOBJ(const citygml::CityModel& cityModel,const std::string& filename){

	std::string cleanFileName = getFilename(filename);
	std::string output = "OBJoutput/"+ cleanFileName + ".obj";
	std::ofstream file(output);
	
	if(file){
		file.clear();
		file << "# Generated OBJ object from DA-POM project 2020 " << std::endl;
		file << "# " << std::endl << std::endl;
		file << "o " << cleanFileName << std::endl << std::endl;

		int vertexCounter = 0;

		double boundingX = cityModel.getEnvelope().getLowerBound().x;
		double boundingY = cityModel.getEnvelope().getLowerBound().y;
		double boundingZ = cityModel.getEnvelope().getLowerBound().z;


		for (int i = 0; i < cityModel.getCityObjectsRoots().size(); i++)
		{
			for (int j = 0; j < cityModel.getCityObjectsRoots()[i]->getChildCount(); j++) {
				citygml::CityObject* obj = cityModel.getCityObjectsRoots()[i]->getChild(j);
				for (int k = 0; k < obj->getGeometries().size();k++) {
					for (int l = 0; l < obj->getGeometry(k)->getPolygons().size();l++) { //faces
						int size = obj->getGeometry(k)->getPolygons()[l]->getVertices().size();

						for (int m = 0; m < size;m++) {
							double mX = ((double)obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].x) - boundingX;
							double mY = ((double)obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].y) - boundingY;
							double mZ = ((double)obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].z) - boundingZ;

							file << std::fixed << "v " << mX << " ";
							file << std::fixed << mY << " ";
							file << std::fixed << mZ << std::endl;
						}
						vertexCounter += size;
						file << "f";
						for (int m = 0; m < size;m++) {
							int temp = (vertexCounter - ((size - 1) - m));
							file << " " << temp;
						}
						file << std::endl << std::endl;
					}
				}
			}
		}
	
		file.close();
	}else {
	 	std::cout << "OBJconverter:.............................:[FAILED]" << std::endl;
		 return;
	}
 	
 	std::cout << "fin" << std::endl;
 }

std::string GMLtoOBJ::getFilename(const std::string& filename) {
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

void GMLtoOBJ::loadBuilding(const citygml::CityModel& cityModel, std::ofstream file) {
	//TODO loader for only 1 buidling
}