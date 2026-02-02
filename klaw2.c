#include "MKL05Z4.h"
#include "klaw2.h"

char k_tab[4][4] = 
{
		//Tablica klawiatury z ustawionymi znakami
    {'A', '1', '2', '3'},
    {'B', '4', '5', '6'},
    {'C', '7', '8', '9'},
    {'D', '0', 'E', 'F'}
};

char k_rows[4] = {k_R1, k_R2, k_R3, k_R4};
char k_cols[4] = {k_C1, k_C2, k_C3, k_C4};

void k_init(void)
{
	if (k_PORT == PORTA)
		// Ustawienie zegara na port A
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 
	else if (k_PORT == PORTB)
		// Ustawienie zegara na port B
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 

	// Wiersze jako wyjœcia
	for (int i = 0; i < 4; i++) {
		k_PORT->PCR[k_rows[i]] |= PORT_PCR_MUX(1);
		if (k_PORT == PORTA)
			PTA->PDDR |= (1 << k_rows[i]);
		else if (k_PORT == PORTB)
			PTB->PDDR |= (1 << k_rows[i]);
	}

	// Konfiguracja kolumn jako wejœcia z rezystorami podci¹gaj¹cymi
	for (int i = 0; i < 4; i++) {
		k_PORT->PCR[k_cols[i]] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	}
}

// Funkcja opóŸnienia (debounce)
void delay_ms(uint32_t ms){
    uint32_t count;
    while (ms--) {
        for (count = 0; count < 7000; count++) {
        }
    }
}

char k_read(void)
{
	for (uint8_t i = 0; i < 4; i++) {
		// Ustawienie niskiego stanu dla danego wiersza
		if (k_PORT == PORTA)
			PTA->PDOR = ~(1 << k_rows[i]);
		else if (k_PORT == PORTB)
			PTB->PDOR = ~(1 << k_rows[i]);

		// Sprawdzenie stanu kolumn
		for (uint8_t j = 0; j < 4; j++) {
			if (k_PORT == PORTA) {
				if (!(PTA->PDIR & (1 << k_cols[j])))
					return k_tab[i][j];
			} else if (k_PORT == PORTB) {
				if (!(PTB->PDIR & (1 << k_cols[j])))
					return k_tab[i][j];
			}
		}

		// Ustawienie wiersza na wysoki stan
		if (k_PORT == PORTA)
			PTA->PDOR |= (1 << k_rows[i]);
		else if (k_PORT == PORTB)
			PTB->PDOR |= (1 << k_rows[i]);
	}
	return 0;
}
