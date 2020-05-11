#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <iostream>
#include <list>

// 特定の文字列を含んでいるか判定する関数
template <class T, class U>
bool contain(const std::basic_string<T> &s, const U &v)
{
    return s.find(v) != std::basic_string<T>::npos;
}

// split関数
std::list<std::string> split(std::string str, std::string delim)
{
    std::list<std::string> result;
    int cutAt;
    while ((cutAt = str.find_first_of(delim)) != str.npos)
    {
        if (cutAt > 0)
        {
            result.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
    }
    if (str.length() > 0)
    {
        result.push_back(str);
    }
    return result;
}

// CURL コールバック関数
size_t callBackFunc(char *ptr, size_t size, size_t nmemb, std::string *stream)
{
    int realsize = size * nmemb;
    stream->append(ptr, realsize);
    return realsize;
}

// HTMLタグを除外
void removeHTMLTag(std::string &str)
{
    int start;
    bool tag = true;

    while (tag)
    {
        start = 0;
        tag = false;

        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '<')
            {
                start = i;
                tag = true;
            }
            if (str[i] == '>')
                str.erase(start, (i - start + 1));
        }
    }

    return;
}

#endif