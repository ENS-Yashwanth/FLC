#!/bin/bash

echo "Checking PMIC Power Goods on I2C0"

while [ "$(i2cget -y 0 0x20 0x01)" == "0x00" && "$(i2cget -y 0 0x20 0x00)" == "0x00" ]; do
	echo "PMIC Power Goods not ready on I2C0. Waiting..."
	sleep 1
done 

echo "PMIC Power Goods are ready on I2C0."

echo "Checking PMIC Power Goods on I2C1"

while [ "$(i2cget -y 1 0x20 0x01)" == "0x00" && "$(i2cget -y 1 0x20 0x00)" == "0x00" ]; do
	echo "PMIC Power Goods not ready on I2C1. Waiting..."
	sleep 1
done

echo "PMIC Power Goods are ready on I2C1."

echo "Releasing GF Resets...."

#GF0
i2cset -y 0 0x21 0x06 0xC0   #Configure pins as outputs
i2cset -y 0 0x21 0x07 0xFF

i2cset -y 0 0x21 0x02 0x0F   #GF0_CB_nPOR released
sleep 1
i2cset -y 0 0x21 0x02 0x1F   #GF0_CB_nRST released
sleep 1
i2cset -y 0 0x21 0x02 0x3F   #GF0_CORERST_n released
sleep 1

#GF1
i2cset -y 0 0x21 0x06 0x00   #Configure pins as outputs
i2cset -y 0 0x21 0x07 0x3f

i2cset -y 0 0x21 0x02 0x7F   #GF1_CB_nPOR released
sleep 1
i2cset -y 0 0x21 0x02 0xFF   #GF1_CB_nRST released
sleep 1
i2cset -y 0 0x21 0x03 0x40   #GF1_CORERST_n released
sleep 1


#GF2
i2cset -y 0 0x21 0x06 0x00   #Configure pins as outputs
i2cset -y 0 0x21 0x07 0x07

i2cset -y 0 0x21 0x03 0x60   #GF2_CB_nPOR released
sleep 1
i2cset -y 0 0x21 0x03 0x70   #GF2_CB_nRST released
sleep 1
i2cset -y 0 0x21 0x03 0x78   #GF2_CORERST_n released
sleep 1

#GF3
i2cset -y 0 0x21 0x06 0x00   #Configure pins as outputs
i2cset -y 0 0x21 0x07 0x00

i2cset -y 0 0x21 0x03 0x7C   #GF3_CB_nPOR released
sleep 1
i2cset -y 0 0x21 0x03 0x7E   #GF3_CB_nRST released
sleep 1
i2cset -y 0 0x21 0x03 0x7F   #GF3_CORERSTn released
sleep 1
