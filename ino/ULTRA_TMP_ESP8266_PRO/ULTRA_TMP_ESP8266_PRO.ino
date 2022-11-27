#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
#define tempPin A0 // DHT pin

long duration, distance; // Duration used to calculate distance

void setup()
{
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(tempPin, INPUT);
}
 
void loop()
{
/* The following trigPin/echoPin cycle is used to determine the
distance of the nearest object by bouncing soundwaves off of it. */

int reading = analogRead(tempPin);
reading = map(reading,0,1023,0,3300);
float t = (reading - 550) * 0.1;

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
Serial.print("Distance : ");
Serial.print(distance);
Serial.print(" Temperature : ");
Serial.print(t);
Serial.print(" \xC2\xB0");
Serial.println("C");
//Delay 50ms before next reading.
delay(50);
}