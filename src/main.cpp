#include <Arduino.h>
#include<WS2812FX.h>

int echoPin = 24;
int trigPin = 22;
long duration;
int distance;
#define LED_COUNT 150
#define LED_PIN 26
#define TIMER_MS 5000

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

unsigned long last_change = 0;
unsigned long now = 0;

int getDistance(){
   // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");
  return distance;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(200);
  ws2812fx.setColor(0x00FF00);
  ws2812fx.setMode(42);
  ws2812fx.start();
  Serial.begin(9600);
}

bool startShow = false;
int effect = 53;

void loop() {
  delay(2000);
  int distance = getDistance();
  if(distance<30){
    startShow = true;
    Serial.println("Distance (cm): ");
    Serial.println(distance);
    Serial.println("Infected by Covid");
  }

  else{
    Serial.println("Not too close yet!");
    delay(200);
  }

  while(startShow){
    now = millis();
    ws2812fx.service();

    if(effect == 53){
      effect = 43;
    }
    else{
      effect = 53;
    }

    if(now - last_change > TIMER_MS) {
      ws2812fx.setMode(effect);
      last_change = now;
    }
  }
  
}