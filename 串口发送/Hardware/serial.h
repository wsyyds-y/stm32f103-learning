#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>


int fputc(int ch,FILE *f);
void serial_send (uint8_t *data,uint16_t size);

void serial_init (void);

#endif 



