#include <algorithm>
#include <QPointer>
#include "input_parser.h"
#include "util.h"


void parse(std::string line)
{
    /*
        Tokenize user input into usable objects for use during balancing
    */

    line+=(">"); //make sure the last line is not a blank line to avoid out of bounds excecption

    std::vector<compound> LeftHandSide;
    std::vector<compound> RightHandSide;

    std::vector<element> compound_to_be_stored; //hold elements to be stored in a compound object

    int subscript = 1;

    std::string name = "", subcript_hold = "";

    bool create_element = false;
    bool left_side = true;
    bool has_lower_case = false;

    //Loop through each letter of the user input to parse for elements
    for (size_t character = 0; character < line.size(); ++character) {

        if (line.at(character) == ' ') { continue; }

        // > is appended to so the program doesn't miss the last compound
        if (line.at(character) == '>') {
            RightHandSide.push_back(compound(compound_to_be_stored));
        }

        //add the element before to Lefthandside before changing sides
        if (line.at(character) == '=') {
            LeftHandSide.push_back(compound(compound_to_be_stored, true));
            compound_to_be_stored.clear();
            left_side = false;
            continue;
        }

        // + signals the compound has ended
        if (line.at(character) == '+') {
            if (left_side) {
                LeftHandSide.push_back(compound(compound_to_be_stored));
            }
            else {
                RightHandSide.push_back(compound(compound_to_be_stored));
            }

            compound_to_be_stored.clear();
        }


        //check to see if to see if character is a uppercase
        if (line.at(character) > 64 and line.at(character) < 91) {
            name = line.at(character);

            //check to see if to see if character next to it is a lowercase
            if (line.at(character + 1) > 96 and line.at(character + 1) < 123) {
                name += line.at(character + 1);
                has_lower_case = true;
            }
            else if (line.at(character + 1) > 47 and line.at(character + 1) < 58) {

            }
            else {
                create_element = true;
            }
        }


        //check to see if to see if character is a subscript
        else if(line.at(character) > 47 and line.at(character) < 58){

            subcript_hold += line.at(character);

            if (line.at(character + 1) > 47 and line.at(character + 1) < 58) {
            }
            else{
                subscript = std::stoi(subcript_hold);
                create_element = true;
                subcript_hold = "";
            }
        }

        //if there is no subscript after lowercase
        else if (line.at(character) > 96 and line.at(character) < 123 and has_lower_case == true) {
            if (line.at(character + 1) == ' ' or line.at(character + 1) == '>') {
                create_element = true;
            }
            else if (line.at(character + 1) > 64 and line.at(character + 1) < 91) {
                create_element = true;
            }
        }


        if (create_element) {
            compound_to_be_stored.push_back(element(name, subscript));
            create_element = false;
            has_lower_case = false;
            name = "";
            subscript = 1;
        }

    }

    equation chemical_equation(LeftHandSide, RightHandSide); // stored in equation class so to lessen amount of args passed to function
    Turn_into_Algebra_Equation(chemical_equation);
}


