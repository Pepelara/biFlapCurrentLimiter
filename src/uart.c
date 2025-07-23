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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stc12.h>
#include <stdlib.h>

#include "uart.h"




void uart_puts(char *str)
{
    uint8_t i = 0;
    while(1) {
        SBUF = str[i++];
        while ((SCON & (1<<1)) == 0); //Wait until transmit complete;
        SCON &= ~(1<<1); //clear TI
        if(str[i] == 0) break;
    }
}

void uart_putc(char chr)
{
    SBUF = chr;
    while ((SCON & (1<<1)) == 0); //Wait until transmit complete;
    SCON &= ~(1<<1); //clear TI
}

void uart_put(uint8_t *data, int len)
{
    uint8_t i = 0;
    while(len--) {
        SBUF = data[i++];
        while ((SCON & (1<<1)) == 0); //Wait until transmit complete;
        SCON &= ~(1<<1); //clear TI
        if(data[i] == 0) break;
    }
}

char uart_getc(void)
{
    while(RI == 0);
    RI = 0;
    return SBUF;
}


void uart_gets(char *str, uint8_t maxlen)
{
    uint8_t i = 0;
    do{
        str[i] = uart_getc();
    }while((str[i++] != 0x0D) && (i < maxlen));
}
