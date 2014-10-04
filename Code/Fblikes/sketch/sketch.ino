/*
  Display Fb likes on TFT Screen

  Copyright Ankit Daftery 2014

  This code is released in the public domain, without any warranties whatsoever

 */


#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

#include <Process.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);


int isInt = 0;
int num_likes = 0;
int i = 0;
String str = "";
void setup() {
  TFTscreen.begin();


  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(2);      // set the font size
  TFTscreen.text("My Pages:\n ", 0, 0);    // write the text to the top left corner of the screen
  TFTscreen.setTextSize(2);      // ste the font size very large for the loop

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();  // make contact with the linux processor
  digitalWrite(13, HIGH);  // Led on pin 13 turns on when the bridge is ready

  delay(2000);  // wait 2 seconds
}

void loop() {// 
  Process wifiCheck;  // initialize a new process

  wifiCheck.runShellCommand("python /mnt/sda1/facebooklikes/getme.py");  // command you want to run

  while (wifiCheck.running()) {
    //Serial.println("r");
  }

  // while there's any characters coming back from the
  // process, print them to the serial monitor:
  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    str += c;
  }
  char printout[str.length()];
  char b[] = "55";
  str.toCharArray(printout, str.length()  );
  TFTscreen.stroke(255, 255, 255);    // set the font color
  TFTscreen.text(printout, 0, 20);      // print the sensor value
  delay(2500);      // wait for a moment
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.text(printout, 0, 20);    // print the sensor value
  delay(2500);
  i = 0;
  str="";
}



