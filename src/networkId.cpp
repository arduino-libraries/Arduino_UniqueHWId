/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "networkId.h"

bool networkId::begin() {
#if   defined(ARDUINO_NANO_RP2040_CONNECT) || \
      defined(ARDUINO_SAMD_MKRWIFI1010)    || \
      defined(ARDUINO_SAMD_NANO_33_IOT)    || \
      defined(ARDUINO_PORTENTA_C33)        || \
      defined(ARDUINO_UNOR4_WIFI)
    WiFi.setTimeout(0);
    int result = WiFi.begin("In33dm4c4ddr35", "In33dm4c4ddr35");
    return (result != WL_NO_SHIELD) ? true : false;
#elif defined(ARDUINO_PORTENTA_H7_M7)      || \
      defined(ARDUINO_NICLA_VISION)        || \
      defined(ARDUINO_GIGA)
    WiFi.setTimeout(0);
    int result = WiFi.begin("In33dm4c4ddr35", "In33dm4c4ddr35", ENC_TYPE_TKIP);
    return ( result != WL_NO_SHIELD) ? true : false;
#elif defined(ARDUINO_OPTA)
    Ethernet.begin(NULL, 0, 0);
    return true;
#endif
}

bool networkId::get(uint8_t *in, uint32_t size) {
#if IFACE_MAC_ADDR_LENGTH == 0
    (void)in;
    (void)size;
    return false;
#else
    if (size < IFACE_MAC_ADDR_LENGTH) {
        return false;
    }
#if   defined(ARDUINO_NANO_RP2040_CONNECT) || \
      defined(ARDUINO_SAMD_MKRWIFI1010)    || \
      defined(ARDUINO_SAMD_NANO_33_IOT)    || \
      defined(ARDUINO_PORTENTA_C33)        || \
      defined(ARDUINO_UNOR4_WIFI)          || \
      defined(ARDUINO_PORTENTA_H7_M7)      || \
      defined(ARDUINO_NICLA_VISION)        || \
      defined(ARDUINO_GIGA)
    WiFi.macAddress(in);
#elif defined(ARDUINO_OPTA)
    Ethernet.MACAddress(in);
#endif
    return true;
#endif
}
