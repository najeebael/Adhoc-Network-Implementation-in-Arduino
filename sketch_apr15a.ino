#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

const int tmpSensorPin = A0;
const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;
int reading;
float voltage;

void setup()
{
    Serial.begin(9600);    // Debugging only

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    readDistance();
    readTmp();
    
    char msg[50];
    dtostrf(voltage,10 ,2 , msg);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}

void readTmp(){
  reading = analogRead(tmpSensorPin);
  voltage = (reading* 5.0 *100 / 1023.0) - 50 ; // instead of map() and constrain()
}

void readDistance(){
  // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
}
