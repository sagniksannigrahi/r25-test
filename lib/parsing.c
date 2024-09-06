//we are implementing code to control motors for a rover using data received from an RC transmitter. Basically we are implementing code to control a sabrtooth motor driver(we are only trying to control motor 1 using S1 of Sabertooth), connected to drive motors of the rover, using data received from an RC transmitter( the transmitter is configured to transmit data in extended limits). The data from the transmitter is being recieved by a SBUS reciever module nad the data protocol used here.
//Task 0 ::- Here we just create a fork
// Task 2::- Here we just add some new function interpolation in the parsing.c area .. here we just check the chanel size if it is greter or less than 2048 .. if it is less then then we just put [[[scaled_value=(2048 - channel) / 16 + 64;]]]and in the else part we use [[scaled_value = (channel - 2048) / 16;]] .. Thats all
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
    scaled_value = scaled_value < 0 ? 0 : scaled_value > 127 ? 127 : scaled_value; //It is  a quick way to keep scaled_value between 0 and 127..

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
