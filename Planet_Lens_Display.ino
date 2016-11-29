#include <AFMotor.h>
#include <Button.h>

//create white motor #1, yellow motor #2, at 64kHz pwm
AF_DCMotor white(1,MOTOR12_64KHZ);
AF_DCMotor yellow(2);

//define pins, variables that won't change:

//turn on internal pull-up resistor for button pins
Button mercuryButton = Button(22,PULLUP);
Button venusButton = Button(24,PULLUP);    
Button earthButton = Button(26,PULLUP);
Button moonButton = Button(28,PULLUP);
Button marsButton = Button(30,PULLUP);
Button jupiterButton = Button(32,PULLUP);
Button saturnButton = Button(34,PULLUP);
Button uranusButton = Button(36,PULLUP);
Button neptuneButton = Button(38,PULLUP);
Button plutoButton = Button(40,PULLUP);

const int mercuryledPin = 23;    //planet selection LEDs
const int venusledPin = 25;
const int earthledPin = 27;
const int moonledPin = 29;
const int marsledPin = 31;
const int jupiterledPin = 33;
const int saturnledPin = 35;
const int uranusledPin = 37;
const int neptuneledPin = 39;
const int plutoledPin = 41;

const int sunPin = 53;      //Sun LED on button board
const int lightPin = 52;    //main light

const int wpotPin = A7;    //white potentiometer pin
const int ypotPin = A8;    //yellow potentiometer pin

/* NOTES.....................................................
WHITE:  Topmost(Zero) = 175
           Bottommost = 900
          
YELLOW:    Topmost(Zero) = 255
           Bottommost = 600
.............................................................
*/

//White Motor
const int wMercuryPosition = 225;
const int wVenusPosition = 465;
const int wEarthPosition = 455;
const int wMoonPosition = 808;
const int wMarsPosition = 430;
const int wJupiterPosition = 350;
const int wSaturnPosition = 330;
const int wUranusPosition = 318;
const int wNeptunePosition = 350;
const int wPlutoPosition = 900;
    //set white motor speeds
    const int wUpSpeed = 75;
    const int wDownSpeed = 85;

//Yellow Motor
const int yMercuryPosition = 225;
const int yVenusPosition = 400;
const int yEarthPosition = 332;
const int yMoonPosition = 366;
const int yMarsPosition = 310;
const int yJupiterPosition = 300;
const int ySaturnPosition = 310;
const int yUranusPosition = 366;
const int yNeptunePosition = 350;
const int yPlutoPosition = 330;
    //set yellow motor speeds
    const int yUpSpeed = 255;
    const int yDownSpeed = 150;




//variables that will change:
int wlensPosition = 0;
int ylensPosition = 0;
int wPlace = 0;
int yPlace = 0;

int planetPin = sunPin;    //set planetPin as sunPin (only initially)
int lastPin = sunPin;      //set last planet LED pin temporarily

long lightTime = 9000;    //set lag time after planet adjustment
long previousMillis = -1*(lightTime) - 1;




void setup() {
  pinMode(wpotPin, INPUT);    //declare potentiometer as input
  pinMode(ypotPin, INPUT);
  
  //set planet selection LEDs as output, and turn all off
  pinMode(mercuryledPin, OUTPUT);  digitalWrite(mercuryledPin,LOW);
  pinMode(venusledPin, OUTPUT);    digitalWrite(venusledPin,LOW);
  pinMode(earthledPin, OUTPUT);    digitalWrite(earthledPin,LOW);
  pinMode(moonledPin, OUTPUT);     digitalWrite(moonledPin,LOW);
  pinMode(marsledPin, OUTPUT);     digitalWrite(marsledPin,LOW);
  pinMode(jupiterledPin, OUTPUT);  digitalWrite(jupiterledPin,LOW);
  pinMode(saturnledPin, OUTPUT);   digitalWrite(saturnledPin,LOW);
  pinMode(uranusledPin, OUTPUT);   digitalWrite(uranusledPin,LOW);
  pinMode(neptuneledPin, OUTPUT);  digitalWrite(neptuneledPin,LOW);
  pinMode(plutoledPin, OUTPUT);    digitalWrite(plutoledPin,LOW);
  
  pinMode(sunPin, OUTPUT);      //Sun LED on button board
  pinMode(lightPin, OUTPUT);    //main light
}


