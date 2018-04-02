#include <IRremote.h>
int RECV_PIN = 11; // 
int output1 = 2;
int output2 = 4;
int output3 = 6;
int itsONled[] = {0,0,0,0};
#define code1  0xFF807F // 
#define code2  0xFFA05F // 
#define code3  0xFF906F // 
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
 Serial.begin(9600);   // 
 irrecv.enableIRIn();  // 
 pinMode(output1, OUTPUT);
 pinMode(output2, OUTPUT);
 pinMode(output3, OUTPUT);
}
void loop() {
 if (irrecv.decode(&results)) {
   unsigned int value = results.value;
   switch(value) {
      case code1:
        if(itsONled[1] == 1) {        // 
           digitalWrite(output1, LOW);   // 
           itsONled[1] = 0;           // 
        } else {                      // 
            digitalWrite(output1, HIGH); // 
            itsONled[1] = 1;          // 
        }
         break; 
      case code2:
        if(itsONled[2] == 1) {
           digitalWrite(output2, LOW);
           itsONled[2] = 0;
        } else {
            digitalWrite(output2, HIGH);
            itsONled[2] = 1;
        }
         break;
      case code3:
        if(itsONled[3] == 1) {
           digitalWrite(output3, LOW);
           itsONled[3] = 0;
        } else {
            digitalWrite(output3, HIGH);
            itsONled[3] = 1;
        }
         break;          
   }
   Serial.println(value); // you can comment this line
   irrecv.resume(); // Receive the next value
 }
} 
