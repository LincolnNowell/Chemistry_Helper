#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <algorithm>
#include <cmath>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <QMessageBox>
#include <QString>


class element {

    //class stores element name and number

public:

    element(std::string ele_name, int num) :
        name(ele_name), numb_of_elements(num)
    {

    }

    std::string name;
    int numb_of_elements;
};


class compound {

    // stores elements in vector
    // The compound stores a Variable so it can be turned into a algebriac equation
public:

    compound(const std::vector<element>& k_elements, bool ChangeSide = false) :
    compound_elements(k_elements), mChangeSide(ChangeSide)
    {
    }

    std::vector<element> compound_elements;

    size_t size = compound_elements.size();
    int Constant = 0;
    char mVariable = ' ';
    bool mChangeSide = false; // if the compound is right before the equals sign set to true

};


class equation
{
public:

    //stores both the left and right sides of the equation
    equation(const std::vector<compound>& Left, const std::vector<compound>& Right) : left(Left), right(Right){}

    std::vector<compound> left, right;
};


class Variable {

public:

    Variable(char Var = ' ', double Num = 0) : var(Var), constant(Num) {}

    char var = ' ';
    double constant = 0.0;
    bool solved_for;
};

void parse(std::string line);
void Turn_into_Algebra_Equation(const equation&);
void Insert_Variables(std::string&,const std::map<char,double>&);
void Solve_for_Variable(std::string,std::map<char,double>&);
Variable Find_Variable(std::vector<Variable>, std::vector<Variable>);
std::vector<double> Check_For_Fractions(std::map<char,double>&);

#endif // INPUT_PARSER_H
