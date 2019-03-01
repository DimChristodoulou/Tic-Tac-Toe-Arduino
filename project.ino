//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12


#include <LCD5110_Graph.h>

LCD5110 myGLCD(4,5,6,8,7);

extern unsigned char SmallFont[];

int vcc = 3;
int led = 2;
bool led_on = true;
int y;
int playersTurn = 0;
int playersMoves[3][3];

void setup()
{
  pinMode(led,OUTPUT);
  pinMode(vcc,OUTPUT);
  
  digitalWrite(vcc,HIGH);
  digitalWrite(led,LOW);
  
  myGLCD.InitLCD();
  myGLCD.setContrast(65);
  myGLCD.setFont(SmallFont);

  Serial.begin(9600);
  
  randomSeed(analogRead(0));

  //KATHETES
  myGLCD.drawLine(33,0,33,47);
  myGLCD.drawLine(49,0,49,47);

  //ORIZONTIES
  myGLCD.drawLine(18,15,65,15);
  myGLCD.drawLine(18,31,65,31);

  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      playersMoves[i][j] = 0;
    }
  }

  myGLCD.update();
}

void drawX(int moveX,int moveY){
  myGLCD.drawLine(18+moveX*16,0+moveY*16,32+moveX*16,14+moveY*16);
  myGLCD.drawLine(32+moveX*16,0+moveY*16,18+moveX*16,14+moveY*16);
  myGLCD.update();
}

void drawO(int moveX, int moveY){
  myGLCD.drawCircle(25+moveX*16,7+moveY*16,7);
  myGLCD.update();
}

void toggleLED(){
  if(led_on==true){
    digitalWrite(led,HIGH);
    led_on = false;
  }
  else{
    digitalWrite(led,LOW);
    led_on = true;
  }
}

void playerOMove(int x, int y){
  if ( playersMoves[x][y] == 0 ){
    drawO(x,y);
    playersMoves[x][y] = 2;
    playersTurn = 1;
  }
}

void playerXMove(int x, int y){
  if( playersMoves[x][y] == 0 ){
    drawX(x,y);
    playersMoves[x][y] = 1;
    playersTurn = 0;
  }
}

void checkWin(){
  if( (playersMoves[0][0] == 1 && playersMoves[0][1] == 1 && playersMoves[0][2] == 1) || (playersMoves[1][0] == 1 && playersMoves[1][1] == 1 && playersMoves[1][2] == 1) || (playersMoves[2][0] == 1 && playersMoves[2][1] == 1 && playersMoves[2][2] == 1) ||
      (playersMoves[0][0] == 1 && playersMoves[1][0] == 1 && playersMoves[2][0] == 1) || (playersMoves[0][1] == 1 && playersMoves[1][1] == 1 && playersMoves[2][1] == 1) || (playersMoves[0][2] == 1 && playersMoves[1][2] == 1 && playersMoves[2][2] == 1) ||
      (playersMoves[0][0] == 1 && playersMoves[1][1] == 1 && playersMoves[2][2] == 1) || (playersMoves[0][2] == 1 && playersMoves[1][1] == 1 && playersMoves[2][0] == 1) ){
        myGLCD.clrScr();
        myGLCD.print("PLAYER X WINS!", CENTER, 0);
        myGLCD.print("PRESS R", CENTER, 16);
        myGLCD.print("TO REPLAY", CENTER, 32);
        myGLCD.update();
      }
  if( (playersMoves[0][0] == 2 && playersMoves[0][1] == 2 && playersMoves[0][2] == 2) || (playersMoves[1][0] == 2 && playersMoves[1][1] == 2 && playersMoves[1][2] == 2) || (playersMoves[2][0] == 2 && playersMoves[2][1] == 2 && playersMoves[2][2] == 2) ||
      (playersMoves[0][0] == 2 && playersMoves[1][0] == 2 && playersMoves[2][0] == 2) || (playersMoves[0][1] == 2 && playersMoves[1][1] == 2 && playersMoves[2][1] == 2) || (playersMoves[0][2] == 2 && playersMoves[1][2] == 2 && playersMoves[2][2] == 2) ||
      (playersMoves[0][0] == 2 && playersMoves[1][1] == 2 && playersMoves[2][2] == 2) || (playersMoves[0][2] == 2 && playersMoves[1][1] == 2 && playersMoves[2][0] == 2) ){
        myGLCD.clrScr();
        myGLCD.print("PLAYER O WINS!", CENTER, 0);
        myGLCD.print("PRESS R", CENTER, 16);
        myGLCD.print("TO REPLAY", CENTER, 32);
        myGLCD.update();
      }
}

void resetAll(){

  myGLCD.clrScr();
  
  //KATHETES
  myGLCD.drawLine(33,0,33,47);
  myGLCD.drawLine(49,0,49,47);

  //ORIZONTIES
  myGLCD.drawLine(18,15,65,15);
  myGLCD.drawLine(18,31,65,31);

  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      playersMoves[i][j] = 0;
    }
  }

  myGLCD.update();
}

void loop()
{
  char rx_byte;
    
  if(playersTurn == 1){    
    if (Serial.available() > 0) {    // is a character available?
      rx_byte = Serial.read();       // get the character
      if(rx_byte == '1'){
        playerXMove(0,0);
      }
      if(rx_byte == '2'){
        playerXMove(1,0);
      }
      if(rx_byte == '3'){
        playerXMove(2,0);
      }
      if(rx_byte == '4'){
        playerXMove(0,1);
      }
      if(rx_byte == '5'){
        playerXMove(1,1);
      }
      if(rx_byte == '6'){
        playerXMove(2,1);
      }
      if(rx_byte == '7'){
        playerXMove(0,2);
      }
      if(rx_byte == '8' ){
        playerXMove(1,2);
      }
      if(rx_byte == '9'){
        playerXMove(2,2);
      }
      if(rx_byte == 'r'){
        resetAll();
      }
      checkWin();
      Serial.print("PLAYER X typed: ");
      Serial.println(rx_byte);
    }
  }
  else if (playersTurn == 0){    
    if (Serial.available() > 0) {    // is a character available?
      rx_byte = Serial.read();       // get the character
      if(rx_byte == '1'){
        playerOMove(0,0);
      }
      if(rx_byte == '2'){
        playerOMove(1,0);
      }
      if(rx_byte == '3'){
        playerOMove(2,0);
      }
      if(rx_byte == '4'){
        playerOMove(0,1);
      }
      if(rx_byte == '5'){
        playerOMove(1,1);
      }
      if(rx_byte == '6'){
        playerOMove(2,1);
      }
      if(rx_byte == '7'){
        playerOMove(0,2);
      }
      if(rx_byte == '8' ){
        playerOMove(1,2);
      }
      if(rx_byte == '9'){
        playerOMove(2,2);
      }
      if(rx_byte == 'r'){
        resetAll();
      }
      checkWin();
      Serial.print("PLAYER 0 typed: ");
      Serial.println(rx_byte);
    }
  }
}
