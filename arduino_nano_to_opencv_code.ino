String msg = "";

//#define serial

#define relay 2

void readSerialPort()
{
  msg = "";
 
  if (Serial.available()) {
      delay(10);
      while (Serial.available() > 0) {
          msg += (char)Serial.read();
      }
      Serial.flush();
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH);
}

void loop()
{
  readSerialPort();

  if (msg == "a")
  {
    digitalWrite(relay, LOW);

    delay(60000);

    digitalWrite(relay, HIGH);

    delay(5000);    
  }
}
