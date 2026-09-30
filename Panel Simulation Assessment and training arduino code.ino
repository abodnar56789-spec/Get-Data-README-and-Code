#include <U8g2lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);
const int button1 = 2; // These tell Arduino where the six physical buttions are connected
const int button2 = 3; // For each of these the const means the value will not change while program is running 
const int button3 = 4; // For example for this specifc line button 3 will be connected to pin 4
const int button4 = 5; //
const int button5 = 6; //
const int button6 = 7; //
const int LED[] = {14,15,16,17,10,11};// This is an array contains the Arduino pints that are conected to six blue LEDs
//LED[0] is pin 14 (A0)
//LED [1] is pin 15 (A1) and so on until LED [5]
const int Red = 8; //Red LED is on pin 8
const int greenLed = 9; //Green LED is pin 9
void checkEntered1(int button);//Line 14 until line 20 are functions that exist later in the program 
void showReadyScreen();
void showTaskScreen();//Function that shows the screen where the operator selects Task 1 to perfrom or Task 2 or Task 3
int findPracticeStep();//Function that finds which sequence step has has the most mistakes 
int findWrongSteps(int wrongSteps[]);
void showWrongSteps(int wrongSteps[], int wrongCount);
void compareCode();
void close_all();
void resetSequence();
const int SEQUENCE_LENGTH = 6;//Each sequnce contains 6 buttons input
const int correctCodes[][SEQUENCE_LENGTH] =  {
  {6,5,4,4,2,3},   //The first correct sequences of buttons pressed
  {6,5,3,3,3,6},   //The second correct sequences of buttons pressed (i have added two more correct sequnces to express that the machine can have different seguences of buttons pressed)
  {6,5,2,2,1,1}    //The third correct sequences of buttons pressed
};

const int NUMBER_OF_CODES =
  sizeof(correctCodes) / sizeof(correctCodes[0]);// This line calculates how many valid sequnces I have 

int entered[SEQUENCE_LENGTH] = {0};//This creates space for six entered buttons

int mistakes = 0;//This stores how many complete incorrect attempts the operator has made.

