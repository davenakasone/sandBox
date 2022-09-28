//Matthew Howard and Mina Rofael
//CpE200L - 1001
//Final Project LCD Display

module lcd(
	input CLOCK_50,  	  //50 MHz clock
	output LCD_ON,	 	  // lcd power on/off
	output LCD_BLON, 	  //lcd backlight on/off
	output LCD_RW,	 	  //lcd read/write (0 = write, 1 = read)
	output LCD_EN,   	  //lcd enable
	output LCD_RS,	 	  //lcd command/data select, 0 = command, 1 = data
	input [7:0] LCD_DATA, //lcd data bus 8 bits
	
	

