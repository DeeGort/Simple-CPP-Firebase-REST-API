#pragma once
#include <curl/curl.h>
#include <string>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string post(const char * url, const char * body)
{
	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	// In windows, this will init the winsock stuff
	curl_global_init(CURL_GLOBAL_ALL);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");

	// get a curl handle
	curl = curl_easy_init();
	if (curl) {
		// First set the URL that is about to receive our POST. This URL can
		// just as well be a https:// URL if that is what should receive the
		// data.
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		// Now specify the POST data
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);

		// Perform the request, res will get the return code
		res = curl_easy_perform(curl);
		// Check for errors
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		// always cleanup
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return readBuffer;
}