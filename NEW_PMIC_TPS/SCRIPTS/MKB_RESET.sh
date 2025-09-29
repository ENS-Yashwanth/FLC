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

echo "Releasing MKB Resets...."

i2cset -y 0 0x21 0x06 0xF8   #Configure pins as outputs
i2cset -y 0 0x21 0x07 0xFF

i2cset -y 0 0x21 0x02 0x01   #CB_nPOR released
sleep 1
i2cset -y 0 0x21 0x02 0x03   #CB_nRST released
sleep 1
i2cset -y 0 0x21 0x02 0x07   #CORERST_n released
sleep 1
