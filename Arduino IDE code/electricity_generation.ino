int led=12;
int sensor=A0;
int threshold= 900;

void setup() {
  pinMode(12,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  int value=analogRead(sensor);
  if (value>=threshold)
  {
    digitalWrite(led,HIGH);
    //delay(100);
    Serial.println(value);
  }
  else
  digitalWrite(led,LOW);
  value=0; // resetting analogRead(sensor) to zero
  Serial.println(value);
}