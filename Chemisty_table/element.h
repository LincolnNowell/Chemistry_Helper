#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
public:
    Element();
    ~Element();

private:
    int atomic_number;
    std::string abbreviation;
    std::string name;
    double atomic_mass;
    int charge;
};


#endif // ELEMENT_H
