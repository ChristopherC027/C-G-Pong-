// Program to exercise the MD_MAX72XX library
// Uses most of the functions in the library
#include <MD_MAX72xx.h>

// Turn on debug statements to the serial output
#define  DEBUG  1

#if  DEBUG
#define  PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)

#endif

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define MAX_DEVICES 4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
#define  DELAYTIME  100  // in milliseconds


int delayTime = 150;                //CONTROLS GAMEPLAY SPEED


//BUTTON INITIALIZATIONS 
int buzzPin = 7;
int yesButtonPin = 2;
int yesButtonState = 0;
int noButtonPin = 3;
int noButtonState = 0;
int onButtonPin = 4;
int onButtonState = 0;
int easyButtonPin = 5;
int easyButtonState = 0;
int hardButtonPin = 6;
int hardButtonState = 0;

//BOUNDARIES
int minC = 0;
int maxC = mx.getColumnCount()-1;
const int minR = 0;
const int maxR = ROW_SIZE-1;

int  hitCounter = 0;

//HITBOX FOR PLAYER 1 PADDLE (EASYMODE)
int Rowpadpos1_1;
int Rowpadpos2_1;
int Rowpadpos3_1;
int Rowpadpos4_1;
int Colpadpos_1 = 1;

//HITBOX FOR PLAYER 2 PADDLE (EASYMODE)
int Rowpadpos1_2;
int Rowpadpos2_2;
int Rowpadpos3_2;
int Rowpadpos4_2;
int Colpadpos_2 = 30;

//HITBOX FOR PLAYER 1 PADDLE (HARDMODE)
int Rowpadpos1_3;
int Rowpadpos2_3;
int Colpadpos_3 = 1;

//HITBOX FOR PLAYER 2 PADDLE (HARDMODE)*/
int Rowpadpos1_4;
int Rowpadpos2_4;
int Colpadpos_4 = 30;

int startRow = random(0,8);
int startCol = random(15,17);

int  r, c;          //STARTING BALL POSITION
int8_t dR = 1, dC = 1;  //DELTA ROW AND COLUMN

boolean gameOn;
boolean randomBall;
boolean gameOver;
boolean turnOff;
boolean easyMode;
boolean hardMode;

int p1Score = 0;    //PLAYER 1 SCORE 
int p2Score = 0;    //PLAYER 2 SCORE 
  
int note[] = {700, 600, 500, 400, 300, 200};  //SERIES OF NOTES PLAYED BY BUZZER 


//A STARTING FUNCTION THAT WILL ALLOW THE PLAYERS TO CHOOSE BETWEEN HARD MODE & EASY MODE 
void chooseDiff(){
  scrollText("CHOOSE DIFFICULTY      ");
  easyButtonState = digitalRead(easyButtonPin);
  hardButtonState = digitalRead(hardButtonPin);
  if (easyButtonState == HIGH) {
    easyMode = true;
  }
  if (hardButtonState == HIGH) {
    hardMode = true;
  }
  easyButtonState = LOW;
  hardButtonState = LOW;
}

