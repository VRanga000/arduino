/*
 * Borrowed heavily from: HC-SR04 example sketch
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 * by Isaac100
 * Modularized and wifi-enabled by mindgrep
 * 
 */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


void initWifi() {
  WiFi.begin("SNOWMAN2", "xxxx");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

}

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!\n");
}

void handleStop() {
  
}

void startWebServer() {
  server.on("/", handleRoot);
  server.begin();
  
  Serial.println("HTTP server started");
}

const int echoPin = 12; //D1 mini pin D6
const int trigPin = 13; //D1 mini pin D7
const int safeDistance = 15; //safe distance from obstacle in cm
//const int rpiSignalPin = 16; //D1 mini pin D0

const int motor1_trigger = 16; //D0

const int SPEED_OF_SOUND = 0.0343; //speed of sound 

float duration, distance;

int calculateDistance(int duration) {
  return (duration*0.0343)/2;
}

void initSonar() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(rpiSignalPin, OUTPUT);  
}

void startSonar() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = calculateDistance(duration);

  if(distance < safeDistance) {
    Serial.print("WARNING GORNING! Approaching object!!");
    stop_motors();
  }
  
  if(distance > safeDistance+1) {
    Serial.print("Danger averted!");
    start_motors();
  }

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}

void initMotors() {
  pinMode(motor1_trigger, OUTPUT);
  start_motors();  
}

void start_motors() {
  digitalWrite(motor1_trigger, HIGH);
}

void stop_motors() {
  digitalWrite(motor1_trigger, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  
  //initSonar();
  initMotors();
  initWifi();
  startWebServer();
}

void loop() {
 //startSonar();
  server.handleClient();
}
