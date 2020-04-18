#include <Arduino.h>
#include <driver/i2s.h>

#define PIN_MIC_LR  22
#define PIN_MIC_WS  19
#define PIN_MIC_SCK 23
#define PIN_MIC_SD  33

const i2s_port_t I2S_PORT = I2S_NUM_0;

const int BLOCK_SIZE = 1024;

void setup(void)
{
    esp_err_t err;

    Serial.begin(115200);
    Serial.println("\nESP32-microphone");

    // The I2S config as per the example
    const i2s_config_t i2s_config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),      // Receive, not transfer
        .sample_rate = 22050,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,   // although the SEL config should be left, it seems to transmit on right
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // Interrupt level 1
        .dma_buf_count = 8,     // number of buffers
        .dma_buf_len = BLOCK_SIZE,      // samples per buffer
        .use_apll = true
    };

    // The pin config as per the setup
    const i2s_pin_config_t pin_config = {
        .bck_io_num = PIN_MIC_WS,   // BCKL
        .ws_io_num = PIN_MIC_SCK,   // LRCL
        .data_out_num = -1,         // not used (only for speakers)
        .data_in_num = PIN_MIC_SD   // DOUT
    };

    // Configuring the I2S driver and pins.
    // This function must be called before any I2S driver read/write operations.
    err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
        Serial.printf("Failed installing driver: %d\n", err);
        while (true);
    }
    err = i2s_set_pin(I2S_PORT, &pin_config);
    if (err != ESP_OK) {
        Serial.printf("Failed setting pin: %d\n", err);
        while (true);
    }
    
    // setup L/R
    pinMode(PIN_MIC_LR, OUTPUT);
    digitalWrite(PIN_MIC_LR, 0);
}

void loop(void)
{
}


