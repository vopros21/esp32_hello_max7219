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
#define BLINK_GPIO_white 2
#define BLINK_GPIO_red 3
#define BLINK_GPIO_blue 4
#define BLINK_GPIO_green 5
#define BLINK_GPIO_yellow 6  // Change this to match your board's LED pin
#define BLINK_PERIOD_MS 500  // Blink period in milliseconds
#define SWITCH_PERIOD_MS 500  // Blink period in milliseconds

void reset_gpio(int gpio_num)
{
    gpio_reset_pin(gpio_num);
    gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT);
}


void run_blink_task(int n)
{
    bool led_state = false;
    int k = 0;
    while (1) {
        led_state = 1;
        for (int i = 2; i < 7; i++) {
            gpio_set_level(i, !led_state);
        }
        for (int i = 0; i < n; i++) {
            gpio_set_level((k + i) % 5 + 2, led_state);        
        }
        vTaskDelay(SWITCH_PERIOD_MS / portTICK_PERIOD_MS);
        k++;
    }
}

void app_main(void)
{
    // Configure the GPIO pin
    reset_gpio(BLINK_GPIO_white);
    reset_gpio(BLINK_GPIO_red);
    reset_gpio(BLINK_GPIO_blue);
    reset_gpio(BLINK_GPIO_green);
    reset_gpio(BLINK_GPIO_yellow);
    
    ESP_LOGI(TAG, "Blink example started");
        
    run_blink_task(3);
}
