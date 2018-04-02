#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include "IRremote.h"


int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
int colorSaturation = 155
RgbColor red(colorSaturation, 0, 0);
RgbColor orange(255, 140, 0);
RgbColor yellow(255, 255, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor purple(139, 0, 139);
RgbColor white(colorSaturation);
RgbColor black(0);

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {

  case 0xFF629D: Serial.println(" FORWARD"); break;
  case 0xFF22DD: Serial.println(" LEFT");    break;
  case 0xFF02FD: Serial.println(" -OK-");    break;
  case 0xFFC23D: Serial.println(" RIGHT");   break;
  case 0xFFA857: Serial.println(" REVERSE"); break;
  case 0xFF6897: strip.SetPixelColor(red); //1
  case 0xFF9867: strip.SetPixelColor(orange); //2
  case 0xFFB04F: Serial.println(" 3");    break; //3
  case 0xFF30CF: Serial.println(" 4");    break; //4
  case 0xFF18E7: Serial.println(" 5");    break; //5
  case 0xFF7A85: Serial.println(" 6");    break; //6
  case 0xFF10EF: Serial.println(" 7");    break; //7
  case 0xFF38C7: Serial.println(" 8");    break; //8
  case 0xFF5AA5: Serial.println(" 9");    break; //9
  case 0xFF4AB5: Serial.println(" 0");    break; //0
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} 
