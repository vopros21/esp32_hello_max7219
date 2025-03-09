/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "blink_example";
#define BLINK_GPIO 6  // Change this to match your board's LED pin
#define BLINK_PERIOD_MS 1000  // Blink period in milliseconds

void app_main(void)
{
    // Configure the GPIO pin
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    
    ESP_LOGI(TAG, "Blink example started");
    
    bool led_state = false;
    
    while (1) {
        // Toggle LED state
        led_state = !led_state;
        
        // Set the GPIO level according to the state
        gpio_set_level(BLINK_GPIO, led_state);
        
        ESP_LOGI(TAG, "Turning the LED %s!", led_state ? "ON" : "OFF");
        
        // Delay for the blink period
        vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
    }
}
