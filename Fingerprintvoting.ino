#include <LiquidCrystal.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define PB1 A0  //Candidate 1
#define PB2 A1  //Candidate 2
#define PB3 A2  //Candidate 3
#define PB4 A3  //Candidate 4
#define PB5 A4  //Check Status

#define buzzer 4
#define voice_playback 5

int a = 0, b = 0, c = 0, d = 0;
int a1 = 0, b1 = 0, c1 = 0, d1 = 0;

void setup() {
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  pinMode(PB5, INPUT_PULLUP);

  pinMode(voice_playback, OUTPUT);
  digitalWrite(voice_playback, HIGH);
  
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" Voting System  ");
}

void loop() {
  if (Serial.available() > 0) {
    char signal = Serial.read();
    
    if (signal == 'F') { 
      finger.begin(57600); 
      int fingerprintID = getFingerprintID(); 

      if (fingerprintID >= 1 && fingerprintID <= 4) {
        Serial.println("Fingerprint Access Granted");

        lcd.setCursor(0, 1);
        lcd.print("                ");
        delay(100);
        
        if(fingerprintID == 1) {
          lcd.print("Mughuntha Granted");
          a1++;
        } else if(fingerprintID == 2) {
          lcd.print(" Harish Granted ");
          b1++;
        } else if(fingerprintID == 3) {
          lcd.print("Sai Akash Granted");
          c1++;
        } else if(fingerprintID == 4) {
          lcd.print("Nithish Granted ");
          d1++;
        }

        if ((a1 >= 2) || (b1 >= 2) || (c1 >= 2) || (d1 >= 2)) {
          digitalWrite(buzzer, HIGH);
          lcd.setCursor(0, 1);
          lcd.print(" Already Voted  ");
          delay(2000);
          digitalWrite(buzzer, LOW);
          lcd.setCursor(0, 1);
          lcd.print("                ");
          delay(100);
        } else {
          handleVoting(fingerprintID);
        }
      }
    } 
    // Handle other cases like checking status, etc.
  }
  delay(500);
}

void handleVoting(int fingerprintID) {
  int voteCount = 0;
  
  while (1) {
    if (digitalRead(PB1) == LOW) {
      a++;
      voteCount++;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      lcd.setCursor(0, 1);
      lcd.print("Voted Successfully");
      sendMessage(fingerprintID);
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      break;
    } else if (digitalRead(PB2) == LOW) {
      b++;
      voteCount++;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      lcd.setCursor(0, 1);
      lcd.print("Voted Successfully");
      sendMessage(fingerprintID);
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      break;
    } else if (digitalRead(PB3) == LOW) {
      c++;
      voteCount++;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      lcd.setCursor(0, 1);
      lcd.print("Voted Successfully");
      sendMessage(fingerprintID);
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      break;
    } else if (digitalRead(PB4) == LOW) {
      d++;
      voteCount++;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      lcd.setCursor(0, 1);
      lcd.print("Voted Successfully");
      sendMessage(fingerprintID);
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(100);
      break;
    }
  }

  if (voteCount >= 2) {
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print(" Already Voted  ");
    delay(2000);
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(100);
  }
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  return finger.fingerID;
}

void sendMessage(int fingerprintID) {
  // Implement your message sending functionality here
  // Use fingerprintID to determine which candidate voted and send the appropriate message
}

void message1(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+917358341347");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Mughuntha Voted Successfully'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}

void message2(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+917200030070");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Harish Voted Successfully'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}

void message3(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+916381772850");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Sai Akash Voted Successfully'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}

void message4(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+918248836046");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Nithish Voted Successfully'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}

void message5(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+917358341347");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Mughuntha - You havent Voted'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}

void message6(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+917200030070");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Harish - You havent Voted'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}

void message7(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+916381772850");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Sai Akash - You havent Voted'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}

void message8(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("+918248836046");delay(500);//Change the calling number
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Nithish - You havent Voted'\r\n");delay(500);//17
  delay(500);
  Serial.write((char)26);
}
