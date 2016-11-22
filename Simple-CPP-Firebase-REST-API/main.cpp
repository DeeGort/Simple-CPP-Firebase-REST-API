#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <curl/curl.h>
#include "post.h"
#include "get.h"
#include "parser.h"

int main(void)
{
	// Login form
	std::string apikey;
	std::string username;
	std::string password;

	std::cout << "API key: ";
	std::cin >> apikey;

	std::cout << "Username: ";
	std::cin >> username;

	std::cout << "Password: ";
	std::cin >> password;

	// Get user token
	std::stringstream authURL;
	std::stringstream authJSON;

	authURL << "https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key="
			<< apikey;

	authJSON << "{"
		<< "	\"email\": \"" << username << "\","
		<< "	\"password\": \"" << password << "\","
		<< "	\"returnSecureToken\": \"true\""
		<< "}";

	// Post form
	std::string postResponse = post(authURL.str().c_str(), authJSON.str().c_str());

	// Print result
	std::cout << "HTTPS Response:" << std::endl
			  << postResponse << std::endl;

	// Get user token
	std::string token = getJsonValue(postResponse, "\"idToken\":");
	std::cout << "User Token:" << std::endl
			  << token << std::endl;

	// End point url form
	std::string endPointURL;

	std::cout << "End point URL: ";
	std::cin >> endPointURL;

	// Get databese response
	std::stringstream fullURL;
	fullURL << endPointURL
		<< "?auth="
		<< token;

	get(fullURL.str().c_str());

	std::cout << std::endl;
	system("PAUSE");
	return 0;
}