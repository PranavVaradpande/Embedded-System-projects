// CONNECTIONS:
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND
// introducing all libraries
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial myserial(0,1);
ThreeWire myWire(8,7,9); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
//rtc date time variables
int a,b,c,d,e,f; 
//slot hour and seconds variables
int h1,h2,h3,h4; int m1,m2,m3,m4; 
//default time
int sh1=10,sm1=0,s1=0;int sh2=13,sm2=00,s2=00; int sh3=13,sm3=50,s3=00; int sh4=17,sm4=20,s4=00; 
//string to store bluetooth data
String z;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

byte customChar[8] = {
  B00011,
  B00110,
  B01001,
  B11000,
  B10100,
  B10000,
  B10000,
  B11100
};
byte customChar1[8] = {
 B10000,
  B10100,
  B11000,
  B10001,
  B10000,
  B01001,
  B00110,
  B00011
};

byte customChar2[8] = {
  B00100,
  B01010,
  B10001,
  B00000,
  B00000,
  B00100,
  B00100,
  B11111
  };
byte customChar3[8] = {
  B11111,
  B00100,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100};
byte customChar4[] = {
  B00001,
  B00101,
  B00011,
  B10001,
  B00001,
  B10010,
  B01100,
  B11000
};

byte customChar5[] = {
 B11000,
  B01100,
  B10010,
  B00011,
  B00101,
  B00001,
  B00001,
  B00111
};


void setup() {
  myserial.begin(9600);
  lcd.begin(16,4);
  lcd.setCursor(0,0);
  lcd.createChar(1,customChar);
  lcd.createChar(2,customChar1);
  lcd.createChar(3,customChar2);
  lcd.createChar(4,customChar3);
  lcd.createChar(5,customChar4);
  lcd.createChar(6,customChar5);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,OUTPUT);
  lcd.setCursor(0,4);
  lcd.print("Clock System");
  delay(1000);
  lcd.setCursor(1,4);
  lcd.print("Starting....");
  delay(1000);
  lcd.clear();
   Serial.begin(57600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}
void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
    lcd.setCursor(1,4);
    lcd.print(dt.Day());
    lcd.setCursor(1,6);
    lcd.print("/");
    lcd.setCursor(1,7);
    lcd.print(dt.Month());
    lcd.setCursor(1,9);
    lcd.print("/");
    lcd.setCursor(1,10);
    lcd.print(dt.Year());
    
    lcd.setCursor(2,4);
    lcd.print(dt.Hour());
    lcd.setCursor(1,6);
    lcd.print(":");
    lcd.setCursor(1,7);
    lcd.print(dt.Minute());
    lcd.setCursor(1,9);
    lcd.print(":");
    lcd.setCursor(1,10);
    lcd.print(dt.Second());
 int count=0;
 int slot=map(analogRead(A0),0,1023,1,5);
 int Hr=map(analogRead(A1),0,1023,0,24);
 int Min=map(analogRead(A2),0,1023,0,59);
 int Home=digitalRead(2);
 int save=digitalRead(3);
 int reset=digitalRead(4);
 if(Home==0){ count=count+1; 
  while(Home!=0){
  lcd.setCursor(4,3);
  lcd.print("Time Slot");
   
    switch(slot){
    case 1: lcd.setCursor(5,3);
            lcd.print("Time slot 1");h1=Hr, m1=Min;
           break;
    case 2: lcd.setCursor(5,3);
            lcd.print("Time slot 2");h2=Hr ,m2=Min;
           break;
    case 3: lcd.setCursor(5,3);
            lcd.print("Time slot 3");h3=Hr, m3=Min;
           break;
    case 4: lcd.setCursor(5,3);
            lcd.print("Time slot 4");h4=Hr ,m4=Min;
           break;
    case 5: lcd.setCursor(5,3);
            lcd.print("Default");sh1=10,sm1=0,s1=0,sh2=13,sm2=00,s2=00,sh3=13,sm3=50,s3=00,sh4=17,sm4=20,s4=00; 
           break;
      }
 if(slot==1||slot==2||slot==3||slot==4){
  
    if(count==1){
            lcd.clear();
            lcd.setCursor(5,3);
            lcd.print(Hr);
            lcd.setCursor(5,6);
            lcd.print(":");
            lcd.setCursor(5,7);
            lcd.print(Min);
             
          }
      }
    if(count==2){
       lcd.clear();
       lcd.setCursor(4,3);
       lcd.print("Saving....");
       delay(500);
       lcd.clear();
       lcd.setCursor(4,3);
       lcd.print("Time slot saved");
       delay(500);
       lcd.clear();
        }
    } 
  }

if((h1==dt.Hour()&&m1==dt.Minute()||h2==dt.Hour()&&m2==dt.Minute()||h3==dt.Hour()&&m3==dt.Minute()||h4==dt.Hour()&&m4==dt.Minute())&&dt.Second()==0){
    digitalWrite(5,HIGH); delay(4000);digitalWrite(5,LOW);
  }
else if(sh1==dt.Hour()&&sm1==dt.Minute()&&s1==dt.Second()||sh2==dt.Hour()&&sm2==dt.Minute()&&s2==dt.Second()||sh3==dt.Hour()&&sm3==dt.Minute()&&s3==dt.Second()||sh4==dt.Hour()&&sm4==dt.Minute()&&s4==dt.Second()){
     digitalWrite(5,HIGH); delay(4000);digitalWrite(5,LOW);
  }
}
#define countof(a) (sizeof(a) / sizeof(a[0]))

void loop() { lcd.setCursor(1,0);
lcd.write(1);
lcd.setCursor(1,1);
lcd.write(2);
lcd.setCursor(2,1);
lcd.write(3);
lcd.setCursor(2,0);
lcd.write(4);
lcd.setCursor(3,1);
lcd.write(5);
lcd.setCursor(3,0);
lcd.write(6);
 RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(10000); // ten seconds
    

}
