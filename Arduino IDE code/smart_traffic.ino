//defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
//defines button pin
int buttonPin = 7;

// defines variables
long duration;
int distance;
int maxDistance = 20; // Maximum distance to detect in centimeters
int carCount = 0;

// Define distance thresholds for car counting
int nearThreshold = 5;   // Threshold for detecting a car nearby
int mediumThreshold = 15; // Threshold for detecting a car at medium distance
int farThreshold = 25;   // Threshold for detecting a car at far distance

// Traffic light pins
const int redPin = 2;     // Red LED connected to pin 2
const int yellowPin = 3;  // Yellow LED connected to pin 3
const int greenPin = 4;   // Green LED connected to pin 4

unsigned long startTime = 0; // Variable to store the start time for car counting
unsigned long countDuration = 30000; // Duration for car counting in milliseconds (10 seconds)
bool carCounting = true; // Flag to indicate whether to count cars or control traffic lights

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Starts the serial communication
}

void loop() 
{
  if (carCounting) 
  {
    // Start counting cars
    unsigned long currentTime = millis();
    if (currentTime - startTime >= countDuration) {
      carCounting = false; // Stop car counting after 10 seconds
      startTime = currentTime; // Reset start time for traffic light control
    } 
    else 
    {
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 microseconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2;

      // Check if distance is within the maximum limit
      if (distance <= maxDistance) {
        // Object detected within range, print distance
        Serial.print("Distance: ");
        Serial.println(distance);

        // Count cars based on distance
       if (distance >= nearThreshold) {
          carCount++;
        } /*else if (distance <= mediumThreshold) {
          carCount++;
        } else if (distance <= farThreshold) {
          carCount++;
        }*/
      } 
      else {
        // Object not detected within range, print out of range message
        Serial.println("Out of range");
      }

      // Print the car count
      Serial.print("Number of Cars: ");
      Serial.println(carCount);
    }
  } 
  else 
  {
    // Traffic light control
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
    
    if (carCount <= 2){
    lightTraffic();
    }
    else if (carCount>=3 && carCount<=6){
    mediumTraffic();
    }
    else if (carCount>6 && carCount<=9){
    moderateTraffic();
    }
    else {
    heavyTraffic();
    }
  

    // Yellow light for 6 seconds
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
    delay(6000);

    // Red light for maximum 10 seconds
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
    delay(10000);

    // Reset car count after each cycle
    carCount = 0;
    carCounting = true; // Start counting cars again
    startTime = millis(); // Reset start time for car counting
  }
}

void lightTraffic(){
 for (int i=1; i<=5; i++){ //5 secs green light duration for light traffic
   int state=digitalRead(buttonPin);

   if (state==0){
    Serial.print(i);
    Serial.print(" no pedestrian\n");
    delay(1000);
    
   }
   else if(state==1){
    Serial.print("PEDESTRIAN CROSSING\n");
    int j = (5-i)*1000/2; //remaining green light duration is halved if pedestrian pushes button 
    delay(j);
    return;
   }
   }
}

void mediumTraffic(){ //10 secs green light duration for medium traffic
 for (int i=1; i<=10; i++){
   int state=digitalRead(buttonPin);

   if (state==0){
    Serial.print(i);
    Serial.print(" no pedestrian\n");
    delay(1000);
    
   }
   else if(state==1){
    Serial.print("PEDESTRIAN CROSSING\n");
    int j = (10-i)*1000/2;
    delay(j);
    return;
   }
   }
}

void moderateTraffic(){ 
 for (int i=1; i<=20; i++){ //20 secs green light duration for moderate traffic
   int state=digitalRead(buttonPin);

   if (state==0){
    Serial.print(i);
    Serial.print(" no pedestrian\n");
    delay(1000);
   }
   else if(state==1){
    Serial.print("PEDESTRIAN CROSSING\n");
    int j = (20-i)*1000/2;
    delay(j);
    return;
   }
   }
}

void heavyTraffic(){
 for (int i=1; i<=30; i++){ //30 secs green light duration for heavy traffic
   int state=digitalRead(buttonPin);

   if (state==0){
    Serial.print(i);
    Serial.print(" no pedestrian\n");
    delay(1000);
    
   }
   else if(state==1){
    Serial.print("PEDESTRIAN CROSSING\n");
    int j = (30-i)*1000/2;
    delay(j);
    return;
   }
   }
}
