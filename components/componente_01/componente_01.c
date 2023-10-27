#include "componente_01.h" 
#include "driver/gpio.h" 

// funcao interna para enviar um pulso no pino de clock
static void hc595_pulse(hc595_t* chip) 
{
    gpio_set_level(chip->clock_pin, 0); // define o pino de clock para o nivel baixo
    gpio_set_level(chip->clock_pin, 1); // define o pino de clock para o nível alto
}

// inicializa o chip 74HC595 com os respectivos pinos
void hc595_init(hc595_t* chip, int data_pin, int latch_pin, int clock_pin) 
{
    chip->data_pin = data_pin;   // atribui o pino de dados
    chip->latch_pin = latch_pin; // atribui o pino latch
    chip->clock_pin = clock_pin; // atribui o pino de clock

    // define os pinos como saidas
    gpio_set_direction(data_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(latch_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(clock_pin, GPIO_MODE_OUTPUT);
}

// escreve um valor de 8 bits no 74HC595
void hc595_write(hc595_t* chip, uint8_t value) 
{
    for (int i = 0; i < 8; i++) 
    {   // percorre cada bit do valor e escreve o bit no pino de dados
        gpio_set_level(chip->data_pin, (value & (1 << i)) ? 1 : 0);
        hc595_pulse(chip); // Envia um pulso no pino de clock.
    }
    // altera o latch pin para transferir os bits para os pinos de saida do 74HC595
    gpio_set_level(chip->latch_pin, 1);
    gpio_set_level(chip->latch_pin, 0);
}

// zera todos os bits do 74HC595
void hc595_clear_all(hc595_t* chip) 
{
    hc595_write(chip, 0x00);
}

// seta como 1 todos os bits do 74HC595
void hc595_set_all(hc595_t* chip) 
{
    hc595_write(chip, 0xFF);
}

// zera um bit específico do 74HC595
void hc595_clear_bit(hc595_t* chip, uint8_t bit) 
{
    uint8_t value = ~(1 << bit);
    hc595_write(chip, value);
}

// seta um bit específico do 74HC595
void hc595_set_bit(hc595_t* chip, uint8_t bit) 
{
    uint8_t value = (1 << bit);
    hc595_write(chip, value);
}