bool assessmentLocked = false;//This is a bool and it can have only two values "true" or "false"
int selectedTask = -1; // -1 means that no task has been selected yet
// 0 = Task 1
// 1 = Task 2
// 2 = Task 3
int stepMistakes[SEQUENCE_LENGTH] = {0};// Counts how many times EACH STEP was done incorrectly
// stepMistakes[0] = mistakes at step 1
// stepMistakes[1] = mistakes at step 2
// etc.
int practiceStep = 0;//Stores which step currently needs the most practice
void setup(){ //Run once at sketch startup

  Serial.begin(9600); //Begin Serial. Starts communication between Arduino and computer

  pinMode(button1, INPUT_PULLUP); // For line 54 to 59 INPUT_PULLUP means Arduino actives an internal pull-up resistor. It also gives button NOT pressed = HIGH. Button pressed = LOW
  pinMode(button2, INPUT_PULLUP); 
  pinMode(button3, INPUT_PULLUP); 
  pinMode(button4, INPUT_PULLUP); 
  pinMode(button5, INPUT_PULLUP); 
  pinMode(button6, INPUT_PULLUP); 

  pinMode(Red, OUTPUT); //the red LED is an output
  pinMode(greenLed, OUTPUT); // the green LED is an output
 

  digitalWrite(Red, LOW); //turn the red LED off
  digitalWrite (greenLed, LOW);//turn the green LED off
  for (int i = 0; i < 6;i++) 
   { 
    Serial.println(correctCodes[0][i]); 
    Serial.println(entered[i]); 
                                 
    pinMode(LED[i],OUTPUT);
    digitalWrite(LED[i], LOW); 
    }

  display.begin();
  display.setPowerSave(0);
  display.setFont(u8x8_font_pxplusibmcgathin_f);
  
 showTaskScreen();//At first the Task 1, Task 2 or Task 3 slecton screen is visible
}

  void loop() {

  if (assessmentLocked == true) {
    return;//If it is true Arduino immediately leaves loop()
  }
  if (selectedTask == -1) {// Untill no task has been selcted, Arduino waits for operator to choose a task

    // Button 1 selects Task 1
    if (digitalRead(button1) == LOW) {

      selectedTask = 0;//Button 1 selects Task 1. Array start at 0, therefore task 1 is stored as 0

      showReadyScreen();//Shows that Task 1 is selected and asks the operator to enter sequence

      delay(250);

      return;
    }

    // Button 2 selects Task 2
    else if (digitalRead(button2) == LOW) {

      selectedTask = 1;//Button 2 selcts task 2 and is stored as index 1 

      showReadyScreen();

      delay(250);

      return;
    }

    // Button 3 selects Task 3
    else if (digitalRead(button3) == LOW) {

      selectedTask = 2;//Button 3 selects Task 3 and is stored as index 2

      showReadyScreen();

      delay(500);

      return;
    }
    return;
  }
  if (digitalRead(button1) == LOW){ //If button 1 is pressed
    checkEntered1(1); //Call checkEntered and pass it a 1
    
    delay(250);//Wait 250 miliseconds
    
  }
  else if (digitalRead(button2) == LOW){ //If button2 is pressed
    checkEntered1(2); //call checkEntered1 and pass it a 2
    
    delay(250); //Wait 250 miliseconds
    
  }
  else if (digitalRead(button3) == LOW){ //If button 3 is pressed
    checkEntered1(3); //call checkEntered1 and pass it a 3
    
    delay(250); //Wait 250 miliseconds
    
  }
  else if (digitalRead(button4) == LOW){ //If button 4 is pressed
    checkEntered1(4); //call checkEntered1 and pass it a 4
    
    delay(250); //Wait 250 miliseconds
    
  }
    else if (digitalRead(button5) == LOW){ //if button 5 is pressed
    checkEntered1(5); //call checkEntered1 and pass it a 5
    
    delay(250); //Wait 250 miliseconds
    
  }
    else if (digitalRead(button6) == LOW){ //if button 6 is pressed
    checkEntered1(6); //call checkEntered1 and pass it a 6
    
    delay(250); //Wait 250 miliseconds
    
  }
}
  void checkEntered1(int button){ //Receives whichever button was pressed
  digitalWrite(LED[button-1],HIGH);//Turns on the corresponding blue LED. Array indexes from 0 1 2 3 4 5 thats why -1 in brackets
  if (entered[0] != 0){ //If the first postion already contains something, Arduino knows that the first button was already entered
    checkEntered2(button);
  }
  else if(entered[0] == 0){ 
    entered[0] = button; 
    Serial.print("1: ");Serial.println(entered[0]); 
  }
}
void registerButton (int ButtonNumber) {

}
void checkEntered2(int button){ 
  digitalWrite(LED[button-1],HIGH);
  if (entered[1] != 0){ 
    checkEntered3(button); 
  }
  
  else if(entered[1] == 0){ 
    entered[1] = button; 
    Serial.print("2: ");Serial.println(entered[1]); 
  }
  
}
void checkEntered3(int button){  
  digitalWrite(LED[button-1],HIGH);
  if (entered[2] != 0){ 
    checkEntered4(button); 
  }
  
  else if (entered[2] == 0){ 
    entered[2] = button; 
    Serial.print("3: ");Serial.println(entered[2]); 
  }
  
}
void checkEntered4(int button){  
  digitalWrite(LED[button-1],HIGH);
  if (entered[3] != 0){ 
    checkEntered5(button); 
  }
  
  else if (entered[3] == 0){ 
    entered[3] = button; 
    Serial.print("4: ");Serial.println(entered[3]); 
  }
  
}
void checkEntered5(int button){  
  digitalWrite(LED[button-1],HIGH);
  if (entered[4] != 0){ 
    checkEntered6(button); 
  }
  
  else if (entered[4] == 0){ 
    entered[4] = button; 
    Serial.print("5: ");Serial.println(entered[4]); 
  }
  
}

