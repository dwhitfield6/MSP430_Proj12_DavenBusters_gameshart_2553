#include <msp430.h> 

#define POT1 INCH_1
#define POT2 INCH_2
#define lightSense INCH_3
#define LED0 BIT0
#define LED1 BIT7
#define motor BIT4

unsigned int adcvalue1 = 0;// variable for storing digital value of CH4 input
unsigned int adcvalue2 = 0;// variable for storing digital value of CH5 input
unsigned int adcvalue3 = 0;// variable for storing digital value of CH5 input
int motorcount =990;
int on =0;

unsigned int analogRead(unsigned int pin) {
 ADC10CTL0 = ADC10ON + ADC10SHT_2 + SREF_0;
 ADC10CTL1 = ADC10SSEL_0 + pin;
 if (pin==INCH_0){
 ADC10AE0 = 0x01;
 }
 else if (pin==INCH_1){
 ADC10AE0 = 0x02;
 }
 else if (pin==INCH_2){
 ADC10AE0 = 0x04;
 }
 else if (pin==INCH_3){
  ADC10AE0 = 0x08;
  }
 else if (pin==INCH_4){
  ADC10AE0 = 0x10;
  }
 else if(pin==INCH_5){
 ADC10AE0 = 0x20;
 }
 else if(pin==INCH_6){
  ADC10AE0 = 0x40;
  }
 else if(pin==INCH_7){
  ADC10AE0 = 0x80;
  }
 ADC10CTL0 |= ENC + ADC10SC;
 while (1) {
 if (((ADC10CTL0 & ADC10IFG)==ADC10IFG)) {
 ADC10CTL0 &= ~(ADC10IFG +ENC);
 break;
 }
 }
 return ADC10MEM;
 }

void main(void) {

WDTCTL = WDTPW + WDTHOLD; //Stop Watchdog Timer
P1DIR |= (LED0 + LED1 + motor);// P1.0=>LED1 and P1.6=>LED2
P1OUT |= (motor);
__enable_interrupt(); // enable all interrupts

while (1){
 adcvalue1 = analogRead(POT1);// Read the analog input from channel 4
 adcvalue2 = analogRead(POT2);// Read the analog input from channel 5
 adcvalue3 = analogRead(lightSense);// Read the analog input from channel 5
 if(adcvalue2>adcvalue3)
 {
	 if(on<1000)
	 {
	 on++;
	 }
	 P1OUT |= (LED1);
	 P1OUT &= ~LED0;
 }
 else
 {
	 on =0;
	 P1OUT |= LED0;
	 P1OUT &= ~LED1;
 }
 if(on ==3)
 {
	 motorcount =0;
 }
if(motorcount == 0)
{
	P1OUT &= ~(motor);

}
motorcount++;
if(motorcount > 1000)
{
	motorcount =990;
}

if(motorcount > adcvalue1)
{
	P1OUT |= (motor);
}
 }

}
