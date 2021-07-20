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

//
// LOGIC ANALYSER PROBE - using Pico as Probe
//

#include "pio.h"
#include "storage.h"
#include "logic_probe.h"
#include "probe_controls.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

struct probe_controls probecontrols;

void probe_init() {
    probecontrols.state = STATE_IDLE;
}

void probe_writestate() {
    printf("%i\n", probecontrols.state);
    puts("Y");
}

void probe_go(char* cmdbuffer) {
    if (probecontrols.state != STATE_IDLE) {
        printf("N Bad state - expecting STATE_IDLE(0) - was %i\n", probecontrols.state);
        return; 
    }
    if (!parse_control_parameters(&probecontrols, cmdbuffer) ) {
        printf("N command parse failure - testcount=%i - cmd=%s\n",getTestnumber(),getCmd());
        return; 
    }
    storage_init(&probecontrols);
    pio_init(&probecontrols);
    pio_arm();
    storage_arm();
    //storage_waituntilcompleted();
    probecontrols.state = STATE_SAMPLING;
    puts("Y");
}

void probe_stop() {
    if (probecontrols.state != STATE_SAMPLING) {
        printf("N Bad state - expecting STATE_SAMPLING(1) - was %i\n", probecontrols.state);
        return;
    }
    // needs to do stop action ; let the real stop change status
    //  *********for debug purposes - do the state change here *******
    probecontrols.state = STATE_SAMPLING_DONE; 
    puts("Y");
}

void probe_writesample() {
    if (probecontrols.state != STATE_SAMPLING_DONE) {
        printf("N Bad state - expecting STATE_SAMPLING_DONE(2) - was %i\n", probecontrols.state);
        return;
    }
    puts(get_RLE_encoded_sample(probecontrols.pinbase));
    puts("Y");
    probecontrols.state = STATE_IDLE;
}
