#include <stdint.h>
#include "esp_system.h"

typedef struct {
  uint8_t *data; // Pointer to the payload data
  size_t size; // Size of the payload data
  uint16_t handle; // Handle of the Bluetooth connection
} bluetooth_message_payload_buffer;

bluetooth_message_payload_buffer buffer;
buffer.data = malloc(500); // Allocate memory for the payload data
buffer.size = 0; // Initialize the payload size
buffer.handle = 0; // Initialize the connection handle

// Receive the payload data
int bytes_received = bluetooth_receive_payload(buffer.data, 500, buffer.handle);

// Check if the receive was successful
if (bytes_received > 0) {
  // The payload was received successfully
  buffer.size = bytes_received;
} else {
  // The receive was not successful
}

// Free the memory for the payload data
free(buffer.data);