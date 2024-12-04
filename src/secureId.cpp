/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "secureId.h"
#include <Arduino_HEX.h>

bool secureId::begin() {
    return !!_se.begin();
}

bool secureId::get(uint8_t *in, uint32_t size) {
#if CRYPTO_SN_SIZE == 0
    (void)in;
    (void)size;
    return false;
#else
    if (size < CRYPTO_SN_SIZE) {
        return false;
    }
    if (!THEXT::decode((_se.serialNumber()).substring(0, CRYPTO_SN_SIZE*2), in, size)) {
        return false;
    }
    return true;
#endif
}
