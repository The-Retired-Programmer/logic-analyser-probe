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

#ifndef _DIGITALSAMPLING_H
#define _DIGITALSAMPLING_H

#include "probe_controls.h"

char* digitalsampling_start(struct probe_controls* probecontrols);

void digitalsampling_teardown();

void digitalsampling_stop();

bool is_digitalsampling_finished();

struct sample_buffers {
    uint32_t buffer_size_words;
    uint32_t *buffers[4];
    uint number_of_buffers;
    uint earliest_valid_buffer;
    uint valid_buffer_count;
    volatile bool sampling_done;
};

struct sample_buffers *getsamplebuffers();

#ifdef TESTINGBUILD

char* setuptransferbuffers(struct probe_controls* controls);

void teardowntransferbuffers();

#endif

#endif
