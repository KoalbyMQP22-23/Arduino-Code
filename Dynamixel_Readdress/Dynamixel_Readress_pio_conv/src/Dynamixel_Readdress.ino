/*******************************************************************************
 * Copyright 2016 ROBOTIS CO., LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#include <DynamixelShield.h>

#define DEBUG_SERIAL Serial2

const uint8_t DEFAULT_DXL_ID = 0x01;
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;

// This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup()
{
  delay(1000);
  // put your setup code here, to run once:
  uint8_t present_id = DEFAULT_DXL_ID;
  uint8_t new_id = 0;

  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  while (!DEBUG_SERIAL)
    ;

  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(115200);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.print("PROTOCOL ");
  DEBUG_SERIAL.print(DXL_PROTOCOL_VERSION, 1);
  DEBUG_SERIAL.print(", ID ");
  DEBUG_SERIAL.print(present_id);
  DEBUG_SERIAL.print(": ");
  if (dxl.ping(present_id) == true)
  {
    DEBUG_SERIAL.print("ping succeeded!");
    DEBUG_SERIAL.print(", Model Number: ");
    DEBUG_SERIAL.println(dxl.getModelNumber(present_id));

    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(present_id);

    // set a new ID for DYNAMIXEL. Do not use ID 200
    new_id = 0x07;
    if (dxl.setID(present_id, new_id) == true)
    {
      present_id = new_id;
      DEBUG_SERIAL.print("ID has been successfully changed to ");
      DEBUG_SERIAL.println(new_id);
    }
    else
    {
      DEBUG_SERIAL.print("Failed to change ID to ");
      DEBUG_SERIAL.println(new_id);
    }
  }
  else
  {
    DEBUG_SERIAL.println("ping failed!");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}
