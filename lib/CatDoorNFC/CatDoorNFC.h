#ifndef CATDOORNFC_H
#define CATDOORNFC_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <PN532_HSU.h>
#include <PN532.h>

class CatDoorNFC {
public:
    CatDoorNFC(HardwareSerial &serial, uint8_t rxPin, uint8_t txPin);
    void begin();
    bool isCatDetected(); // Returns true if cat's tag is detected
    String getLastUID();  // Returns last read UID in string format

private:
    PN532_HSU *pn532hsu;
    PN532 *nfc;
    HardwareSerial &pnSerial;
    uint8_t rx, tx;
    String catTagID = "97:F6:B0:1"; // Cat's Tag ID
    String formatUID(uint8_t *uid, uint8_t length);

    String lastUID = "";
};

#endif
