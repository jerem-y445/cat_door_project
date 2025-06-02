#include "CatDoorNFC.h"

CatDoorNFC::CatDoorNFC(HardwareSerial &serial, uint8_t rxPin, uint8_t txPin)
    : pnSerial(serial), rx(rxPin), tx(txPin) {
    pn532hsu = new PN532_HSU(pnSerial);
    nfc = new PN532(*pn532hsu);
}

void CatDoorNFC::begin() {
    pnSerial.begin(115200, SERIAL_8N1, rx, tx);
    nfc->begin();

    uint32_t versiondata = nfc->getFirmwareVersion();
    if (!versiondata) {
        Serial.println("PN532 not detected. Check connections.");
        while (1);
    }

    Serial.println("PN532 ready.");
    nfc->SAMConfig();
}

bool CatDoorNFC::isCatDetected() {
    uint8_t uid[7];
    uint8_t uidLength;

    if (nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
        lastUID = formatUID(uid, uidLength);
        Serial.print("Detected UID: ");
        Serial.println(lastUID);
        return lastUID == catTagID;
    }

    return false;
}

String CatDoorNFC::getLastUID() {
    return lastUID;
}

String CatDoorNFC::formatUID(uint8_t *uid, uint8_t length) {
    String formatted = "";
    for (uint8_t i = 0; i < length; i++) {
        if (uid[i] < 0x10) formatted += "0";
        formatted += String(uid[i], HEX);
        if (i != length - 1) formatted += ":";
    }
    formatted.toUpperCase();
    return formatted;
}
