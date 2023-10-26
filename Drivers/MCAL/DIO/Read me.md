	Digital I/O driver for the microcontroller ATMega 32
	    Created By: Omar Abdul Qadir   Version= 4.0
		Date: 25/10/2023,	      Day: Wednesday


Note: 

	All the data in the file is readable, And any editing will affect the controller's behavior.
	So It's not recommended to edit any data, Unless you are sure of what is the effect on behaviors.


1. Basic Driver function:

	a. Define the direction of pins and ports to be either output or input.
	b. Assign values to the output pins and ports.
	c. Get the values of the input pins and ports.
	
2. Pins and ports states through regesters:

	-----------------------------------------------------------------
	| State          | DDRx | PORTx | State description             | 
	|----------------------------------------------------------------
	| OUTPUT / LOW   |  1   |   0   | output port & its state is 0  |
	| ---------------------------------------------------------------
	| OUTPUT / HIGH  |  1   |   1   | output port & its state is 1  |
	| ---------------------------------------------------------------
	| INPUT / FLOAT  |  0   |   0   | input port floating if not    |
	|                |      |       | stated by another component   |
	| ---------------------------------------------------------------
	| INPUT / PULLUP |  0   |   1   | input port pulled up to HIGH  |
	|                |      |       | by internal pull up circuit   |
	-----------------------------------------------------------------

3. List of driver functions:

	I. INIT Function:
		a. DIO_vInit( void )
	
	II. Set direction:
		a. DIO_vSetPortDirection( u8 copy_u8PortID , u8 copy_u8PortDirection )
		b. DIO_vSetPinDirection( u8 copy_u8PortID , u8 copy_u8PinID , u8 copy_u8PinDirection )

	III. Set output value:
		a. DIO_vSetPortValue( u8 copy_u8PortID , u8 copy_u8PortValue )
		b. DIO_vSetPinValue( u8 copy_u8PortID , u8 copy_u8PinID , u8 copy_u8PinValue )
	
	IIII. Get input value:
		a. DIO_u8GetPortValue( u8 copy_u8PortID , u8* ptr_u8PortValue )
		b. DIO_u8GetPinValue( u8 copy_u8PortID , u8 copy_u8PinID , u8* ptr_u8PinValue )
