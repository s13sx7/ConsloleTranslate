#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <sstream>

using json=nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

void QueryMaker(std::string &query){
	std::stringstream ss{query};
	std::string clearQuery, word;
	while(ss >> word){
		clearQuery+=word+"%20";
	}
	query=clearQuery;
}



std::string MakeUrl(std::string &str){
	std::string url = "https://api.mymemory.translated.net/get?q=" + str + "&langpair=en|ru";
	return url;
}


int main(void)
{
    CURL *curl;
    CURLcode resp;
    std::string response;
	std::string query;

    curl = curl_easy_init();

	while(true){
		while(query.empty()){
		std::cout << "Translate:  (QQ for quit)\n";
		getline(std::cin,query);
		}
		if(query=="QQ")
			break;
		QueryMaker(query);
		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, MakeUrl(query).c_str()); 

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			resp = curl_easy_perform(curl);
			if(resp == CURLE_OK) {
			try{
			json jsonParser = json::parse(response);
			std::string translatedText = jsonParser["responseData"]["translatedText"];
			std::cout << translatedText << std::endl;
			}catch (json::exception &e) {std::cout << "error: " << e.what() << std::endl;}
			} else {
				std::cout << curl_easy_strerror(resp) << std::endl;  
			}
    		}
		response="";
		query="";
	}
	
    curl_easy_cleanup(curl);
    return 0;
}
