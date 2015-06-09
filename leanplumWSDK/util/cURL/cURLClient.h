#include <curl.h>
#include <sstream>

class CURLClient
{
private:
	CURL* curl;
	std::stringstream ss;
	long http_code;

public:
	CURLClient()
		: curl(curl_easy_init())
		, http_code(0)
	{

	}

	~CURLClient()
	{
		if (curl) curl_easy_cleanup(curl);
	}

	std::string Get(const std::string& url)
	{
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		ss.str("");
		http_code = 0;
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			printf("curl_easy_perform() failed:%s\n", curl_easy_strerror(res));  
		}
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		return ss.str();
	}

	std::string GetWithRequest(const std::string& url, const std::string& request)
	{
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8");  
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);  
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		ss.str("");
		http_code = 0;
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			printf("curl_easy_perform() failed:%s\n", curl_easy_strerror(res));  
		}
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		return ss.str();
	}

	long GetHttpCode()
	{
		return http_code;
	}

private:
	static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
	{
		return static_cast<CURLClient*>(userp)->Write(buffer, size, nmemb);
	}

	size_t Write(void *buffer, size_t size, size_t nmemb)
	{
		ss.write((const char*)buffer, size*nmemb);
		return size*nmemb;
	}
};