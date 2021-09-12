
//HC-12 Module : ARDUINO PINS
// VCC:3.3V - GND:GND -  RX:11 - TX:10

//HC-12 Receiver Code
#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

int MaxV = 200;

byte incomingByte;
String readBufferx = "";
String readBuffery = "";
String readBufferm = "";

String m = "";
String X_pos;
String Y_pos;

//JoyStick Values
int x_pos;
int y_pos;
int Mode;

//Switch Values
int y_drivem;
int lasty_drivem;
int x_drivem;
int lastx_drivem;

int pwm;

//Motor Test Example
//#ifndef (__AVR_ATmega1280__) || ndef(__AVR_ATmega2560__)
//#error "This library only supports Arduino Mega boards."
//#endif
#include "DualVNH5019MotorShieldMod3.h"
//#include <Encoder.h>

//set up the class dot names for the libraries and
// configure library pins

int INA1 = 30;
int INB1 = 32;
int EN1DIAG1 = 28;
int CS1 = A0;
int INA2 = 24;
int INB2 = 26;
int EN2DIAG2 = 22;
int CS2 = A1;
int INA3 = 31;
int INB3 = 33;
int EN3DIAG3 = 29;
int CS3 = A2;
int INA4 = 25;
int INB4 = 27;
int EN4DIAG4 = 23;
int CS4 = A3;
int PWM1 = 9;
int PWM2 = 5;
int PWM3 = 6;
int PWM4 = 3;

int i;
float f;

DualVNH5019MotorShieldMod3 md(INA1, INB1, EN1DIAG1, CS1, INA2, INB2, EN2DIAG2, CS2, INA3, INB3, EN3DIAG3, CS3, INA4, INB4, EN4DIAG4, CS4, PWM1, PWM2, PWM3, PWM4);


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  HC12.begin(9600);

  Serial.println("Starting 2X Dual VNH5019 Motor Shield - Mod3 LIB");
  //start the motor shields and motor pins
  md.init();
  y_pos = 8;
  x_pos = 8;
}

void loop()
{
     //HC-12 Receiver Code
  
    readBufferx = "";
    readBufferm = "";
    readBuffery = "";
  
    boolean starty = false;
    boolean startm = false;
    boolean startx = false;
  
    while (HC12.available())
    {
      incomingByte = HC12.read();
      delay(5);
  
  
      // Read Y Signal "y#e" ///
      if (starty == true) {
        if (incomingByte != 'e') {
          readBuffery += char(incomingByte);
        }
        else {
          starty = false;
        }
      }
      else if (incomingByte == 'y') {
        starty = true;
      }
      // Read X Signal "x#e" ///
      if (startx == true) {
        if (incomingByte != 'e') {
          readBufferx += char(incomingByte);
        }
        else {
          startx = false;
        }
      }
      else if (incomingByte == 'x') {
        startx = true;
      }
      // Read Mode Signal "m#e" ///
      if (startm == true) {
        if (incomingByte != 'e') {
          readBufferm += char(incomingByte);
        }
        else {
          startm = false;
        }
      }
      else if (incomingByte == 'm') {
        startm = true;
      }
      ////////////////////////////////////Read Variables///////////////////////////////
  
      X_pos = readBufferx; // 0-1024
      Y_pos = readBuffery; // 0-1024
      m = readBufferm; // # goes up by 1 when button is pressed
      x_pos = X_pos.toInt();
      y_pos = Y_pos.toInt();
      Mode = m.toInt();
    }

    Mode = Mode % 2;
Serial.println (Mode);
//Serial.println (Mode);
  
  
    if (Mode == 0)
    {
      int i = -1 * map(y_pos, 8,16,0,MaxV);
 
  md.setM1Speed(i);
  md.setM2Speed(i);
  md.setM3Speed(i);
  md.setM4Speed(i);
      
//      Serial.println(i);
    }
    if (Mode == 1)
    {
      int i = map(x_pos, 8,16,0,MaxV);

  md.setM1Speed(-i);
  md.setM2Speed(-i);
  md.setM3Speed(i);
  md.setM4Speed(i);
    }
  


}
