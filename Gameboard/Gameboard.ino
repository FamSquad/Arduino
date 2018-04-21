#include <NeoPixelBus.h>
#include <IRLibAll.h>
#include "Point.h"

const uint16_t PixelCount = 150;
const uint8_t PixelPin1 = 13;  // make sure to set this to the correct pin, ignored for Esp8266
const uint8_t PixelPin2 = 12;  // make sure to set this to the correct pin, ignored for Esp8266

#define BORDERS true

#define MAX_X 11
#define MAX_Y 23
#define TRIM_X 1
#define TRIM_Y 0

#define colorSaturation 64
#define colorHalf 32
#define RMT_POWER 0xFFA25D
#define RMT_ROTATE 0xFF9867
#define RMT_FFLEFT 0xFF02FD
#define RMT_FFRIGHT 0xFFC23D
#define RMT_MINUS 0xFFA857
#define RMT_PLUS 0xFF906F
#define RMT_PLAY 0xFF22DD
#define RMT_EQ 0xFFE01F
#define RMT_MODE 0xFF629D

#define DEFAULT_DELAY 1000


// define both strips
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip1(PixelCount, PixelPin1);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip2(PixelCount, PixelPin2);

//Create a receiver object to listen on pin 10
IRrecv myReceiver(10);

//Create a decoder object 
IRdecode myDecoder; 

// define helpful colors
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor purple(colorHalf, 0, colorHalf);
RgbColor cyan(0, colorHalf, colorHalf);
RgbColor orange(colorSaturation, colorHalf, 0);
RgbColor yellow(colorHalf, colorHalf, 0);
RgbColor magenta(colorSaturation, 0, colorSaturation);
RgbColor gray(16);
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

void setup()
{
  
  Serial.begin(9600);
  while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println(F("Initializing..."));
  Serial.flush();

  // initialize random number generator
  randomSeed(analogRead(0));

  myReceiver.enableIRIn(); // Start the IR receiver
  Serial.println(F("Ready to receive IR signals"));

  // this resets all the neopixels to an off state
  strip1.Begin();
  strip2.Begin();

  delay(200);

  Serial.println();
  Serial.println(F("Running..."));

  ResetGame();
}

void Repaint() 
{
  for (int i=0;i<=MAX_Y;i++){
    for (int j=0;j<=MAX_X;j++){
      SetColor(j, i, Well[i][j]);
    }
  }    
  Refresh();
}


/***

*/
void DrawHLine(int y, RgbColor color)
{
  for (int x = 0; x <= MAX_X; x++) {
    SetColor(x, y, color);
  }
}

void DrawVLine(int x, RgbColor color)
{
  for (int y = 0; y <= MAX_Y; y++) {
    SetColor(x, y, color);
  }
}



