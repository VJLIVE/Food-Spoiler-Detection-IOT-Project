#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial nodemcu(8, 9);

#define DHTPIN 13        // DHT11 data pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int pinRedLed = 12;
int pinGreenLed = 11;
int pinSensor = A5;
int THRESHOLD = 250;
int buzzer = 10;

int rdata = 0;
String mystring;

void setup()
{
  Serial.begin(9600);
  nodemcu.begin(9600);
  dht.begin();

  pinMode(buzzer, OUTPUT);
  pinMode(pinRedLed, OUTPUT);
  pinMode(pinGreenLed, OUTPUT);
  pinMode(pinSensor, INPUT);
}

void loop()
{
  rdata = analogRead(pinSensor);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (rdata >= THRESHOLD) {
    digitalWrite(pinRedLed, HIGH);
    digitalWrite(pinGreenLed, LOW);
    digitalWrite(buzzer, HIGH);
    delay(50);
  } else {
    digitalWrite(pinRedLed, LOW);
    digitalWrite(pinGreenLed, HIGH);
    digitalWrite(buzzer, LOW);
  }

  if (isnan(temp) || isnan(hum)) {
    mystring = "Error reading DHT11";
  } else if (rdata < THRESHOLD) {
    mystring = "Methane: " + String(rdata) +
               ", Temp: " + String(temp) + "C" +
               ", Humidity: " + String(hum) + "%";
  } else {
    mystring = "Food Spoiled!!!!\nMethane: " + String(rdata) + "Temp: " + String(temp) + "C" + 
               ", Humidity: " + String(hum) + "%";
  }

  nodemcu.println(mystring);
  Serial.println(mystring);

  mystring = "";
  delay(1000);
}
