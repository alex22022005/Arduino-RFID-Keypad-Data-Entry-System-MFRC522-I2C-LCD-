#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the address to 0x27 or 0x3F based on your LCD

// Keypad
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Initialize serial communications with the computer
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID");
  
  // Initialize RFID
  SPI.begin();      
  mfrc522.PCD_Init();   
  
  // Initialize keypad
  lcd.setCursor(0, 1);
  lcd.print("Enter Details");
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RFID Detected");

    // Read RFID
    String rfid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfid += String(mfrc522.uid.uidByte[i], HEX);
    }

    lcd.setCursor(0, 1);
    lcd.print("ID: " + rfid);
    delay(2000); // Display RFID for 2 seconds
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Details:");
    
    // Manual entry using keypad
    String details = "";
    while (true) {
      char key = keypad.getKey();
      if (key) {
        if (key == '#') break; // Finish entry
        details += key;
        lcd.setCursor(0, 1);
        lcd.print(details);
      }
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ID: " + rfid);
    lcd.setCursor(0, 1);
    lcd.print("Data: " + details);
    
    delay(5000); // Display result for 5 seconds
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scan RFID");
    lcd.setCursor(0, 1);
    lcd.print("Enter Details");
  }
}
