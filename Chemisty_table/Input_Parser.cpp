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

	// stores elements in vector
	// The compound stores a Variable so it can be turned into a algebriac equation
public:

	compound(const std::vector<element>& k_elements, bool ChangeSide = false) :
	compound_elements(k_elements), mChangeSide(ChangeSide)
	{
	}

	std::vector<element> compound_elements;

	int size = compound_elements.size();
	int Constant = 0;
	char mVariable = ' ';
	bool mChangeSide = false; // if the compound is right before the equals sign set to true

};

struct equation
{
	//stores both the left and right sides of the equation
	equation(const std::vector<compound>& Left, const std::vector<compound>& Right) : left(Left), right(Right){}

	std::vector<compound> left, right;
};

struct Variable {

	Variable(char Var = ' ', int Num = 0) : var(Var), constant(Num) {}

	char var = ' ';
	int constant = 0;
};

void Turn_into_Algebra_Equation(const equation&);
Variable Solve_for_Variable(std::string, char,std::vector<Variable>);

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

	std::vector<Variable> constants;

	char Solved_For = 'A';

	//Find the compounds that have the the element and concat to string
	for (size_t element = 0; element < equation_to_balance.left.size(); element++)
	{
		for (size_t compound = 0; compound < equation_to_balance.left[element].size; compound++)
		{
			for (size_t inner_compound = 0; inner_compound < total.size(); inner_compound++)
			{

				for (size_t inner_element = 0; inner_element < total[inner_compound].size; inner_element++)
				{
					if (total[inner_compound].compound_elements[inner_element].name == " ") {
						equation += " = ";
					}

					if (equation_to_balance.left[element].compound_elements[compound].name == 
						total[inner_compound].compound_elements[inner_element].name) 
					{
						

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

			std::cout << equation << "\n";
			//constants.push_back(getConstant(equation, Solved_For,constants));
			equation = "";
			//++Solved_For;
		}
	}
	
}

/*
Variable Solve_for_Variable(std::string Algebra_Equation, char Solve_for, std::vector<Variable> known_constansts) {

	int num;
	char var = ' ';
	bool change_sides = false;

	std::vector<Variable> LeftHandSide, RightHandSide;

	for (size_t character = 0; character < Algebra_Equation.size(); character++){

		if (Algebra_Equation.at(character) == ' ') { continue; }

		if (Algebra_Equation.at(character) == '=') { change_sides = true; continue; }

		if (Algebra_Equation.at(character) > 47 and Algebra_Equation.at(character) < 58)
		{
			std::string hold_char = " ";
			hold_char += Algebra_Equation.at(character);


			if (Algebra_Equation.at(character + 2) > 47 and Algebra_Equation.at(character + 2) < 58) {
				hold_char += " * " + Algebra_Equation.at(character + 2);
			}
			else {
				var = Algebra_Equation.at(character + 1);
			}

			num = std::stoi(hold_char);


			if (Algebra_Equation.at(character) == '>') {
				RightHandSide.push_back(Variable(var, num));
			}

			if (change_sides != true) {
				LeftHandSide.push_back(Variable(var, num));
			}
			else {
				RightHandSide.push_back(Variable(var, num));
			}

			
		}
	}

	Variable Compiler_stop_whining;
	return Compiler_stop_whining;
}




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
*/