void checkEntered6(int button){ 
  digitalWrite(LED[button-1],HIGH);
  if (entered[5] == 0){ 
    entered[5] = button; 
    Serial.print("6: ");Serial.println(entered[5]); 
    delay(100); //Time for processing
    compareCode(); //Starts checking whether the entered sequence is correct
  }
}
//line 132 untill 194 that use checkEntered() receives whciver button was pressed. 
//For example checkEntered(5), measn inside the function button=5 and the digitalWrite(LED[button-1],HIGH) turns the corresponding 4th blue LED
void compareCode() {//Function that compares what the operator entered with the allowed/valid sequences

  bool correct = false;//Arduino starts by trying to find match adn so far no macth has been found


  // Print entered sequence for debugging
  for (int i = 0; i < SEQUENCE_LENGTH; i++) {

    Serial.println(entered[i]);//This prints all six entered button numbers to the Serial Monitor
  }

  // Compare entered sequence ONLY
  // with the selected task

for (int i = 0; i < SEQUENCE_LENGTH; i++) {//Checks all six entered steps against the sequence coressponding to chosen task

  if (entered[i] != correctCodes[selectedTask][i]) {//Compares each pressed button with the coresponding valid steps of the chosen task 

    correct = false;//If one step does not match the selcted task sequence, the attempt is incorrect

    break;
  }

  else {

    correct = true;//If the checked step matches the sequence is considred correct 
  }
}

  if (correct == true) {

    Serial.println("CORRECT");//And if the valid sequnce matched the  prints "CORRECT"

    digitalWrite(Red, LOW);//If "CORRECT" the red LED is off
    digitalWrite(greenLed, HIGH);//And the green LED is on


    display.clearDisplay();//Screen clears up

    display.draw2x2String(0, 1, "GOOD");//Screen shows "GOOD" and "JOB!"
    display.draw2x2String(0, 4, "JOB!");


    delay(2000);


    digitalWrite(greenLed, LOW);//And then the green LED is off


    resetSequence();

    selectedTask = -1;//Resets the task selection

    showTaskScreen();//Text returns to starting position of Task selection if the task completed correctly 
  }

  else {//But if entered sequence did not macth any of the valid sequences

    mistakes++;//mistake count increses by one

// Array that will contain the wrong step numbers
int wrongSteps[SEQUENCE_LENGTH];//This is an array that can store which steps are wrong 

int wrongCount = findWrongSteps(wrongSteps);//This function fills the wrongSteps array and returns back how many wrong postions it found
practiceStep = findPracticeStep();//Makes practiseStep equl to 1, 2, 3, 4, 5 or 6 depdnign on which stepp has the most mistakes
Serial.println("WRONG");

Serial.print("Wrong steps: ");

for (int i = 0; i < wrongCount; i++) {//Goes through every worng step

  Serial.print(wrongSteps[i]);//Prints each number of the mistake

  if (i < wrongCount - 1) {
    Serial.print(", ");
  }
}

Serial.println();

Serial.print("Mistakes: ");
Serial.println(mistakes);

    Serial.print("Mistakes: ");
    Serial.println(mistakes);


    digitalWrite(greenLed, LOW);//Green LED off
    digitalWrite(Red, HIGH);//Red LED on

    if (mistakes >= 3) {//If the operator made three or more unsuccessful attempts

      display.clearDisplay();

      display.drawString(0, 0, "NOT ADMISSIBLE");//Screen displays "NOT ADDMISSIBLE FOR REAL FACTORY"
      display.drawString(0, 2, "FOR REAL FACTORY");


      showWrongSteps(wrongSteps, wrongCount);

      display.setCursor(0, 6);
      display.print("STEP ");
      display.print(practiceStep);

      display.setCursor(0, 7);
      display.print("MORE PRACTICE");


      assessmentLocked = true;

      close_all();

      return;//Leaves the compareCode() loop
      //And beacouse of line 89 and 90 if an opetors presses further, it is ignored
    }

    else {//But if mistake done are less than three

      display.clearDisplay();

      display.drawString(0, 0, "MISTAKE");//Screen shows "MISTAKE TRY AGAIN" along with "WRONG STEPS" and the mistake count "Mistakes"
      display.drawString(0, 2, "TRY AGAIN");


     showWrongSteps(wrongSteps, wrongCount);

    display.setCursor(0, 6);
    display.print("STEP ");
    display.print(practiceStep);

    display.setCursor(0, 7);
    display.print("MORE PRACTICE");


      delay(5000);//waits for 5 second


      digitalWrite(Red, LOW);//Red LED is off


      resetSequence();//Clears the attempts

      showReadyScreen();//Asks the operator to try again. This is very important part of the training process, with multiple attempts opertor is able to review and correct his mistakes
    }
  }
}


