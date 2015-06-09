 
#include "derivative.h" 
//Ports
#define setPortB(x) 	(GPIOB_PDOR |= (1 << x))
#define clearPortB(x) 	(GPIOB_PDOR &= ~(1 << x))
#define setPortD(x) 	(GPIOD_PDOR |= (1 << x))
#define clearPortD(x) 	(GPIOD_PDOR &= ~(1 << x))

#define readPortB(x)	((GPIOB_PDIR &= (1 << x)) >> x)
#define	nButtonPressed  1
#define	nButtonFree     0 

#define btn1			3

//Leds
#define turnOnRedLed	clearPortB(18)
#define turnOffRedLed	setPortB(18)
#define turnOnGreenLed	clearPortB(19)
#define turnOffGreenLed	setPortB(19)
#define turnOnBlueLed	clearPortD(1)
#define turnOffBlueLed	setPortD(1)
#define turnOffazulLed	setPortD(1)
//Time
#define	n1sec			2000000  
#define	n2sec			4000000
#define	n500ms			1000000  
//--------------------------------------------------------------
//Declare Prototypes
void cfgPorts(void);
void delay(long ltime);
             
int main(void)
{	

	int init =0;
	cfgPorts();	
	turnOnRedLed;
	turnOffGreenLed;
	turnOffBlueLed; 
	for(;;)
    {
		while((init | readPortB(btn1)) == 0){
		turnOffRedLed;
		turnOffGreenLed;
		turnOffBlueLed;
		}
		//if((GPIOB_PDIR & 0x00000008) == 0)
		if(readPortB(btn1) == nButtonPressed)
		{
			turnOnRedLed;
			turnOffGreenLed;
			turnOffBlueLed;
			init = 1;
		}
		else{
			turnOffRedLed;
			turnOnGreenLed;
			turnOffBlueLed;
		}
    } 
    return 0;
}
 //--------------------------------------------------------------
void cfgPorts(void)
{
    //Turn on clock for portb and portd
    SIM_SCGC5 = SIM_SCGC5_PORTB_MASK;
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;   
     
    /* Set pins of PORTB as GPIO */
    PORTB_PCR3 	= PORT_PCR_MUX(1);
	PORTB_PCR18 = PORT_PCR_MUX(1);
    PORTB_PCR19 = PORT_PCR_MUX(1);
	PORTB_PCR1 	= PORT_PCR_MUX(1);
     
    //Configure all PortB as outputs
    GPIOB_PDDR = 0xFFFFFFF7; //1111 1111 1111 1111 1111 1111 1111 0111
     
    //Configure all PortD as outputs
    GPIOD_PDDR = 0xFFFFFFFF;
}
//--------------------------------------------------------------
void delay(long ltime)
{
	while (ltime > 0)
	{
		ltime--;
	}
}
