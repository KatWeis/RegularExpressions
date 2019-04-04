#pragma once

#include <map>
#include <vector>

using namespace std;

template <class T>
class Entry
{
public:
	Entry(string key, T value);
	~Entry();

	// Returns the key part of the entry
	string GetKey() { return key; };

	// Returns the value part of the entry
	T GetValue() { return value; };

	// Returns the type of the entry
	T GetType() { return typeid(value).name(); };

private:
	string key; // The key used to find this entry (its name)
	T value; // The value for this entry (generic, can be of any type)
};

template<class T>
inline Entry<T>::Entry(string key, T value)
{
	this->key = key;
	this->value = value;
}

template<class T>
inline Entry<T>::~Entry()
{
	delete this;
}

class Section
{
public:
	Section(string name, vector<Section*> subs, bool isSub);
	~Section();

	// List subsections for a named section
	void ListSubsections();

	// List all key/value pairs for a section/subsection
	void ListAllEntries();

	// Gets a subsection by name from a named section
	Section* GetSubsection(string name);

	// Gets an entry by key from a named section/subsection
	template <class T>
	Entry<T>* GetEntry(string name);

private:
	map<string, Section> subsections; // Hash table of names to subsections
	map<string, Entry<void*>> entries; // Hash table of names to Entries

	bool isSubsection; // Boolean marking this as a section or subsection

	string name; // Name of the section/subsection which also serves as the key for it
};

// Essentially want this to be a static class -- couldn't make that work without unresolved external symbol errors
// Only one set of "Settings" at a time
class Settings
{
public:
	// Disallow creating an instance of this object
	Settings();
	~Settings();

	// Return a list of all sections from the config file
	void ParseConfigFile(string filepath);

	// Return a list of all sections from the config file
	vector<Section*> ListAllSections();

	// Returns a named section if it exists
	Section* ListNamedSection(string name);

private:
	map<string, Section*> sections; // Hash table of names to sections
};


