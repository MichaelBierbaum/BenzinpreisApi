#include "TankerkoenigWrapper.h"
const char* ID_Gaukoenigshofen_ZG = "2599dfbd-54c1-473d-a0df-a1538ba120b6";
const char* ID_Giebelstadt_Herm = "2de4b5a8-b37e-4c39-9de9-e0564a432721";
const char* ID_Giebelstadt_Total = "8de34af7-aa39-48de-981c-442d2b4cdf9a";
const char* ID_Marktbreit_Aral = "bfe87e5d-03ff-4af8-99b1-ab4dc996b2a3";
const char* ID_Marktsteft_HEM = "c94c910f-2766-4ea6-9d0c-6213a77860be";
const char* ID_Ochsenfurt_ECenter = "932a8c52-ef25-40b8-8d7a-ad323bb78e0d";
const char* ID_Ochsenfurt_OMV = "d1a7208a-6a0f-4a98-9eb1-2a10374f70f9";
const char* ID_Ochsenfurt_Agip = "bfa946e7-e48a-47e6-8b34-187d684fa9e8";
const char* ID_Ochsenfurt_Wengel = "a3c6f7ff-8bff-449a-a2b0-d13022b8f1e4";
const char* ID_Reichenberg_Wengel = "3261710a-e951-4494-9cc1-2bd717a273c2";
GasStationInfo RaiBa(
            /*id*/"2599dfbd-54c1-473d-a0df-a1538ba120b6",
            /*name*/"Raiffeisen Lagerhaus GmbH Gaukönigshofen",
            /*brand*/"ZG Raiffeisen Energie",
            /*street*/"Raiffeisenplatz",
            /*place*/"Gaukönigshofen",
            /*lat*/49.634,
            /*lng*/10.0065,
            /*houseNumber*/"3",
            /*postCode*/97253);
GasStationInfo ECenter(
			/*id*/"932a8c52-ef25-40b8-8d7a-ad323bb78e0d",
			/*name*/"Tankstelle am E-Center",
			/*brand*/"E Center",
			/*street*/"Dr.-Martin-Luther-Str.",
			/*place*/"Ochsenfurt",
			/*lat*/49.662109,
			/*lng*/10.066862,
			/*houseNumber*/"6",
			/*postCode*/97199);

#include <stdio.h>//fuer snprintf
#include <string.h>//fuer strcmp

char buff[200];

#include <HTTPClient.h>
HTTPClient http;

#include <ArduinoJson.h>

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

//for Parsing program see https://arduinojson.org/v5/assistant/
bool TankerkoenigWrapper::ParseJsonForDetailrequest(string &jsonData)
{
    const size_t capacity = 2*JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(17) + 450;
    DynamicJsonBuffer jsonBuffer(capacity);

    const char* json = jsonData.c_str();

    JsonObject& root = jsonBuffer.parseObject(json);

    bool ok = root["ok"]; // true
    if(ok == false)
        return false;

    const char* license = root["license"]; // "CC BY 4.0 -  https://creativecommons.tankerkoenig.de"
    const char* data = root["data"]; // "MTS-K"
    const char* status = root["status"]; // "ok"

    JsonObject& station = root["station"];
    const char* station_id = station["id"]; // "2599dfbd-54c1-473d-a0df-a1538ba120b6"
    const char* station_name = station["name"]; // "Raiffeisen Lagerhaus GmbH Gaukönigshofen"
    const char* station_brand = station["brand"]; // "ZG Raiffeisen Energie"
    const char* station_street = station["street"]; // "Raiffeisenplatz"
    const char* station_houseNumber = station["houseNumber"]; // "3"
    long station_postCode = station["postCode"]; // 97253
    const char* station_place = station["place"]; // "Gaukönigshofen"

    bool station_wholeDay = station["wholeDay"]; // true
    bool station_isOpen = station["isOpen"]; // true
    float station_e5 = station["e5"]; // 1.779
    float station_e10 = station["e10"]; // 1.729
    float station_diesel = station["diesel"]; // 1.859
    float station_lat = station["lat"]; // 49.634
    float station_lng = station["lng"]; // 10.0065

    return true;
}

bool TankerkoenigWrapper::UpdatePrices(string &jsonData)
{
    return ParseJsonForDetailrequest(jsonData);
}

string TankerkoenigWrapper::CreateUrlForPrices()
{
    //example:
    //return https://creativecommons.tankerkoenig.de/json/prices.php?ids=4429a7d9-fb2d-4c29-8cfe-2ca90323f9f8,446bdcf5-9f75-47fc-9cfa-2c3d6fda1c3b,60c0eefa-d2a8-4f5c-82cc-b5244ecae955,44444444-4444-4444-4444-444444444444&apikey=00000000-0000-0000-0000-000000000002;
    snprintf(buff, sizeof(buff),
        "https://creativecommons.tankerkoenig.de/json/prices.php?ids=%s,%s,%s&apikey=%s",
        ID_Gaukoenigshofen_ZG,
        ID_Ochsenfurt_ECenter,
        ID_Giebelstadt_Herm,
        key.c_str());
    return buff;
}

TankerkoenigWrapper::TankerkoenigWrapper(const char *tankerkoenig_api_key)
{
    gasStation = RaiBa;
    key = tankerkoenig_api_key;
};

TankerkoenigWrapper::~TankerkoenigWrapper()
{
}

//Umkreissuche
string TankerkoenigWrapper::CreateUrlForRadiusSearch(Spritsorte type, double radius)
{
    //example:
    //return "https://creativecommons.tankerkoenig.de/json/list.php?lat=49.6339&lng=10.00658&rad=2.0&sort=dist&type=all&apikey=00000000-0000-0000-0000-000000000002";
    
    snprintf(buff, sizeof(buff), 
        "https://creativecommons.tankerkoenig.de/json/list.php?lat=%f&lng=%f&rad=%f&sort=%s&type=%s&apikey=%s",
        gasStation.GetLat(),
        gasStation.GetLng(),
        radius,
        "dist", //price, dist
        Sorten[type].c_str(),
        key.c_str());
    return buff;
}

//request for one special gas station
string TankerkoenigWrapper::CreateUrlForDetailrequest(const char *gasStationID)
{
    const char* id;
    if(strcmp(gasStationID, "") != 0)
        id = gasStationID;
    else if(gasStation.GetId().empty() == false)
        id = gasStation.GetId().c_str();
    else
        id = ID_Gaukoenigshofen_ZG;

    //example:
    //return "https://creativecommons.tankerkoenig.de/json/detail.php?id=24a381e3-0d72-416d-bfd8-b2f65f6e5802&apikey=00000000-0000-0000-0000-000000000002";
    snprintf(buff, sizeof(buff),
        "https://creativecommons.tankerkoenig.de/json/detail.php?id=%s&apikey=%s",
        id,
        key.c_str());
    return buff;
}
