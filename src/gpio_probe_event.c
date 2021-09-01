 /**
 * Copyright 2021 Richard Linsdale (richard at theretiredprogrammer.uk).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// =========================================================================
//
//  LOGIC PROBE - Digital Sampling Events  using GPIO for event capture
//
//   events are used to terminate the digital sampling.
//
// =========================================================================

#include <stdlib.h>
#include "hardware/gpio.h"
#include "probe_controls.h"
#include "gpio_probe_event_internal.h"

enum gpio_irq_level gpioirq;
bool event_triggered;
uint pin;
bool enabled;

void gpio_probe_event_init(struct probe_controls* controls) {
    event_triggered = false;
    pin = controls->ev_pin;
    enabled = controls->ev_enabled;
    if (enabled) {
        gpio_set_irq_enabled(pin, 0, false);
        gpio_init(pin);
        switch (controls->ev_trigger) {
        case TRIGGER_ON_LOW:
            gpioirq =  GPIO_IRQ_LEVEL_LOW;
            break;
        case TRIGGER_ON_HIGH:
            gpioirq =  GPIO_IRQ_LEVEL_HIGH;
            break;
        case TRIGGER_ON_FALL:
            gpioirq =  GPIO_IRQ_EDGE_FALL ;
            break;
        case TRIGGER_ON_RISE:
            gpioirq =  GPIO_IRQ_EDGE_RISE;
            break;
        }
    }
}

void gpio_probe_event_start() {
    if (enabled) {
        gpio_set_irq_enabled_with_callback(pin, gpioirq, true, &gpio_callback);
    }
}

void gpio_callback(uint pin, uint32_t events) {
    event_triggered = true;
    gpio_set_irq_enabled(pin, gpioirq, false);
    gpio_acknowledge_irq(pin, events);
}

bool has_event_triggered() {
    return event_triggered;
}

