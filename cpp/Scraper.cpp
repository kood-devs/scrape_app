#include "Proc.h"
#include "Scraper.h"

char *getNewsTitle(char *URL, char *KEYWORD)
{
    Proc objMain(URL, KEYWORD);
    objMain.execMain();
    return objMain.getTitle();
}