#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
u8g2_uint_t offset;

#include "Pos.h"
Pos *pos;

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "credentials.h"

#include "TankerkoenigWrapper.h"
GasStationInfo RaiBa(
  /*id*/"2599dfbd-54c1-473d-a0df-a1538ba120b6",
  /*name*/"Raiffeisen Lagerhaus GmbH Gaukönigshofen",
  /*brand*/"ZG Raiffeisen Energie",
  /*street*/"Raiffeisenplatz",
  /*place*/"Gaukönigshofen",
  /*lat*/49.634,
  /*lng*/10.0065,
  /*houseNumber*/3,
  /*postCode*/97253
  );
TankerkoenigWrapper tankerkoenig(RaiBa, tankerkoenig_api_key);

const int BUTTON_PIN = 18;
volatile bool tasterGedrueckt = false;

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  delay(10);

  setup_OLED();
  setupTaster();
  startWiFi();
  tankerkoenig.UpdatePrices();
  delay(1000);
  Serial.print("setup abgeschlossen");
}

void loop(void)
{
  u8g2_prepare();

  showLineHeader();

  u8g2.sendBuffer();
  delay(1000);
  tasterGedrueckt = false;
}

void setup_OLED()
{
  u8g2.begin();
  //u8g2.setFont(u8g2_font_logisoso32_tf);
  u8g2.setFont(u8g2_font_6x10_tf);
  int displayHeight = u8g2.getDisplayHeight();
  Serial.print("displayHeight: "); Serial.println(displayHeight);
  pos = new Pos(0, 0, displayHeight);
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
    tankerkoenig.UpdatePrices();
  }
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

void u8g2_prepare(void)
{
  u8g2.setFont(u8g2_font_6x10_tf);
  //u8g2.setFont(u8g2_font_u8glib_4_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.clearBuffer(); // clear the internal memory once
  u8g2.setFontMode(1);
}

void showLineHeader()
{
  u8g2.setCursor(0, 0);

  u8g2.printf("%6s | %6s | %6s", "Time", "e10", "diesel");
}