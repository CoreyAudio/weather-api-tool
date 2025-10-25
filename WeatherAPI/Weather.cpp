#include "Weather.h"

using json = nlohmann::json;

Weather::Weather(const string& api, const string& location)
    : api_key(api), locationKey(location), isRain(false), temp(0.0)
{
}

void Weather::buildPath()
{
    path = "/currentconditions/v1/" + locationKey + "?apikey=" + api_key;
    httplib::Client url("dataservice.accuweather.com");
    res = url.Get(path.c_str());
}

void Weather::weatherParse()
{
    if (res && res->status == 200)
    {
        try
        {
            const auto j = json::parse(res->body, nullptr, false);
            if (j.is_discarded() || j.empty())
            {
                cerr << "Invalid or empty JSON response.\n";
                return;
            }

            const auto& current = j.front();

            wText = current.value("WeatherText", "Unknown");
            isRain = current.value("HasPrecipitation", false);

            const auto& tempObj = current["Temperature"]["Imperial"];
            temp = tempObj.value("Value", 0.0);
            uom = tempObj.value("Unit", " ");
        }
        catch (const json::exception& e)
        {
            cerr << "JSON parse error: " << e.what() << '\n';
        }
    }
    else
    {
        cerr << "Request failed or returned invalid status.\n";
    }
}

void Weather::fetch()
{
    buildPath();
    weatherParse();
}

void Weather::printData() const
{
    cout << "\n----Current Weather----\n"
        << "Forecast: " << wText << '\n'
        << "Is it raining? " << (isRain ? "Yes" : "No") << '\n'
        << "Temperature: " << temp << ' ' << uom << '\n';
}
