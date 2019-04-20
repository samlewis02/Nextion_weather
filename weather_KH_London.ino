//
// Get local weather from openweathermap
//
// Display time and weather from two cities,
// using a touch on the place to change cities
//
// Tested 20/2/19
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Thread.h>
#include <ThreadController.h>
#include <WiFiUdp.h>
#include "TimeLib.h"
#include "Nextion.h"
#include <ArduinoJson.h>
#include "getNtpTime.h"
#include "sendToNextion.h"
#include "getWeather.h"
#include "parseJson.h"
#include "sendStatus.h"
#include "DebugMacros.h"

void  t0PopCallback(void *ptr);
NexText  t0 = NexText(0, 8, " t0");
NexTouch *nex_listen_list[] =
{
  &t0,
  NULL
};

const char* ssid = "P874-21-2-3F"; //  network SSID
const char* pass  = "077190028";     // network password
WiFiUDP Udp;
const unsigned int localPort = 8888;  // local port to listen for UDP packets
static char outtime[9];

float ltemp;
float lhum;
float lpres;
String descString;
String lplace;
int iconn;
String city1 = "Kaohsiung,TW";
String city2 = "London,GB";
String myPlace;
ThreadController ThreadControl = ThreadController();
Thread* weatherThread = new Thread();
int timeZone = 1;     // GB time. Use 8 for Kaohsiung
IPAddress ip(192, 168, 1, 136);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void  t0PopCallback(void *ptr)
{
  DPRINTLN("Place change");
  if (myPlace == city1)
  {
    myPlace = city2;
    timeZone = 1;
    sendStatus("Place change: " + String(city2));
  }
  else
  {
    myPlace = city1;
    timeZone = 8;
    sendStatus("Place change: " + String(city1));
  }
  parse_json(getWeather());
  setTime(getNtpTime());
  sendToNextion();
}

void handleWeather (void)
{
  DPRINT("Time: "); DPRINTLN(outtime);
  DPRINTLN("Update weather");
  parse_json(getWeather());
}
/**********************************SETUP***************************/
void setup() {
  //Serial.begin(9600);
  //nexSerial.begin(9600);
  nexInit();
  t0.attachPop( t0PopCallback);

  //WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);
  WiFi.mode(WIFI_STA);
  int cnt = 1;
  while (WiFi.status() != WL_CONNECTED ) {
    yield();
    delay(500);
    DPRINT(".");
    sendStatus("Connecting..." + String(cnt++));
  }
  DPRINT("IP address = "); DPRINTLN(WiFi.localIP());
  sendStatus("Connected. IP = " + (WiFi.localIP().toString()));
  Udp.begin(localPort); // for NTP
  setSyncProvider(getNtpTime);
  setSyncInterval(1000);
  weatherThread->onRun(handleWeather);    // temperature and humidity
  weatherThread->setInterval(5 * 60 * 1000);  // 5 minutes
  ThreadControl.add(weatherThread);
  myPlace = city2;
  parse_json(getWeather());
  delay(1000);
  sendToNextion();
}

time_t prevDisplay = 0; // when the digital clock was displayed
/************************************LOOP******************************/
void loop() {
  ThreadControl.run();
  nexLoop(nex_listen_list);
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      sendToNextion();
    }
  }
}
