#ifndef GMLTOOBJ_HPP
#define GMLTOOBJ_HPP


#include <fstream>
#include <math.h>
#include "../Module.hpp"
#include "../../CityModel/CityModel.hpp"

class GMLtoOBJ : public Module
{
public:
    GMLtoOBJ(std::string name);

	void processOutputLocation(std::string & arg);

    void createMyOBJ(const citygml::CityModel& cModel, std::string argOutputLoc);
	std::string eraseExtension(const std::string& filename);


	void processCityModel(const citygml::CityModel& cityModel);
	void processCityObject(const citygml::CityObject& cityObject);
	void processGeometries(const citygml::CityObject& cityObject);

	void setGMLFilename(const std::string & filename);

private:
	std::ofstream file;
	std::string gmlFilename;
	std::string outputLocation;	// path to ouput location : "output/obj/<filename>" or "/path/to/<filename>"

	int vertexCounter;
	double boundingX;
	double boundingY;
	double boundingZ;
};

#endif // !GMLTOOBJ_HPP
