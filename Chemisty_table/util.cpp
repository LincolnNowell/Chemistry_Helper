#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <Dense>
#include "util.h"



int GCD(std::vector<float>& equation){

    //sort vector before checking for gcd
    std::sort(equation.begin(), equation.end());

    int gcd = 1;

    for(size_t num = 0; num < equation.size(); ++num)
    {

        float result = equation[num] * gcd;

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

    return (gcd);
}

std::vector<float> SolveForSolutions(std::vector<std::vector<float>>matrix){

    int row = matrix.size(), col = matrix[0].size();
    Eigen::VectorXd solution(row);
    for(int i = 0; i < static_cast<int>(matrix.size()); i++){
        solution(i) = matrix[i][matrix.size()];
    }

    Eigen::MatrixXd m1(row,col - 1);
    for(int i = 0; i < m1.rows(); i++){
        for(int j = 0; j < m1.cols(); j++){
            m1(i,j) = matrix[i][j];
        }
    }

    Eigen::VectorXd m3 = m1.colPivHouseholderQr().solve(solution);

    std::vector<float> sol;
    for(int i = 0; i < m3.size(); i++){
        sol.push_back(m3(i));
    }

    return  sol;
}

