// NeoPixelTest
// This example will cycle between showing four pixels as Red, Green, Blue, White
// and then showing those pixels as Black.
//
// Included but commented out are examples of configuring a NeoPixelBus for
// different color order including an extra white channel, different data speeds, and
// for Esp8266 different methods to send the data.
// NOTE: You will need to make sure to pick the one for your platform 
//
//
// There is serial output of the current state so you can confirm and follow along
//

#include <NeoPixelBus.h>

const uint16_t PixelCount = 300; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 13;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

// three element pixels, in different order and speeds
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, Neo400KbpsMethod> strip(PixelCount, PixelPin);

// For Esp8266, the Pin is omitted and it uses GPIO3 due to DMA hardware use.  
// There are other Esp8266 alternative methods that provide more pin options, but also have
// other side effects.
//NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
//
// NeoEsp8266Uart800KbpsMethod uses GPI02 instead

// You can also use one of these for Esp8266, 
// each having their own restrictions
//
// These two are the same as above as the DMA method is the default
// NOTE: These will ignore the PIN and use GPI03 pin
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266Dma400KbpsMethod> strip(PixelCount, PixelPin);

// Uart method is good for the Esp-01 or other pin restricted modules
// NOTE: These will ignore the PIN and use GPI02 pin
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266Uart400KbpsMethod> strip(PixelCount, PixelPin);

// The bitbang method is really only good if you are not using WiFi features of the ESP
// It works with all but pin 16
//NeoPixelBus<NeoGrbFeature, NeoEsp8266BitBang800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266BitBang400KbpsMethod> strip(PixelCount, PixelPin);

// four element pixels, RGBW
//NeoPixelBus<NeoRgbwFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);

int a=169;
int b=168;
int c=179;
int d=19;

void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();


    Serial.println();
    Serial.println("Running...");
}


void loop()
{

  delay(100);

    Serial.println("Colors R, G, B, W...");

    // set the colors, 
    // if they don't match in order, you need to use NeoGrbFeature feature
    strip.SetPixelColor(a, red);
    strip.SetPixelColor(b, red);
    strip.SetPixelColor(c, red);
    strip.SetPixelColor(d, red);
    // the following line demonstrates rgbw color support
    // if the NeoPixels are rgbw types the following line will compile
    // if the NeoPixels are anything else, the following line will give an error
    //strip.SetPixelColor(3, RgbwColor(colorSaturation));
    strip.Show();


    delay(100);

    Serial.println("Off ...");

    // turn off the pixels
    strip.SetPixelColor(a, black);
    strip.SetPixelColor(b, black);
    strip.SetPixelColor(c, black);
    strip.SetPixelColor(d, black);
    strip.Show();

    a = a-1;
    b = b-1;
    c = c+1;
    d = d-1;
   

}

    /*Serial.println("HSL Colors R, G, B, W...");

    // set the colors, 
    // if they don't match in order, you may need to use NeoGrbFeature feature
    strip.SetPixelColor(168, red);
    strip.SetPixelColor(167, red);
    strip.SetPixelColor(180, red);
    strip.SetPixelColor(18, red);
    strip.Show();


    delay(1000);

    strip.SetPixelColor(168, black);
    strip.SetPixelColor(167, black);
    strip.SetPixelColor(180, black);
    strip.SetPixelColor(18, black);
    strip.Show();

    delay(1);

    Serial.println("HSL Colors R, G, B, W...");

    // set the colors, 
    // if they don't match in order, you may need to use NeoGrbFeature feature
    strip.SetPixelColor(167, red);
    strip.SetPixelColor(166, red);
    strip.SetPixelColor(181, red);
    strip.SetPixelColor(17, red);
    strip.Show();


    delay(1000);

    
    strip.SetPixelColor(167, black);
    strip.SetPixelColor(166, black);
    strip.SetPixelColor(181, black);
    strip.SetPixelColor(17, black);
    strip.Show();

    delay(1);

    Serial.println("HSL Colors R, G, B, W...");

    // set the colors, 
    // if they don't match in order, you may need to use NeoGrbFeature feature
    strip.SetPixelColor(166, red);
    strip.SetPixelColor(165, red);
    strip.SetPixelColor(182, red);
    strip.SetPixelColor(16, red);
    strip.Show();


    delay(1000);

    strip.SetPixelColor(166, black);
    strip.SetPixelColor(165, black);
    strip.SetPixelColor(182, black);
    strip.SetPixelColor(16, black);
    strip.Show();

    delay(1);

    Serial.println("HSL Colors R, G, B, W...");

    // set the colors, 
    // if they don't match in order, you may need to use NeoGrbFeature feature
    strip.SetPixelColor(165, red);
    strip.SetPixelColor(164, red);
    strip.SetPixelColor(183, red);
    strip.SetPixelColor(16, red);
    strip.Show();


    delay(1000);


    Serial.println("Off again...");

    // turn off the pixels
    strip.SetPixelColor(0, hslBlack);
    strip.SetPixelColor(1, hslBlack);
    strip.SetPixelColor(2, hslBlack);
    strip.SetPixelColor(3, hslBlack);
    strip.Show();

    delay(2000);

}
*/
