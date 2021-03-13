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

    void createMyOBJ(const citygml::CityModel& cModel, const std::string& filename);
    std::string getFilename(const std::string& filename);

	void processCityModel(const citygml::CityModel& cityModel);
	void processCityObject(const citygml::CityObject& cityObject);
	void processGeometries(const citygml::CityObject& cityObject);

private:
	std::ofstream file;

	int vertexCounter;
	double boundingX;
	double boundingY;
	double boundingZ;
};

#endif // !GMLTOOBJ_HPP
