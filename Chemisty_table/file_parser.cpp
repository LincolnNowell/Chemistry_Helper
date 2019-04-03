#include <string>
#include <iostream>
#include <vector>


class element{

    //class stores element name and number

    public:

        element(std::string ele_name, int num) :
        name(ele_name), numb_of_elements(num)
        {

        }

        int numb_of_elements;

        std::string name;

};

class compound{

    //stores elements in vector
    public:

    compound(const std::vector<element>& elements){
        compound_elements = elements;
    }

    std::vector<element> compound_elements;

    int size = compound_elements.size();

};



int main()
{
    std::string line = " 2H5O + N4H + 3Ar = He7 + 3Ne + CO2 ";

    std::vector<compound> LeftHandSide;
    std::vector<compound> RightHandSide;

    std::vector <element> compound_to_be_stored;

    char exponent_symbol = char(94);

    int numb_elements = 1, exponent = 1, subscript = 1, total = 1;

    std::string name = "", store = "";

    bool create_element = false;
    bool left_side = true;

    for(size_t character = 0; character < line.size(); character++){

        if(line.at(character) == '='){
            left_side = false;
            continue;
        }

        if(line.at(character) == '+'){
            if(left_side == true){
                LeftHandSide.push_back(compound(compound_to_be_stored));
            }
            else{
                RightHandSide.push_back(compound(compound_to_be_stored));
            }

            compound_to_be_stored.empty();
        }


        // check if the character behind it is a exponent symbol
        if(character > 0 and line.at(character - 1) == exponent_symbol){
            if(line.at(character) > 47 and line.at(character) < 58){
                store = line.at(character);
                exponent = std::stoi(store);
            }
        }

        //check to see if to see if character is a constant
        else if(line.at(character) > 47 and line.at(character) < 58){
            store = line.at(character);
            numb_elements = std::stoi(store);
        }

        //check to see if to see if character is a subscript
        if(character > 0 and line.at(character - 1) != exponent_symbol and line.at(character - 1) != ' '){
            if(line.at(character) > 47 and line.at(character) < 58){
                store = line.at(character);
                subscript = std::stoi(store);
                create_element = true;
            }
        }

        //check to see if to see if character is a uppercase
        if(line.at(character) > 64 and line.at(character) < 91){
            name = "";
            name = line.at(character);
        }

        //check to see if to see if character is a lowercase
        else if(line.at(character) > 97 and line.at(character) < 123){
            name += line.at(character);
        }

        if(create_element == true){
            total = numb_elements * subscript;
            compound_to_be_stored.push_back(element(name,total));
            create_element = false;
        }
    }

/*
    for(size_t character = 0; character < line.size(); character++){

        if(line.at(character) == '='){
            left_side = false;
            std::cout << "Changing side.\n";
            numb_elements = "";
            continue;
        }

        // check if the character behind it is a exponent symbol
        if(character > 0 and line.at(character - 1) == exponent_symbol){
            if(line.at(character) > 47 and line.at(character) < 58){
                exponent = line.at(character);
            }
        }
        else{

            //check to see if to see if character is a constant
            if(line.at(character) > 47 and line.at(character) < 58){
                numb_elements = line.at(character);
            }

            //check to see if character is a uppercase
            else if(line.at(character) > 64 and line.at(character) < 91){
                name+= line.at(character);

                //check to see if character is a lowercase
                if(line.at(character + 1) > 97 and line.at(character + 1) < 123){
                    name+= line.at(character + 1);
                    
                    //check if character after lowercase is subscript
                    if(line.at(character + 2) < 47 and line.at(character + 2) < 58){
                        subscript = line.at(character + 2);
                    }
                }
                
                //check for subscript
                else if(line.at(character + 1) < 47 and line.at(character + 1) < 58){
                    subscript = line.at(character + 1);
                }
            }


            if(line.at(character) != ' ' and line.at(character) != '+' and left_side != false){
                LeftHandSide.push_back(element(name, numb_elements, exponent,subscript));

                name = "";
                numb_elements = "";
                exponent = "";
                subscript = "";
            }
            else if(left_side == false){
                RightHandSide.push_back(element(name, numb_elements, exponent,subscript));

                name = "";
                numb_elements = "";
                exponent = "";
                subscript = "";
            }

        }
        
    }

    for(size_t index = 0; index < LeftHandSide.size(); index++)
    {
        for(size_t detail = 0; detail < LeftHandSide[index].numb_details; detail++)
        {
            std::cout << LeftHandSide[index].details[detail] << " ";
        }   
    }

    std::cout << "RightHandSide\n";

    for(size_t index = 0; index < RightHandSide.size(); index++)
    {
        for(size_t detail = 0; detail < RightHandSide[index].numb_details; detail++)
        {
            std::cout << RightHandSide[index].details[detail] << " ";
        }   
    }
    
    std::cout << std::stoi("2") + 2;
    
  */  
}
