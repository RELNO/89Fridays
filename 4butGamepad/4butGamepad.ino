/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                      89 Fridays @ MIT Media Lab
                                     RELNO + Borja / City Science
This program turns your Arduino into a four button keyboard controller for your arcade games.
It was originally designed to be compatible with "89 Fridays Racer" game, based on @jakedordon's javascript-racer.
Game available at: https://relno.github.io/89Fridays/index.html
Note: This code only runs on 32u4 and SAMD based boards, due to the usage of the Keyboard library.
                                    April 26, 2019. Cambridge, MA
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


//Include keyboard library, wich only works on 32u4 and SAMD based boards (Leonardo, Esplora, Zero, Due and MKR Family).
#include <Keyboard.h>

//Define the pins for the 4 buttons
const int up = 4;
const int left = 6;
const int right = 2;
const int down = 8;

//Define button state variables
int upState;
int leftState;
int downState;
int rightState;

//Define the state of the buttons in the previous loop turn, and set to high (not pressed)
int prevupState = HIGH;
int prevleftState = HIGH;
int prevdownState = HIGH;
int prevrightState = HIGH;

void setup() {

  //Set pinModes for the buttons to INPUT_PULLUP (HIGH=not pressed button, LOW=pressed button)
  pinMode(up, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);

  //Start keyboard communication through USB
  Keyboard.begin();
}

void loop() {

  //Read input from buttons
  upState = digitalRead(up);
  leftState = digitalRead(left);
  downState = digitalRead(down);
  rightState = digitalRead(right);

  if (upState==LOW && leftState==LOW && rightState==LOW && downState==LOW){
        //If all buttons pressed, refresh the website (Ctrl+F5), release the keys and wait 2 seconds for the website to refresh
        Keyboard.press(KEY_RIGHT_CTRL);
        Keyboard.press(KEY_F5);
        Keyboard.releaseAll();

        delay(2000);
  }
  else{

      //Check if any of the buttons changed state form the previous loop turn
      bool moveup=((upState != prevupState));
      bool moveleft= ((leftState != prevleftState));
      bool movedown=((downState != prevdownState));
      bool moveright=((rightState != prevrightState));

      //If any button changed state, press or release that button
      if (moveup or moveleft or movedown or moveright){
      
        if (moveup){
            if (upState==LOW){Keyboard.press(KEY_UP_ARROW);}
            else {Keyboard.release(KEY_UP_ARROW);} 
        }
        if (moveleft){
            if (leftState==LOW){Keyboard.press(KEY_LEFT_ARROW);}
            else {Keyboard.release(KEY_LEFT_ARROW);} 
        }
        if (movedown){
            if (downState==LOW){Keyboard.press(KEY_DOWN_ARROW);}
            else {Keyboard.release(KEY_DOWN_ARROW);} 
        }
        if (moveright){
            if (rightState==LOW){Keyboard.press(KEY_RIGHT_ARROW);}
            else {Keyboard.release(KEY_RIGHT_ARROW);} 
        }

        //Wait 50ms for the next loop turn to start
        delay(50);
      }
  }

  //Set actual button states to previous states in the nect loop turn
  prevupState = upState;
  prevleftState = leftState;
  prevdownState = downState;
  prevrightState = rightState;
}
