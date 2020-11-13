/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
 */

#ifndef __BLE_BUTTON_SERVICE_H__
#define __BLE_BUTTON_SERVICE_H__

class ButtonService {
public:
    const static uint16_t BUTTON_SERVICE_UUID              = 0xA000;
    const static uint16_t BUTTON_STATE_CHARACTERISTIC_UUID = 0xA001;
    const static uint16_t LED_SERVICE_CHAR_UUID = 0xA010;

    ButtonService(BLE &_ble, bool buttonPressedInitial) :
        ble(_ble), buttonState(BUTTON_STATE_CHARACTERISTIC_UUID, &buttonPressedInitial, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        GattCharacteristic *charTable[] = {&buttonState};
        GattCharacteristic *charTable2[] = {&LED_state};
        GattService         buttonService(ButtonService::BUTTON_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
        GattService LED_service(ButtonService::BUTTON_SERVICE_UUID,charTable2, sizeof(charTable2/sizeof(GattCharacteristic *)));
        ble.gattServer().addService(buttonService);
        ble.gattServer().addService(LED_service);
    }

    GattAttribute::Handle_t getValueHandle() const
    {
        return LED_state.getValueHandle();
    }

    void updateButtonState(bool newState) {
        ble.gattServer().write(buttonState.getValueHandle(), (uint8_t *)&newState, sizeof(bool));
        
    }

    void control_LED(){
        ble.gattServer().required()
    }

private:
    BLE                              &ble;
    ReadOnlyGattCharacteristic<bool>  buttonState;
    ReadWriteGattCharacteristic<bool> LED_state;
};

#endif /* #ifndef __BLE_BUTTON_SERVICE_H__ */
