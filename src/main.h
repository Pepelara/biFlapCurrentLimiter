/*   
   Copyright 2025 Pepelara

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#ifndef _MAIN_H_
#define _MAIN_H_

void main(void);
void delay_msp(__data uint16_t ms);
uint16_t adc_read(uint8_t channel);

SFR(T2H, 			0xD6);
SFR(T2L, 			0xD7);

SFR(CL, 			0xE9);
SFR(CH, 			0xF9);

SFR(CCAPM2, 		0xDC);
SFR(PCA_PWM2, 		0xF4);
SFR(CCAP2L,			0xEC);
SFR(CCAP2H,			0xFC);

SFR(CCAPM0, 		0xDA);
SFR(PCA_PWM0, 		0xF2);
SFR(CCON,			0xD8);
SFR(CMOD,			0xD9);
SFR(CCAP0L,			0xEA);
SFR(CCAP0H,			0xFA);

#endif
