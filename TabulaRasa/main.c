#include <avr/io.h>
#include <util/delay.h>

//Configutations

#define PORT_7_SEGMENT PORTD
#define DDR_7_SEGMENT DDRD
#define DDR_MULTI DDRB
#define PORTMULTI PORTB


int NUMBER = 0;
int INPUTNUMBER =0;


void SevenSegment(int INPUTNUMBER)
{
if(INPUTNUMBER > 9) //Conditioning of the Inputnumber
      {
        for (int a=0; a<10;a++)
            {
            NUMBER=INPUTNUMBER%10; //This extracts the last digit using modulo  
            PORTMULTI=0b00000001;  //Turn on first Display     
            Display(NUMBER);
            _delay_ms(1);
            NUMBER=INPUTNUMBER/10;  //This Shaves of the last digit of inputnumber
            PORTMULTI=0b00000010;  //Turn on Second Display
            Display(NUMBER);
            _delay_ms(1);
            }
      }
    else
      {
        NUMBER=INPUTNUMBER;
        PORTMULTI=0b00000001;  //Turn on first Display 
        Display(NUMBER);
      }
}
void Display(int NUMBER)
{

switch (NUMBER)//Maps the number in number to the display rather crudely (its very flexible and readable though)
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
   DDR_MULTI=0b11111111;  //All Multiplexing  pins are outputs
   int count = 0;
   while(1)               //loop forever
   {
      
      SevenSegment(INPUTNUMBER);
      
         INPUTNUMBER++;
      if(INPUTNUMBER==99)  
      {
         INPUTNUMBER=0;
      }
    
    _delay_ms(7);
      
     
   }
}

