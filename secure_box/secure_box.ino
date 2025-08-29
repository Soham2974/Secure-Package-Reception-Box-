/*
 * 📦 Secure Package Reception Box - Base Code
 *
 * ⚠️ Disclaimer:
 * This code is generated with the help of AI (ChatGPT) and is meant 
 * as a **reference / learning implementation** for academic use only.
 * Users must modify pin mappings, thresholds, and hardware configs 
 * according to their actual STM32 board setup.
 *
 * Semester V Mini Project (AY 2024-25)
 * Don Bosco Institute of Technology, Mumbai
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// ---------------- Pin Configurations ----------------
// Adjust these pins based on your STM32 variant
#define LED_RED   PA15     // Red LED for error/lock
#define LED_GREEN PA13     // Green LED for success/unlock
#define IR_SENSOR A0       // IR sensor input pin
#define SERVO_PIN D10      // Servo motor pin

// GSM Module → Use Serial1 (PA9=TX, PA10=RX on STM32 Blue Pill/Nucleo)
// Change pins if using another STM32 board
#define sim800L Serial1    

// ---------------- LCD Setup ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD (check address with scanner)

// ---------------- Keypad Setup ----------------
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = { D9, D8, D7, D6 };   // Adjust STM32 pins
byte colPins[COLS] = { D5, D4, D3, D2 };   // Adjust STM32 pins
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// ---------------- Servo Setup ----------------
Servo doorServo;

// ---------------- Variables ----------------
String generatedOTP = "";
String userOTP = "";
const String userPhone = "+91XXXXXXXXXX";   // Change to recipient number
unsigned long otpStartTime = 0;
const unsigned long OTP_TIMEOUT = 30000;    // 30 sec timeout for OTP

// ====================================================
// Setup
// ====================================================
void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(IR_SENSOR, INPUT);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);   // Green ON = Locked state

  // LCD Init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Box Locked");

  // GSM Init
  sim800L.begin(9600);

  // Servo Init
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);  // Locked position

  // Random Seed for OTP
  randomSeed(analogRead(A1));

  // Debug on USB Serial
  Serial.begin(9600);
  Serial.println("System Initialized...");
}

// ====================================================
// Loop
// ====================================================
void loop() {
  if (digitalRead(IR_SENSOR) == HIGH) {
    Serial.println("Person detected!");
    
    // Generate OTP and send SMS
    generatedOTP = generateOTP();
    sendSMS(userPhone, "Box OTP: " + generatedOTP);
    Serial.println("Generated OTP: " + generatedOTP);

    lcd.clear(); 
    lcd.setCursor(0,0); 
    lcd.print("Enter OTP:");

    userOTP = "";
    otpStartTime = millis();

    // Wait for OTP input with timeout
    while (userOTP.length() < 4 && (millis() - otpStartTime < OTP_TIMEOUT)) {
      char key = customKeypad.getKey();
      if (key && isDigit(key)) {
        userOTP += key;
        lcd.setCursor(userOTP.length()-1, 1); 
        lcd.print("*");
      }
    }

    // OTP verification
    if (userOTP.equals(generatedOTP)) {
      Serial.println("Correct OTP!");
      lcd.clear(); lcd.setCursor(0,0); lcd.print("OTP Correct!");
      openBoxSequence();
      sendSMS(userPhone, "Package Delivered. Box locked.");
    } else {
      Serial.println("Wrong OTP or Timeout!");
      lcd.clear(); lcd.setCursor(0,0); lcd.print("Access Denied!");
      sendSMS(userPhone, "Access denied - Wrong OTP/Timeout.");
    }

    delay(3000);
    lcd.clear(); lcd.setCursor(0,0); lcd.print("Box Locked");
  }
}

// ====================================================
// Helper Functions
// ====================================================

// Generate 4-digit random OTP
String generateOTP() {
  int val = random(0, 10000);
  char buf[5];
  sprintf(buf, "%04d", val);
  return String(buf);
}

// Send SMS using SIM800L
void sendSMS(String number, String text) {
  sim800L.println("AT+CMGF=1");  
  delay(500);
  sim800L.print("AT+CMGS=\"");  
  sim800L.print(number);
  sim800L.println("\"");
  delay(500);
  sim800L.print(text);
  delay(200);
  sim800L.write(26);   // Ctrl+Z to send
  delay(3000);
}

// Unlock box for 5 seconds, then lock again
void openBoxSequence() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);

  doorServo.write(90);   // Unlock
  delay(5000);           // Wait 5 sec for delivery
  doorServo.write(0);    // Lock again

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
}
