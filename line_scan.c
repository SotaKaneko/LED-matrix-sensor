#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define MCP3208_CLK 11
#define MCP3208_DOUT 9
#define MCP3208_DIN 10
#define MCP3208_CS   8

#define SPI_CHANNEL 0 // GPIO 8(CE0)
#define SPI_SPEED   100000

#define MCP3208_channel0 0
#define MCP3208_channel1 1
#define MCP3208_channel2 2
#define MCP3208_channel3 3
#define MCP3208_channel4 4
#define MCP3208_channel5 5
#define MCP3208_channel6 6
#define MCP3208_channel7 7

int start_RW_MCP3208 (unsigned char MCP3208_Channel) {
  unsigned char buffer[3];
  int MCP3208Value = 0;

  buffer[0] = ((MCP3208_Channel & 0x07) >> 2) | 0x06;
  buffer[1] = ((MCP3208_Channel & 0x07) << 6);
  buffer[2] = 0x00;
 
  digitalWrite (MCP3208_CS, 0);

  wiringPiSPIDataRW (SPI_CHANNEL, buffer, 3);
 
  buffer[1] = 0x0f & buffer[1];
  MCP3208Value = (buffer[1] << 8) | buffer[2];

  digitalWrite (MCP3208_CS, 1);

  return MCP3208Value;
}

int main (void) {
  int MCP3208_channel0_value = 0;
  int MCP3208_channel1_value = 0;
  int MCP3208_channel2_value = 0;
  int MCP3208_channel3_value = 0;
  int MCP3208_channel4_value = 0;
  int MCP3208_channel5_value = 0;
  int MCP3208_channel6_value = 0;
  int MCP3208_channel7_value = 0;

  char light_line[32] ="● ● ● ● ● ● ● ●";
  char  dark_line[32] ="○ ○ ○ ○ ○ ○ ○ ○";

  if (wiringPiSetup () == -1) {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror(errno));
    return 1;
  }

  if (wiringPiSPISetup (SPI_CHANNEL, SPI_SPEED) == -1) {
    fprintf (stdout, "wiringPiSPISetup is failed: %s\n", strerror(errno));
    return 1;
  }

  pinMode (MCP3208_CS, OUTPUT);

  while(1)
    {
      system("clear");

      MCP3208_channel0_value = start_RW_MCP3208 (MCP3208_channel0);
      MCP3208_channel1_value = start_RW_MCP3208 (MCP3208_channel1);
      MCP3208_channel2_value = start_RW_MCP3208 (MCP3208_channel2);
      MCP3208_channel3_value = start_RW_MCP3208 (MCP3208_channel3);
      MCP3208_channel4_value = start_RW_MCP3208 (MCP3208_channel4);
      MCP3208_channel5_value = start_RW_MCP3208 (MCP3208_channel5);
      MCP3208_channel6_value = start_RW_MCP3208 (MCP3208_channel6);
      MCP3208_channel7_value = start_RW_MCP3208 (MCP3208_channel7);

      int highest_voltage_line = -1;
      int highest_voltage = 0;
      //      for(int line_number = -1; line_number < 8; ++line_number) {
        if(MCP3208_channel0_value > highest_voltage) {
          highest_voltage = MCP3208_channel0_value;
          highest_voltage_line = 0;
        }
        if (MCP3208_channel1_value > highest_voltage){
          highest_voltage = MCP3208_channel1_value;
          highest_voltage_line = 1;
        }
        if (MCP3208_channel2_value > highest_voltage){
          highest_voltage = MCP3208_channel2_value;
          highest_voltage_line = 2;
        }
        if (MCP3208_channel3_value > highest_voltage){
          highest_voltage = MCP3208_channel3_value;
          highest_voltage_line = 3;
        }
        if (MCP3208_channel4_value > highest_voltage){
          highest_voltage = MCP3208_channel4_value;
          highest_voltage_line = 4;
        }
        if (MCP3208_channel5_value > highest_voltage){
          highest_voltage = MCP3208_channel5_value;
          highest_voltage_line = 5;
        }
        if (MCP3208_channel6_value > highest_voltage){
          highest_voltage = MCP3208_channel6_value;
          highest_voltage_line = 6;
        }
        if (MCP3208_channel7_value > highest_voltage){
          highest_voltage = MCP3208_channel7_value;
          highest_voltage_line = 7;
        }
        //      }

      // print header
      printf("========================================\n");
      printf("MCP3208 digital output.\n");
      printf("========================================\n");

      // channel0
      printf("Ch0 Value = %04u", MCP3208_channel0_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel0_value));

      // channel1
      printf("Ch1 Value = %04u", MCP3208_channel1_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel1_value));

      // channel2
      printf("Ch2 Value = %04u", MCP3208_channel2_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel2_value));

      // channel3
      printf("Ch3 Value = %04u", MCP3208_channel3_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel3_value));

      // channel4
      printf("Ch4 Value = %04u", MCP3208_channel4_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel4_value));

      // channel5
      printf("Ch5 Value = %04u", MCP3208_channel5_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel5_value));

      // channel6
      printf("Ch6 Value = %04u", MCP3208_channel6_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel6_value));

      // channel7
      printf("Ch7 Value = %04u", MCP3208_channel7_value);
      printf("\tVoltage = %.3f\n", ((3.3/4096) * MCP3208_channel7_value));

      printf("----------------------------------------\n\n");

      printf("highest voltage      = %d (Line%d)\n", highest_voltage, highest_voltage_line);

      for(int line_number = 0; line_number < 8; ++line_number) {
        if(line_number == highest_voltage_line) {
          printf("Line%d\t%s\n", line_number, light_line);
        } else {
          printf("Line%d\t%s\n", line_number, dark_line);
        }
      }

      // print footer
      printf("\n========================================\n");

      usleep(1000000);
  }
  return 0;
}

// :Note - Degital output code = 4096 * Vin / Vref
// compile        -> 'gcc line_scan.c -lwiringPi -lm'
// compile(debug) -> 'gcc -Wall line_scan.c -lwiringPi -lm'
