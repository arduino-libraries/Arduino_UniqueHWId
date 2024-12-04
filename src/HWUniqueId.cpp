/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <Arduino_SHA256.h>
#include <Arduino_HEX.h>
#include "HWUniqueId.h"

bool HWUniqueId::begin() {
    _init =_sId.begin() && _nId.begin();
    return _init;
}

bool HWUniqueId::get(uint8_t* in, uint32_t size) {
    if (_init == false || size < BOARD_PROVISIONING_ID_SIZE) {
        Serial.println("BOARD_PROVISIONING_ID_SIZE ERROR");
        return false;
    }
    uint8_t offset = 0;
    if (!microId::get(&in[offset], size)) {
        Serial.println("microId ERROR");
        return false;
    }
    offset += UC_UID_SIZE;
    if (!_nId.get(&in[offset], size - offset)) {
        Serial.println("networkId ERROR");
        return false;
    }
    offset += IFACE_MAC_ADDR_LENGTH;
    if (!_sId.get(&in[offset], size - offset)) {
        Serial.println("secureId ERROR");
        return false;
    }
    return true;
}

String HWUniqueId::get() {
    uint8_t data[BOARD_PROVISIONING_ID_SIZE];
    if (!get(data, sizeof(data))) {
        return String("");
    }
    uint8_t out[SHA256_DIGEST_SIZE];
    SHA256::sha256(data, sizeof(data), out);
    return THEXT::encode(out, sizeof(out));
}