//EASY MODE GAME 
void paddleGame1(){

  
    mx.clear();

    //PADDLE PLAYER 1 (TOP)
    int sensorValue3 = analogRead(A0);                        //READS POTENTIOMETER SENSOR
    if (sensorValue3 <= 1023 && sensorValue3 >= 852.5)
    {
      mx.setColumn(0, 0x7);    //LIGHTS 3 LED PIXELS FOR PADDLE 1 DEPENDING ON SENSOR VALUE 
      if (dR == 1){            //PADDLE HITBOX IF BALL TRAVELING TO THE RIGHT                             
        Rowpadpos1_1 = 0;
        Rowpadpos2_1 = 1;
        Rowpadpos3_1 = 2;
      }
      else{           //PADDLE HITBOX IF BALL TRAVELING TO THE LEFT. 
        Rowpadpos1_1 = 1;
        Rowpadpos2_1 = 2;
        Rowpadpos3_1 = 3;
      }
    }
    else if (sensorValue3 <= 852.4 && sensorValue3 >= 682)
    {
      mx.setColumn(0, 0xe);
      if (dR == 1){
        Rowpadpos1_1 = 0;
        Rowpadpos2_1 = 1;
        Rowpadpos3_1 = 2;
      }
      else{
        Rowpadpos1_1 = 2;
        Rowpadpos2_1 = 3;
        Rowpadpos3_1 = 4;
      }
    }
    else if (sensorValue3 <= 681.9 && sensorValue3 >= 511.5)
    {
      mx.setColumn(0, 0x1c);
      if (dR == 1){
        Rowpadpos1_1 = 1;
        Rowpadpos2_1 = 2;
        Rowpadpos3_1 = 3;
      }
      else{
        Rowpadpos1_1 = 3;
        Rowpadpos2_1 = 4;
        Rowpadpos3_1 = 5;
      }
    }
    else if (sensorValue3 <= 511.4 && sensorValue3 >= 341)
    {
      mx.setColumn(0, 0x38);
      if (dR == 1){
        Rowpadpos1_1 = 2;
        Rowpadpos2_1 = 3;
        Rowpadpos3_1 = 4;
      }
      else{
        Rowpadpos1_1 = 4;
        Rowpadpos2_1 = 5;
        Rowpadpos3_1 = 6;
      }
    }
    else if (sensorValue3 <= 340.9 && sensorValue3 >= 170.5)
    {
      mx.setColumn(0, 0x70);
      if (dR == 1){
        Rowpadpos1_1 = 3;
        Rowpadpos2_1 = 4;
        Rowpadpos3_1 = 5;
      }
      else{
        Rowpadpos1_1 = 5;
        Rowpadpos2_1 = 6;
        Rowpadpos3_1 = 7;
      }
    }
    else
    {
      mx.setColumn(0, 0xe0);
      if (dR == 1){
        Rowpadpos1_1 = 4;
        Rowpadpos2_1 = 5;
        Rowpadpos3_1 = 6;
      }
      else{
        Rowpadpos1_1 = 5;
        Rowpadpos2_1 = 6;
        Rowpadpos3_1 = 7;
      }
    }

    //PADDLE PLAYER 2
    int sensorValue4 = analogRead(A1);
    if (sensorValue4 <= 1023 && sensorValue4 >= 852.5)
    {
      mx.setColumn(31, 0x7);
       if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_2 = 0;
        Rowpadpos2_2 = 1;
        Rowpadpos3_2 = 2;
      }
      else{
        Rowpadpos1_2 = 1;
        Rowpadpos2_2 = 2;
        Rowpadpos3_2 = 3;
      }
    }
    else if (sensorValue4 <= 852.4 && sensorValue4 >= 682)
    {
      mx.setColumn(31, 0xe);
      if (dR == 1){
        Rowpadpos1_2 = 0;
        Rowpadpos2_2 = 1;
        Rowpadpos3_2 = 2;
      }
      else{
        Rowpadpos1_2 = 2;
        Rowpadpos2_2 = 3;
        Rowpadpos3_2 = 4;
      }
    }
    else if (sensorValue4 <= 681.9 && sensorValue4 >= 511.5)
    {
      mx.setColumn(31, 0x1c);
      if (dR == 1){
        Rowpadpos1_2 = 1;
        Rowpadpos2_2 = 2;
        Rowpadpos3_2 = 3;
      }
      else{
        Rowpadpos1_2 = 3;
        Rowpadpos2_2 = 4;
        Rowpadpos3_2 = 5;
      }
    }
    else if (sensorValue4 <= 511.4 && sensorValue4 >= 341)
    {
      mx.setColumn(31, 0x38);
      if (dR == 1){
        Rowpadpos1_2 = 2;
        Rowpadpos2_2 = 3;
        Rowpadpos3_2 = 4;
      }
      else{
        Rowpadpos1_2 = 4;
        Rowpadpos2_2 = 5;
        Rowpadpos3_2 = 6;
      }
    }
    else if (sensorValue4 <= 340.9 && sensorValue4 >= 170.5)
    {
      mx.setColumn(31, 0x70);
      if (dR == 1){
        Rowpadpos1_2 = 3;
        Rowpadpos2_2 = 4;
        Rowpadpos3_2 = 5;
      }
      else{
        Rowpadpos1_2 = 5;
        Rowpadpos2_2 = 6;
        Rowpadpos3_2 = 7;
      }
    }
    else
    {
      mx.setColumn(31, 0xe0);
      if (dR == 1){
        Rowpadpos1_2 = 4;
        Rowpadpos2_2 = 5;
        Rowpadpos3_2 = 6;
      }
      else{
        Rowpadpos1_2 = 5;
        Rowpadpos2_2 = 6;
        Rowpadpos3_2 = 7;
      }
    }

  //HANDLES CORNER SITUATIONS 
    if ((sensorValue3 <= 1023 && sensorValue3 >= 852.5) && (r == 0) && (c == 1)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }
    if((sensorValue3 <= 170.4) && (r == 7) && (c == 1)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }
    if ((sensorValue4 <= 1023 && sensorValue4 >= 852.5) && (r == 0) && (c == 30)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }
    if((sensorValue4 <= 170.4) && (r == 7) && (c == 30)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }


    //MOVES THE BALL
    mx.setPoint(r, c, false);
    r += dR;
    c += dC;
    mx.setPoint(r, c, true);


    if ((r == minR) || (r == maxR)){
      dR = -dR;
      tone(buzzPin, 300, 20);
    }

    //IF BALL HITS PADDLE PLAYER 1
    if ((c == Colpadpos_1) && ((r ==  Rowpadpos1_1) || (r ==  Rowpadpos2_1) || (r ==  Rowpadpos3_1))){
    
      //IF BALL HITS LEFTMOST PIXEL OF THE PADDLE 
      if ((r == Rowpadpos1_1) && (dR == 1) && ((r != minR) || (r != maxR))){
         dR = -dR;        //LEFTMOST PIXEL OF THE PADDLE WILL HIT THE BALL TO THE RIGHT
         tone(buzzPin, 300, 20);
      }
      //IF BALL HITS RIGHTMOST PIXEL OF THE PADDLE 
      if ((r == Rowpadpos3_1) && (dR == -1) && ((r != minR) || (r != maxR))){
         dR = -dR;        //RIGHTMOST PIXEL OF THE PADDLE WILL HIT THE BALL TO THE LEFT 
         tone(buzzPin, 300, 20);
      }
      
      dC = -dC;
      tone(buzzPin, 300, 20);

      //CHANGES DIRECTION OF BALL
      hitCounter += 1;
      if (hitCounter % 5 == 0){     //MAKES GAME PLAY FASTER
        if (delayTime >= 20)
          delayTime -= 5;
      }
    }

    //IF BALL HITS PADDLE PLAYER 2
    if ((c == Colpadpos_2) && ((r ==  Rowpadpos1_2) || (r ==  Rowpadpos2_2) || (r ==  Rowpadpos3_2))){
    
      //IF BALL HITS LEFTMOST PIXEL OF THE PADDLE 
      if ((r == Rowpadpos1_2) && (dR == 1) && ((r != minR) || (r != maxR))){
         dR = -dR;        //LEFTMOST PIXEL OF THE PADDLE WILL HIT THE BALL TO THE RIGHT
         tone(buzzPin, 300, 20);
      }
      //IF BALL HITS RIGHTMOST PIXEL OF THE PADDLE
      if ((r == Rowpadpos3_2) && (dR == -1) && ((r != minR) || (r != maxR))){
         dR = -dR;        //RIGHTMOST PIXEL OF THE PADDLE WILL HIT THE BALL TO THE LEFT 
         tone(buzzPin, 300, 20);
      }

      dC = -dC;
      tone(buzzPin, 300, 20);
      
      hitCounter += 1;
      if (hitCounter % 5 == 0){
        if (delayTime >= 20)    //SETS LIMIT OF HOW FAST THE BALL CAN TRAVEL 
          delayTime -= 5;     //MAKES BALL SPEED FASTER WHEN HITCOUNTER IS DIVISIBLE BY 5 
      }
    }

    if (c == minC)          //IF BALL DOESN'T HIT PADDLE 1
    {
      p2Score += 1;         //INCREMENTS P2 SCORE 
      for(int i = 0; i < 6; i++){
        tone(buzzPin, note[i], 150);
        delay(100);
      }
      gameOn = false;
    }
    else if(c == maxC)        //IF BALL DOESN'T HIT PADDLE 2
    {
      p1Score += 1;
      for(int i = 0; i < 6; i++){
        tone(buzzPin, note[i], 150);
        delay(100);
      }

      gameOn = false;
    }
    delay(delayTime);
}