void Turn_into_Algebra_Equation(const equation& equation_to_balance, bool redo) {

    static int tries = 0;

    std::vector<compound> total;

    //combine the left and right sides
    for (auto& Cmpd : equation_to_balance.left)
    {
        total.push_back(Cmpd);
        if (Cmpd.mChangeSide == true) {
            std::vector<element> dummy_vector = { element(" ", 0) }; //set dummy vector so to check for equals sign
            total.push_back(compound(dummy_vector));
        }
    }

    for (auto& Cmpd : equation_to_balance.right) {total.push_back(Cmpd);}

    //give each compound a variable
    char var = 'A';
    for (auto& Cmpd : total) { if (Cmpd.compound_elements[0].name == " ") {} else { Cmpd.mVariable = var++; } }

    std::string equation = "";

    // map holds the coefficecents that have been solved for
    std::map<char,double> coeffiecents;
    coeffiecents.insert(std::pair<char,double>('A', 1));// Let A = 1 used to solve for first coeffiecent

    size_t num_elements = 0;
    bool use_substitution = false;

    std::vector<std::string> equations;

    //Find the compounds that have the the element and concat to string
    for (size_t compound = 0; compound < equation_to_balance.left.size(); ++compound)
    {
        for (size_t element = 0; element < equation_to_balance.left[compound].size; ++element)
        {
            for (size_t inner_compound = 0; inner_compound < total.size(); ++inner_compound)
            {

                for (size_t inner_element = 0; inner_element < total[inner_compound].size; ++inner_element)
                {
                    if (total[inner_compound].compound_elements[inner_element].name == " ") {
                        equation += " = ";
                    }

                    if (equation_to_balance.left[compound].compound_elements[element].name ==
                        total[inner_compound].compound_elements[inner_element].name)
                    {

                        ++num_elements;

                        //replace variable with its value
                        if (total[inner_compound].Constant != 0) {
                            equation += std::to_string(total[inner_compound].compound_elements[inner_element].numb_of_elements) +
                                "(" + std::to_string(total[inner_compound].Constant) + ")";
                        }
                        else {
                            equation += std::to_string(total[inner_compound].compound_elements[inner_element].numb_of_elements) + total[inner_compound].mVariable;
                        }
                    }
                }
            }


            if(num_elements == total.size() - 1){
                use_substitution = true;
            }

            equations.push_back(equation);
            num_elements = 0;
            equation = "";
        }
    }

    if(redo){
        struct greater_than{
            bool operator()(const std::string& first, const std::string& second){
                return first.size() < second.size();
            }
        };

        greater_than ASC;

        std::sort(equations.begin(),equations.end(), ASC);
    }

    if(use_substitution){
        for(size_t index = 0;index < equations.size(); ++index){
            Solve_for_Variable(equations[index],coeffiecents);
        }
    }
    else{
        for(size_t index = 0;index < equations.size(); ++index){
            Solve_for_Variable(equations[index],coeffiecents);
        }
    }


   Add_Coeffiecents_To_Compound(total,coeffiecents);

   bool balanced = is_balanced(total);

   if(!balanced and tries < 1){
       ++tries;
       Turn_into_Algebra_Equation(equation_to_balance,true);
   }
   else{
       
       tries = 0;
       std::string hold = Create_Output(total);

       Format_Output(hold);

       //Display output
       QPointer<QMessageBox> output = new QMessageBox();
       output->setText(QString::fromStdString(hold));
       output->show();
   }
}

std::vector<double> Check_For_Fractions(std::map<char,double>& coeffiecents){

    /*
     * If the any of the coeffiecents are decimals find the comman multiple and multiply each number by it
        eliminating the fractions
    */

    bool has_fraction = false;
    std::vector<double> to_be_sorted;
    std::vector<double> numbers;

    // floor the value and compare it to original to see if it is a decimal
    for(const auto& [key,value] : coeffiecents){
        if(std::floor(value) != value){
            has_fraction = true;
        }
    }

    if(has_fraction){
        for(const auto& [key,value] : coeffiecents){
            to_be_sorted.push_back(value);
        }

        int gcd = GCD(to_be_sorted);

        for(auto& [key,value] : coeffiecents){
            numbers.push_back(value * gcd);
        }
    }

    else {
        for(const auto& [key,value] : coeffiecents){
            numbers.push_back(value);
        }
    }

    return numbers;
}

/*Insert known values into the equation*/
void Insert_Variables(std::string& Algebra_Equation, const std::map<char,double>& known_constants){
    for(auto const& [key,value] : known_constants){
        for (size_t line = 0; line < Algebra_Equation.size(); ++line) {
            if(key == Algebra_Equation.at(line)){
                std::string hold = "(" + std::to_string(value) + ")"; // put parenthesis around the known value
                int location = static_cast<int>(line) + 1;
                //replace known values in the string
                Algebra_Equation.replace(Algebra_Equation.begin() + static_cast<int>(line),Algebra_Equation.begin() + location, hold);
            }
        }
    }
}

