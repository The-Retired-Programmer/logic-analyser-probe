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
// Logic Analyser -  frontend command handling
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "logic_probe.h"
#include "hardware/watchdog.h"

char linebuffer[200];
char *insertchar;

char messagebuffer[256];

static void force_reset() {
    watchdog_enable(10, true);
    while(1);
}

static int ack_puts() {
    puts("Y");
}

static int nak_puts(char *response) {
    printf("N %s\n", response);
}

static void _action_command(char *line) {
    switch (line[0]) {
    case 'p': 
        probe_ping();
        break;
    case 'f': 
        probe_flash(line);
        break;
    case 'w': 
        probe_waveform(line);
        break;
    case '?': 
        probe_getstate();
        break;
    case 'g':
        probe_go(line);
        break;
    case 's': 
        probe_stop();
        break;
    case 'd':
        probe_getsample();
        break;
    default: // unknown command
        sprintf(messagebuffer, "Unknown command %s\n",line);
        nak_puts(messagebuffer);
    }
}

static bool linebuilder() {
    while (true) {
        int rawch = getchar_timeout_us(0);
        if (rawch ==  PICO_ERROR_TIMEOUT) {
            return false;
        }
        char ch = (char) rawch;
        if (ch == '!' ) {
            force_reset();
        }
        if (ch == '\n' || ch == '\r') {
            *insertchar='\0';
            return true;
        }
        if (ch>= '\x20' && ch <= '\x7e') {
            *insertchar++ = ch;
        }
    }
}

// =============================================================================
//
// module API
//
// =============================================================================

void frontend_commands_controller_init() {
    insertchar = linebuffer;
    probe_init(puts,ack_puts, nak_puts);
}

void frontend_commands_controller() {
    if (linebuilder()) {
        _action_command(linebuffer);
        insertchar = linebuffer;
    }
}

#ifdef TESTINGBUILD

void action_command(char *line) {
    _action_command(line);
}

#endif

