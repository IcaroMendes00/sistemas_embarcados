#ifndef BIB_H
#define BIB_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include <ctype.h>

#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_nimble_hci.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "sdkconfig.h"
#include "esp_idf_version.h"
#include "esp_wifi.h"
#include "esp_timer.h"
#include "esp_system.h"
#include "esp_netif.h"
#include <esp_ipc.h>
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "mqtt_client.h"

// led
#define led17 GPIO_NUM_17 
#define led18 GPIO_NUM_18

#define delay(value) vTaskDelay(value / portTICK_PERIOD_MS)

// wifi
#define WIFI_SSID      "brisa-1726032"
#define WIFI_PASSWORD  "s17houuz"

// mqtt
#define MQTT_URI       "mqtt://192.168.0.111"
#define MQTT_PORT      1883

void blinkLed(void);

// wifi mqtt
static void wifi_event_handler(void*, esp_event_base_t, int32_t, void*);
void connect_wifi(void);
static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event);
static void mqtt_event_handler(void*, esp_event_base_t, int32_t, void*);
void mqtt_connect(void);
void sendMensage(char chave);

// ble
void saveData(char *data, uint16_t *index);
static int device_write(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);
static int device_read(uint16_t con_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);
static int ble_gap_event(struct ble_gap_event *event, void *arg);
void ble_app_advertise(void);
void ble_app_on_sync(void);
void host_task(void *param);
void connectBLE(void);

#endif