int findWrongSteps(int wrongSteps[]) {

  int wrongCount = 0;


  // Compare the entered buttons only
  // with the selected task

  for (int i = 0; i < SEQUENCE_LENGTH; i++) {

    if (entered[i] != correctCodes[selectedTask][i]) {//checks if the step is wrong specifically for the task that the operator selected

      // Store which step was wrong
      wrongSteps[wrongCount] = i + 1;

      wrongCount++;


      // Also remember that this particular
      // step was wrong one more time
      stepMistakes[i]++;//Adds 
    }
  }

  return wrongCount;//Returns the total number of incorrect steps
}
int findPracticeStep() {//Finds whcih of the six steps has been incorrect most often 

  int highestMistakes = 0;//Stores the highest number of mistakes found so far

  int worstStep = 0;//Stores the number of the step that currently has the most mistakes


  for (int i = 0; i < SEQUENCE_LENGTH; i++) {//Checks the mistake count for all six steps 

    if (stepMistakes[i] > highestMistakes) {

      highestMistakes = stepMistakes[i];

      worstStep = i + 1;//This lines shows step number from 1 to 6 instead of 0 to 5 
    }
  }


  return worstStep;//Displays the step number that needs the most practice
}
void showWrongSteps(int wrongSteps[], int wrongCount) {//This fucntion takes the wrong-step information adn displays it on the screen 

  display.setCursor(0, 4);
  display.print("Wrong steps:");//This is how the screen displays the heading

  display.setCursor(0, 5);//Then the text moves to mext screen row

  for (int i = 0; i < wrongCount; i++) {//prints every wrong step

    display.print(wrongSteps[i]);

    if (i < wrongCount - 1) {
      display.print(" ");
    }
  }
}

 void resetSequence() {//This line resets Arduino for another attemp

  for (int i = 0; i < SEQUENCE_LENGTH; i++) {//Changes the operator's sequence back to 0 0 0 0 0 0

    entered[i] = 0;
  }

  close_all();//Turns off all six bluw LEDs for another attempt to start
}
void showReadyScreen() {

  display.clearDisplay();

  display.drawString(0, 0, "TRAINING PANEL");

  display.setCursor(0, 2);
  display.print("TASK ");
  display.print(selectedTask + 1);

  display.drawString(0, 4, "ENTER SEQUENCE");

  display.setCursor(0, 6);
  display.print("Mistakes: ");
  display.print(mistakes);
}
void showTaskScreen() {//Screen text is back to the inital


  display.clearDisplay();//Clears the pevious information


  display.drawString(0, 0, "TRAINING PANEL");//Shows the title text


  display.drawString(0, 2, "SELECT TASK");//Asks to choose the task the operator wants to perform/train

  display.drawString(0, 4, "1 2 3");//Shows the three available tasks that correspond to button 1, 2 and 3 

  display.drawString(0, 6, "PRESS BUTTON");

  display.setCursor(0, 5);

  display.print("Mistakes: ");//And now the screen shows the current number of mistakes 

  display.print(mistakes);
}

void close_all(){
digitalWrite(LED[0],LOW);
digitalWrite(LED[1],LOW);
digitalWrite(LED[2],LOW);
digitalWrite(LED[3],LOW);
digitalWrite(LED[4],LOW);
digitalWrite(LED[5],LOW);
}
