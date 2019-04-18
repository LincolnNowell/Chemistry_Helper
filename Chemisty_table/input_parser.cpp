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

    std::vector<element> compound_to_be_stored;

    int subscript = 1;

    std::string name = "", subcript_hold = "";

    bool create_element = false;
    bool left_side = true;
    bool has_lower_case = false;

    for (size_t character = 0; character < line.size(); ++character) {

        if (line.at(character) == ' ') { continue; }

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
            if (left_side == true) {
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
            if (line.at(character + 1) == ' ') {
                create_element = true;
            }
            else if (line.at(character + 1) > 64 and line.at(character + 1) < 91) {
                create_element = true;
            }
        }


        if (create_element == true) {
            compound_to_be_stored.push_back(element(name, subscript));
            create_element = false;
            has_lower_case = false;
            name = "";
            subscript = 1;
        }
    }

    equation chemical_equation(LeftHandSide, RightHandSide);
    Turn_into_Algebra_Equation(chemical_equation);
}



void Turn_into_Algebra_Equation(const equation& equation_to_balance) {

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

    char var = 'A';
    for (auto& Cmpd : total) { if (Cmpd.compound_elements[0].name == " ") {} else { Cmpd.mVariable = var++; } }

    std::string equation = "";

    std::map<char,double> coeffiecents;
    coeffiecents.insert(std::pair<char,double>('A', 1));// Let A = 1 used to solve for first coeffiecent


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
                        //equation += equation_to_balance.left[compound].compound_elements[element].name;


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

            Solve_for_Variable(equation,coeffiecents);
            equation = "";
        }
    }


   std::vector<double>coeffiecents_to_add = Check_For_Fractions(coeffiecents);

   size_t gap_for_equals_sign = 0;

   for (size_t start = 0; start < total.size(); ++start) {
       if(total[start].mVariable == ' '){
           gap_for_equals_sign = 1;
           continue;
       }

       total[start].Constant = static_cast<int>(coeffiecents_to_add[start - gap_for_equals_sign]);
   }

   std::string hold = "";

   for(const auto& Compound : total){
       if(Compound.mVariable == ' '){
           hold += "= ";
       }
       else if(Compound.Constant < 2){
           hold += std::to_string(Compound.Constant);
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


    size_t store = 0;
    bool ready = false;

   for (size_t line = 0; line < hold.size(); ++line) {
       if(hold.at(line) == '+'){
           store = line;
           ready = true;
       }

       if(ready and (hold.at(line) == '=' or line == hold.size() - 1)){
           hold.erase(hold.begin() + store);
           ready = false;
       }
   }

   QPointer<QMessageBox> output = new QMessageBox();
   output->setText(QString::fromStdString(hold));
   output->show();
}

std::vector<double> Check_For_Fractions(std::map<char,double>& coeffiecents){

    bool has_fraction = false;
    std::vector<double> to_be_sorted;
    std::vector<double> numbers;

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
                Algebra_Equation.replace(Algebra_Equation.begin() + static_cast<int>(line),Algebra_Equation.begin() + location, hold);
                //replace known values in the string
            }
        }
    }
}

Variable Find_Variable(std::vector<Variable>& LeftHandSide,std::vector<Variable>& RightHandSide){
    bool Var_On_Left = false;
    bool Var_On_Right = false;
    char var = ' ';
    double sum = 0;



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

    if(Var_On_Left){
        for (size_t element = 0; element < RightHandSide.size(); ++element) {
            for (size_t left = 0; left < LeftHandSide.size(); ++left) {
                if(LeftHandSide[element].var == ' '){
                    RightHandSide[left].constant -= LeftHandSide[element].constant;
                }
                else{
                    RightHandSide[left].constant /= LeftHandSide[element].constant;
                }
            }
        }

        for(const auto& obj : RightHandSide){
            sum += obj.constant;
        }
    }
    else if(Var_On_Right){
        for (size_t element = 0; element < LeftHandSide.size(); ++element) {
            for (size_t right = 0; right < RightHandSide.size(); ++right) {
                if(RightHandSide[element].var == ' '){
                    LeftHandSide[right].constant -= RightHandSide[element].constant;
                }
                else{
                    LeftHandSide[right].constant /= RightHandSide[element].constant;
                }
            }
        }
        for(const auto& obj : LeftHandSide){
            sum += obj.constant;
        }
    }


    return Variable(var, sum);
}


void Solve_for_Variable(std::string Algebra_Equation, std::map<char,double>& known_constansts) {

    Insert_Variables(Algebra_Equation, known_constansts);

    double num = 0;
    char var = ' ';
    bool change_sides = false;
    std::string hold_coefficent = "";
    std::string hold_char = "";
    bool var_has_value = false;
    bool create_element = false;


    std::vector<Variable> LeftHandSide, RightHandSide;

    for (size_t character = 0; character < Algebra_Equation.size(); character++){

        if (Algebra_Equation.at(character) == ' ') { continue; }
        if (Algebra_Equation.at(character) == '=') { change_sides = true; continue; }

        if(var_has_value and Algebra_Equation.at(character) != ')'){
            hold_char += Algebra_Equation.at(character);
            continue;
        }

        if(Algebra_Equation.at(character) == '('){
            var_has_value = true;
        }
        else if(Algebra_Equation.at(character) == ')'){
            var_has_value = false;
            num = std::stod(hold_coefficent) * std::stod(hold_char);
            var = ' ';
            create_element = true;
        }

        else{
            //check for coeffients
            if (Algebra_Equation.at(character) > 47 and Algebra_Equation.at(character) < 58)
            {
                hold_coefficent = Algebra_Equation.at(character);
            }
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
    //std::cout << obj.var << " " << obj.constant << "\n";
    known_constansts.insert(std::pair(obj.var,obj.constant));
}

/*
        // check if the character behind it is a exponent symbol
        if (character > 0 and line.at(character - 1) == exponent_symbol) {
            if (line.at(character) > 47 and line.at(character) < 58) {
                store = line.at(character);
                exponent = std::stoi(store);
                create_element = true;
            }
        }
        // check if the character behind it is a exponent symbol
        if (character > 0 and line.at(character - 1) == exponent_symbol) {
            if (line.at(character) > 47 and line.at(character) < 58) {
                store = line.at(character);
                exponent = std::stoi(store);
                create_element = true;
            }
        }


            if (Algebra_Equation.at(character) == '(') {

            }
            else {
                //store variable and the number of elements
                var = Algebra_Equation.at(character + 1);
                num = std::stod(hold_char);
            }

            if (Algebra_Equation.at(character) == '>') {
                RightHandSide.push_back(Variable(var, num));
            }
            if (change_sides != true) {
                LeftHandSide.push_back(Variable(var, num));
            }
            else {
                RightHandSide.push_back(Variable(var, num));
            }
*/
