#include "componente_01.h"

void app_main() {

    hc595_t chip;
    hc595_init(&chip, 23, 22, 21);
    hc595_set_all(&chip);
    vTaskDelay(1000 / 1);
    hc595_clear_all(&chip);
    
}