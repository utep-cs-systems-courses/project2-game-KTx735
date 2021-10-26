//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int blinkLimit = 5;  // duty cycle = 1/blinkLimit
int blinkCount = 0;  // cycles 0...blinkLimit-1
int secondCount = 0; // state var representing repeating time 0…1s

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking 
  blinkCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
  } else		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;

  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second /*Original 250*/
    secondCount = 0;
    blinkLimit ++;	     // reduce duty cycle
    if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7. /*Original 8*/
      blinkLimit = 0;
  }

  /* Idea

blinkLimit = 1, 2, 3, 4;

if(blinkCountS1 >= 500)
{
 blinkCountS1 = 0;
 blinkLimit = (blinkLimit % 4) + 1;  Takes care of the number of repeats
}

if(blinkCountS2 >= 250)
{
 //Reset Count
 onOff ^=1;
}

if(bc3 >= blinkLimit)
{
 P1OUT |= (LED_GREEN = onOff);
}else P1OUT &= ~LED_GREEN;

*/

  
} 

