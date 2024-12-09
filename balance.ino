/*
==================================
University of Southern California
Viterbi School of Engineering 
AME-Department
AME 201: Statics
A.Potnuru and A. Cajal
===================================


This code was adapted from the code given in:
https://www.instructables.com/Arduino-Scale-With-5kg-Load-Cell-and-HX711-Amplifi/
For any feedback or questions contact: A. Cajal (cajal@usc.edu)
*/


#include "HX711.h"

#define DOUT_PIN  3
#define SCK_PIN  2

HX711 scale;

float calibration_factor = -10; //MODIFY THIS VALUE

void setup() {
  printTittle(); // THIS FUNCTION PRINTS THE TIT
  printPreprocess();
  
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 2);
  Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}




/*--- AUXILIARY FUNCTIONS ---*/

/*
 * Here's a little function to print the tittle.
 */
void printTittle(){
  Serial.begin(9600);
  Serial.println("University of Southern California");
  Serial.println("Viterbi School of Engineering");
  Serial.println("Aerospace and Mechanical Engineering Department");
  Serial.println("AME 201 - Prof. Akshay Potnuru, T.A. Arturo Cajal");
  Serial.println("Author: A. Cajal");
  Serial.println("Revised: A. Potnuru");
  Serial.println("Last updated: 04/07/21");
  Serial.println(" ");
  Serial.println("Press enter to continue");
  waitForSerial();
}

/*
 * Here's a little function to print instructions.
 */
void printPreprocess(){

  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  Serial.println("Type start to begin");
  waitForSerial();
}


/*
 * Here's a little function to wait for a keypress and
 * then kill the data received.
 */
void waitForSerial(){
  while (!Serial.available()) {
  }
  Serial.println(Serial.read());
}
