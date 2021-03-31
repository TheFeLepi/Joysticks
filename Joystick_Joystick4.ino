// Requires Arduino Joystick Library https://github.com/MHeironimus/ArduinoJoystickLibrary


#include <Joystick.h>
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  6, 0,                  // Button Count, Hat Switch Count
  true, true, false,   // X, Y, noZ Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, true,          // No rudder but throttle (Trimm)
  false, false, false);  // No accelerator, brake, or steering


 
int CenterX;          ///Set MIN and MAX for Axis
int MaxX = 860;
int MinX = 200;

int CenterY;
int MaxY = 730;           
int MinY = 280;

int XA;
int YA;
int Trim;

int ButtA;
int valA;
int ButtAold = 0;

int TrigOld= 0;
int Trig;

//////////////////////
void setup() {

  pinMode(A9, INPUT_PULLUP);
  pinMode(A2, INPUT);
  pinMode(A6, INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);


// Initialize Joystick Library
  Joystick.begin();
    Joystick.setXAxisRange(-512, 512);
    Joystick.setYAxisRange(-512, 512);
    Joystick.setThrottleRange(0, 1024);
delay(5000);

CenterX = analogRead(A2);
CenterY = analogRead(A6);

}

void loop() {

///TRIMM              //Set TrimmValue and Center (Abaout 10° clearance before change Value
Trim=analogRead(A9);
if(Trim<520){Trim=520;}
if(Trim>996){Trim=995;}
if(Trim<778){Trim=map(Trim,778,520,0,-512);}
if(Trim>832){Trim=map(Trim,832,995,0,512);}
if(Trim<=832){if(Trim>=778){Trim=0;}}

//XAXIS   
XA=analogRead(A2);

if(XA<MinX){XA=MinX;}
if(XA>MaxX){XA=MaxX;}
if(XA<=(CenterX+10) && XA>=(CenterX-10)){XA=0;}
if(XA<(CenterX-10) && XA!=0){XA=map(XA,(CenterX-10),MinX,0,-512);}
if(XA>(CenterX+10)){XA=map(XA,(CenterX+10),(MaxX-1),0,512);}

//YAXIS
YA=analogRead(A6);

if(YA<MinY){YA=MinY;}
if(YA>MaxY){YA=MaxY;}
if(YA<=(CenterY+10) && YA>=(CenterY-10)){YA=0;}
if(YA<(CenterY-10)&& YA!=0){YA=map(YA,(CenterY-10),MinY,0,-512);}
if(YA>(CenterY+10)){YA=map(YA,(CenterY+10),MaxY,0,512);}

///Button Set Your Values 
valA=analogRead(A1);

if(valA>850){ButtA=1;}      //Highest to Low Values get a bit lower than Your actual Value
else if(valA>750){ButtA=2;}     
else if(valA>665){ButtA=3;}
else if(valA>630){ButtA=4;}
else if(valA>550){ButtA=5;}
else {ButtA=0;}

if(ButtAold != ButtA){
 for (int i=0; i <=5; i++){
Joystick.setButton(i,0);
}
if(ButtA != 0){Joystick.setButton((ButtA-1),1);}
ButtAold = ButtA;}          ///Only Set when diffrent Values
///Trigger

if(analogRead(A0)> 500){
Trig=1;
}
else{
  Trig=0;
  }
if(Trig!=  TrigOld){
  Joystick.setButton(5,Trig);
  TrigOld=Trig;}                  ///Only Set when diffrent Values



// Output Controls    

  Joystick.setYAxis(YA);
  Joystick.setXAxis(XA);
  Joystick.setThrottle(Trim);
  

  Joystick.sendState();

} 
