/*
  Title: 7seg_Count
  Authored By: Brad Beacham (TheBradl3s)
  Date: 3/12/2015

  Displays 0 through to 9 on a 7 segment display and either increases or decreases the count depending on the button pressed.

  Pins 2, 3, 4, 5, 6, 8, 9 for 7seg display hookup (See setup() for which connects to what segments, change as per requirements.
  Pins 11, 12 for inputs to increase and decrease the count

  Hold both buttons for 2 seconds to make the display count through 0-9 twice.
 */

// Function Declaration 
void Display(int num);
bool ButtonHold(int num); // num = time in seconds the button is held for
void CountThrough(int times);

int number = 0;
bool VerifyButtonHold = true;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);
  pinMode(8, OUTPUT); // Segment A
  pinMode(9, OUTPUT); // Segment B
  pinMode(2, OUTPUT); // Segment C
  pinMode(3, OUTPUT); // Segment D
  pinMode(4, OUTPUT); // Segment E
  pinMode(5, OUTPUT); // Segment F
  pinMode(6, OUTPUT); // Segment G
  pinMode(12, INPUT); // Button Input - Increases Displayed Number
  pinMode(11, INPUT); // Button 2 Input - Decreases displayed number

  Display(99);
  
}



// the loop function runs over and over again forever
void loop() {

  if (digitalRead(11) == HIGH) {
    number++;
    if (number >= 10) {
      number = 0;
    }
    
    delay(400);
  } 

  if (digitalRead(12) == HIGH) { 
    number--;
    if (number < 0) {
      number = 9;
    }
    
    delay(400);
  }   
  Display(number);

if (ButtonHold(2) == VerifyButtonHold) {
    CountThrough(2);
    delay(1000);

  }
  
};

void CountThrough(int times) {
  for (int i=0; i < times; i++) {
    Display(0);
    delay(200);
    Display(1);
    delay(200);
    Display(2);
    delay(200);
    Display(3);
    delay(200);
    Display(4);
    delay(200);
    Display(5);
    delay(200);
    Display(6);
    delay(200);
    Display(7);
    delay(200);
    Display(8);
    delay(200);
    Display(9);
    delay(200);
  }
    Display(0);

}

bool ButtonHold(int num) {
  if (digitalRead(11) == HIGH && digitalRead(12) == HIGH) {
    Serial.print("Both buttons pressed, WAITING to see if held\n");
    delay(num*1000);
    if (digitalRead(11) == HIGH && digitalRead(12) == HIGH) {
      Serial.print("both buttons held, must be true!\n");
      return (true);
    }
     else {
      return (false);
    }
      
  }
}

void Display (int num) {
  switch (num) {
    case 0:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      break; 
    case 1:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);    
      break;
    case 2:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);       
      break;
    case 3:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);     
      break;
    case 4:
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);     
      break;
    case 5:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);     
      break;
    case 6:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);     
      break;
    case 7:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);     
      break;
    case 8:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);     
      break;
    case 9:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);     
      break;
    case 99: //Turns 7seg display off
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);      
      break;
       
  }
}





























