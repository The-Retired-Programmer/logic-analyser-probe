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
// logical analyser - storage manager
//

void storage_init(uint samplesize, uint firstpin, uint pinspersample);

void storage_arm();

void storage_waituntilcompleted();

uint32_t *get_capturebuf(uint logicalindex);

uint get_capturebuf_size();

uint get_bufs_count();

char *get_RLE_encoded_sample(uint pin);