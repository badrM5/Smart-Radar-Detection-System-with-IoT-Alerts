#define BOTtoken "8745020407:AAF8wIohjvDC7SeDDnjm_esB8lDeSABQ5_4"
#define CHAT_ID "7857726338"
#define BLYNK_TEMPLATE_ID "TMPL2-5hJHUFO"
#define BLYNK_TEMPLATE_NAME "radar"
#define BLYNK_AUTH_TOKEN "jexFGeS8y4SbaXaRH1nnb8nsMsq-SB8D"
#define trigPin 12
#define echoPin 13
#include <ESP32Servo.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
// WiFi
char ssid[] = "Orange_Darbox-B724";
char pass[] = "5yJ72n52";
long duration;
int distance ;
bool alertSent = false;
Servo myservo;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int calculateDistance()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  return distance;
}

void setup()
{
  client.setInsecure();
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(14);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
 int i ;
 for (i=15; i<=165; i++)
 {
  myservo.write(i);
  delay(15);
  calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
 }
 for(i=165; i>=15; i--)
 {
  myservo.write(i);
  delay(15);
  calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  
 }
 if(distance <= 15 && !alertSent) {
  bot.sendMessage(CHAT_ID, "⚠️ Objet detecte a moins de 15 cm !", "");
  alertSent = true;
 }
  // Si objet proche

/*if(distance <= 15 && !alertSent) {
  Blynk.virtualWrite(V0, "Objet detecte a moins de 15 cm !");
  Blynk.virtualWrite(V1, 255);   // LED ON
  Blynk.logEvent("objet_proche", "Objet detecte !");
  alertSent = true;
}

if(distance > 20) {
  Blynk.virtualWrite(V0, "Zone securisee");
  Blynk.virtualWrite(V1, 0);     // LED OFF
  alertSent = false; }
  */
 
 
  delay(100); 

}

