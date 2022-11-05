#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID   "Your_Template_ID"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Your_Auth_Token";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SmS_jiofi";
char pass[] = "sms123458956";

#define dataPin  0
#define latchPin 2
#define clockPin 3

int blynk_data = 0b00000000;
int previous_blynk_data = 0b00000000;

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  if (pinValue == 1)
  {
    blynk_data |= 0b00000001;
  }
  else
  {
    blynk_data &= 0b11111110;
  }
  //Serial.print("New Data - "); Serial.println(blynk_data);
  //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  if (pinValue == 1)
  {
    blynk_data |= 0b00000010;
  }
  else
  {
    blynk_data &= 0b11111101;
  }
  //Serial.print("New Data - "); Serial.println(blynk_data);
  //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
}


BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
  if (pinValue == 1)
  {
    blynk_data |= 0b00000100;
  }
  else
  {
    blynk_data &= 0b11111011;
  }
  //Serial.print("New Data - "); Serial.println(blynk_data);
  //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
}


BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
  if (pinValue == 1)
  {
    blynk_data |= 0b00001000;
  }
  else
  {
    blynk_data &= 0b11110111;
  }
  //Serial.print("New Data - "); Serial.println(blynk_data);
  //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  Serial.println(pinValue);
  switch (pinValue)
  {
    case 0:
      blynk_data &= 0b10001111;
      blynk_data |= 0b00000000;
      //Serial.print("New Data - "); Serial.println(blynk_data);
      //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
      break;
    case 1:
      blynk_data &= 0b10001111;
      blynk_data |= 0b00010000;
      //Serial.print("New Data - "); Serial.println(blynk_data);
      //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);;
      break;
    case 2:
      blynk_data &= 0b10001111;
      blynk_data |= 0b00100000;
      //Serial.print("New Data - "); Serial.println(blynk_data);
      //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
      break;
    case 3:
      blynk_data &= 0b10001111;
      blynk_data |= 0b00110000;
      //Serial.print("New Data - "); Serial.println(blynk_data);
      //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
      break;
    case 4:
      blynk_data &= 0b10001111;
      blynk_data |= 0b01000000;
      //Serial.print("New Data - "); Serial.println(blynk_data);
      //Serial.print("Pre Data - "); Serial.println(previous_blynk_data);
      break;
    default:
      break;
  }
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, previous_blynk_data);
  digitalWrite(latchPin, HIGH);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  blynk_run();
}

void blynk_run() {
  if ((blynk_data ^ previous_blynk_data) != 0)
  {
    previous_blynk_data = blynk_data;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, blynk_data);
    digitalWrite(latchPin, HIGH);
  }
}
