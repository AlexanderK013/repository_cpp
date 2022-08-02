/*
  Appending to Strings using the += operator and concat()
 
 Examples of how to append different data types to strings
 
 created 27 July 2010
 modified 2 Apr 2012
 by Tom Igoe
 
 http://arduino.cc/en/Tutorial/StringAppendOperator
 
 This example code is in the public domain.
 */
String stringOne, stringTwo;

const int comGetData = 1;




void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  stringOne = String("");
 
}

void loop() {
 
	  if (Serial.available() > 0) {
//		   Serial.println("*************loop**********");
		  stringOne = String("");
	    // you can subtract 48 to get the actual value:0 through 9 in ASCII
	    int bitToSet = Serial.read() - 48;//Serial.read();//
//	    Serial.print("bitToSet=");
//	        Serial.println(bitToSet);
	    switch (bitToSet) {
	    	case comGetData:
	    		  // adding a string to a string:
				  stringOne += "1;20;99;28;99;28;1;20;99;28;99;28;1;20;99;28;99;28;1;20;99;28;99;28;";
				  stringOne += "1;50;99;28;99;28;1;50;99;28;99;28;1;50;99;28;99;28;1;50;99;28;99;28;";
				  stringOne += "1;20;99;28;99;28;1;20;99;28;99;28;1;20;99;28;99;28;1;20;99;28;99;28;";
				  stringOne += "1;20;99;28;99;28;1;20;99;28;99;28;1;20;99;28;99;28;1;20;99;28;99;28;";
	    		//	    		  stringOne += "1;2;3;2;";
	    		//	    		  stringOne += "adding a string to a string";
	    		   Serial.println(stringOne);  // prints  "Sensor "
	    		break;



	    	default:
	    		  stringOne += "0;0;0;";
	    		   Serial.println(stringOne);  // prints  "Sensor "
	    		break;

	    }

	  }
 
//  // do nothing while true:
//  while(true);
}

