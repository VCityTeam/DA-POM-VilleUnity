#include "GMLtoOBJ.hpp"

GMLtoOBJ::GMLtoOBJ(std::string name) : Module(name)
{
}

 void GMLtoOBJ::createMyOBJ(const citygml::CityModel& cityModel,const std::string& filename){

	std::string cleanFileName = getFilename(filename);
	std::string output = "OBJoutput/"+ cleanFileName + ".obj";
	file = std::ofstream(output);
		
	if(file){
		file.clear();
		file << "# Generated OBJ object from DA-POM project 2020 " << std::endl;
		file << "# " << std::endl << std::endl;
		file << "o " << cleanFileName << std::endl << std::endl;

		vertexCounter = 0;

		boundingX = cityModel.getEnvelope().getLowerBound().x;
		boundingY = cityModel.getEnvelope().getLowerBound().y;
		boundingZ = cityModel.getEnvelope().getLowerBound().z;

		processCityModel(cityModel);

		//std::cout << "DEBUG" << std::endl;
		//std::cout << cityModel.getCityObjectsMap().size() << std::endl;
		//std::cout << cityModel.getCityObjectsRoots()[0]->getType() << std::endl;


		/*for (int i = 0; i < cityModel.getCityObjectsRoots().size(); i++)
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
		}*/

		// For every CityObject located at the root
		//for (int i = 0; i < cityModel.getCityObjectsRoots().size(); i++)
		//{
		//	for (int j = 0; j < cityModel.getCityObjectsRoots()[i]->getChildCount(); j++) {
		//		citygml::CityObject* obj = cityModel.getCityObjectsRoots()[i]->getChild(j);

		//		std::cout << "////////////////// " << obj->getType() << std::endl;
		//		std::cout << "////////////////// " << citygml::CityObjectsType::COT_BuildingPart << std::endl;

		//		if(obj->getType() == citygml::CityObjectsType::COT_BuildingPart) {
		//			for (int k = 0; k < obj->getChildren().size();k++) {
		//				for (int l = 0; l < obj->getChildren()[k]->getGeometries().size();l++) { //faces
		//					for (int m = 0; m < obj->getChildren()[k]->getGeometry(l)->getPolygons().size();m++) { //faces
		//						int size = obj->getChildren()[k]->getGeometry(l)->getPolygons()[m]->getVertices().size();
		//						for (int n = 0; n < size; n++) {
		//							double mX = ((double)obj->getChildren()[k]->getGeometry(l)->getPolygons()[m]->getVertices()[n].x);
		//							double mY = ((double)obj->getChildren()[k]->getGeometry(l)->getPolygons()[m]->getVertices()[n].y);
		//							double mZ = ((double)obj->getChildren()[k]->getGeometry(l)->getPolygons()[m]->getVertices()[n].z);
		//							//std::cout << "v " << mX << " " << mY << " " << mZ << std::endl;
		//							file << std::fixed << "v " << mX << " ";
		//							file << std::fixed << mY << " ";
		//							file << std::fixed << mZ << std::endl;
		//						}
		//						vertexCounter += size;
		//						file << "f";
		//						for (int m = 0; m < size;m++) {
		//							int temp = (vertexCounter - ((size - 1) - m));
		//							file << " " << temp;
		//						}
		//						file << std::endl << std::endl;
		//					}
		//				}
		//			}
		//		}
		//		else {
		//			for (int k = 0; k < obj->getGeometries().size();k++) {
		//				for (int l = 0; l < obj->getGeometry(k)->getPolygons().size();l++) { //faces
		//					int size = obj->getGeometry(k)->getPolygons()[l]->getVertices().size();

		//					for (int m = 0; m < size;m++) {
		//						double mX = ((double)obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].x) - boundingX;
		//						double mY = ((double)obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].y) - boundingY;
		//						double mZ = ((double)obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].z) - boundingZ;

		//						file << std::fixed << "v " << mX << " ";
		//						file << std::fixed << mY << " ";
		//						file << std::fixed << mZ << std::endl;
		//					}
		//					vertexCounter += size;
		//					file << "f";
		//					for (int m = 0; m < size;m++) {
		//						int temp = (vertexCounter - ((size - 1) - m));
		//						file << " " << temp;
		//					}
		//					file << std::endl << std::endl;
		//				}
		//			}
		//		}
		//	}
		//}
		file.close();
	}else {
	 	std::cout << "OBJconverter:.............................:[FAILED]" << std::endl;
		return;
	}
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

void GMLtoOBJ::processCityModel(const citygml::CityModel & cityModel)
{
	std::cout << "CityModel:[ROOT] " << cityModel.getCityObjectsRoots().size() << " children" << std::endl;

	for (int childIdx = 0; childIdx < cityModel.getCityObjectsRoots().size(); childIdx++) {
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
			int size = cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices().size();

			for (int n = 0; n < size; n++) {
				double mX = (cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices()[n].x) - boundingX;
				double mY = (cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices()[n].y) - boundingY;
				double mZ = (cityObject.getGeometry(geoIdx)->getPolygons()[polygonIdx]->getVertices()[n].z) - boundingZ;
				//std::cout << "v " << mX << " " << mY << " " << mZ << std::endl;

				file << std::fixed << "v " << mX << " ";
				file << std::fixed << mY << " ";
				file << std::fixed << mZ << std::endl;
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
