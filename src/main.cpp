#include <Arduino.h>
#include <HardwareSerial.h>
#include <PN532_HSU.h>
#include <PN532.h>

// Use UART2 on ESP32: GPIO 16 (RX), GPIO 17 (TX)
HardwareSerial PNSerial(2); // UART2 instance
PN532_HSU pn532hsu(PNSerial);
PN532 nfc(pn532hsu);

// Tag IDs 
String tagID1 = "174.247.9.5"; // Card ID
String tagID2 = "151.246.176.1"; // Fob ID

void setup() {
  Serial.begin(115200); // Monitor2
  delay(1000); // Give time to connect to Serial
  Serial.println("Starting PN532 Test...");

  // Start UART2 for PN532 communication
  PNSerial.begin(115200, SERIAL_8N1, 16, 17); // RX=16, TX=17

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Didn't find PN53x module. Check wiring and interface.");
    while (1); // Halt
  }

  // Successfully connected
  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware Version: ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print(".");
  Serial.println((versiondata >> 8) & 0xFF, DEC);

  nfc.SAMConfig();
  Serial.println("PN532 initialized and ready.");
}

void loop() {
  Serial.println("Waiting for an ISO14443A card...");
  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("Found a card!");
    Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(uid[i], HEX);
      if (i != uidLength - 1) Serial.print(":");
    }
    Serial.println();
    delay(2000); // Wait before next read
  } else {
    Serial.println("No card detected.");
    delay(1000);
  }
}
