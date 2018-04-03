#include <NeoPixelBus.h>

const uint16_t PixelCount = 150; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin1 = 13;  // make sure to set this to the correct pin, ignored for Esp8266
const uint8_t PixelPin2 = 12;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

// define both strips
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip1(PixelCount, PixelPin1);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip2(PixelCount, PixelPin2);

// define helpful colors
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

int VerticalMap[24][12] = {
  {143,  97,  95,  49,  47,   1,   1,  47,  49,  95,  97, 143},
  {142,  98,  94,  50,  46,   2,   2,  46,  50,  94,  98, 142},
  {141,  99,  93,  51,  45,   3,   3,  45,  51,  93,  99, 141},
  {140, 100,  92,  52,  44,   4,   4,  44,  52,  92, 100, 140},
  {139, 101,  91,  53,  43,   5,   5,  43,  53,  91, 101, 139},
  {138, 102,  90,  54,  42,   6,   6,  42,  54,  90, 102, 138},
  {137, 103,  89,  55,  41,   7,   7,  41,  55,  89, 103, 137},
  {136, 104,  88,  56,  40,   8,   8,  40,  56,  88, 104, 136},
  {135, 105,  87,  57,  39,   9,   9,  39,  57,  87, 105, 135},
  {134, 106,  86,  58,  38,  10,  10,  38,  58,  86, 106, 134},
  {133, 107,  85,  59,  37,  11,  11,  37,  59,  85, 107, 133},
  {132, 108,  84,  60,  36,  12,  12,  36,  60,  84, 108, 132},
  {131, 109,  83,  61,  35,  13,  13,  35,  61,  83, 109, 131},
  {130, 110,  82,  62,  34,  14,  14,  34,  62,  82, 110, 130},
  {129, 111,  81,  63,  33,  15,  15,  33,  63,  81, 111, 129},
  {128, 112,  80,  64,  32,  16,  16,  32,  64,  80, 112, 128},
  {127, 113,  79,  65,  31,  17,  17,  31,  65,  79, 113, 127},
  {126, 114,  78,  66,  30,  18,  18,  30,  66,  78, 114, 126},
  {125, 115,  77,  67,  29,  19,  19,  29,  67,  77, 115, 125},
  {124, 116,  76,  68,  28,  20,  20,  28,  68,  76, 116, 124},
  {123, 117,  75,  69,  27,  21,  21,  27,  69,  75, 117, 123},
  {122, 118,  74,  70,  26,  22,  22,  26,  70,  74, 118, 122},
  {121, 119,  73,  71,  25,  23,  23,  25,  71,  73, 119, 121}
};


void setup()
{
    Serial.begin(9600);
    while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    // this resets all the neopixels to an off state
    strip1.Begin();
    strip2.Begin();

    strip1.Show();
    strip2.Show();

    Serial.println();
    Serial.println("Running...");

}



/**
 * This method sets pixel color based on (X, Y) coordinates 
 * for a pixel on the matrix in vertical orientation. 
 */
void SetColor(int x, int y, RgbColor color)
{
  if (y<0 || y>23 || x<0 || x>11) {
    // error - invalid input
    return;
  }

  if (x<6) {
    strip1.SetPixelColor(VerticalMap[y][x], color);
  }
  else {
    strip2.SetPixelColor(VerticalMap[y][x], color);
  }
}

void Refresh() {
  strip1.Show();
  strip2.Show();
}

int x = 0;
int y = 0;

void loop()
{
    SetColor(x, y, red);
    Refresh();
    delay(50);
    SetColor(x, y, black);
    Refresh();

    if (x<11) {
      x++;
    }
    else if (y<22) {
      x = 0;
      y++;
    }
    else {
      x = 0;
      y = 0;
    }

}

