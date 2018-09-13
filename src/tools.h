#pragma once

#include <map>
#include <string>

typedef void* (*NewInstancePt)();

class Tools
{
public:
	static void* CreateObject(const char *className)
	{
		std::map<std::string, NewInstancePt>::const_iterator it;
		it = dynCreateMap.find(className);
		if (it == dynCreateMap.end())
			return NULL;
		else
		{
			NewInstancePt np = it->second;
			return np();
		}
	}

	static void RegisterClass(const char *className, NewInstancePt np)
	{
		dynCreateMap[className] = np;
		nameIdMap[className] = count;
		idNameMap[count] = className;
		++count;
	}

	static int getId(const char *className) {
		std::map<std::string, int>::const_iterator it;
		it = nameIdMap.find(className);
		if (it == nameIdMap.end())
			return -1;
		else
			return it->second;
	}

	static std::string getName(int id) {
		std::map<int, std::string>::const_iterator it;
		it = idNameMap.find(id);
		if (it == idNameMap.end())
			return "NoSuchClass";
		else
			return it->second;
	}


private:
	static std::map<std::string, NewInstancePt> dynCreateMap;
	static std::map<std::string, int> nameIdMap;
	static std::map<int, std::string> idNameMap;
	static int count;
};

std::map<std::string, NewInstancePt> Tools::dynCreateMap;
std::map<std::string, int> Tools::nameIdMap;
std::map<int, std::string> Tools::idNameMap;
int Tools::count = 0;

class Register
{
public:
	Register(const char *className, NewInstancePt np)
	{
		Tools::RegisterClass(className, np);
	}
};



