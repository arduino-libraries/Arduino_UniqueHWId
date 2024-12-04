/*
    This file is part of the Arduino_HWUniqueId library.

    Copyright (c) 2024 Arduino SA

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <Arduino_HWUniqueId.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  HWUniqueId Id;
  if(Id.begin()) {
    Serial.println(Id.get());
  } else {
    Serial.println("cannot get board hardware unique Id");
  }

}

void loop() {
}