void paddleGame2(){

  //HARDMODE
     mx.clear();

    //PADDLE PLAYER 1 (TOP)
    int sensorValue = analogRead(A0);                        //READS POTENTIOMETER SENSOR
    if (sensorValue <= 1023 && sensorValue >= 876.86)
    {
      mx.setColumn(0, 0x3);                                  //LIGHTS 3 LED PIXELS FOR PADDLE 1
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_3 = 0;
        Rowpadpos2_3 = 1;
      }
      else{
        Rowpadpos1_3 = 1;
        Rowpadpos2_3 = 2;
      }
    }
    else if (sensorValue <= 876.85 && sensorValue >= 730.72)
    {
      mx.setColumn(0, 0x6);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_3 = 0;
        Rowpadpos2_3 = 1;
      }
      else{
        Rowpadpos1_3 = 2;
        Rowpadpos2_3 = 3;
      }
    }
    else if (sensorValue <= 730.71 && sensorValue >= 584.58)
    {
      mx.setColumn(0, 0xc);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_3 = 1;
        Rowpadpos2_3 = 2;
      }
      else{
        Rowpadpos1_3 = 3;
        Rowpadpos2_3 = 4;
      }
    }
    else if (sensorValue <= 584.57 && sensorValue >= 438.43)
    {
      mx.setColumn(0, 0x18);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_3 = 2;
        Rowpadpos2_3 = 3;
      }
      else{
        Rowpadpos1_3 = 4;
        Rowpadpos2_3 = 5;
      }
    }
    else if (sensorValue <= 438.42 && sensorValue >= 292.29)
    {
      mx.setColumn(0, 0x30);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_3 = 3;
        Rowpadpos2_3 = 4;
      }
      else{
        Rowpadpos1_3 = 5;
        Rowpadpos2_3 = 6;
      }
    }
    else if (sensorValue <= 292.28 && sensorValue >= 146.15)
    {
      mx.setColumn(0, 0x60);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_3 = 4;
        Rowpadpos2_3 = 5;
      }
      else{
        Rowpadpos1_3 = 6;
        Rowpadpos2_3 = 7;
      }
    }
    else
    {
      mx.setColumn(0, 0xc0);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_3 = 5;
        Rowpadpos2_3 = 6;
      }
      else{
        Rowpadpos1_3 = 6;
        Rowpadpos2_3 = 7;
      }
    }


    int sensorValue2 = analogRead(A1);                        //READS POTENTIOMETER SENSOR
    if (sensorValue2 <= 1023 && sensorValue2 >= 876.86)
    {
      mx.setColumn(31, 0x3);                                  //LIGHTS 3 LED PIXELS FOR PADDLE 1
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_4 = 0;
        Rowpadpos2_4 = 1;
      }
      else{
        Rowpadpos1_4 = 1;
        Rowpadpos2_4 = 2;
      }
    }
    else if (sensorValue2 <= 876.85 && sensorValue2 >= 730.72)
    {
      mx.setColumn(31, 0x6);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_4 = 0;
        Rowpadpos2_4 = 1;
      }
      else{
        Rowpadpos1_4 = 2;
        Rowpadpos2_4 = 3;
      }
    }
    else if (sensorValue2 <= 730.71 && sensorValue2 >= 584.58)
    {
      mx.setColumn(31, 0xc);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_4 = 1;
        Rowpadpos2_4 = 2;
      }
      else{
        Rowpadpos1_4 = 3;
        Rowpadpos2_4 = 4;
      }
    }
    else if (sensorValue2 <= 584.57 && sensorValue2 >= 438.43)
    {
      mx.setColumn(31, 0x18);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_4 = 2;
        Rowpadpos2_4 = 3;
      }
      else{
        Rowpadpos1_4 = 4;
        Rowpadpos2_4 = 5;
      }
    }
    else if (sensorValue2 <= 438.42 && sensorValue2 >= 292.29)
    {
      mx.setColumn(31, 0x30);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_4 = 3;
        Rowpadpos2_4 = 4;
      }
      else{
        Rowpadpos1_4 = 5;
        Rowpadpos2_4 = 6;
      }
    }
    else if (sensorValue2 <= 292.28 && sensorValue2 >= 146.15)
    {
      mx.setColumn(31, 0x60);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_4 = 4;
        Rowpadpos2_4 = 5;
      }
      else{
        Rowpadpos1_4 = 6;
        Rowpadpos2_4 = 7;
      }
    }
    else
    {
      mx.setColumn(31, 0xc0);
      if (dR == 1){                                          //DEPENDING ON POTENTIOMETER VALUE
        Rowpadpos1_4 = 5;
        Rowpadpos2_4 = 6;
      }
      else{
        Rowpadpos1_4 = 6;
        Rowpadpos2_4 = 7;
      }
    }

    if ((sensorValue <= 1023 && sensorValue >= 876.86) && (r == 0) && (c == 1)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }
    if((sensorValue <= 146.15) && (r == 7) && (c == 1)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }
    if ((sensorValue2 <= 1023 && sensorValue2 >= 876.86) && (r == 0) && (c == 30)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }
    if((sensorValue2 <= 146.15) && (r == 7) && (c == 30)){
      dC = -dC;
      tone(buzzPin, 300, 20);
    }

   Serial.print(Rowpadpos2_3);
   PRINTS("\n");
    //MOVES THE BALL
    mx.setPoint(r, c, false);
    r += dR;
    c += dC;
    mx.setPoint(r, c, true);


    if ((r == minR) || (r == maxR)){
      dR = -dR;
      tone(buzzPin, 300, 20);
    }

    //IF BALL HITS PADDLE PLAYER 1
    if ((c == Colpadpos_3) && ((r ==  Rowpadpos1_3) || (r ==  Rowpadpos2_3))){

      if ((r == Rowpadpos1_3) && (dR == 1) && ((r != minR) || (r != maxR))){
         dR = -dR;
         tone(buzzPin, 300, 20);
      }
      if ((r == Rowpadpos2_3) && (dR == -1) && ((r != minR) || (r != maxR))){
         dR = -dR;
         tone(buzzPin, 300, 20);
      }

      dC = -dC;
      tone(buzzPin, 300, 20);

      //CHANGES DIRECTION OF BALL
      hitCounter += 1;
      if (hitCounter % 5 == 0){     //MAKES GAME PLAY FASTER
        if (delayTime >= 20)
          delayTime -= 5;
      }
    }

    //IF BALL HITS PADDLE PLAYER 2
    if ((c == Colpadpos_4) && ((r ==  Rowpadpos1_4) || (r ==  Rowpadpos2_4))){

      if ((r == Rowpadpos1_4) && (dR == 1) && ((r != minR) || (r != maxR))){
         dR = -dR;
         tone(buzzPin, 300, 20);
      }
      if ((r == Rowpadpos2_4) && (dR == -1) && ((r != minR) || (r != maxR))){
         dR = -dR;
         tone(buzzPin, 300, 20);
      }

      dC = -dC;
      tone(buzzPin, 300, 20);
      hitCounter += 1;
      if (hitCounter % 5 == 0){
        if (delayTime >= 20)
          delayTime -= 5;
      }
    }

    if (c == minC)
    {
      p2Score += 1;
      for(int i = 0; i < 6; i++){
        tone(buzzPin, note[i], 150);
        delay(100);
      }
      gameOn = false;
    }
    else if(c == maxC)
    {
      p1Score += 1;
      for(int i = 0; i < 6; i++){
        tone(buzzPin, note[i], 150);
        delay(100);
      }

      gameOn = false;
    }
    delay(delayTime);
}

