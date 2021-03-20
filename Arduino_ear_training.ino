/*
This sketch uses the buzzer to play songs.
The Arduino's tone() command will play notes of a given frequency.
We'll provide a function that takes in note characters (a-g),
and returns the corresponding frequency from this table:

  note 	frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz

For more information, see http://arduino.cc/en/Tutorial/Tone
*/

const int buttonPin1 = 2; 
const int buttonPin2 = 3; 
const int buttonPin3 = 4; 
const int buttonPin4 = 5; 
const int buttonPin5 = 6; 
const int buttonPin6 = 7; 
const int buttonPin7 = 8; 
const int buttonPin8 = 9; 

const int ledPinGreen =  11;  
const int ledPinRed =  12;  
const int buzzerPin = 10;  

 // variables for reading the pushbutton status
int buttonState1 = 0;        
int buttonState2 = 0; 
int buttonState3 = 0;        
int buttonState4 = 0; 
int buttonState5 = 0;        
int buttonState6 = 0; 
int buttonState7 = 0;        
int buttonState8 = 0; 

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 200;

int noteNamesLen = 8;  // number of notes we're storing (length of noteNames[] array)
char noteNames[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() 
{
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);
  pinMode(buttonPin8, INPUT);
  
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
}

void playArpeggio()
{ 
  int i;
  char arpeggio[] = {'c','e','g','C'};
  int arpeggioLen = 4;
  int duration = tempo;
  for(i = 0; i < arpeggioLen; i++)
  {
    char note = arpeggio[i];
    int currFreq = getFrequency(note);
    tone(buzzerPin, currFreq, duration);
    delay(duration);
  }
  delay(5*tempo);
}

int noteCount = 4;
char randNotes[4]; //size should be equal to noteCount
int currAnswerIndex = 0;
bool isCorrectAnswer = true;

bool doButtonStuff()
{
  //this is HIGH or LOW
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState7 = digitalRead(buttonPin7);
  buttonState8 = digitalRead(buttonPin8);
  
  bool buttonPressed = false;
  char notePressed;
  if(buttonState1 == HIGH)
  {
    notePressed = 'c';
    buttonPressed = true;
  }
  else if(buttonState2 == HIGH)
  {
    notePressed = 'd';
    buttonPressed = true;
  }
  else if(buttonState3 == HIGH)
  {
    notePressed = 'e';
    buttonPressed = true;
  }
  else if(buttonState4 == HIGH)
  {
    notePressed = 'f';
    buttonPressed = true;
  }
  else if(buttonState5 == HIGH)
  {
    notePressed = 'g';
    buttonPressed = true;
  }
  else if(buttonState6 == HIGH)
  {
    notePressed = 'a';
    buttonPressed = true;
  }
  else if(buttonState7 == HIGH)
  {
    notePressed = 'b';
    buttonPressed = true;
  }
  else if(buttonState8 == HIGH)
  {
    notePressed = 'C';
    buttonPressed = true;
  }

  int currFreq;
  int soundTime = tempo; //ms 
  if(buttonPressed)
  {
    currFreq = getFrequency(notePressed);
    tone(buzzerPin, currFreq, soundTime);
    delay(soundTime/2); //allows the sound to play
    Serial.println(notePressed);
    char currCorrectNote = randNotes[currAnswerIndex];

    isCorrectAnswer = notePressed == currCorrectNote;
    
    Serial.print("correct answer:");
    Serial.println(randNotes[currAnswerIndex]);
    Serial.print("my answer:");
    Serial.println(notePressed);
    if(isCorrectAnswer)
    {
      Serial.print("Correct!");
      digitalWrite(ledPinGreen, HIGH);
    }
    else
    {
      Serial.print("Wrong!");
      digitalWrite(ledPinRed, HIGH);
    }
    delay(soundTime/2);
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinRed, LOW);
    
    currAnswerIndex++;  
  }

  if(currAnswerIndex == noteCount)
  {
    currAnswerIndex = 0;
    Serial.println(isCorrectAnswer);
    isCorrectAnswer = true;
    delay(500);
    return true;  
  }
  return false;
}

void playRandomNotes()
{
  int i;
  int correctIndices[noteCount];
  for(i = 0; i < noteCount; i++)
  {
    int randIndex = random(noteNamesLen);
    randNotes[i] = noteNames[randIndex];
  }
  
  for (i = 0; i < noteCount; i++) 
  {
    int duration = 1 * tempo;  // length of note in ms
    char note = randNotes[i];
    Serial.print(i);
    Serial.print(":");
    Serial.print(note);
    Serial.println("");
    int currFreq = getFrequency(note);
    tone(buzzerPin, currFreq, duration);
    delay(duration);            // wait for tone to finish
    delay(tempo/10);            // wait a short time so notes don't blend together
  }
}

void loop() 
{
  playArpeggio();
  playRandomNotes();
  
  while(true)
  {
    if(doButtonStuff())
    {
      break;  
    }
  }
}

int getFrequency(char note) 
{
  int i;
  for (i = 0; i < noteNamesLen; i++)  
  {
    if (noteNames[i] == note)        
    {
      return(frequencies[i]);    
    }
  }
  return(0);
}
