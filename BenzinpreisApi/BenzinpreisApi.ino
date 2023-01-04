#include <U8g2lib.h> //https://github.com/olikraus/u8g2/wiki/u8g2reference
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
u8g2_uint_t offset;

#include <WiFi.h>
#include "credentials.h"
#include "TankerkoenigWrapper.h"

TankerkoenigWrapper tankerkoenig(tankerkoenig_api_key);

const int BUTTON_PIN = 18;
int displayHeight = 0, displayWidth = 0;
volatile bool tasterGedrueckt = false;
void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  delay(10);

  setup_OLED();
  setupTaster();
  startWiFi();

  UpdatePrices();

  delay(1000);
  Serial.println("setup abgeschlossen");
}

void loop(void)
{
  u8g2_prepare();
  if(tasterGedrueckt)
  {
    UpdatePrices();
    tasterGedrueckt = false;
  }
  PrintPrices();
  delay(1000);
}

void u8g2_prepare(void)
{
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.clearBuffer(); // clear the internal memory once
  u8g2.setFontMode(1);
  u8g2.setCursor(0, 0);
}

string scrollingBrand;
GasStationInfo gasStation;
void PrintPrices()
{
  ScrollBrand();

  int maxCharHeight = u8g2.getMaxCharHeight();
  int x = 0, y = 0, line = 0;
  u8g2.setCursor(x, y + line*maxCharHeight);
  u8g2.printf("%s", scrollingBrand.c_str());

  ++line;
  ++line;
  u8g2.setCursor(x, y + line*maxCharHeight);
  u8g2.printf("%6s|%6s %s", "Benzin", "Diesel", "Name");

  for(int i = 0; i < DimGasStations; ++i)
  {
    ++line;
    u8g2.setCursor(x, y + line*maxCharHeight);
    gasStation = tankerkoenig.GetGasStation(i);
    u8g2.printf("% 1.3f|% 1.3f %s", gasStation.e5, gasStation.diesel, gasStation.PrintBrand());
  }

  u8g2.sendBuffer();
}

void ScrollBrand()
{
  gasStation = tankerkoenig.GetGasStation(0);
  if(scrollingBrand.empty() || scrollingBrand.length() < 1)
    scrollingBrand = gasStation.PrintBrand();
  else
    scrollingBrand = scrollingBrand.substr(1);
}

void setup_OLED()
{
  u8g2.begin();
  //u8g2.setFont(u8g2_font_logisoso32_tf);
  u8g2.setFont(u8g2_font_6x10_tf);
  displayHeight = u8g2.getDisplayHeight();
  displayWidth = u8g2.getDisplayWidth();
  Serial.print("displayHeight: "); Serial.println(displayHeight);
  Serial.print("displayWidth : "); Serial.println(displayWidth);
}

void setupTaster()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), OnPushButton, RISING);
}

void OnPushButton()
{
  if (!tasterGedrueckt)
  {
    tasterGedrueckt = true;
    scrollingBrand.clear();

    Serial.println(tankerkoenig.CreateUrlForDetailrequest().c_str());
    Serial.println(tankerkoenig.CreateUrlForRadiusSearch().c_str());
    Serial.println(tankerkoenig.CreateUrlForPrices().c_str());

    return;
  }
}

void UpdatePrices()
{
  string url = tankerkoenig.CreateUrlForPrices();
  string jsonData = tankerkoenig.GetJsonForUrl(url.c_str());
  Serial.println(jsonData.c_str());
  tankerkoenig.ParseJsonForPrices(jsonData);
  tankerkoenig.SortGasStations();
}

void startWiFi()
{
  WiFi.begin(ssid, password);

  u8g2.setCursor(10, 10);
  u8g2.printf("connecting to Wifi");
  u8g2.setCursor(30, 30);
  u8g2.printf("\"%s\"", ssid);
  u8g2.setCursor(30, 30);
  u8g2.sendBuffer();

  int counter = 0;
  //Serial.println("connect WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.print("WiFi connected with IP address: ");
  Serial.println(WiFi.localIP());
}