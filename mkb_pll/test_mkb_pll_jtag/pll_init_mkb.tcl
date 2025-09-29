# PLL Register Addresses
set MKB_PLL_CTRL1_ADDR 0x26000100
set MKB_PLL_CTRL2_ADDR 0x26000104
set MKB_PLL_CTRL3_ADDR 0x26000108

# Bitfield Definitions (CTRL1)
set PLL_LOCKED_BIT [expr {1 << 30}]
set PLL_DSM_EN_BIT [expr {1 << 20}]
set PLL_DAC_EN_BIT [expr {1 << 1}]
set PLL_ENABLE_BIT [expr {1 << 0}]

# Bitfiled Definitions (CTRL2)
set REFDIV_SHIFT  0
set REFDIV_MASK   0x3F
set FBDIV_SHIFT   6
set FBDIV_MASK    0xFFF
set POSDIV0_SHIFT 20
set POSDIV0_MASK  0xF
set POSDIV1_SHIFT 24
set POSDIV1_MASK  0xF
set POSDIV2_SHIFT 28
set POSDIV2_MASK  0xF

# Bitfield Definitions (CTRL3)
set FRAC_SHIFT    0
set FRAC_MASK     0xFFF
set POSDIV3_SHIFT 24
set POSDIV3_MASK  0xF
set FOUTEN_SHIFT  28
set FOUTEN_MASK   0xF

# PLL Configuration values
set ref_div_val           10
set fb_div_int_val        200
set fb_div_frac_24bit_val 0x123456
set posdiv_out_0_val      4
set posdiv_out_1_val      8
set posdiv_out_2_val      16
set posdiv_out_3_val      32
set num_outputs_val       4
set frac_mode_enabled     1

# Read current CTRL1 and clear ENABLE bit
set current_ctrl1 [mrd $MKB_PLL_CTRL1_ADDR]
set new_ctrl1 [expr {$current_ctrl1 & (!$PLL_ENABLE_BIT)}]
mwr $MKB_PLL_CTRL1_ADDR $new_ctrl1
puts "CTRL1 after disbaling PLL: [format 0x%08X $new_ctrl1]"

# --- Program CTRL2 ---
set reg_ctrl2_val 0
set reg_ctrl2_val [expr {($ref_div_val << $REFDIV_SHIFT) | ($fb_div_int_val << $FBDIV_SHIFT) | ($post_div_out_0_val << $POSTDIV0_SHIFT) | ($post_div_out_1_val << $POSTDIV1_SHIFT) | ($post_div_out_2_val << $POSTDIV2_SHIFT)}]

mwr $MKB_PLL_CTRL2_ADDR $reg_ctrl2_val
puts "CTRL2 programmed: [format 0x%08X $reg_ctrl2_val]"

# --- Program CTRL3 ---
set fouten_mask_val [expr {(1 << $num_outputs_val) - 1}] 
set reg_ctrl3_val [expr {($fb_div_frac_24bit_val << $FRAC_SHIFT) | ($post_div_out_3_val << $POSTDIV3_SHIFT) | ($fouten_mask_val << $FOTEN_SHIFT)}]

mwr $MKB_PLL_CTRL3_ADDR $reg_ctrl3_val
puts "CTRL3 programmed: [format 0x%08X $reg_ctrl3_val]"

# --- Program CTRL1 (Fractional mode) ---
set reg_ctrl1_val [mrd $MKB_PLL_CTRL1_ADDR]
if {$frac_mode_enabled} {
	set reg_ctrl_val [expr {$reg_ctrl1_val | $PLL_DSM_EN_BIT | $PLL_DAC_EN_BIT}]
} else {
	set reg_ctrl_val [expr {$reg_ctrl1_val & ~($PLL_DSM_EN_BIT | $PLL_DAC_EN_BIT)}]
}
mwr $MKB_PLL_CTRL1_ADDR $reg_ctrl1_val
puts "CTRL1 after fractional mode config: [format 0x%08X $reg_ctrl1_val]"

# --- Enable PLL ---
set final_ctrl1 [expr {$reg_ctrl1_val | $PLL_ENABLE_BIT}]
mwr $MKB_PLL_CTRL1_ADDR $final_ctrl1
puts "PLL Enabled: [format 0x%08X $final_ctrl1]"

# --- Poll for lock ---
set timeout 1000000
puts "Waiting for PLL lock ..."
while {$timeout > 0} {
	set pll_status [mrd $MKB_PLL_CTRL1_ADDR]
	if {[expr {$pll_status & $PLL_LOCKED_BIT}] != 0} {
		puts "PLL is locked"
		break
	}
	set timeout [expr {timeout - 1}]
}
if {$timeout == 0} {
	puts "PLL failed to lock within timeout"
}
