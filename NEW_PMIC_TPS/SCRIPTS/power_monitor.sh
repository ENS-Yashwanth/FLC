
	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x0 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN0: VDD_CORE"\t""\t":             $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x1 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN1: GF23-VDDQ"\t""\t":            $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x2 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN2: IPM_MEM_VDD2"\t":         $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x3 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN3: VDD_IO_1V8"\t":           $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x4 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN4: VDD_RDIMM56"\t":          $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x5 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN5: EP12_VDDL"\t""\t":            $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x6 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN6: VDD_RDIMM12"\t":          $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x10 0x8 0x11 0x7 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN7: VPP_RDIMM56"\t":          $output




	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x0 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN0: EP12_VDDH"\t""\t":            $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x1 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN1: RC2-VDDL"\t""\t":             $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x2 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN2: VPP_RDIMM12"\t":           $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x3 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN3: RC1-VDDH"\t""\t":             $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x4 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN4: GF23-VDD"\t""\t":             $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x5 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN5: GF01-VDDQ"\t""\t":            $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x6 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN6: IPM_VDDQ_VDD"\t":         $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x11 0x8 0x11 0x7 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN7: EP34_VDDL"\t""\t":            $output




	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x0 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN0: VDD_RDIMM34"\t":          $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x1 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN1: EP34_VDDH"\t""\t":            $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x2 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN2: VPP_RDIMM78"\t":          $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x3 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN3: GF01-VDD"\t""\t":             $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x4 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN4: VDD_RDIMM78"\t":          $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x5 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN5: RC1-VDDL"\t""\t":             $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x6 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN6: VPP_RDIMM34"\t":          $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x12 0x8 0x11 0x7 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN7: GND"\t""\t":                  $output




	voltage_hex=$(i2ctransfer -y 0 w3@0x13 0x8 0x11 0x0 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN0: IPM_MEM_VDDQ"\t":         $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x13 0x8 0x11 0x1 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN1: D2D_VDDQ"\t""\t":             $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x13 0x8 0x11 0x2 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*3.3/4096}")
	echo -e AIN2: 1V8"\t""\t":                  $output

	voltage_hex=$(i2ctransfer -y 0 w3@0x13 0x8 0x11 0x3 r2)
	voltage_hex_ub=$(echo $voltage_hex | cut -d' ' -f1)
	voltage_hex_ub_shifted=$(($voltage_hex_ub << 8))
	voltage_hex_lb=$(echo $voltage_hex | cut -d' ' -f2)
	voltage_total=$(($voltage_hex_ub_shifted + $voltage_hex_lb))
	voltage=$(($voltage_total >> 4))
	output=$(awk "BEGIN {print $voltage*2*3.3/4096}")
	echo -e AIN3: 3V3"\t""\t":                  $output
