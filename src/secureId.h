/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#if   defined(ARDUINO_NANO_RP2040_CONNECT) || \
      defined(ARDUINO_SAMD_NANO_33_IOT)    || \
      defined(ARDUINO_SAMD_MKRWIFI1010)    || \
      defined(ARDUINO_SAMD_MKRGSM1400)     || \
      defined(ARDUINO_SAMD_MKRWAN1300)     || \
      defined(ARDUINO_SAMD_MKRWAN1310)     || \
      defined(ARDUINO_SAMD_MKRNB1500)      || \
      defined(ARDUINO_SAMD_MKR1000)        || \
      defined(ARDUINO_PORTENTA_H7_M7)      || \
      defined(ARDUINO_OPTA)                || \
      defined(ARDUINO_GIGA)
    #include <Arduino_SecureElement.h>
    #define CRYPTO_SN_SIZE 9
#elif defined(ARDUINO_PORTENTA_C33)        || \
      defined(ARDUINO_NICLA_VISION)
    #include <Arduino_SecureElement.h>
    #define CRYPTO_SN_SIZE 18
#elif defined(ARDUINO_UNOR4_WIFI)
    #include <Arduino_SecureElement.h>
    #define CRYPTO_SN_SIZE 6
#else
    #define CRYPTO_SN_SIZE 0
#endif

/*
 * This library contains the methods to get crypto serial number
 */
class secureId {

public:
    bool begin();
    bool get(uint8_t *in, uint32_t size);

private:
    SecureElement _se;
};