/***
   This method sets pixel color based on (X, Y) coordinates
   for a pixel on the matrix in vertical orientation.
*/
void SetColor(int x, int y, RgbColor color)
{
  if (y < 0 || y > MAX_Y || x < 0 || x > MAX_X) {
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


  if (x < MAX_X-1) {
    x++;
  }
  else if (y < MAX_Y-1) {
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

  if (x < MAX_X-1) {
    x++;
  }
  else {
    x = 0;
  }

  if (y < MAX_Y-1) {
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

int loopCount = 0;
int gameDelay = DEFAULT_DELAY;
unsigned long lastCommand = 0;

// will store last time a piece was moved was updated
unsigned long previousMillis = 0;      
// interval at which to move a piece (milliseconds)
const long interval = DEFAULT_DELAY;   


bool CollidesAt(int x, int y, int rotation) 
{
  for (int i=0; i<4; i++) {
    uint8_t* p = Tetraminos[currentPiece][rotation][i];
    int px = p[0] + x;
    int py = p[1] + y;

    if (px < TRIM_X || px > MAX_X-TRIM_X || py < TRIM_Y || py > MAX_Y-TRIM_Y) {
      //Serial.println("wall collision!");
      return true;
    }

    if (Well[py][px] != black) {
      //Serial.println("collision!");
      return true;
    }
  }
  return false;
}

void ResetGame()
{
  // re-initialize the well
  for (int i=0;i<=MAX_Y;i++){
    for (int j=0;j<=MAX_X;j++){
      Well[i][j] = black;
    }
    if (BORDERS) {
      Well[i][0] = gray;
      Well[i][MAX_X] = gray;
    }
  }

  Repaint();
}

void FixToWell() 
{
  for (int p = 0; p < 4; p++) {
    int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
    int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
    Well[py][px] = currentColor;
  }  
}

void NewPiece()
{
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

// Move the piece left or right
void MoveX(int i) 
{
  if (!CollidesAt(currentPosX + i, currentPosY, rotation)) {
    // blacken the piece at the current position
    for (int p = 0; p < 4; p++) {
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      SetColor(px, py, black);
    }

    currentPosX +=i;

    // draw new piece at the new position
    for (int p = 0; p < 4; p++) {
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      SetColor(px, py, currentColor);
    }
  }
}  

void Rotate()
{
  int newRot = 0;
  if (rotation < 3) {
    newRot = rotation + 1;
  }
  
  if (!CollidesAt(currentPosX, currentPosY, newRot)) {
    // blacken the piece at the current position
    for (int p = 0; p < 4; p++) {
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      SetColor(px, py, black);
    }

    rotation = newRot;

    // draw new piece at the new position
    for (int p = 0; p < 4; p++) {
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      SetColor(px, py, currentColor);
    }
    
  }
}

// Move the piece down or up
void MoveY(int i) 
{
  if (!CollidesAt(currentPosX, currentPosY+i, rotation)) {
    // blacken the piece at the current position
    for (int p = 0; p < 4; p++) {
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      SetColor(px, py, black);
    }

    currentPosY +=i;

    // draw new piece at the new position
    for (int p = 0; p < 4; p++) {
      int px = currentPosX + Tetraminos[currentPiece][rotation][p][0];
      int py = currentPosY + Tetraminos[currentPiece][rotation][p][1];
      SetColor(px, py, currentColor);
    }
  }
}  

  // Clear completed rows from the field and award score according to
  // the number of simultaneously cleared rows.
int ClearRows() {
  boolean gap;
  int numClears = 0;
  
  for (int j = TRIM_Y; j <= MAX_Y-TRIM_Y; j++) {
    gap = false;
    for (int i = TRIM_X; i <= MAX_X-TRIM_X; i++) {
      if (Well[j][i] == black) {
        gap = true;
        break;
      }
    }
    if (!gap) {
      DeleteRow(j);
      j -= 1;
      numClears += 1;
    }
  }
  /*
  switch (numClears) {
  case 1:
    score += 100;
    break;
  case 2:
    score += 300;
    break;
  case 3:
    score += 500;
    break;
  case 4:
    score += 800;
    break;
  }
  */

  return numClears;
}

void DeleteRow(int row) {
  for (int j = row; j < MAX_Y-TRIM_Y; j++) {
    for (int i = TRIM_X; i <= MAX_X-TRIM_X; i++) {
      Well[j][i] = Well[j+1][i];
    }
  }
}

void DropPiece()
{
  while (!CollidesAt(currentPosX, currentPosY-1, rotation)) {
    MoveY(-1);    
    //currentPosY--;
  }
}


void UpdateGame()
{
  // check for collision
  if (!CollidesAt(currentPosX, currentPosY-1, rotation)) {
    MoveY(-1);    
    Refresh();
  }
  else {
    if (currentPosY == startY) {
      // we are stuck on new piece!!! game over
      // for now we will do reset
      ResetGame();
    }
    else {
    
      // fix to well
      FixToWell();
  
      // clear rows
      if (ClearRows() > 0) {
        Repaint();
      }
      
      // start with a new piece
      NewPiece();
    }
  }
}

void HandleCommand(unsigned long command)
{
  if (command == RMT_POWER) {
    ResetGame();
    NewPiece();
  }     
  else if (command == RMT_FFLEFT) {
    MoveX(-1);
    Refresh();
  }     
  else if (command == RMT_FFRIGHT) {
    MoveX(1);
    Refresh();
  }     
  else if (command == RMT_ROTATE) {
    Rotate();
    Refresh();
  }     
  else if (command == RMT_PLAY) {
    DropPiece();
    Refresh();
  }     
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long handledCommand = 0;

  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(false);  //Now print results. Use false for less detail

    unsigned long receivedCommand = myDecoder.value;
    if (receivedCommand == 0xFFFFFFFF && (lastCommand == RMT_FFLEFT || lastCommand == RMT_FFRIGHT)) {
      // repeat last command
      receivedCommand = lastCommand;
    } else {
      lastCommand = receivedCommand;
    }
    
    HandleCommand(receivedCommand);
    myReceiver.enableIRIn();      //Restart receiver
  }

  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    UpdateGame();
  }

}

