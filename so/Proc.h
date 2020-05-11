#ifndef __PROC_H__
#define __PROC_H__

#include <string>
#include <vector>

#include <curl/curl.h>

class Proc
{
private:
    CURL *curl;
    CURLcode res;
    std::string chunk, strIter;
    const char *URL, *KEYWORD;
    std::vector<std::string> title;

public:
    Proc(const char *URL_, const char *KEYWORD_);
    ~Proc();
    char *getTitle();
    void execMain();
};

#endif