#include "pch.h"
#include "Settings.h"


void Settings::ParseConfigFile(string filepath)
{
	string secName = "yo";

	string subName = "sup";

	vector<Section*> subs;
	subs.push_back(new Section(subName, subs, true));

	Section* newSec = new Section(secName, subs, false);
	
	sections = { {secName, newSec} };

	// ^^ above is just test code

	// PUT FILE LOADING HERE

	// PUT REGEX PARSING HERE
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
	delete &sections;
}

Section::Section(string name, vector<Section*> subs, bool isSub)
{
	this->name = name;
	isSubsection = isSub;

	if (isSubsection) {
		// move all the sub stuff over from the vector to the map of subsections
	}

	// move over Entries from vector to map of entries
}

Section::~Section()
{
}

void Section::ListSubsections()
{
	for (map<string, Section>::iterator it = subsections.begin(); it != subsections.end(); ++it) {
		std::cout << (it->second).name;
	}
}

void Section::ListAllEntries()
{
	for (map<string, Entry<void*>>::iterator it = entries.begin(); it != entries.end(); ++it) {
		std::cout << (it->second).GetKey() << " : " << (it->second).GetValue();
	}
}

Section* Section::GetSubsection(string name)
{
	// Return the subsection by name if it contains it and this isn't a subsection already
	if (!isSubsection)
		return &subsections.at(name);
	else // Otherwise return a null ptr
		return nullptr;
}

template <class T>
Entry<T>* Section::GetEntry(string name)
{
	return entries.at(name);
}
