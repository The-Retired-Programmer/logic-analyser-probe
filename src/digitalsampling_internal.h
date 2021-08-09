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

//data capture
bool setuptransferbuffers(struct probe_controls* controls);
bool setupDMAcontrollers(struct probe_controls* controls, const volatile uint32_t *readaddress, uint dreq);
void dma_irq_handler();
void storage_waituntilcompleted();
bool setupPIOandSM(struct probe_controls* controls);
bool waitforstartevent(struct probe_controls* controls);
// testing only
char* geterrormessage();
// Run length encoding
void init_rle(uint maxdigits, uint _maxlinelength, void (*outputfunction)(const char *line));
void writetobuffer();
void rle_insertvalue(bool logic_value);
// testing only - Run Length encoding
char* get_linebuffer();