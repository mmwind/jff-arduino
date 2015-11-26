/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define TONE_PIN 2

typedef struct {
  int v[3];
  char colname;
  int note;
} ColorLabel;

#define COLOR_COUNT 9
ColorLabel colors[COLOR_COUNT]={
 {830,897,426,  '0',NOTE_A3},
 {687,746,307,  '1',NOTE_C4},
 {644,350,163,   'R',NOTE_D4},
 {22,  250,  62,   'G',NOTE_E4},
 {1,  5,   2,   'B',NOTE_F4},
 {690,690,285,  'Y',NOTE_G4},
 {220,573,177,  'C', NOTE_A4},
 {665,490,210,  'O', NOTE_B4},
 {631,374,169,  'M', NOTE_C4}
};


float sqr(float x){
 return(x*x); 
}


float getDiffColor(int A[3], int B[3]){
  float v =0;
  for(int i=0; i< 3; i++){
    v += sqr(A[i] - B[i]);
  }
  v = sqrt( v );
  return(v);
}

int getColor(int *in){
  float minval = getDiffColor(colors[0].v, in);
  int  minindex = 0;
  Serial.print(minval);Serial.print(',');
  
  for(int i=1; i<COLOR_COUNT; i++){
    float val = getDiffColor(colors[i].v, in);
    if(val < minval){
      minval = val;
      minindex = i;
    }
    Serial.print(val);Serial.print(',');
  }
  return(minindex);
}

int led = 13;

char names[3] = { 'R', 'G', 'B' };
int leds[3] = { A0, A1, A2 };
unsigned long ledDelay = 5;

int sensorPin = A3;
int sensorVcc = 9;

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(115200);  
   
  for(int i=0; i<3; i++){
  // initialize the digital pin as an output.
  pinMode(leds[i], OUTPUT);   
  }  
  
  pinMode(sensorVcc, OUTPUT); 
  digitalWrite(sensorVcc, HIGH);
}

void readColor(int *col){
  for(int i=0; i<3; i++){
   digitalWrite(leds[i], HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(ledDelay);               // wait 
    
   col[i] = analogRead(sensorPin); 
   
   digitalWrite(leds[i], LOW);    // turn the LED off by making the voltage LOW
   delay(ledDelay);               // wait 
   Serial.print(col[i]);Serial.print("\t");
  }
  Serial.println();
}

void playit(int colidx){
  if(colidx<2){
    noTone(TONE_PIN);
  } else {
    tone(TONE_PIN, colors[colidx].note);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  int col[3];
  readColor(col);
  int colidx = getColor(col);
  Serial.println(colors[colidx].colname);
  playit(colidx);
  delay(100);
}

