/* MQTT and Bluetooth

  
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

/*
Julius Code Starts here
 */
#define MAX_MESSAGE_SIZE 500

// Declare the queues for MQTT and Bluetooth
QueueHandle_t mqttQueue;
QueueHandle_t btQueue;

typedef struct {
    char message[MAX_MESSAGE_SIZE];
    int msg_len;
} Message;


// Init Queus based on message size
void initQueues() 
{
    mqttQueue = xQueueCreate(10, sizeof(Message));
    btQueue = xQueueCreate(10, sizeof(Message));
}

//MQTT message receive
void MQTTMsgRx(char* msg, int msg_len) 
{
    Message newMessage;
    memcpy(newMessage.message, msg, msg_len);
    newMessage.msg_len = msg_len;

    xQueueSend(mqttQueue, &newMessage, portMAX_DELAY);
}

//MQTT message send
void mqttTask(void *pvParameters) {
    Message messageToSend;
    while (1) {
        if (xQueueReceive(mqttQueue, &messageToSend, portMAX_DELAY)) {
            // TODO: Implement your MQTT sending function here.
            // After successful sending, remove the message from the queue.
        }
    }
}

//Bluetooth message receive
void BluetoothMsgRx(char* msg, int msg_len) 
{
    Message newMessage;
    memcpy(newMessage.message, msg, msg_len);
    newMessage.msg_len = msg_len;

    xQueueSend(btQueue, &newMessage, portMAX_DELAY);
}

//Bluetooth message send
void bluetoothTask(void *pvParameters)
 {
    Message messageToSend;
    while (1) {
        if (xQueueReceive(btQueue, &messageToSend, portMAX_DELAY)) {
            // TODO: Implement your Bluetooth sending function here.
            // After successful sending, remove the message from the queue.
        }
    }
 }


//Storing the content of the mqtt queue to NVS
void mqttPersistTask(void *pvParameters) {
    // Open an NVS handle for the "storage" namespace.
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        // Handle error
        return;
    }

    // Enter an infinite loop.
    while (1) {
        // Receive a message from the MQTT queue.
        Message message;
        if (xQueueReceive(mqttQueue, &message, portMAX_DELAY)) {
            // Store the message in NVS.
            err = nvs_set_blob(my_handle, "mqtt_message", &message, sizeof(Message));
            if (err != ESP_OK) {
                // Handle error
                return;
            }
        }
    }

    // Close the NVS handle.
    nvs_close(my_handle);
}

//Storing the content of the bluetooth queue to NVS
void bluetoothPersistTask(void *pvParameters) 
{
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        // Handle error
        return;
    }

    Message message;
    while (1)
    {
        if (xQueueReceive(btQueue, &message, portMAX_DELAY)) {
            err = nvs_set_blob(my_handle, "bluetooth_message", &message, sizeof(Message));
            if (err != ESP_OK) {
                // Handle error
                return;
            }
        }
    }
    nvs_close(my_handle);
}


void app_main(void) 
{
    nvs_flash_init();
    initQueues();

    xTaskCreatePinnedToCore(&mqttTask, "mqttTask", 2048, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(&bluetoothTask, "bluetoothTask", 2048, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(&mqttPersistTask, "mqttPersistTask", 2048, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(&bluetoothPersistTask, "bluetoothPersistTask", 2048, NULL, 5, NULL, 1);

    // TODO: Initialize your MQTT and Bluetooth receivers here.
}
/*
Julius Code Ends here
 */