//PRINTS STRINGS ONTO THE LED MATRIX (PROVIDED BY THE ARDUINO LIBRARY). 
void scrollText(char *p)
{
  uint8_t  charWidth;
  uint8_t cBuf[8];  // this should be ok for all built-in fonts

  mx.clear();

  while (*p != '\0')
  {
    charWidth = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);

    for (uint8_t i=0; i<charWidth + 1; i++) // allow space between characters
    {
      mx.transform(MD_MAX72XX::TSL);
      if (i < charWidth)
        mx.setColumn(0, cBuf[i]);
      delay(50);
    }
  }
}

//PRINTS A BOOM ANIMATION ONTO THE LED MATRIX (PROVIDED BY THE ARDUINO LIBRARY).
void boom()
// Demonstrate the use of buffer based repeated patterns
// across all devices.
{
  mx.clear();
  scrollText("GAME OVER          ");


  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t n=0; n<1; n++)
  {
    byte  b = 0xff;
    int   i = 0;

    while (b != 0x00)
    {
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE-1-i, b);
        mx.setColumn(j, COL_SIZE-1-i, b);
      }
      mx.update();
      delay(3*DELAYTIME);
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE-1-i, 0);
        mx.setColumn(j, COL_SIZE-1-i, 0);
      }

      bitClear(b, i);
      bitClear(b, 7-i);
      i++;
    }

    while (b != 0xff)
    {
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE-1-i, b);
        mx.setColumn(j, COL_SIZE-1-i, b);
      }
      mx.update();
      delay(3*DELAYTIME);
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE-1-i, 0);
        mx.setColumn(j, COL_SIZE-1-i, 0);
      }

      i--;
      bitSet(b, i);
      bitSet(b, 7-i);
    }
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void scoreUpdate()
{

  //PRINTS PLAYER 1 SCORE ON TO LED MATRIX
  if (p1Score == 0)
    scrollText("P1 : 0    ");
  else if (p1Score == 1)
    scrollText("P1 : 1    ");
  else if (p1Score == 2)
    scrollText("P1: 2    ");
  else if (p1Score == 3)
    scrollText("P1: 3    ");
  else if (p1Score == 4)
    scrollText("P1: 4    ");
  else if (p1Score == 5)
  {
    scrollText("P1: 5    ");
  }

  //PRINTS PLAYER 2 SCORE ON TO LED MATRIX 
  if (p2Score == 0)
    scrollText("P2 : 0    ");
  else if (p2Score == 1)
    scrollText("P2 : 1    ");
  else if (p2Score == 2)
    scrollText("P2: 2    ");
  else if (p2Score == 3)
    scrollText("P2: 3    ");
  else if (p2Score == 4)
    scrollText("P2: 4    ");
  else if (p2Score == 5)
  {
    scrollText("P2: 5    ");
  }

  //IF PLAYER 1 SCORE OR PLAYER 2 SCORE REACHES 5 THEN GAME OVER!
  if ((p1Score == 5) || (p2Score == 5))
  {
    boom();
    gameOver = true;
  }
  //ELSE WE KEEP PLAYING
  else
  {
    gameOn = true;
    randomBall = true;
  }
}