Variable Find_Variable(std::vector<Variable> Left,std::vector<Variable> Right){

    /*
        Variable is solved for like in an algebraic equation
    */

    bool Var_On_Left = false;
    bool Var_On_Right = false;
    char var = ' ';
    double sum = 0;

    std::vector<Variable>LeftHandSide(Left), RightHandSide(Right);


    //finds location of unsolved variable
    for(const auto& obj : LeftHandSide){
        if(obj.var != ' '){
            Var_On_Left = true;
            Var_On_Right = false;
            var = obj.var;
        }
    }
    for(const auto& obj : RightHandSide){
        if(obj.var != ' '){
            Var_On_Left = false;
            Var_On_Right = true;
            var = obj.var;
        }
    }




    /*
        loop through the variables on the side of the unknown variable.
        if it is a variable divide all the numbers on the other side by that number,
        else if subtract. Then Sum all the number on the side without the variable to get it's value
    */

    if(Var_On_Left){
        for (size_t element = 0; element < LeftHandSide.size(); ++element) {
            for (size_t right = 0;  right < RightHandSide.size(); ++right) {
                if(LeftHandSide[element].var == ' '){
                    RightHandSide[right].constant -= LeftHandSide[element].constant;
                }
                else{
                    RightHandSide[right].constant /= LeftHandSide[element].constant;
                }
            }
        }

        for(const auto& obj : RightHandSide){sum += obj.constant;}

    }
    else if(Var_On_Right){
        for (size_t element = 0; element < RightHandSide.size(); ++element) {
            for (size_t left = 0; left < LeftHandSide.size(); ++left) {
                if(RightHandSide[element].var == ' '){
                    LeftHandSide[left].constant -= RightHandSide[element].constant;
                }
                else{
                    LeftHandSide[left].constant /= RightHandSide[element].constant;
                }
            }
        }

        for(const auto& obj : LeftHandSide){sum += obj.constant;}
    }

    return Variable(var, sum);
}


void Solve_for_Variable(std::string Algebra_Equation, std::map<char,double>& known_constansts) {

    Insert_Variables(Algebra_Equation, known_constansts);

    double num = 0;
    char var = ' ';
    bool change_sides = false;
    std::string hold_coefficent = "";
    std::string hold_known_value = "";
    bool var_has_value = false;
    bool create_element = false;


    std::vector<Variable> LeftHandSide, RightHandSide;

    for (size_t character = 0; character < Algebra_Equation.size(); character++){

        if (Algebra_Equation.at(character) == ' ') { continue; }
        if (Algebra_Equation.at(character) == '=') { change_sides = true; continue; }

        //store the numbers inside parenthesis
        if(var_has_value and Algebra_Equation.at(character) != ')'){
            hold_known_value += Algebra_Equation.at(character);
            continue;
        }

        //the known values are surrounded by parenthesises if a open bracket is meet a flag is set to true
        if(Algebra_Equation.at(character) == '('){
            var_has_value = true;
        }

        //multipy coefficent and know value together
        else if(Algebra_Equation.at(character) == ')'){
            var_has_value = false;
            num = std::stod(hold_coefficent) * std::stod(hold_known_value);
            hold_known_value = ' ';
            var = ' ';
            create_element = true;
        }

        else{
            //check for coeffients
            if (Algebra_Equation.at(character) > 47 and Algebra_Equation.at(character) < 58)
            {
                hold_coefficent = Algebra_Equation.at(character);
            }
            //runs if variable is unsolved
            else if (Algebra_Equation.at(character) > 63 and Algebra_Equation.at(character) < 91){
                var = Algebra_Equation.at(character);
                num = std::stod(hold_coefficent);
                create_element = true;
            }
        }

        if(create_element){
             if (change_sides) {
                 RightHandSide.push_back(Variable(var, num));
                 create_element = false;
             }
             else {
                 LeftHandSide.push_back(Variable(var, num));
                 create_element = false;
             }
         }
    }



    Variable obj(Find_Variable(LeftHandSide, RightHandSide));
    known_constansts.insert(std::pair(obj.var,obj.constant));
}

