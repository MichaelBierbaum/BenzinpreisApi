#include "TankerkoenigWrapper.h"

#include <stdio.h>//fuer snprintf

char buff[200];

#include <HTTPClient.h>
HTTPClient http;

string TankerkoenigWrapper::GetJson()
{
    string jsonData = "E";
    string url = CreateUrlForDetailrequest();
    http.begin(url.c_str());
    int httpCode = http.GET();
    if(httpCode == 200){
        jsonData = http.getString().c_str();
    }
    http.end();

    return jsonData;
}

bool TankerkoenigWrapper::ParseJson(string &jsonData)
{
    if(/*jsonData != OK*/false)
        return false;

    return true;
}

bool TankerkoenigWrapper::UpdatePrices(string &jsonData)
{
    return ParseJson(jsonData);
}

TankerkoenigWrapper::TankerkoenigWrapper(GasStationInfo &gasStation, const char *tankerkoenig_api_key)
{
    this->gasStation = gasStation;
    this->key = tankerkoenig_api_key;
};

TankerkoenigWrapper::~TankerkoenigWrapper()
{
}

//Umkreissuche
string TankerkoenigWrapper::CreateUrlForRadiusSearch(Spritsorte type)
{
    //example:
    //return "https://creativecommons.tankerkoenig.de/json/list.php?lat=49.6339&lng=10.00658&rad=2.0&sort=dist&type=all&apikey=00000000-0000-0000-0000-000000000002";
    snprintf(buff, sizeof(buff), 
        "https://creativecommons.tankerkoenig.de/json/list.php?lat=%f&lng=%f&rad=0.0&sort=%s&type=%s&apikey=%s",
        gasStation.GetLat(),
        gasStation.GetLng(),
        "dist", //price, dist
        Sorten[type],
        key);
    return buff;
}

//request for one special gas station
string TankerkoenigWrapper::CreateUrlForDetailrequest()
{
    string id = gasStation.GetId();

    //example:
    //return "https://creativecommons.tankerkoenig.de/json/detail.php?id=24a381e3-0d72-416d-bfd8-b2f65f6e5802&apikey=00000000-0000-0000-0000-000000000002";
    snprintf(buff, sizeof(buff),
        "https://creativecommons.tankerkoenig.de/json/detail.php?id=%s&apikey=%s",
        id.c_str(),
        key.c_str());
    return buff;
}
