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
#define SWITCH_PERIOD_MS 100  // Blink period in milliseconds

void app_main(void)
{
    // Configure the GPIO pin
    gpio_reset_pin(BLINK_GPIO_white);
    gpio_set_direction(BLINK_GPIO_white, GPIO_MODE_OUTPUT);
    gpio_reset_pin(BLINK_GPIO_red);
    gpio_set_direction(BLINK_GPIO_red, GPIO_MODE_OUTPUT);
    gpio_reset_pin(BLINK_GPIO_blue);
    gpio_set_direction(BLINK_GPIO_blue, GPIO_MODE_OUTPUT);
    gpio_reset_pin(BLINK_GPIO_green);
    gpio_set_direction(BLINK_GPIO_green, GPIO_MODE_OUTPUT);
    gpio_reset_pin(BLINK_GPIO_yellow);
    gpio_set_direction(BLINK_GPIO_yellow, GPIO_MODE_OUTPUT);
    
    ESP_LOGI(TAG, "Blink example started");
    
    bool led_state = false;
    
    while (1) {
        // Toggle LED state
        led_state = !led_state;
        
        // Set the GPIO level according to the state
        gpio_set_level(BLINK_GPIO_white, led_state);
        vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
        
        gpio_set_level(BLINK_GPIO_red, led_state);
        vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
        
        gpio_set_level(BLINK_GPIO_blue, led_state);
        vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
        
        gpio_set_level(BLINK_GPIO_green, led_state);
        vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
        
        gpio_set_level(BLINK_GPIO_yellow, led_state);
        vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
        
        ESP_LOGI(TAG, "Turning the LED %s!", led_state ? "ON" : "OFF");
        
        // Delay for the blink period
        vTaskDelay(BLINK_PERIOD_MS / portTICK_PERIOD_MS);
    }
}
