
/*
 * This is Testcode to develop the principles of 7-Segment Operations, principles developed here are to be turned into a working library later 
 *
 * Code to display 0-9 or 0-F to 7-segment display.
 * Change Variable dec_hex in Main function to swap between
 * hex and decimal. Warning: clock speed is defined as 1MHz (F_CPU) because new
 * AVR devices have default 1MHz Internal RC. Change F_CPU to match your clock speed.
 * There are 7-segments + decimal point (DP) and they are active low, that is 0 = segment on. 
 * DP is always off (1).
 *
 *   PIN wiring on PORTB is 
 *
 *  Pin Segment
 *  7    g
 *  6    b
 *  5    d
 *  4    f
 *  3    DP
 *  2    e
 *  1    a
 *  0    c 
 */

// clock speed for delay

#include <avr/io.h>
#include <util/delay.h>

//Configurations

//**************
// Change constant here to change port used by 7-segment

#define PORT_7_SEGMENT PORTB
#define DDR_7_SEGMENT DDRB
#define PORT_DISPLAY PORTD 
#define DDR_DISPLAY DDRD 

void SevenSegment(uint8_t count, uint8_t dec,uint8_t display_number)
{
//  This function shows value of count on display the decimal point is displayed if dp=1
  
  int CountDis = 0;
  
  //Multiplexing Block
  PORT_DISPLAY |= 1;                 //first display on (initial state)
  for(int a=0; a<display_number;a++)
  {
  CountDis = count%10;              //get the last number of count
  count = count/10;                  //shave the last number of count
  PORTD << 1;                       // Leftshift to get next Displaypin for Multiplexing
  }
  
  if(count <dec)                //Determines if a number is in or out of range
   {
      switch (CountDis)             //Maps the number in CountDis to the display rather crudely (its very flexible and readable though)
      {
         case 0:
         PORT_7_SEGMENT=0b10001000;
         break;

         case 1:
         PORT_7_SEGMENT=0b10111110;
         break;

         case 2:
         PORT_7_SEGMENT=0b00011001;
         break;

         case 3:
         PORT_7_SEGMENT=0b00011100;
         break;

         case 4:
         PORT_7_SEGMENT=0b00101110;
         break;

         case 5:
         PORT_7_SEGMENT=0b01001100;
         break;

         case 6:
         PORT_7_SEGMENT=0b01001000;
         break;

         case 7:
         PORT_7_SEGMENT=0b10111100;
         break;

         case 8:
         PORT_7_SEGMENT=0b00001000;
         break;

         case 9:
         PORT_7_SEGMENT=0b00001100;
         break;
      }
      
   }
   else
   {
      //This symbol on display shows that count was greater than 9 
      //so display can't handle it
      //Needs to be changed in a clever way to allow multiplexing  

      PORT_7_SEGMENT=0b11011111;
   }
}



int main()
{
   //Setup
   DDR_7_SEGMENT=0xFF;    //All output
   PORT_7_SEGMENT=0xFF;   //All segments off
   DDR_DISPLAY=0xFF;      //All Pins are outputs for now
   
   uint8_t count=0;
   uint8_t dec=10;        //Range 0-9 = 10 
   uint8_t display_number=1; //number off Displays
   while(1)               //loop forever
   {
      SevenSegment(count,dec,display_number);

      count++;
      if(count==dec)  
      {
         count=0;
      }
      _delay_ms(1000);
   }
}
