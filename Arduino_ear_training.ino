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

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

char songNotes[] = "cdfda ag cdfdg gf "; // a space represents a rest

// Beats is an array values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.

int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 200;

const int numNotes = 8;  // number of notes we're storing
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
  int currFreq;
  int soundTime = 500; //ms
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

  if(buttonPressed)
  {
    currFreq = getFrequency(notePressed);
    tone(buzzerPin, currFreq, soundTime);
    Serial.println(notePressed);
    delay(1000);

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
    return true;  
  }
  return false;
}

char getRandomNoteName()
{
  int randIndex = random(numNotes);
  return noteNames[randIndex];
}

void playRandomNotes()
{
  int i;
  for(i = 0; i < noteCount; i++)
  {
    randNotes[i] = getRandomNoteName();
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
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.
  
  int i;

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.
  
  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (noteNames[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}
