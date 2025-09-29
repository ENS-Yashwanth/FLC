/* This file contains the header file for the file containing the test cases for the API for Initialisation based on PLLTS12FFCFRACF for Mockingbird */

#ifndef TEST_MKB_PLL
#define TEST_MKB_PLL

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include "pll_init_mkb.h"

/* Function prototypes */

void pll_frac_mode_lock(void);
void pll_lock(void); 
void pll_edge_case_lock_high_input(void); 
void pll_edge_case_lock_low_input(void); 
void pll_invalid_input_case_below_min(void); 
void pll_invalid_input_case_above_max(void);
void pll_invalid_output_case_below_min(void); 
void pll_invalid_output_case_above_max(void); 
void pll_invalid_config_case_vco_range_mismatch(void); 

#endif /* TEST_MKB_PLL */
