#include "bib.h"

TaskHandle_t TaskMenu = NULL;
TaskHandle_t TaskMain = NULL;

esp_mqtt_client_handle_t client;

void run_main()
{    
    nvs_flash_init();
    connect_wifi();
    ble_connect();

    mqtt_connect();

    while(1);
    blinkLed();
}

void app_main(void)
{
    xTaskCreate(&run_main, "CallMain", 8192, NULL, 1, &TaskMain);
}






