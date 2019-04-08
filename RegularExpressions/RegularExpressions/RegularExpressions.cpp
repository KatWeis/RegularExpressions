// RegularExpressions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <fstream>
#include <regex>

#include "Settings.h"

using namespace std;

int main()
{
	//string line; // used to read one line of the file at a time

	//regex g_string("\".*\""); // a well formed string
	//regex comment("\\*?#"); // struggling to figure out how to allow use if there's an escape character // ISSUE
	//regex prop("="); // can use prefix and suffix to send well-formed data into entries as keys and values
	//regex section("\\[\\w+(:\\w+)?\\]"); // pulls out sections and subsections (haven't tested yet)
	//smatch match;

	//// Read in the file
	//ifstream myFile;
	//myFile.open("config.txt");

	string file = "config.txt";
	bool running = true;

	Settings* s = new Settings();

	// Setup the file
	while (s->ParseConfigFile(file) == false) {
		cout << "Config file could not be loaded for the above reasons. Please enter the filepath to a different config file - ";

		getline(cin, file);

		if (file == "q") {
			running = false;
			break;
		}
	}

	// Do main loop
	while (running) {



		getline(cin, file);

		if (file == "q") {
			running = false;
		}
	}

	

	//// Check if the file was opened properly
	//if (myFile.is_open()) {
	//	while (getline(myFile, line)) {
	//		// Check if the line includes a section
	//		if (regex_search(line, match, section)) {
	//			cout << "Section - " << match[0] << ", Subsection - " << match.str(1) << "\n";
	//		}
	//		// If the line includes a # then we only want to use the part of the line before that
	//		if (regex_search(line, match, comment)) {
	//			line = match.prefix();
	//		}
	//		cout << line << '\n';
	//	}

	//	// Close the file
	//	myFile.close();
	//}
	//else cout << "Unable to open file";
	
	cin.get();

	delete s;
	//return 0;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
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
