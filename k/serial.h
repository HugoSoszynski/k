#ifndef SERIAL_H_
#define SERIAL_H_

/*
 * Serial driver definition
 * 8250 UART
 */

#define _COM1 0x3F8

#define _LCR _COM1 + 3

#define _DLL _COM1
#define _DLM _COM1 + 1

#define _IER _COM1 + 1

#define _FCR _COM1 + 2

#define _THR _COM1

void init_serial();
int write(const char* buf, unsigned long count);

#endif /* !SERIAL_H_ */