#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>


void parse(std::string line);

class element {

	//class stores element name and number

public:

	element(std::string ele_name, int num) :
		name(ele_name), numb_of_elements(num)
	{

	}

	int numb_of_elements;

	std::string name;

};

class compound {

	//stores elements in vector
public:

	compound(const std::vector<element>& k_elements) :
	compound_elements(k_elements)
	{
	}

	std::vector<element> compound_elements;

	int size = compound_elements.size();

};

struct equation
{
	//stores both the left and right sides of the equation
	equation(std::vector<compound> Left, std::vector<compound> Right) : left(Left), right(Right){}

	std::vector<compound> left, right;
};

void balance(equation);

int main() {

	std::string user_input;
	std::cout << "Enter a Chemical Equation.\n";
	std::getline(std::cin, user_input);
	parse(user_input);
}


void parse(std::string line)
{	
	/*
		Tokenize user input into usable objects for use during balancing
	*/

	line+=(">"); //make sure the last line is not a blank line to avoid out of bounds excecption
	
	std::vector<compound> LeftHandSide;
	std::vector<compound> RightHandSide;

	std::vector<element> compound_to_be_stored;

	int exponent_num = 1, subscript = 1;

	std::string name = "", subcript_hold = "";

	bool create_element = false;
	bool left_side = true;
	bool has_lower_case = false;
	bool has_subscript = false;

	for (size_t character = 0; character < line.size(); character++) {

		if (line.at(character) == ' ') { continue; }

		if (line.at(character) == '>') {
			RightHandSide.push_back(compound(compound_to_be_stored));
		}

		//add the element before to Lefthandside before changing sides
		if (line.at(character) == '=') {
			LeftHandSide.push_back(compound(compound_to_be_stored));
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
				has_subscript = true;
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
	balance(chemical_equation);
}

void balance(equation equation_to_balance) {
	
	char Variable = 'a';
	std::vector<compound> total;

	//take out elements that are the same in each compound an assign variables to them
	std::map<char, int> Algebra_Equation;
	
	//combine the left and right sides
	for(auto& Cmpd : equation_to_balance.left) {total.push_back(Cmpd);}

	for (auto& Cmpd : equation_to_balance.right) {total.push_back(Cmpd);}


	for (size_t element = 0; element < equation_to_balance.left.size(); element++)
	{
		for (size_t compound = 0; compound < equation_to_balance.left[element].size; compound++)
		{
			for (size_t inner_compound = 0; inner_compound < total.size(); inner_compound++)
			{
				for (size_t inner_element = 0; inner_element < total[inner_compound].size; inner_element++)
				{
					if (equation_to_balance.left[element].compound_elements[compound].name == 
						total[inner_compound].compound_elements[inner_element].name) 
					{
						Algebra_Equation.insert(std::make_pair((Variable++),
							total[inner_compound].compound_elements[inner_element].numb_of_elements));
					}
				}
			}
		}
	}
	
}
