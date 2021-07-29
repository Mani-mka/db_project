void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(8, HIGH);
  digitalWrite(4, HIGH);
  delay(1000);

}
