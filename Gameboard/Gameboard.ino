#include <NeoPixelBus.h>
#include "Point.h"

const uint16_t PixelCount = 150;
const uint8_t PixelPin1 = 13;  // make sure to set this to the correct pin, ignored for Esp8266
const uint8_t PixelPin2 = 12;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 64
#define colorHalf 32

// define both strips
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip1(PixelCount, PixelPin1);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip2(PixelCount, PixelPin2);

// define helpful colors
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor purple(colorHalf, 0, colorHalf);
RgbColor cyan(0, colorHalf, colorHalf);
RgbColor orange(colorSaturation, colorHalf, 0);
RgbColor yellow(colorHalf, colorHalf, 0);
RgbColor magenta(colorSaturation, 0, colorSaturation);
RgbColor gray(4);
RgbColor white(colorSaturation);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);

// Screen Map
uint8_t VerticalMap[24][12] = {
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

RgbColor Well[24][12];

RgbColor TetraminoColors[8] = {red, green, blue, purple, cyan, magenta, orange, yellow};

uint8_t Tetraminos[7][4][4][2] = {
  // I-Piece
  {
    { {0, 1}, {1, 1}, {2, 1}, {3, 1} },
    { {1, 0}, {1, 1}, {1, 2}, {1, 3} },
    { {0, 1}, {1, 1}, {2, 1}, {3, 1} },
    { {1, 0}, {1, 1}, {1, 2}, {1, 3} }
  },

  // J-Piece
  {
    { {0, 1}, {1, 1}, {2, 1}, {2, 0} },
    { {1, 0}, {1, 1}, {1, 2}, {2, 2} },
    { {0, 1}, {1, 1}, {2, 1}, {0, 2} },
    { {1, 0}, {1, 1}, {1, 2}, {0, 0} }
  },

  // L-Piece
  {
    { {0, 1}, {1, 1}, {2, 1}, {2, 2} },
    { {1, 0}, {1, 1}, {1, 2}, {0, 2} },
    { {0, 1}, {1, 1}, {2, 1}, {0, 0} },
    { {1, 0}, {1, 1}, {1, 2}, {2, 0} }
  },

  // O-Piece
  {
    { {0, 0}, {0, 1}, {1, 0}, {1, 1} },
    { {0, 0}, {0, 1}, {1, 0}, {1, 1} },
    { {0, 0}, {0, 1}, {1, 0}, {1, 1} },
    { {0, 0}, {0, 1}, {1, 0}, {1, 1} }
  },

  // S-Piece
  {
    { {1, 0}, {2, 0}, {0, 1}, {1, 1} },
    { {0, 0}, {0, 1}, {1, 1}, {1, 2} },
    { {1, 0}, {2, 0}, {0, 1}, {1, 1} },
    { {0, 0}, {0, 1}, {1, 1}, {1, 2} }
  },

  // T-Piece
  {
    { {1, 0}, {0, 1}, {1, 1}, {2, 1} },
    { {1, 0}, {0, 1}, {1, 1}, {1, 2} },
    { {0, 1}, {1, 1}, {2, 1}, {1, 2} },
    { {1, 0}, {1, 1}, {2, 1}, {1, 2} }
  },

  // Z-Piece
  {
    { {0, 0}, {1, 0}, {1, 1}, {2, 1} },
    { {1, 0}, {0, 1}, {1, 1}, {0, 2} },
    { {0, 0}, {1, 0}, {1, 1}, {2, 1} },
    { {1, 0}, {0, 1}, {1, 1}, {0, 2} }
  }


};
/*
  Point* Tetraminos[3][4][4] = {


      // I-Piece
      {
        { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(3, 1) },
        { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(1, 3) },
        { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(3, 1) },
        { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(1, 3) }
      },

      // J-Piece
      {
        { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(2, 0) },
        { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(2, 2) },
        { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(0, 2) },
        { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(0, 0) }
      },

      // L-Piece
      {
        { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(2, 2) },
        { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(0, 2) },
        { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(0, 0) },
        { new Point(1, 0), new Point(1, 1), new Point(1, 2), new Point(2, 0) }
      },

      // O-Piece
      {
        { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) },
        { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) },
        { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) },
        { new Point(0, 0), new Point(0, 1), new Point(1, 0), new Point(1, 1) }
      },

      // S-Piece
      {
        { new Point(1, 0), new Point(2, 0), new Point(0, 1), new Point(1, 1) },
        { new Point(0, 0), new Point(0, 1), new Point(1, 1), new Point(1, 2) },
        { new Point(1, 0), new Point(2, 0), new Point(0, 1), new Point(1, 1) },
        { new Point(0, 0), new Point(0, 1), new Point(1, 1), new Point(1, 2) }
      },

      // T-Piece
      {
        { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(2, 1) },
        { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(1, 2) },
        { new Point(0, 1), new Point(1, 1), new Point(2, 1), new Point(1, 2) },
        { new Point(1, 0), new Point(1, 1), new Point(2, 1), new Point(1, 2) }
      },

      // Z-Piece
      {
        { new Point(0, 0), new Point(1, 0), new Point(1, 1), new Point(2, 1) },
        { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(0, 2) },
        { new Point(0, 0), new Point(1, 0), new Point(1, 1), new Point(2, 1) },
        { new Point(1, 0), new Point(0, 1), new Point(1, 1), new Point(0, 2) }
      }
  };
*/

void setup()
{
  Serial.begin(9600);
  while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println(F("Initializing..."));
  Serial.flush();

  // this resets all the neopixels to an off state
  strip1.Begin();
  strip2.Begin();


  //initialize the well
  for (int i=0;i<24;i++){
    for (int j=0;j<12;j++){
      Well[j][i] = black;
    }
  }

 // comment out for now - wall sides
 // for (int w=0;w<24;w++){
 //   SetColor(0, w, gray);
 //   SetColor(11, w, gray);
 // }

  delay(200);

  strip1.Show();
  strip2.Show();

  Serial.println();
  Serial.println(F("Running..."));

}

void Repaint() 
{
  for (int i=0;i<24;i++){
    for (int j=0;j<12;j++){
      SetColor(j, i, Well[i][j]);
    }
  }    
  Refresh();
}


/***

*/
void DrawHLine(int y, RgbColor color)
{
  for (int x = 0; x < 12; x++) {
    SetColor(x, y, color);
  }
}

void DrawVLine(int x, RgbColor color)
{
  for (int y = 0; y < 23; y++) {
    SetColor(x, y, color);
  }
}



/***
   This method sets pixel color based on (X, Y) coordinates
   for a pixel on the matrix in vertical orientation.
*/
void SetColor(int x, int y, RgbColor color)
{
  if (y < 0 || y > 23 || x < 0 || x > 11) {
    // error - invalid input
    return;
  }

  if (x < 6) {
    strip1.SetPixelColor(VerticalMap[y][x], color);
  }
  else {
    strip2.SetPixelColor(VerticalMap[y][x], color);
  }
}

/***
   This method refreshes both strips.
*/
void Refresh() {
  strip1.Show();
  strip2.Show();
}


// Starting position for sample program
int x = 0;
int y = 0;

void OneByOne() {
  SetColor(x, y, red);
  Refresh();
  delay(50);
  SetColor(x, y, black);
  Refresh();

  delay(10);

  //Serial.println("X=");
  //Serial.println(x);


  if (x < 11) {
    x++;
  }
  else if (y < 22) {
    x = 0;
    y++;
  }
  else {
    x = 0;
    y = 0;
  }
}

void LineByLine() {
  DrawVLine(x, purple);
  DrawHLine(y, purple);
  Refresh();
  delay(50);
  DrawVLine(x, black);
  DrawHLine(y, black);
  Refresh();

  delay(10);

  if (x < 11) {
    x++;
  }
  else {
    x = 0;
  }

  if (y < 22) {
    y++;
  }
  else {
    y = 0;
  }
}

int currentPiece = 0;
int rotation = 0;
RgbColor currentColor = red;

const int startX = 5;
const int startY = 19;

int currentPosX = startX;
int currentPosY = startY;


bool CollidesAt(int x, int y, int rotation) 
{
  for (int i=0; i<4; i++) {
    uint8_t* p = Tetraminos[currentPiece][rotation][i];
    int px = p[0] + x;
    int py = p[1] + y;
    Serial.print("currentPiece=");
    Serial.println(currentPiece);
    Serial.print("i=");
    Serial.println(i);
    Serial.print("px=");
    Serial.println(px);
    Serial.print("py=");
    Serial.println(py);
    
    if (Well[py][px] != black) {
      Serial.print("collision!");
      return true;
    }
  }
  return false;
}

void DrawPoints()
{
//  Refresh();

  delay(300);

  // check for collision
  if (currentPosY>0 && !CollidesAt(currentPosX, currentPosY-1, rotation)) {

    // blacken the piece at the current position
    for (int p = 0; p < 4; p++) {
      //uint8_t point[2] = Tetraminos[currentPiece][rotation][p];
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      SetColor(px, py, black);
    }

    currentPosY--;
    // draw new piece at the new position
    for (int p = 0; p < 4; p++) {
      //        uint8_t point[2] = Tetraminos[currentPiece][rotation][p];
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];

    /*
            Serial.print("currentPosX=");
            Serial.println(currentPosX);
            Serial.print("currentPosY=");
            Serial.println(currentPosY);
            Serial.print("p=");
            Serial.println(p);


            Serial.print("X=");
            Serial.println(px);
            Serial.print("Y=");
            Serial.println(py);

            Serial.println("-------------------------");
    */
      SetColor(px, py, currentColor);
    }
    
    Refresh();
  }
  else {
    // fix to wall
    for (int p = 0; p < 4; p++) {
      //        uint8_t point[2] = Tetraminos[currentPiece][rotation][p];
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      Well[py][px] = currentColor;
    }
    
    
    // start with a new piece
    currentPosY = startY;
    currentPosX = random(1, 7);
    
    // pick next piece
    if (currentPiece < 6) {
      currentPiece++;
    }
    else {
      currentPiece = 0;
    }
    // set rotation to random value
    rotation = random(0, 3);
    
    //picks random color
    currentColor = TetraminoColors[random(0,7)];
  }

}

void loop()
{
  //LineByLine();
  DrawPoints();

}

