//LED PINS : ARDUINO PINS
// 1:GND - 2:5V - 3:9 - 4:7 - 5:GND - 6:6 - 11:5 - 12:4 - 13:3 - 14:2 - 15:220ohm:5V - 16:GND
//HC-12 Module : ARDUINO PINS
// VCC:3.3V - GND:GND -  RX:11 - TX:10
//JoyStick : ARDUINO PINS

#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin


int Contrast = 50;

int X_pos;
int Y_pos;
int x_key = A0;                                               
int y_key = A1;                                               
int x_pos;
int y_pos;
int button = 8;
int mode = 0;

void setup ( ) {
Serial.begin (9600) ;
HC12.begin(9600);               // Serial port to HC12

lcd.begin(16,2);
analogWrite(9 , Contrast);

pinMode (button, INPUT);
pinMode (x_key, INPUT) ;                     
pinMode (y_key, INPUT) ;    
digitalWrite(button, HIGH);

lcd.setCursor(0,0);
lcd.print("Mode: FB");          
}

void loop ( ) {
  
X_pos = analogRead(x_key) ;  
Y_pos = analogRead(y_key) ;  

x_pos = map(X_pos, 0, 1024 , 0 , 17);
y_pos = map(Y_pos, 0, 1024 , 0 , 17);

int switchValue = digitalRead(button);

if (switchValue == 0)
{
  mode += 1;
//  HC12.println("m " + String(mode));
  if (mode%2 == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("Mode: FB");
  }
  else if (mode%2 == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Mode: RL");
  }
  delay(200);
}
HC12.println("x" + String(x_pos) + "ey" + String(y_pos) + "em" + String(mode) +"e");
Serial.println("x" + String(x_pos) + "ey" + String(y_pos) + "em" + String(mode) +"e");
 delay(100);




 


}
