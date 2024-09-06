#include <stdint.h>
#include <parsing.h>
#include <math.h>

int interpolation(uint16_t channel) {
    int scaled_value;

    // Map the 16-bit channel value to a 7-bit value
    if (channel < 2048) {
        // Backward direction (64-127)
        scaled_value = (2048 - channel) / 16 + 64;
    } else {
        // Forward direction (0-63)
        scaled_value = (channel - 2048) / 16;
    }

    // Ensure the scaled value is within the 7-bit range (0-127)
    scaled_value = scaled_value < 0 ? 0 : scaled_value > 127 ? 127 : scaled_value;

    return scaled_value;
}

uint16_t *parse_buffer(uint8_t buff[]) { 
    static uint16_t channel[16];

    uint16_t mask = 0x7ff;

    channel[0]  = ((buff[1] | buff[2]<<8)                 & mask);
    channel[1]  = ((buff[2]>>3 | buff[3]<<5)              & mask);
    channel[2]  = ((buff[3]>>6 | buff[4]<<2 | buff[5]<<10) & mask);
    channel[3]  = ((buff[5]>>1 | buff[6]<<7)              & mask);
    channel[4]  = ((buff[6]>>4 | buff[7]<<4)              & mask);
    channel[5]  = ((buff[7]>>7 | buff[8]<<1 | buff[9]<<9)  & mask);
    channel[6]  = ((buff[9]>>2 | buff[10]<<6)             & mask);
    channel[7]  = ((buff[10]>>5| buff[11]<<3)             & mask);
    channel[8]  = ((buff[12]   | buff[13]<<8)             & mask);
    channel[9]  = ((buff[13]>>3| buff[14]<<5)             & mask);
    channel[10] = ((buff[14]>>6| buff[15]<<2| buff[16]<<10)& mask);
    channel[11] = ((buff[16]>>1| buff[17]<<7)             & mask);
    channel[12] = ((buff[17]>>4| buff[18]<<4)             & mask);
    channel[13] = ((buff[18]>>7| buff[19]<<1| buff[20]<<9) & mask);
    channel[14] = ((buff[20]>>2| buff[21]<<6)             & mask);
    channel[15] = ((buff[21]>>5| buff[22]<<3)             & mask);

    return channel;
}
