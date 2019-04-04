// RegularExpressions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <fstream>
#include <regex>

#include "Settings.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n"; 

	string line; // used to read one line of the file at a time

	regex comment("#");
	smatch match;

	// Read in the file
	ifstream myFile;
	myFile.open("config.txt");

	// Check if the file was opened properly
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			// If the line includes a # then we only want to use the part of the line before that
			if (regex_search(line, match, comment)) {
				line = match.prefix();
			}
			cout << line << '\n';
		}

		// Close the file
		myFile.close();
	}
	else cout << "Unable to open file";
	

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
