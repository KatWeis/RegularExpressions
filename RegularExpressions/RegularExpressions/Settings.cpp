#include "pch.h"
#include "Settings.h"


bool Settings::ParseConfigFile(string filepath)
{
	bool parsed = true;
	int lineNum = 0; //var to keep track of which line has the error on it
	
	//sections.insert_or_assign(secName, newSec);
	


	// ^^ above is just test code

	// Regex expressions to check
	regex comment("\\*?#"); // struggling to figure out how to allow use if there's an escape character // ISSUE
	regex section("\\[(\\w+)(:\\w+)?\\]"); // pulls out sections and subsections (tested basic, but not edge-cases)
	regex entry("(\\w+)=(((\".*\")|(true|TRUE|false|FALSE)|(\\d+\\.\\d+f$)|([0-9]+))|(\\{(.+[,;]?)+\\}))"); // any alpha-numeric on the left (no spaces), then an =, then a valid value type
	regex list("((\".*\")|(true|TRUE|false|FALSE)|(\\d+\\.\\d+f$)|([0-9]+))");

	string line; // used to read one line of the file at a time
	smatch match; // Stores any successful matches from the regex

	// Used to track which section and subsection each entry belongs to
	string currentSection = "";
	string currentSubsection = "";

	// PUT FILE LOADING HERE

	// Read in the file
	ifstream myFile;
	myFile.open(filepath);

	// Check if the file was opened properly
	if (myFile.is_open()) {
		// PUT REGEX PARSING HERE
		while (getline(myFile, line)) {
			line.erase(line.find_last_not_of(" \t\v\f\r\n") + 1); //Trimming the whitespace from the end
			lineNum++; //increment the line number by 1
			// Check if the line includes a section
			if (regex_search(line, match, section)) {
				cout << "Section - " << match[1] << ", Subsection - " << match.str(2) << "\n";
				currentSection = match[1]; // the section
				string tempSub = match[2]; // the subsection
				currentSubsection = tempSub.erase(0, 1); // remove the semi-colon from the subsection's string

				// Add the sections
				if (sections[currentSection]->GetSubsection(currentSubsection) == nullptr) {

				}
			}
			// Check if the line includes a property/entry
			if (regex_search(line, match, entry)) {
				// Must be within a section/subsection
				if (currentSection == ""){
					cout << "Malformed config line on line # - " << lineNum << endl;
					cout << "All key values must be contained within a section or subsection" << endl;
					parsed = false;
					break; // break out of the loop because we don't need to continue after failure
				}
				else {
					string value;
					if (match.str(9) != "") { // Multilist
						value = match.str(9);
						smatch listMatch; // Stores any successful matches from the regex for the list

						regex_search(value, listMatch, list);

						if (listMatch.length() < count(value.begin(), value.end(), ';')-1) {
							cout << "Malformed config line on line # - " << lineNum << endl;
							cout << "Lists must be made up of accepted value types (string, float, int, or bool)" << endl;
							parsed = false;
							break; // break out of the loop because we don't need to continue after failure
						}

						// Add to the current section and subsection as a list/vector type
					}
					if (match.str(3) != "") { // STRING
						value = match.str(3);

						// Replace spaces with dashes "as-is"
						for (int i = 0; i < value.size(); i++) {
							if (value[i] == ' ') {
								value[i] = '-';
							}
						}
							

						// Add to the current section and subsection as a string type
					}
					else if (match.str(4) != "") { // BOOL
						value = match.str(4);

						// Add to the current section and subsection as a boolean type
					}
					if (match.str(5) != "") { // FLOAT
						value = match.str(5);

						// Add to the current section and subsection as an float type
					}
					else if (match.str(6) != "") { // INTEGER
						value = match.str(6);

						string suf = match.suffix();
						// If the integer has a period further forward, discard it
						if (suf.find('.') != std::string::npos)
						{
							cout << "Malformed config line on line # - " << lineNum << endl;
							cout << "Numbers must be in the form of integers (without decimals)\n or floats (ending with f)" << endl;
							parsed = false;
							break; // break out of the loop because we don't need to continue after failure
						}
						// Add to the current section and subsection as a integer type
					}
					if (match.str(10) != "") { // DEFAULT -- empty right side
						value = match.str(10);

						// Add to the current section and subsection as a list/vector type
					}
					cout << "Key - " << match.str(1) << ", Value - " << value << "\n";
				}
			}
			// If the line includes a # then we only want to use the part of the line before that
			if (regex_search(line, match, comment)) {
				line = match.prefix();
			}
			cout << line << '\n';
		}

		// Close the file
		myFile.close();
	}
	else {
		cout << "Unable to open file" << endl;
		parsed = false;
	}

	return parsed;
}

vector<Section*> Settings::ListAllSections()
{
	vector<Section*> allSecs;

	for (map<string, Section*>::iterator it = sections.begin(); it != sections.end(); ++it) {
		allSecs.push_back(it->second);
	}

	return allSecs;
}

Section* Settings::ListNamedSection(string name)
{
	return sections.at(name);
}

Settings::Settings()
{
}


Settings::~Settings()
{
	// Delete all of the Sections in this Setting config
	for (std::map<string, Section*>::iterator it = sections.begin(); it != sections.end(); ++it)
		delete it->second;
	
}

Section::Section(string name, vector<Section*> subs, bool isSub)
{
	this->name = name;
	isSubsection = isSub;

	if (isSubsection) {
		// move all the sub stuff over from the vector to the map of subsections
		for (size_t i = 0; i < subs.size(); i++)
		{
			subsections.insert_or_assign(subs[i]->name, subs[i]);
		}
		
	}

	// move over Entries from vector to map of entries
}

Section::~Section()
{
	for (map<string, Section*>::iterator it = subsections.begin(); it != subsections.end(); ++it) {
		delete it->second;
	}

	for (map<string, Entry<void*>*>::iterator it = entries.begin(); it != entries.end(); ++it) {
		delete it->second;
	}
}

void Section::ListSubsections()
{
	for (map<string, Section*>::iterator it = subsections.begin(); it != subsections.end(); ++it) {
		std::cout << (it->second)->name;
	}
}

void Section::ListAllEntries()
{
	for (map<string, Entry<void*>*>::iterator it = entries.begin(); it != entries.end(); ++it) {
		std::cout << (it->second)->GetKey() << " : " << (it->second)->GetValue();
	}
}

Section* Section::GetSubsection(string name)
{
	// Return the subsection by name if it contains it and this isn't a subsection already
	if (!isSubsection)
		return subsections.at(name);
	else // Otherwise return a null ptr
		return nullptr;
}

template <class T>
Entry<T>* Section::GetEntry(string name)
{
	return entries.at(name);
}