void loop() {
  
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > lightTime) {
    digitalWrite(lightPin, LOW);
    digitalWrite(sunPin, LOW);
    digitalWrite(planetPin, LOW); }
  else {
    digitalWrite(lightPin, HIGH); }
  
  ////// when a BUTTON is pressed...
  if(mercuryButton.isPressed()
  ||venusButton.isPressed()
  ||earthButton.isPressed()
  ||moonButton.isPressed()
  ||marsButton.isPressed()
  ||jupiterButton.isPressed()
  ||saturnButton.isPressed()
  ||uranusButton.isPressed()
  ||neptuneButton.isPressed()
  ||plutoButton.isPressed()) {
    
    digitalWrite(lastPin, LOW);    //turn off last planet LED
    digitalWrite(lightPin, HIGH);    //turn on MAIN LIGHT
    digitalWrite(sunPin, HIGH);      //turn on sun LED on button board
       
       //write PLACE based on which button was pressed
       if(mercuryButton.wasPressed()) {
          wPlace = wMercuryPosition;
          yPlace = yMercuryPosition;
          planetPin = mercuryledPin;
       }else if(venusButton.wasPressed()) {
          wPlace = wVenusPosition;
          yPlace = yVenusPosition;
          planetPin = venusledPin;
       }else if(earthButton.wasPressed()) {
          wPlace = wEarthPosition;
          yPlace = yEarthPosition;
          planetPin = earthledPin;
       }else if(moonButton.wasPressed()) {
          wPlace = wMoonPosition;
          yPlace = yMoonPosition;
          planetPin = moonledPin;
       }else if(marsButton.wasPressed()) {
          wPlace = wMarsPosition;
          yPlace = yMarsPosition;
          planetPin = marsledPin;
       }else if(jupiterButton.wasPressed()) {
          wPlace = wJupiterPosition;
          yPlace = yJupiterPosition;
          planetPin = jupiterledPin;
       }else if(saturnButton.wasPressed()) {
          wPlace = wSaturnPosition;
          yPlace = ySaturnPosition;
          planetPin = saturnledPin;
       }else if(uranusButton.wasPressed()) {
          wPlace = wUranusPosition;
          yPlace = yUranusPosition;
          planetPin = uranusledPin;
       }else if(neptuneButton.wasPressed()) {
          wPlace = wNeptunePosition;
          yPlace = yNeptunePosition;
          planetPin = neptuneledPin;
       }else if(plutoButton.wasPressed()) {
          wPlace = wPlutoPosition;
          yPlace = yPlutoPosition;
          planetPin = plutoledPin;
       }
  
  digitalWrite(planetPin, HIGH);      //turn on planet button LED
       
  wlensPosition = analogRead(wpotPin);    //read potentiometers
  ylensPosition = analogRead(ypotPin);
          
          
    //WHITE MOTOR
    if(wlensPosition < wPlace) {
      white.setSpeed(wDownSpeed);
      white.run(FORWARD);}
    else if(wlensPosition > wPlace) {
      white.setSpeed(wUpSpeed);
      white.run(BACKWARD);}
      
      //YELLOW MOTOR
      if(ylensPosition < yPlace) {
      while(ylensPosition < yPlace){
        yellow.setSpeed(yDownSpeed);
        yellow.run(FORWARD);
        if(wlensPosition == wPlace) {white.run(RELEASE);}
        wlensPosition = analogRead(wpotPin);  //read positions
        ylensPosition = analogRead(ypotPin);
      }
        yellow.run(RELEASE);      //stop yellow motor
        
      }else if(ylensPosition > yPlace) {
        while(ylensPosition > yPlace){
          yellow.setSpeed(yUpSpeed);
          yellow.run(BACKWARD);
          if(wlensPosition == wPlace) {white.run(RELEASE);}
          wlensPosition = analogRead(wpotPin);  //read positions
          ylensPosition = analogRead(ypotPin);
        }
        yellow.run(RELEASE);      //stop yellow motor
      }
      
      wlensPosition = analogRead(wpotPin);   //check position again
               
      if(wlensPosition > wPlace) {
        while(wlensPosition > wPlace) {
          white.setSpeed(wUpSpeed);
          white.run(BACKWARD);
          wlensPosition = analogRead(wpotPin);
        }
      }else if(wlensPosition < wPlace) {
          while(wlensPosition < wPlace) {
            white.setSpeed(wDownSpeed);
            white.run(FORWARD);
            wlensPosition = analogRead(wpotPin);
          }
      }
      
      white.run(RELEASE);
      
      lastPin = planetPin;    //save last planet LED pin
      previousMillis = currentMillis;    //save time motors stopped
      delay(100);
      
  }      // "a button was pressed" loop
  
  
}        //void loop() { }

