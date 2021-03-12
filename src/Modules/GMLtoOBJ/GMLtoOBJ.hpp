#ifndef GMLTOOBJ_HPP
#define GMLTOOBJ_HPP


#include <fstream>
#include <math.h>
#include "../Module.hpp"
//#include "../XMLParser/CityGMLHandlerLibXml2.hpp"
#include "../../CityModel/CityModel.hpp"

class GMLtoOBJ : public Module
{
public:
    GMLtoOBJ(std::string name);

    void createMyOBJ(const citygml::CityModel& cModel, const std::string& filename);
    std::string getFilename(const std::string& filename);

    void loadBuilding(const citygml::CityModel& cityModel, std::ofstream file);

    ~GMLtoOBJ();
private:

};

#endif // !GMLTOOBJ_HPP
