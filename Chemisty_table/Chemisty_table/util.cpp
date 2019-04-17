#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"


int GCD(std::vector<double>& equation){

    //sort vector before checking for gcd
    std::sort(equation.begin(), equation.end());

    int gcd = 1;

    for(size_t num = 0; num < equation.size(); ++num)
    {

        double result = equation[num] * gcd;

        // check if number result is a whole number
        if(std::floor(result) == result){
        }
        else{
            //try next number
            ++gcd;

            //start at beginning
            num = static_cast<size_t>(-1);
        }
    }

    return gcd;
}

int stoi_expression(std::string expression) {

    char operation = ' ';

    std::string num1 = "", num2 = "";
    bool second_number = false;

    for (size_t letter = 0; letter < expression.size(); letter++){

        if (expression.at(letter) < 58 and expression.at(letter) > 47) {
            if (second_number == false) { num1 += expression.at(letter); }
            else { num2 += expression.at(letter); }
        }
        else if (expression.at(letter) != ' ') { operation = expression.at(letter); }
        else { second_number = true; }
    }


    switch (operation)
    {
    case '*':
        return std::stoi(num1) * std::stoi(num2);
    case '+':
        return std::stoi(num1) + std::stoi(num2);
    case '-':
        return std::stoi(num1) - std::stoi(num2);
    case '/':
        return std::stoi(num1) / std::stoi(num2);

    default:
        //throw "Invalid Input";
        break;
    }

    return 0;
}
