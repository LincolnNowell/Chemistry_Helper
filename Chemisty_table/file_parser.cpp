#include <string>
#include <iostream>
#include <vector>
#include <cmath>

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

	compound(const std::vector<element>& elements) {
		compound_elements = elements;
	}

	std::vector<element> compound_elements;

	int size = compound_elements.size();

};



int main()
{
	std::string line = " H5O + N4H + Ar = He7 + Ne + CO2 ";

	std::vector<compound> LeftHandSide;
	std::vector<compound> RightHandSide;

	std::vector <element> compound_to_be_stored;
	std::vector <element> total_elements;

	char exponent_symbol = char(94);

	int exponent_num = 1, subscript = 1;

	std::string name = "", subcript_hold = "";

	bool create_element = false;
	bool left_side = true;
	bool has_lower_case = false;
	bool has_subscript = false;

	for (size_t character = 0; character < line.size(); character++) {

		if (line.at(character) == ' ') { continue; }

		if (line.at(character) == '=') {
			left_side = false;
			continue;
		}

		if (line.at(character) == '+') {
			if (left_side == true) {
				LeftHandSide.push_back(compound(compound_to_be_stored));
			}
			else {
				RightHandSide.push_back(compound(compound_to_be_stored));
			}

			compound_to_be_stored.empty();
		}


		//check to see if to see if character is a uppercase
		if (line.at(character) > 64 and line.at(character) < 91) {
			name = "";
			name = line.at(character);

			//check to see if to see if character next to it is a lowercase
			if (line.at(character + 1) > 97 and line.at(character + 1) < 123) {
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

			if (line.at(character + 1) < 47 and line.at(character + 1) > 58) {
			}
			else{
				subscript = std::stoi(subcript_hold);
				create_element = true;
				subcript_hold = "";
			}
		}

		//if there is now subscript after lowercase
		else if (line.at(character) > 97 and line.at(character) < 123 and has_lower_case == true) {
			if (line.at(character + 1) == ' ') {
				create_element = true;
			}

		}


		if (create_element == true) {
			std::cout << subscript << " " << name << "\n";
			compound_to_be_stored.push_back(element(name, subscript));
			create_element = false;
			subscript = 1;
		}
	}


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
*/
