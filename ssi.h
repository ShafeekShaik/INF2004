#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

// SSI tags - tag length limited to 8 bytes by default
const char * ssi_tags[] = {"test"};

#define MAX_LENGTH 100
char received_data[MAX_LENGTH];

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {
  size_t printed;
  switch (iIndex) {
    case 0: //test
    {
      printed = snprintf(pcInsert, iInsertLen, "%s", received_data);
    }
    break;
  default:
    printed = 0;
    break;
  }
  return (u16_t)printed;
}

void send_data(const char *data){
    strncpy(received_data, data, MAX_LENGTH - 1);
    received_data[MAX_LENGTH - 1] = '\0';
}

// Initialise the SSI handler
void ssi_init() {
  // Initialise ADC (internal pin)
  adc_init();
  adc_set_temp_sensor_enabled(true);
  adc_select_input(4);

  http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
