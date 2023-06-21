#include <stdint.h>
#include "esp_system.h"

typedef struct mqtt_message_buffer {
  uint8_t *payload;
  size_t payload_size;
  bool is_free;
} mqtt_message_buffer_t;

mqtt_message_buffer_t *mqtt_message_buffer_alloc(size_t payload_size) {
  mqtt_message_buffer_t *buffer = (mqtt_message_buffer_t *)heap_caps_malloc(
      sizeof(mqtt_message_buffer_t), MALLOC_CAP_8BIT);
  if (buffer == NULL) {
    return NULL;
  }

  buffer->payload = (uint8_t *)heap_caps_malloc(payload_size, MALLOC_CAP_8BIT);
  if (buffer->payload == NULL) {
    free(buffer);
    return NULL;
  }

  buffer->payload_size = payload_size;
  buffer->is_free = false;

  return buffer;
}

void mqtt_message_buffer_free(mqtt_message_buffer_t *buffer) {
  if (buffer == NULL) {
    return;
  }

  heap_caps_free(buffer->payload);
  heap_caps_free(buffer);
}