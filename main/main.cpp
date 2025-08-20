#include "driver/uart.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>

static const char* TAG="BNO_UART";
#define LED GPIO_NUM_13
#define UARTP UART_NUM_2
#define TX GPIO_NUM_17
#define RX GPIO_NUM_16

extern "C" void app_main(void) {
    gpio_config_t io{}; io.mode=GPIO_MODE_OUTPUT; io.pin_bit_mask=(1ULL<<LED); gpio_config(&io);
    gpio_set_level(LED,0);

    uart_config_t c{
        .baud_rate=115200,
        .data_bits=UART_DATA_8_BITS,
        .parity=UART_PARITY_DISABLE,
        .stop_bits=UART_STOP_BITS_1,
        .flow_ctrl=UART_HW_FLOWCTRL_DISABLE,
        .source_clk=UART_SCLK_APB
    };
    uart_param_config(UARTP,&c);
    uart_set_pin(UARTP,TX,RX,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
    uart_driver_install(UARTP,1024,1024,0,nullptr,0);

    ESP_LOGI(TAG,"UART started");

    // minimal "read chip ID" command (register 0x00, length=1)
    uint8_t cmd[4]={0xAA,0x01,0x00,0x01};

    while(true){
        uart_write_bytes(UARTP,(const char*)cmd,4);
        uint8_t r[64];
        int n=uart_read_bytes(UARTP,r,sizeof(r),pdMS_TO_TICKS(200));
        if(n>0){
            char buf[256]; int m=0;
            for(int i=0;i<n && m<250;i++) m+=snprintf(buf+m,sizeof(buf)-m,"%02X ",r[i]);
            ESP_LOGI(TAG,"RX %.*s",m,buf);
        } else {
            ESP_LOGW(TAG,"no reply");
        }
        gpio_set_level(LED,1);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_set_level(LED,0);
        vTaskDelay(pdMS_TO_TICKS(900));
    }
}
