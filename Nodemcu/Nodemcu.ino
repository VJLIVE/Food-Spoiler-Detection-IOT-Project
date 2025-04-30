#define BLYNK_TEMPLATE_ID "TMPL3Wd7wVHXc"
#define BLYNK_TEMPLATE_NAME "FoodSpoiler"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

String sdata; 
char auth[] = "jY15iMAEeiFPjpfUpH5cCp2eKIhKzijR";

// Your WIFI credentials.
// Set password to "" for open networks.
char ssid[] = "Rkvj";
char pass[] = "Speaker1";

BlynkTimer timer;

String  myString; // complete message from Arduino, which consists of sensors data
char rdata; // received characters

void myTimerEvent()
{
  Blynk.virtualWrite(V1, millis() / 1000);
  
}
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, sensorvalue1); 

}

void loop()
{
   if (Serial.available() == 0) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

   }
   
  if (Serial.available() > 0) 
  {
    rdata = Serial.read(); 
    myString = myString + rdata; 
  
  }

}

void sensorvalue1()
{
sdata = myString ;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V12, sdata);
   myString = "";
}
