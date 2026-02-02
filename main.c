/*--------------------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - projekt
					
					Temat projektu: 
					4. Gra w kości: losowa generacja pięciu cyfr od 1 do 6, trzy „rzuty”, po każdym możliwość
					zatrzymania dowolnej ilości wylosowanych cyfr lub zrezygnowania z już wylosowanych.
					Zasady podobne do pokera.
					
					autor: Hubert Durnaś
					wersja: 25.01.2025
--------------------------------------------------------------------------------------------------*/

#include "MKL05Z4.h"
#include "klaw2.h"
#include "ADC.h"
#include "lcd1602.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DICE_NUM 5
#define MAX_ROLL 3

int dice[DICE_NUM] = {0};
int kept[DICE_NUM] = {0};

// Wykonuje rzut kością dla niezatrzymanych kostek, generując losowe wartości za pomocą ADC
void make_a_dice_roll(int amount_of_dice) {
    for (int i = 0; i < amount_of_dice; i++) {
        if (!kept[i]) {
            // Odczyt wartości z ADC i użycie jej jako źródła losowości
            ADC0->SC1[0] = ADC_SC1_ADCH(8); // Kanał 8 (PTB11)
            while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0); // Czekaj na zakończenie konwersji
            uint16_t adc_value = ADC0->R[0];
            dice[i] = (adc_value % 6) + 1;
        }
    }
    return;
}

// Wyświetla aktualne wartości kości na ekranie LCD, zaznaczając zatrzymane (^)
void show_dice_lcd(int amount_of_dice) {
    char buffer[17] = {'\0'};
    int offset = 0;

    LCD1602_ClearAll();
		
		LCD1602_Print("Dice:");

    // Wyświetlenie wartości kości z oznaczeniem ^ dla zatrzymanych
    for (int i = 0; i < amount_of_dice; i++) {
        if (kept[i]) {
            offset += sprintf(&buffer[offset], "^%d ", dice[i]);
        } else {
            offset += sprintf(&buffer[offset], "%d ", dice[i]);
        }
        if (offset >= 16) {
            break;
        }
    }

    LCD1602_SetCursor(0, 1);
		buffer[16] = '\0';
    LCD1602_Print(buffer);
		return;
}

// Pozwala użytkownikowi zaznaczyć lub odznaczyć zatrzymanie wybranych kostek
void update_kept_lcd(int amount_of_dice) {
    char key = '0';

    LCD1602_ClearAll();
    LCD1602_Print("Choose your dice");
    LCD1602_SetCursor(0, 1);
    LCD1602_Print("1-5, 7=over");
	
    while (key != '7') {
        key = k_read();
        if (key == '7') {
						show_dice_lcd(amount_of_dice);
            break;
        } else if (key >= '1' && key <= '5') {
            int indeks = key - '1';
            kept[indeks] = !kept[indeks];
            show_dice_lcd(amount_of_dice);
						key = 0;
        }
    }
		return;
}

int main() {
    k_init();           // Inicjalizacja klawiatury
    LCD1602_Init();     // Inicjalizacja LCD
	  ADC_Init();         // Inicjalizacja ADC


    LCD1602_ClearAll();
    LCD1602_Print("Dice poker!");
    LCD1602_SetCursor(0, 1);
    LCD1602_Print("Press '1'");

	  // Oczekiwanie na pierwszy rzut
    while (1) {
        char key = k_read();
        if (key == '1') {
            make_a_dice_roll(DICE_NUM); // Wykonaj pierwszy rzut po naciśnięciu '1'
            break;
        }
    }		
    // Obsługa do trzech rzutów
    for (int roll = 1; roll <= MAX_ROLL; roll++) {
        LCD1602_ClearAll();
        char buffer[17] = {'\0'};
        sprintf(buffer, "Roll no. %d", roll);
        LCD1602_Print(buffer);
				LCD1602_SetCursor(0, 1);
				LCD1602_Print("Press '8':");

        if (roll > 1) { // Wykonuj rzut dopiero od drugiego kroku
            make_a_dice_roll(DICE_NUM);
        }
				while(1) {
					char key = k_read();
					if (key == '8') {
						break;
					}
				}
        show_dice_lcd(DICE_NUM);

        if (roll < MAX_ROLL) {
            update_kept_lcd(DICE_NUM);
        }
				LCD1602_SetCursor(0, 0);
				LCD1602_Print("Press 9");
				while(1) {
					char key = k_read();
					if (key == '9') {
						break;
					}
				}
    }

		// Wyświetlenie komunikatu o końcu gry
    LCD1602_ClearAll();
    LCD1602_Print("Game over!");
    LCD1602_SetCursor(0, 1);
    LCD1602_Print("Press '0':");

		while(1) {
					char key = k_read();
					if (key == '0') {
						break;
					}
				}
		show_dice_lcd(DICE_NUM);

    return 0;
}
