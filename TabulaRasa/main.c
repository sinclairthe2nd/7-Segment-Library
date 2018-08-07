#include <avr/io.h>
#include <util/delay.h>

//Configutations

#define PORT_7_SEGMENT PORTD
#define DDR_7_SEGMENT DDRD
int number = 0;


void SevenSegment(uint8_t number)
{
switch (number)//Maps the number in number to the display rather crudely (its very flexible and readable though)
      {
         case 0:
         PORT_7_SEGMENT=0b01000000;
         break;

         case 1:
         PORT_7_SEGMENT=0b01111001;
         break;

         case 2:
         PORT_7_SEGMENT=0b00100100;
         break;

         case 3:
         PORT_7_SEGMENT=0b00110000;
         break;

         case 4:
         PORT_7_SEGMENT=0b00011001;
         break;

         case 5:
         PORT_7_SEGMENT=0b00010010;
         break;

         case 6:
         PORT_7_SEGMENT=0b00000010;
         break;

         case 7:
         PORT_7_SEGMENT=0b01111000;
         break;

         case 8:
         PORT_7_SEGMENT=0b00000000;
         break;

         case 9:
         PORT_7_SEGMENT=0b00010000;
         break;
      }
}

int main(void)
{
   //Setup
   DDR_7_SEGMENT=0b11111111;    //All output
   PORT_7_SEGMENT=0xFF;   //All segments off
      
   while(1)               //loop forever
   {
     //  PORT_7_SEGMENT=0b00000000;
      SevenSegment(number);
      
      number++;
      if(number==10)  
      {
         number=0;
      }
      _delay_ms(250);
      
     
   }
}

