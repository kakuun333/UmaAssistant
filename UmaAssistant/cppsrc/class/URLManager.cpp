#include "../stdafx.h"

URLManager* URLManager::_instance = nullptr;


size_t URLManager::_WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
	size_t total_size = size * nmemb;
	output->append(static_cast<char*>(contents), total_size);
	return total_size;
}


std::string URLManager::GetResponseByUrl(std::string url)
{
    std::string response;

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT); // 初始化 libcurl

    curl = curl_easy_init(); // 創建一個 CURL 句柄

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // 設置 url，並且 url 必須為 const char*

        // 設置回調函數
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &URLManager::_WriteCallback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);


        res = curl_easy_perform(curl); // 請求 HTTP

        // 檢查請求結果
        if (res == CURLE_OK)
        {
            std::cout << "res == CURLE_OK" << std::endl;
        }
        else
        {
            std::cout << "curl_easy_perform() failed: \n" << curl_easy_strerror(res) << std::endl;
        }


        curl_easy_cleanup(curl); // 清理 CURL 句柄
    }

    curl_global_cleanup(); // 清理 libcurl


    return response;
}