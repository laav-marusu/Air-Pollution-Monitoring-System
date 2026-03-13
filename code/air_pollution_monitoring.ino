#define BLYNK_TEMPLATE_ID "TMPL3tYcoAte7"
#define BLYNK_TEMPLATE_NAME "AIR POLUTION MONITORING SYSTEM "
#define BLYNK_AUTH_TOKEN "CkaQfSQtc8zpigMBu53wQwjLDYWxI7ma"

#define BLYNK_PRINT Serial

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>

// LCD setup (I2C address and dimensions)
LiquidCrystal_I2C lcd(0x27, 20, 4); // Change 0x27 if your LCD has a different I2C address

// Pin Definitions
const int mq2Pin = 34;      // MQ-2 analog output connected to GPIO34
const int mq135Pin = 35;    // MQ-135 analog output connected to GPIO35
const int buzzerPin = 15;   // Buzzer connected to GPIO13 (adjust as needed)

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize the LCD
    lcd.init();
    lcd.backlight();
    
    // Initialize Blynk with Wi-Fi credentials
    Blynk.begin(BLYNK_AUTH_TOKEN, "Sunny", "sunny123");

    // Display initial message
    lcd.setCursor(0, 0);
    lcd.print("Gas Monitoring");
    delay(2000); // Show for 2 seconds

    // Set up buzzer pin
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW); // Ensure buzzer is off initially
}

void loop() {
    // Run Blynk process
    Blynk.run();

    // Read and process MQ-2 sensor data
    int mq2PPM = analogRead(mq2Pin);
    
    // Read and process MQ-135 sensor data
    int mq135AQI = analogRead(mq135Pin);
    
    // Clear the LCD for new data
    lcd.clear();
    
    // Display MQ-2 PPM on the LCD
    lcd.setCursor(0, 0);
    lcd.print("MQ-2 PPM: ");
    lcd.print(mq2PPM);
    
    // Display MQ-135 Air Quality Index on the LCD
    lcd.setCursor(0, 1);
    lcd.print("MQ-135 AQI: ");
    lcd.print(mq135AQI);
    
    // Send sensor values to Blynk
    Blynk.virtualWrite(V0, mq2PPM);
    Blynk.virtualWrite(V1, mq135AQI);

    // Print values to Serial Monitor for debugging
    Serial.print("MQ-2 PPM: ");
    Serial.print(mq2PPM);
    Serial.print(" | MQ-135 AQI: ");
    Serial.println(mq135AQI);

    // Check if MQ-2 PPM exceeds threshold and activate buzzer if true
    if (mq2PPM >= 30) {
        digitalWrite(buzzerPin, HIGH); // Turn on buzzer
    } else {
        digitalWrite(buzzerPin, LOW);  // Turn off buzzer
    }

    // Wait before the next reading
    delay(1000);
}
