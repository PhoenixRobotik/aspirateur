#include "board_kiwi.h"

#include <stdint.h>


void CAN_Rx1_interrupt_handler(void) {

    kiwi->activeLed.toggle();
    uint32_t id;
    uint8_t message[8];
    uint8_t length;
    kiwi->canBus.receive(&id, message, &length);
}

// InterruptSubscriber CAN_Rx1_interrupt(&InterruptCANRx1,
//     &CAN_Rx1_interrupt_handler);

// CAN_Rx1_interrupt.provider->setPriority(0);
// CAN_Rx1_interrupt.subscribe();
