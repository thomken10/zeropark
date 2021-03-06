#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define triggerPin D8
#define echoPin D7
#define ledRed D1
#define ledGreen D2

// generate authentiction from blynk and check your email
char auth[] = "xxxxxxx";

// enter your wifi ssid and password
char ssid[] = "xxxxxxx";
char pass[] = "xxxxxxx";

BlynkTimer timer;

void setup() {
  //begin the ultrasonic sensor  
  Serial.begin (9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //begin the led green and led red
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  //begin blynk setup
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);   
  
}

void loop() {
  Blynk.run();
  timer.run();

}
void sendSensor(){
  long duration, distance;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  

  if (distance < 20){
    digitalWrite(ledRed,HIGH);
    digitalWrite(ledGreen,LOW);
    Serial.println("AVAILABLE");
    //led for blynk
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 255);
    }
  else{
    digitalWrite(ledRed,LOW);
    digitalWrite(ledGreen,HIGH);
    Serial.println("UNAVAILABLE");
    //led for blynk
    Blynk.virtualWrite(V1, 255);
    Blynk.virtualWrite(V2, 0);  
  }

  Serial.print(distance);
  Serial.println(" cm");
  Blynk.virtualWrite(V0, distance);
  delay(100); }
