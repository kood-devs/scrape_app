#include <cstring>
#include <fstream>
#include <iostream>
#include <list>

#include <curl/curl.h>

#include "Utility.h"
#include "Proc.h"

using namespace std;

Proc::Proc(const char *URL_, const char *KEYWORD_)
    : URL(URL_), KEYWORD(KEYWORD_)
{
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (string *)&chunk);
}

Proc::~Proc()
{
    curl_easy_cleanup(curl);
}

char *Proc::getTitle()
{
    string str;
    for (string s : title)
        str += s;

    char *cstr = new char[str.size() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

void Proc::execMain()
{
    res = curl_easy_perform(curl);
    if (res == CURLE_OK)
    {
        list<string> strList = split(chunk, "\n");
        list<string>::iterator iter = strList.begin();

        while (iter != strList.end())
        {
            strIter = *iter;
            if (contain(strIter, KEYWORD))
            {
                // removeHTMLTag(strIter);  // HTMLを除去したい場合
                title.push_back(strIter);
            }
            ++iter;
        }
    }
    return;
}
