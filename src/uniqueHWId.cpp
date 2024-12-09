/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <Arduino_SHA256.h>
#include <Arduino_HEX.h>
#include "uniqueHWId.h"

bool UniqueHWId::begin() {
    _init =_sId.begin() && _nId.begin();
    return _init;
}

bool UniqueHWId::get(uint8_t* in, uint32_t size) {
    if (_init == false || size < BOARD_PROVISIONING_ID_SIZE) {
        return false;
    }
    uint8_t offset = 0;
    if (!microId::get(&in[offset], size)) {
        return false;
    }
    offset += UC_UID_SIZE;
    if (!_nId.get(&in[offset], size - offset)) {
        return false;
    }
    offset += NETWORK_ID_SIZE;
    if (!_sId.get(&in[offset], size - offset)) {
        return false;
    }
    return true;
}

String UniqueHWId::get() {
    uint8_t data[BOARD_PROVISIONING_ID_SIZE];
    if (!get(data, sizeof(data))) {
        return String("");
    }
    uint8_t out[SHA256_DIGEST_SIZE];
    SHA256::sha256(data, sizeof(data), out);
    return THEXT::encode(out, sizeof(out));
}

