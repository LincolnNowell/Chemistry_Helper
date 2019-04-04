#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<std::string> give_variable(int index){

    std::vector<std::string> vars;
    for(size_t i = 65; i < (65 + index); i++)
    {
        vars.push_back(std::to_string(i));
    }

    return vars;  
}
int GCD(std::vector<double> equation){

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
            num = -1;
        }
    }
    
    return gcd;
}

int main()
{
    std::vector<double> set = {1,.50,.25};
    std::cout << GCD(set);
}