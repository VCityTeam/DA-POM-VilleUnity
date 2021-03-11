#ifndef GMLTOOBJ_HPP
#define GMLTOOBJ_HPP


#include <fstream>
#include <math.h>
#include "../Module.hpp"
#include "../XMLParser/CityGMLHandlerLibXml2.hpp"

class GMLtoOBJ : public Module
{
public:
    GMLtoOBJ(std::string name);
    int init();
    // int init();
    int run();

     void createMyOBJ(const citygml::CityModel& cModel);

    ~GMLtoOBJ();
private:

};

#endif // !GMLTOOBJ_HPP
