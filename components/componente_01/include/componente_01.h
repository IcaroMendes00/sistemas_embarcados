#ifndef COMPONENTE_01_H_
#define COMPONENTE_01_H_

#include "esp_system.h"

typedef struct 
{
    int data_pin;
    int latch_pin;
    int clock_pin;

} hc595_t;

// inicializa o chip com os pinos especificados
void hc595_init(hc595_t* chip, int data_pin, int latch_pin, int clock_pin);

// escreve um valor de byte no chip
void hc595_write(hc595_t* chip, uint8_t value);

// zera todos os bits 
void hc595_clear_all(hc595_t* chip);

// zera um bit especifico
void hc595_clear_bit(hc595_t* chip, uint8_t bit);

// seta todos os bits como 1
void hc595_set_all(hc595_t* chip);

// define um bit especifico
void hc595_set_bit(hc595_t* chip, uint8_t bit);

#endif