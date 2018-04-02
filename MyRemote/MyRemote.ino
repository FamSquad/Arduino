#include <IRLibAll.h>

//Create a receiver object to listen on pin 2
IRrecv myReceiver(10);

//Create a decoder object 
IRdecode myDecoder;   

//Define which of 7 segments to light up for each number
int num_array[10][7] = {  { 1,1,1,1,1,1,0 },    // 0
                          { 0,1,1,0,0,0,0 },    // 1
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,0,0,1 },    // 3
                          { 0,1,1,0,0,1,1 },    // 4
                          { 1,0,1,1,0,1,1 },    // 5
                          { 1,0,1,1,1,1,1 },    // 6
                          { 1,1,1,0,0,0,0 },    // 7
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,1,1,0,0,1,1 }};   // 9


void showNumber(int number) {
  // starting with Pin #2
  int pin= 2;
  for (int j=0; j < 7; j++) {
   digitalWrite(pin, num_array[number][j]);
   pin++;
  }   
} 

void eraseNumber() {
  // starting with Pin #2
  int pin= 2;
  for (int j=0; j < 7; j++) {
   digitalWrite(pin, 0);
   pin++;
  }   
} 

void setup() {

  // define pin modes
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);

  // start IR receiver
  Serial.begin(9600);
  delay(2000);
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(false);  //Now print results. Use false for less detail

    if (myDecoder.value == 0xFFFFFFFF) {
      // do nothing - this is a filler value
    } 
    else if (myDecoder.value == 0xFF6897) {
      showNumber(0);
    } 
    else if (myDecoder.value == 0xFF30CF) {
      showNumber(1);
    }
    else if (myDecoder.value == 0xFF18E7) {
      showNumber(2);
    }
    else if (myDecoder.value == 0xFF7A85) {
      showNumber(3);
    }
    else if (myDecoder.value == 0xFF10EF) {
      showNumber(4);
    }
    else if (myDecoder.value == 0xFF38C7) {
      showNumber(5);
    }
    else if (myDecoder.value == 0xFF5AA5) {
      showNumber(6);
    }
    else if (myDecoder.value == 0xFF42BD) {
      showNumber(7);
    }
    else if (myDecoder.value == 0xFF4AB5) {
      showNumber(8);
    }
    else if (myDecoder.value == 0xFF52AD) {
      showNumber(9);
    }
    else
    {
      eraseNumber();
    }
    myReceiver.enableIRIn();      //Restart receiver
  }


 

}
