#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;
char auth[] = "AUTH_TOKEN";
char ssid[] = "SSID";
char pass[] = "PASS";
int ledPin = LED_BUILTIN;
int servoPin = D8;

void setup()
{
  Serial.println("Setting baud rate");
  Serial.begin(9600);
  
  Serial.println("Connecting blynk");
  Blynk.begin(auth, ssid, pass);
  
  testServo();  
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(D3, LOW);
}  

void loop()
{
  Blynk.run();
}

void blinkLED() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
}

BLYNK_WRITE(V1)
{
  blinkLED();
  String paramValue = param.asString();
  String message = "Received = " + paramValue;
  Serial.println(message);
  if(paramValue == "LOCK" || paramValue == "1") {
      Serial.println("LOCK requested");
      lock();
      Blynk.virtualWrite(V1, 1);
  } else if(paramValue == "UNLOCK" || paramValue == "0") {
      Serial.println("UNLOCK requested");
      unlock();
      Blynk.virtualWrite(V1, 0);
  } else {
      Serial.println("Not sure what you want to do.");
  }
}

void testServo() {
  Serial.println();
  Serial.println("Test Servo.");
  lock();
  unlock();
  lock();
  Serial.println("Test complete.");
  Serial.println();
}

bool attachServo() {
  servo.attach(servoPin);
  delay(500);
  bool flag = servo.attached();
  if (flag) {
    digitalWrite(ledPin, LOW);
    Serial.print("Servo attached at ");
    Serial.print(servoPin);
    Serial.print(" pin");
    Serial.println();
  } else {
    Serial.print("Failed to attach servo");
    Serial.print(servoPin);
    Serial.print(" pin");
  }
  return flag;
}

void detachServo() {
  servo.detach();
  delay(10);
  if (!servo.attached()) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Servo detached.");
  } else {
    Serial.println("Failed to detach servo.");
  }
  Serial.println();
}

void lock() {
  if (attachServo()) {
    Serial.println("Locking now");
    servo.write(0);
    delay(2500);
    if(servo.read() == 0) {
      Serial.println("Locked.");
    }
    detachServo();
  }
}

void unlock() {
  if (attachServo()) {
    Serial.println("Unlocking now");
    servo.write(120);
    delay(2500);
    if(servo.read() == 120) {
      Serial.println("Unlocked.");
    }
    detachServo();
  }
}
