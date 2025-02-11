/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#if   defined(ARDUINO_NANO_RP2040_CONNECT) || \
      defined(ARDUINO_SAMD_MKRWIFI1010)    || \
      defined(ARDUINO_SAMD_NANO_33_IOT)    || \
      defined(ARDUINO_PORTENTA_H7_M7)      || \
      defined(ARDUINO_NICLA_VISION)        || \
      defined(ARDUINO_GIGA)
    #include <WiFi.h>
    #define NETWORK_ID_SIZE WL_MAC_ADDR_LENGTH
#elif defined(ARDUINO_SAMD_MKRNB1500)
    #include <MKRNB.h>
    /* We don't take in account Luhn check digit */
    #define NETWORK_ID_SIZE 7
#elif defined(ARDUINO_SAMD_MKRGSM1400)
    #include <MKRGSM.h>
    /* We don't take in account Luhn check digit */
    #define NETWORK_ID_SIZE 7
#elif defined(ARDUINO_SAMD_MKRWAN1300) || \
      defined(ARDUINO_SAMD_MKRWAN1310)
    #include <MKRWAN.h>
    #define NETWORK_ID_SIZE 8
#elif defined(ARDUINO_PORTENTA_C33)
    #include <WiFiC3.h>
    #define NETWORK_ID_SIZE WL_MAC_ADDR_LENGTH
#elif defined(ARDUINO_UNOR4_WIFI)
    #include <WiFi.h>
    #define NETWORK_ID_SIZE 6
#elif defined(ARDUINO_OPTA)
    #include <Ethernet.h>
    #define NETWORK_ID_SIZE 6
#else
    #define NETWORK_ID_SIZE 0
#endif

/*
 * This class contains the methods to get board network Id
 * ARDUINO_NANO_RP2040_CONNECT: reversed
 * ARDUINO_SAMD_MKRWIFI1010: reversed
 * ARDUINO_SAMD_NANO_33_IOT: reversed
 * ARDUINO_PORTENTA_H7_M7: WiFi.setTimeout(0);WiFi.begin("In33dm4c4ddr35", "In33dm4c4ddr35", ENC_TYPE_TKIP) reversed
 * ARDUINO_NICLA_VISION:
 * ARDUINO_GIGA:
 * ARDUINO_PORTENTA_C33: Interface.begin() not reversed
 * ARDUINO_UNOR4_WIFI: not reversed
 * ARDUINO_OPTA: Ethernet.begin(NULL,0,0); reversed
 */
class networkId {

public:
    bool begin();
    bool get(uint8_t *in, uint32_t size);

private:
#if   defined(ARDUINO_SAMD_MKRNB1500)
    NBModem _modem;
#elif defined(ARDUINO_SAMD_MKRGSM1400)
    GSMModem _modem;
#elif defined(ARDUINO_SAMD_MKRWAN1300) || \
      defined(ARDUINO_SAMD_MKRWAN1310)
    LoRaModem _modem;
#endif
};
