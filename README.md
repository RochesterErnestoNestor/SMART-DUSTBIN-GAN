#include <Servo.h>


#define TRIG_PIN PA0    // Ultrasonic sensor trigger pin
#define ECHO_PIN PA1   // Ultrasonic sensor echo pin
#define IR_PIN PA2      // IR sensor pin
#define SERVO_PIN PA3   // Servo motor pin
#define BUZZER_PIN PA4  // Buzzer pin


Servo servo;
int isOpen = 0;  // Track bin state
int buzzer = 0;  // Track buzzer state


void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(IR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
   
    servo.attach(SERVO_PIN);
    servo.write(0);  // Start with bin closed
   
    Serial.begin(115200);  // Debugging
}


void loop() {


*/DETECTION/*


    long duration, distance; // Start all Functions
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration/2) / 29.1;
int irStatus = digitalRead(IR_PIN);
Serial.print("Distance: "); // Value Print On Serial Monitor
    Serial.print(distance);
    Serial.print(" cm, IR Sensor: ");
    Serial.println(irStatus);


*/DUSTBIN CAP OPENING/*


  if (distance < 20) { // If User’s Hand Puts in front of Dustbin
    Serial.println("Opening Bin");  // Dustbin Cap Opens
    servo.write(90); // Servo Motor Rotates 90 Speed
    delay(200); // In 0.2 Seconds
while(distance < 20){ //User’s Hand still remains front
Serial.println("No Move Bin1"); // Cap Remains Opening
          servo.write(0); //Servo Motor stops rotating
          digitalWrite(TRIG_PIN, LOW); //Detect Distance Again
          delayMicroseconds(2);
          digitalWrite(TRIG_PIN, HIGH);
          delayMicroseconds(10);
          digitalWrite(TRIG_PIN, LOW);
          duration = pulseIn(ECHO_PIN, HIGH);
          distance = (duration/2) / 29.1;
          int irStatus = digitalRead(IR_PIN);
          Serial.print(distance); // Distance Value is shown
          		if(irStatus == LOW) { // If Overflow happens
									
*/ALLOW BUZZER TO SOUND ONE TIME ONLY/*
					
           			if (buzzer == 0){ //If Buzzer has Restarted
       				Serial.println("Obstacle detected! Buzzer ON"); 
         				digitalWrite(BUZZER_PIN, HIGH);
         				delay(500); // Buzzer Sounds in 0.5s
   
        				Serial.println("Obstacle detected! Buzzer OFF");
         				digitalWrite(BUZZER_PIN, LOW);
					// Buzzer does not Sound
       				buzzer = 1; // Buzzer is Closed
            			}
        			
*/ENSURE OVERFLOW PROBLEM HAS SOLVED/*


			while (buzzer == 1){ // Overflow Not Solved
				int irStatus = digitalRead(IR_PIN); 
          			Serial.print(irStatus); 
				if(irStatus == LOW) { // Overflow is Solved
					buzzer = 0; // Restart Buzzer
					delay(5000); // Wait for 5 seconds
          				}
			}
     
          		}
      }
 
  }


*/DUSTBIN CAP CLOSURE/*


  else if (distance >= 20) { // If No Hand is Detected
	Serial.println("Closing Bin"); // Dustbin Cap Closes
      servo.write(90); // Servo Motor Rotates 90 Speed
      delay(200); // In 0.2 Seconds
Serial.println("No Move Bin2"); // Dustbin Cap Stays Closed
      servo.write(0); // Make sure Dustbin Cap is always Closed
digitalWrite(TRIG_PIN, LOW); // Detection
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      duration = pulseIn(ECHO_PIN, HIGH);
      distance = (duration/2) / 29.1;
      int irStatus = digitalRead(IR_PIN);
      buzzer = 0; // Make sure Buzzer is always Restarted
  }
}
