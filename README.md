# PMIC
MPS5475 and Texas PMIC programming scripts

PLLTS12FFCFRACF Programmable Fractional PLL and 100MHz CLK programming

*** **** README.txt - This file describes about the procedure of execution of the scripts for the MKB Validation Board **** ***

1.  Place the scripts in the BOOT partition of th sd card
2.  Insert the sd card in the Zybo / Zed board and power on the board and wait for it to boot successfully
3.  After the Zed or Zybo board is booted successfully -
	a. Check for ls ../../media/
	b. If nothing present in it then run the following commands to mount the BOOT partition onto the sd card
		i.   mkdir -p /mnt/scripts
		ii.  mount /dev/mmcblk0p1 /mnt/scripts
		iii. Check for the script if present in the path ls /mnt/scripts
		iv.  Navigate to that directory cd /mnt/scripts
4.  Make the conections of the Zybo / Zed board PMOD interface with the J37 header of the validation board with proper I2C0 and I2C1 interface having a common ground
 	*** Note *** For Zybo board the PMOD interface is JE header pins and for the Zed board the PMOD interface is JF header pins
6.  After placing the power modules in their respective slots, power on the validation board
    *** Note *** For Zybo board the PMOD interface if JE header pins and for the Zed board the PMOD interface is JF header pins
5.  After placing the power modules in their respective slots, power on the validation board 
	a. I2C0 - J60
	b. I2C1 - J4
	  *** Note *** Do not interchange the power modules in any case
	  *** Note *** Wait for some time to stabilise the regulators
	  *** Note *** After power on ensure that the 12V, 0.75V and 3.3V power supply regulator LEDs were turned on. If not then turn off the power immedialtely
	  *** Note *** The 1.8V power supply regulator will be turning on only when the PMIC power modules were programmed successfully
7.  Slaves present on the I2C0 bus -
    i.   0x10, 0x11, 0x12, 0x13 - ADS7138 (power monitors)
    ii.  0x21 - I/O Expander for Resets control (both MKB and GFx)
    iii. 0x20, 0x70, 0x72 - PMIC power modules (I/O expander to control the power goods of the PMICs and Mux selection channels)
    iv.  0x6C - Clock buffer
    v.   0x68 - 100MHz clock generator
    *** Note *** If J13 header is closed the clock generator doesn’t fall on the I2C0 bus
8.  Slaves present on the I2C1 bus -
    i. 0x20, 0x70, 0x72 - PMIC power modules (I/O expander to control the power goods of the PMICs and Mux selection channels)
9.  Run the commands i2cdetect -y -r -a 0  and i2cdetect -y -r -a 1 to check if all the slave devices were present on the respective buses with respective slave addresses
    *** Note *** The I/O expander (0x21) won’t present initially on the I2C0. It can be seen after the voltage programming of the PMIC power modules as it has a dependency of VDD_IO_1V8 (1.8V) supply
10. To power-up the rails of J4 slot run ./J4_PMIC_ENABLE_VER2.sh script
11. To power-up the rails of the J60 slot run ./J60_PMIC_ENABLE_VER2.sh script
12. To monitor the power rails have been programmed successfully run ./power_monitor.sh script
13. Ensure that all the voltage values are within the ranges 
	  *** Note *** If any of the power rail noted to be recorded as zero value then immediately turn off the board
	  *** Note *** Wait for some time to stabilise the power rails and start your respective work 
14. Rerun the commands i2cdetect -y -r -a 0  and i2cdetect -y -r -a 1 to check if all the slave devices were present on the respective buses with respective slave addresses
    *** Note *** Now you should be seeing the I/O expander (0x21) on the I2C0 bus
15. To check the status of the Power goods of the PMIC power modules run the following commands -
    a. i2cget -y 0 0x20 0x01 - This should return 0x1f confirming that all the PMICs on I2C0 (J60 slot) have been programmed successfully and in a good state 
    b. i2cget -y 1 0x20 0x01 - This should return 0x1f confirming that all the PMICs on I2C0 (J60 slot) have been programmed successfully and in a good state
16. To issue reset for the MKB (using the I/O control) incase of the push button does not work run ./MKB_RESET.sh script
17. To issue reset for the GFx (using the I/O control) incase of the push button does not work run ./GF_RESET.sh script
18. To issue all the resets at once (using the I/O control) run ./GLOBAL_RESET.sh script
19. For the 100MHz clock generator and clock buffer to operate close the J13 header (short pins 1,2) with a jumper before power on the validation board
20. To reprogram the J4 (I2C1 slot) PMIC power module if necessary run ./RESET_J4_I2C1_PMIC.sh script
21. To reprogram the J60 (I2C0 slot) PMIC power module if necessary run ./RESET_J60_I2C0_PMIC.sh script
    *** Note *** Run these scripts if incase any voltage reading has exceeded its limit and a reprogramming is to be done to nullify it by disabling the power goods of the PMICs
    *** Note *** If the Power goods were downed then for the next power on of the validation board the PMICs of J4 (I2C1) and J60 (I2C0) slots should be programmed with their respective voltage values and to placed in their respective slots

*** ****                                                                                  **** ***
