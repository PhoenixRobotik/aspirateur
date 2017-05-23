#include "bumper.h"


// InterruptSubscriber EXTI5_to_9_interrupt(&InterruptEXTI5_to_9,
//     &EXTI5_to_9_interrupt_handler);

// InterruptSubscriber EXTI10_to_15_interrupt(&InterruptEXTI10_to_15,
//     &EXTI10_to_15_interrupt_handler);

// EXTI5_to_9_interrupt.subscribe();
// EXTI10_to_15_interrupt.subscribe();


// need to do gpio_name.enable_irq()

void EXTI5_to_9_interrupt_handler() {
	// verifier si la pin en question a effectivement changé d'état
	// + ACK irq
}

void EXTI10_to_15_interrupt_handler() {
	// verifier si la pin en question a effectivement changé d'état
	// + ACK irq
}
