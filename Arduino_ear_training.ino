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

const int buttonPin = 2; 
const int ledPin =  13;   
const int buzzerPin = 9;  

int buttonState = 0;         // variable for reading the pushbutton status

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

char songNotes[] = "cdfda ag cdfdg gf "; // a space represents a rest

// Beats is an array values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.

int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 80;


void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void doButtonStuff()
{
  //this is HIGH or LOW
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH)
  {
    char note = 'c';
    int noteLen = 1;
    int currFreq = getFrequency(note);
    Serial.println(note);
    Serial.println(currFreq);
    tone(buzzerPin, currFreq, noteLen*tempo);
  }
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  digitalWrite(ledPin, buttonState);
}

//char[] getRandomNotes()
//{
//  return ['d','c'];
//}

int extraHz = 0;
void loop() 
{
  int i, duration;
  int songLength = sizeof(beats)/sizeof(int);
  
  for (i = 0; i < songLength; i++) // step through the song arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms
    
    if (songNotes[i] == ' ')          // is this a rest? 
    {
      delay(duration);            // then pause for a moment
    }
    else                          // otherwise, play the note
    {
      int currFreq = getFrequency(songNotes[i]) + extraHz;
      Serial.print(currFreq);
      Serial.print(' ');
      tone(buzzerPin, currFreq, duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }
  Serial.println();
  extraHz += 100;
  
  // We only want to play the song once, so we'll pause forever:
  while(true)
  {
    doButtonStuff();
  }
}



int getFrequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.
  
  int i;
  const int numNotes = 8;  // number of notes we're storing

  char noteNames[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  
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
