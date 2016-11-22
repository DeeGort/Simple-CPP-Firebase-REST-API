#pragma once
#include <string>

std::string getJsonValue(std::string jsonData, const char * key)
{
	char *cstr = new char[jsonData.length() + 1];
	strcpy(cstr, jsonData.c_str());
	char * pch = strtok(cstr, "{}, ");
	while (pch != NULL)
	{
		if (!strcmp(pch, key)) {
			pch = strtok(NULL, ", ");
			break;
		}
		pch = strtok(NULL, ", ");
	}

	std::string result = std::string(pch).substr(1, std::string(pch).size() - 2);
	delete [] cstr;

	return result;
}