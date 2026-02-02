#ifndef keyboard_h
#define keyboard_h

#define k_PORT PORTA

#define k_R1 5
#define k_R2 6
#define k_R3 7
#define k_R4 8

#define k_C1 9
#define k_C2 10
#define k_C3 11
#define k_C4 12

void k_init(void);
char k_read(void);

#endif