bool is_balanced(std::vector<compound>& total){

    /*
        Check if the chemical equation is balanced
    */

    std::vector<std::string> elements = {total[0].compound_elements[0].name};

    std::string stored_element = " ";

    bool balanced = true;

    //store all variables in a vector
    for (size_t compound = 0; compound < total.size(); ++compound){

        for (size_t element = 0; element < total[compound].compound_elements.size(); ++element) {

            stored_element = total[compound].compound_elements[element].name;
            if(stored_element == " "){continue;}

            //don't store if already stored
            if(std::find(elements.begin(),elements.end(), stored_element) != elements.end()){}

            else {
                elements.push_back(stored_element);
            }
       }
    }


    std::vector<int> lefthandside;
    std::vector<int> righthandside;
    bool change_sides = false;

    int leftside = 0, rightside = 0;
    int coefficent;

    for(size_t i = 0; i < elements.size(); ++i){

        stored_element = elements[i];

        for (size_t compound = 0; compound < total.size(); ++compound){

            for (size_t element = 0; element < total[compound].compound_elements.size(); ++element) {

                if(total[compound].Constant == 0){
                    coefficent = 1;
                }
                else{
                    coefficent = total[compound].Constant;
                }


                if(total[compound].compound_elements[element].name == stored_element){
                    if(!change_sides){leftside += total[compound].compound_elements[element].numb_of_elements * coefficent;}
                    else{rightside += total[compound].compound_elements[element].numb_of_elements * coefficent;}
                }
                else if (total[compound].compound_elements[element].name == " "){
                    change_sides = true;
                    lefthandside.push_back(leftside);
                    leftside = 0;
                    rightside = 0;
                }

           }
        }
        righthandside.push_back(rightside);

        leftside = 0;
        rightside = 0;

        change_sides = false;
    }





    //the size of each vector should be the same because they hold the amount of a certain element on each side
    //both sides should contain the element
    for (size_t begin = 0; begin < lefthandside.size(); ++begin) {
        if(lefthandside[begin] != righthandside[begin]){
            balanced = false;
            continue;
        }
    }



    return balanced;
}


void Add_Coeffiecents_To_Compound(std::vector<compound>& total, std::map<char,double>&coeffiecents){

    /*Add Coeffiecents to corresponding compound*/

    std::vector<double>coeffiecents_to_add = Check_For_Fractions(coeffiecents);


    if(coeffiecents_to_add[0] <= 0){coeffiecents_to_add.erase(coeffiecents_to_add.begin());}

    size_t gap_for_equals_sign = 0; // skip the compound that represents the equals sign

    for (size_t start = 0; start < total.size(); ++start) {
        if(total[start].mVariable == ' '){
            gap_for_equals_sign = 1;
            continue;
        }

        total[start].Constant = static_cast<int>(coeffiecents_to_add[start - gap_for_equals_sign]);
    }
}

std::string Create_Output(const std::vector<compound>& total){

    /*
        concat the compound info onto hold string
    */

    std::string hold = "";

    for(const auto& Compound : total){
        //check for equals sign
        if(Compound.mVariable == ' '){
            hold += "= ";
        }

        // if the coefficent is less than 2, just add the name and subscript
        else if(Compound.Constant < 2){
            for(const auto& elements : Compound.compound_elements){
                hold += elements.name;
                if(elements.numb_of_elements > 1){hold += std::to_string(elements.numb_of_elements);}
            }
            hold += " + ";
        }

        else{
            hold+= std::to_string(Compound.Constant);
            for(const auto& elements : Compound.compound_elements){
                hold += elements.name;
                if(elements.numb_of_elements > 1){hold += std::to_string(elements.numb_of_elements);}
            }
            hold += " + ";
        }
    }


    return hold;
}

void Format_Output(std::string& hold){

    /*
     Remove and misplaced + signs
     */

    size_t store = 0;
    bool ready = false;

   for (size_t line = 0; line < hold.size(); ++line) {
       if(hold.at(line) == '+'){
           store = line;
           ready = true;
       }

       // remove the plus signs that gets added at the end
       if(ready and (hold.at(line) == '=' or line == hold.size() - 1)){
           hold.erase(hold.begin() + store);
           ready = false;
       }
   }
}
