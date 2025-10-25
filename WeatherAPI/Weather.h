#pragma once
#include <iostream>
#include "httplib.h"
#include "json.hpp"

using namespace std;

class Weather
{
    const string api_key;
    const string locationKey;
    string path;

    string wText;
    bool isRain;
    double temp;
    string uom;

    httplib::Result res;

    void buildPath();
    void weatherParse();

public:
    Weather(const string& api, const string& location);
    void fetch();
    void printData() const;
};
