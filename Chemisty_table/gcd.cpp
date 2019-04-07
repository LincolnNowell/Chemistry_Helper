#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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
