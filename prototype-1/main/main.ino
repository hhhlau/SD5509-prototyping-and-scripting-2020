#include <DHT.h>
#include <DHT_U.h>

//Prototype 1
const int redLedPin = 10; // the red LED is connected to Pin 0 of the Arduino
const int greenLedPin = 9; // the yellow LED is connected to Pin 1 of the Arduino
const int blueLedPin = 8; // the green LED is connected to Pin 2 of the Arduino
const int feelColdBtnPin = 4;
const int feelHotBtnPin =3;
const int dht22DataPin = 2; // The data pin for DHT 22 

#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(dht22DataPin, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


float tempVal = 0.0;
float humidityVal = 0.0;


/*Humans can be comfortable within a wide range of humidities depending 
on the temperature—from 30–70%—but ideally between 50 % and 60 %. Very 
low humidity can create discomfort, respiratory problems, and aggravate 
allergies in some individuals. */

const float refLowHumidityVal = 45.0;
const float refHighHumidityVal = 55.0;


int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    // initialize the input pins
    pinMode(dht22DataPin, INPUT);
    pinMode(feelHotBtnPin, INPUT);
    pinMode(feelColdBtnPin, INPUT);
    //  initialize the output pins
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(blueLedPin, OUTPUT);
    // initialize the DHT 22
    dht.begin();
}

void offAllLeds() {
  digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(blueLedPin, LOW);
}

void loop() {
    
    delay(2000);
    //Read data and store it to variables hum and temp
    humidityVal = dht.readHumidity();
    tempVal= dht.readTemperature();
    offAllLeds();
    if (humidityVal > refHighHumidityVal){
      digitalWrite(redLedPin, HIGH);
    }else if (humidityVal < refLowHumidityVal) {
      digitalWrite(blueLedPin, HIGH);
    } else {
      digitalWrite(greenLedPin, HIGH);
    };
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humidityVal);
    Serial.print(" %, Temp: ");
    Serial.print(tempVal);
    Serial.println(" Celsius");
    delay(10000); //Delay 2 sec.
}
