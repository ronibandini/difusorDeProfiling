// Difusor de profiling
// Roni Bandini, May 2024, Buenos Aires, Argentina
// Taller de introducción a la Contracultura Maker
// MIT License

#include <Keyboard.h>
#include <Mouse.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

#define MAX_Y 8
#define MAX_X 12

int howManyPhrases=10; 
int prePhraseDelay=3000;


byte allOn[MAX_Y][MAX_X] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

byte allOff[MAX_Y][MAX_X] = {
  { 0,0,0,0,0,0,0,0,0,0,0,0},
  { 0,0,0,0,0,0,0,0,0,0,0,0},
  { 0,0,0,0,0,0,0,0,0,0,0,0},
  { 0,0,0,0,0,0,0,0,0,0,0,0},
  { 0,0,0,0,0,0,0,0,0,0,0,0},
  { 0,0,0,0,0,0,0,0,0,0,0,0},
  { 0,0,0,0,0,0,0,0,0,0,0,0},
  { 0,0,0,0,0,0,0,0,0,0,0,0}    
};


void setup() {


  Serial.begin(115200);
  Serial.println("Difusor de profiling");
  Serial.println("Roni Bandini, 2024, Argentina");
  Serial.println("Open Google, BING, Facebook, etc...");
  
  matrix.begin();
  matrix.renderBitmap(allOn, 8, 12);

  pinMode(13, INPUT_PULLUP);
  
  randomSeed(analogRead(0));

  Keyboard.begin();
  Mouse.begin();
  
}

String getTerm(int getIndex){ 
 String phrases[howManyPhrases] = { "Jetpacks caseros a vapor", "10 libros de Nietzsche para llevar a Tokio", "Como perder al TEG contra un gato", "Cine mudo ruso subtitulado en arameo", "5 libros de Fortran para ancianos piolas", "Instructivo para bailar Lipsi", "Trucos del Portaestudio Tascam para heavy cumbia", "Las 35 mejores atracciones de Ogden","Hipnosis efectiva para gatos tuertos"};
 return phrases[getIndex];
}

void moveMouse(){
  int myX= random(1, 800);
  int myY= random(1, 600);  
  int myDelay= random(500, 1500); 

  Mouse.move(myX,myY);
  delay(myDelay); 
  Mouse.click();
}

void search(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F5);
  delay(200);
  Keyboard.releaseAll();
  delay(prePhraseDelay);
  int myIndex= random(0, howManyPhrases-1);
  String selectedPhrase=getTerm(myIndex);
  Keyboard.print(selectedPhrase);
  Keyboard.press(KEY_RETURN);
  delay(30);
  Keyboard.releaseAll();
  moveMouse();


}

void loop() {

  int sensorVal = digitalRead(13);

  if (sensorVal == LOW) {

    Serial.println("Actuando...");

    matrix.renderBitmap(allOff, 8, 12);
    search();
    matrix.renderBitmap(allOn, 8, 12);

  } 

  delay(500);


}