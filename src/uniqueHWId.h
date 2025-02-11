/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "microId.h"
#include "networkId.h"
#include "secureId.h"

/*
 * This class contains the methods to get board hardware unique id
 */
class UniqueHWId {

public:
    static constexpr int BOARD_PROVISIONING_ID_SIZE  = UC_UID_SIZE +
                                                       NETWORK_ID_SIZE +
                                                       CRYPTO_SN_SIZE;

    bool begin();
    bool get(uint8_t* in, uint32_t size);
    String get();

private:
    secureId _sId;
    networkId _nId;
    bool _init;
};
