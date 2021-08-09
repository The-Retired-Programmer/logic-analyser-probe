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
// test - logical analyser/digitalsampling
//
#include "../src/probe_controls.h"

void test_digitalsampling_init();

// internal
void test_digitalsampling_rle_internals();
void rlelinereceiver(const char *line);
void rlelinereceiverunused(const char *line);
void rlelinereceiver9chars(const char *line);

void test_digitalsampling_dma_internals();
char* setup_controls(struct probe_controls* controls, char * cmd);