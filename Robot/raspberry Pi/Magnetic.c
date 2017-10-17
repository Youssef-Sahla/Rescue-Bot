/*-----------------------------------------------------------------------------
 *Name: Atef Thamer
 *Program: Magnetometer software
 *Discription: This program is for reading 3 sensor data; x,y and z values. 
 *It uses wiring pi library. for more information visit www.wiringpi.com.
 *http://wiringpi.com/reference/i2c-library/
 *
 *------------------------------------------------------------------------------
 *For technical information about the magnetometer, check the manual.
 *------------------------------------------------------------------------------
 */

#include  <unistd.h>
#include  <wiringPi.h>
#include  <wiringPiI2C.h>
#include <stdio.h>
#include <math.h>

typedef unsigned char   uint8_t;
// global variables
//--------------------------------------------------------------------------------
// compass registers from manual
int reg[] = {0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
int fd;
//--------------------------------------------------------------------------------
int main(){

	// wiring pi startup
    wiringPiSetup();
    fd = wiringPiI2CSetup(0x1e);

	// write signal to the magnetometer registers, see manual
	// Simple device write. Some devices accept data this way without needing to access any internal registers
	// These write an 8 or 16 - bit data value into the device register indicated.
    wiringPiI2CWriteReg8(fd, 0x00, 0x70);
    wiringPiI2CWriteReg8(fd, 0x01, 0xA0);
    wiringPiI2CWriteReg8(fd, 0x02, 0x03);
	// Manual recommends 6ms delay
    usleep(60000);

    while(1){
		// write to device
        wiringPiI2CWriteReg8(fd, 0x02, 0x01);
        // Array to save values 
        int data[6];

        for (int i = 0; i < 6 ; ++i) {
			// These read an 8 or 16-bit value from the device register indicated.
            data[i] = wiringPiI2CReadReg8(fd, reg[i]);
        }
        printf("X, Y, Z");
		// 16 bit OR operation
		// Convert three 16-bit 2’s compliment hex values to decimal values
        short x = (data[0] << 8) | data[1]; 
        short y = (data[2] << 8) | data[3];
        short z = (data[4] << 8) | data[5];
		// calculate angle
        float angle = atan2(y, x) * 180 / M_PI;

		// print values
        printf("x=%d, y=%d, z=%d\n", x, y, z);
        printf("angle = %0.1f\n\n", angle);
    }
    return 0;
}