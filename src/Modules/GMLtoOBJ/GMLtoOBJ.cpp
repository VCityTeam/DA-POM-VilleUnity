#include "GMLtoOBJ.hpp"

GMLtoOBJ::GMLtoOBJ(std::string name) : Module(name)
{
}

 void GMLtoOBJ::createMyOBJ(const citygml::CityModel& cityModel){
    std::cout << "Debut des hostilites" << std::endl;
	std::string output = "myObject.obj";
	std::ofstream file(output);
	
	if(file){
		file.clear();
		file << "# Generated OBJ object from DA-POM project 2020 " << std::endl;
		file << "# " << std::endl << std::endl;
		file << "o myObject " << std::endl << std::endl;

		int vertexCounter=0;
		
		for (int i = 0; i < cityModel.getCityObjectsRoots().size(); i++)
		{
			for(int j = 0; j < cityModel.getCityObjectsRoots()[i]->getChildCount(); j++){
				citygml::CityObject* obj = cityModel.getCityObjectsRoots()[i]->getChild(j);
				for(int k=0; k < obj->getGeometries().size();k++){
					for(int l = 0; l<obj->getGeometry(k)->getPolygons().size();l++){ //faces
						file << "# face " << i << " " << j << " " << k << " " << l << std::endl;
						for(int m=0; m < obj->getGeometry(k)->getPolygons()[l]->getVertices().size();m++){

							double fract, intpart;
							double mX = ((double) obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].x) ;
							double mY = ((double) obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].y);
							double mZ = ((double) obj->getGeometry(k)->getPolygons()[l]->getVertices()[m].z) ;
							fract = modf(mX, &intpart);
							double x = fract*10;
							fract = modf(mY, &intpart);
							double y = fract*10;
							fract = modf(mZ, &intpart);
							double z = fract*10;
							
							file << std::fixed << "v " << mX << " ";
							file << std::fixed << mY << " ";
							file << std::fixed << mZ << std::endl;
						}
						vertexCounter += 3;
						file << "f " << vertexCounter-2 << " " << vertexCounter -1 << " " << vertexCounter << std::endl << std::endl;
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