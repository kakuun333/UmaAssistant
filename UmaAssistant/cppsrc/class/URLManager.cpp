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

    curl_global_init(CURL_GLOBAL_DEFAULT); // ��l�� libcurl

    curl = curl_easy_init(); // �Ыؤ@�� CURL �y�`

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // �]�m url�A�åB url ������ const char*

        // �]�m�^�ը��
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &URLManager::_WriteCallback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);


        res = curl_easy_perform(curl); // �ШD HTTP

        // �ˬd�ШD���G
        if (res == CURLE_OK)
        {
            std::cout << "res == CURLE_OK" << std::endl;
        }
        else
        {
            std::cout << "curl_easy_perform() failed: \n" << curl_easy_strerror(res) << std::endl;
        }


        curl_easy_cleanup(curl); // �M�z CURL �y�`
    }

    curl_global_cleanup(); // �M�z libcurl


    return response;
}