void rematch()
{
  mx.clear();
  scrollText("PLAY?    ");            //ASKS IF WE WANT TO PLAY AGAIN.
  yesButtonState = digitalRead(yesButtonPin); 
  noButtonState = digitalRead(noButtonPin);
  
  //IF WE PRESS THE YES BUTTON WE RESET EVERYTHING
  if (yesButtonState == HIGH) {
    p1Score = 0;
    p2Score = 0;
    hitCounter = 0;
    delayTime = 150;
    gameOver = false;
  }
  //IF WE PRESS THE NO BUTTON WE TURN OFF THE GAME
  if (noButtonState == 1) {
    p1Score = 0;
    p2Score = 0;
    turnOff = true;
  }
  yesButtonState = LOW;
  noButtonState = LOW;
}


void clearGame(){
  mx.clear();
  //TURNS OFF THE GAME 
  onButtonState = digitalRead(onButtonPin);
  
  //IF WE PRESS THE ON BUTTON, TURN ON THE LED SCREEN.
  if (onButtonState == 1) {
    setup(); 
  }
}


void setup()
{
  mx.begin();
  
  //PINS SET UP
  pinMode(buzzPin, OUTPUT);
  pinMode(yesButtonPin, INPUT);
  pinMode(noButtonPin, INPUT);
  pinMode(onButtonPin, INPUT);
  pinMode(easyButtonPin, INPUT);
  pinMode(hardButtonPin, INPUT);
#if  DEBUG || ENABLE_FONT_ADJUST
  Serial.begin(9600);
  randomSeed(analogRead(5));
  delay(1000);
#if ENABLE_FONT_ADJUST

#endif // ENABLE_FONT_ADJUST
#endif

  //BOOLEAN SET UP
  gameOn = true;
  randomBall = true;
  gameOver = false;
  turnOff = false;
  hardMode = false;
  easyMode = false;
  //SETS UP GAME BY CHOOSING DIFFICULT
    chooseDiff();
}

void loop(void)
{

  if (easyMode){
    if (turnOff){
      Serial.print(5);
      clearGame();
    }
    else{
      if (gameOver)
        rematch();
      else{
        if (randomBall){
          int startRow = random(1,8);
          int startCol = random(15,17);

          r = startRow;
          c = startCol;      //STARTING BALL POSITION
          randomBall = false;
        }

       if(gameOn){
          paddleGame1();
       } else{
          scoreUpdate();
       }
     }
   }
  }


  if (hardMode){
    if (turnOff){
      Serial.print(5);
      clearGame();
    }
    else{
      if (gameOver)
        rematch();
      else{
        if (randomBall){
          int startRow = random(1,8);
          int startCol = random(15,17);

          r = startRow;
          c = startCol;      //STARTING BALL POSITION
          randomBall = false;
        }

       if(gameOn){
          paddleGame2();
       } else{
          scoreUpdate();
       }
     }
   }
  }
}
