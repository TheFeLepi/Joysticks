void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
pinMode(A6,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
Serial.begin(96000);
}

void loop() {
  Serial.print("____A6=");
  Serial.print(analogRead(A6));
  Serial.print("____A2=");
  Serial.print(analogRead(A2));
  Serial.print("____A1=");
  Serial.print(analogRead(A1));
  Serial.print("____A0=");
  Serial.print(analogRead(A0));
  Serial.print("____A9=");
  Serial.print(analogRead(A9));
  Serial.println();
  delay(200);


}
