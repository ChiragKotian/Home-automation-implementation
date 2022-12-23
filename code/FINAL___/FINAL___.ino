#include <AFMotor.h>

   #include <IRremote.h>
#include <DHT.h>
IRsend irsend;
String inputs;
#define relay1 9 
#define DHTPIN 2
DHT dht(DHTPIN, DHT11);
int automate = 0;
int relay = 0;
void setup()
{;
Serial.begin(9600);
pinMode(relay1, OUTPUT); 
dht.begin();
}
void loop()
{
while(Serial.available()) 
{
delay(10); //Delay to make it stable
char c = Serial.read();
if (c == '#'){
break; 
}
inputs += c; 
}

if (inputs.length() >0)
{
Serial.println(inputs);
if(inputs == "1")
{irsend.sendNEC(0xCF8976, 32);
Serial.println("POWER FAN");
delay(250);}

if(inputs == "2")
{if(relay == 1)
{
digitalWrite(relay1, LOW);
relay = 0;}
else if (relay == 0)
{digitalWrite(relay1, HIGH);
relay = 1;}
Serial.println("POWER EXHAUST FAN");}
if(inputs == "3")
{irsend.sendNEC(0xCFD12E, 32);
Serial.println("SLOW SPEED");
delay(250);}
if(inputs == "4")
{irsend.sendNEC(0xCF51AE, 32);
Serial.println("MEDIUM SPEED");
delay(250);}
if(inputs == "5")
{irsend.sendNEC(0xCF11EE, 32);
Serial.println("FASTEST SPEED");
delay(250);}
if(inputs == "6")
{automate = 0;
  while(automate == 0)
{float t = dht.readTemperature();
  if (isnan(t)) {
   Serial.println("read error:");
   
    
  }
    Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");

  if (t<35)
  {digitalWrite(relay1, LOW);
  relay = 0;}
  else
  {digitalWrite(relay1, HIGH);
  relay = 1;}
  inputs="";
  while(Serial.available()) 
{
delay(10);
  char c = Serial.read(); 
if (c == '#'){
break; 
}
inputs += c;
}

if (inputs.length() >0)
{
Serial.println(inputs);
if (inputs=="6")
{automate=1;}
inputs="";}
  
  delay(500);
   }
}


inputs="";
}
}
