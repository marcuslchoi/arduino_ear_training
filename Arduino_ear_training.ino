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
const int ledPin =  13;   
const int buzzerPin = 9;  

int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0; 

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 200;

int noteNamesLen = 2;  // number of notes we're storing (length of noteNames[] array)
char noteNames[] = { 'c', 'd' }; //, 'e', 'f', 'g', 'a', 'b', 'C' };
int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  pinMode(ledPin, OUTPUT);
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

  int currFreq;
  int soundTime = tempo; //ms 
  if(buttonPressed)
  {
    currFreq = getFrequency(notePressed);
    tone(buzzerPin, currFreq, soundTime);
    delay(soundTime); //allows the sound to play
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
    }
    else
    {
      Serial.print("Wrong!");
    }
    currAnswerIndex++;  
  }
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  digitalWrite(ledPin, buttonState1);

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
    delay(tempo/10); 
  }
}

void loop() 
{
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
