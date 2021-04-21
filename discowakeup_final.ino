
#include <Wire.h>
#include "DFRobot_RGBLCD.h"

const int colorR = 255;
const int colorG = 255;
const int colorB = 0;

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;

const int led0 = 5;
const int led1 = 6;
const int led2 = 7;
const int led3 = 8;

const int buzzer = 12;
const int sensor = 13;

int nappi1arvo = 1;
int nappi2arvo = 1;
int nappi3arvo = 1;
int sensorArvo = digitalRead(sensor);

int flag1 = 0;

int s=0;
int h=19;   
int m=35;
int heratysh=19;
int heratysm=35;

DFRobot_RGBLCD lcd(16,2);  

void setup() {
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(sensor, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    
    lcd.init();
    lcd.setRGB(colorR, colorG, colorB);
    lcd.print("      Moi!      ");
    lcd.setCursor(0,1);
    for (int i = 16; i > 0; i--) {
      lcd.print("[");
      delay(100);
      lcd.print("]");
    }
    delay(500);
    lcd.clear();
}

void loop() {
    int nappi1arvo = digitalRead(button1);
    int nappi2arvo = digitalRead(button2);
    int nappi3arvo = digitalRead(button3);
    int sensorArvo = digitalRead(sensor);
    
    if (nappi1arvo == LOW) { //nappia 1 painettu
      asetukset();
    }
    
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("[---");
    aika();
    lcd.print("---]");
    if (heratysh == h && heratysm == m) {
      flag1 = 3;
      herata();
    }
    
}
void asetukset() {
        flag1 = 1;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[1]   ");
        lcd.print("Heratys");
        lcd.setCursor(0, 1);
        lcd.print("2     ");
        lcd.print("Aika");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Aseta heratys");
        
        heratyssaato();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("1     ");
        lcd.print("Heratys");
        lcd.setCursor(0, 1);
        lcd.print("[2]   ");
        lcd.print("Aika");
        delay(1500);
        ajansaato();
  
}


void heratyssaato() {
  while (flag1 == 1) {
    int nappi1arvo = digitalRead(button1);
    int nappi2arvo = digitalRead(button2);
    int nappi3arvo = digitalRead(button3);
    if (heratysh < 10) {
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.print(heratysh);
    } else {
      lcd.setCursor(0, 1);
      lcd.print(heratysh);
    }
    lcd.setCursor(2, 1);
    lcd.print(":");
    if (heratysm < 10) {
      lcd.setCursor(3, 1);
      lcd.print("0");
      lcd.print(heratysm);
    } else {
      lcd.setCursor(3, 1);
      lcd.print(heratysm);
    }
    if (nappi2arvo == LOW) { 
      heratysh += 1;
      if (heratysh > 23) {heratysh = 0;}
      }
    if (nappi3arvo == LOW) { 
      heratysm += 1;
      if (heratysm > 60) {heratysh ++; heratysm = 0;}
      }
    if (nappi1arvo == LOW) { 
      flag1 = 2; 
      lcd.clear();
      delay(500); 
      }
    delay(100);
   }
}

void ajansaato() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aseta aika");
  while (flag1 == 2) {
    int nappi1arvo = digitalRead(button1);
    int nappi2arvo = digitalRead(button2);
    int nappi3arvo = digitalRead(button3);
    if (h < 10) {
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.print(h);
    } else {
      lcd.setCursor(0, 1);
      lcd.print(h);
    }
    lcd.setCursor(2, 1);
    lcd.print(":");
    if (m < 10) {
      lcd.setCursor(3, 1);
      lcd.print("0");
      lcd.print(m);
    } else {
      lcd.setCursor(3, 1);
      lcd.print(m);
    }
    if (nappi2arvo == LOW) { 
      h += 1;
      if (h > 23) {h = 0;}
      }
    if (nappi3arvo == LOW) { 
      m += 1;
      if (m > 60) {h ++; m = 0;}
      }
    if (nappi1arvo == LOW) { 
      s = 0;
      flag1 = 0; 
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Tallennetaan");
      lcd.setCursor(0, 1);
      lcd.print("asetukset");
      for (int i = 3; i > 0; i--) {
        lcd.print(".");
        delay(500);
      }
      delay(1000);
      lcd.clear();
      }
    delay(100);
  }
}

void herata() {
  while (flag1 == 3) {
    int nappi1arvo = digitalRead(button1);
    int sensorArvo = digitalRead(sensor);
    lcd.setRGB(255, 0, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("----HERATYS!----");
    
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    buzz(2500, 50);
    buzz(2000, 50);
    buzz(1500, 50);
    buzz(1000, 50);
    lcd.setRGB(0, 255, 255);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("----HERATYS!----");
    digitalWrite(led0, LOW  );
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    buzz(500, 50);
    buzz(1000, 50);
    buzz(1500, 50);
    buzz(2000, 50);
    if (sensorArvo == 1) {
      digitalWrite(LED_BUILTIN, HIGH);
      flag1 = 0; 
      lcd.setRGB(255, 255, 0);
      lcd.clear(); 
      heratysh = 0;
      heratysm = 0;
      lcd.setCursor(0, 0);
      lcd.print("Torkku aktivoitu");
      heratysm = heratysm + 5;
      delay(1500);
    }
    
    if (nappi1arvo == LOW) { 
      flag1 = 0; 
      lcd.setRGB(255, 255, 0);
      lcd.clear(); 
      heratysh = 0;
      heratysm = 0;
      lcd.setCursor(0, 0);
      lcd.print("Heratys nollattu");
      delay(1500);
      }
  }
}

void aika() {
  s +=1;
  if(s>=60){ s=s-60; m +=1;}
  if(m==60){ m=0; h +=1;}
  if(h==24){h=1;}
  
  lcd.print(int(h/10));
  lcd.print(h%10);
  lcd.print(":"); 
  lcd.print(int(m/10));
  lcd.print(m%10);
  lcd.print(":");
  lcd.print(int(s/10));
  lcd.print(s%10);
}

void buzz(long frequency, long length) {
  long delayValue = 1000000/frequency/2; 

  long numCycles = frequency * length/ 1000; 

 for (long i=0; i < numCycles; i++){
    digitalWrite(buzzer,HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(buzzer,LOW); 
    delayMicroseconds(delayValue); 
  }
}
