/* This file contains test cases for the PLL Initialisation API based on PLLTS12FFCFRACF for Goldfinch */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include "pll_init_gfh.h"
#include "test_pll_init_gfh.h"

/**** ---- pll_frac_mode_lock ---- ****/
/*
 * @brief - frac_mode_en - Yes
 *
 */
void pll_frac_mode_lock(void) {
	printf("\n *** --- pll_frac_mode_lock test -> TC_001 --- *** \n");
	/*** --- Scenario 1 -> Input - 133 MHz, Output - 1066 MHz --- ***/
	printf("\n *** --- Scenario 1: 133 MHz input, 1066MHz output --- *** \n");
	float output_freqs_gfh1[] = {1066.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh1, 1, 133.0f);
	if (status == PLL_INIT_SUCCESS) {
		printf("Scenario 1 PLL initialized and locked successfully\n");
		printf("Expected Output - 1066MHz\n");

		// --- Poll the frac_mode_en bit --- //
		int timeout = 10000;
		int frac_mode_en = 0;

		while (timeout--) {
			uint32_t reg_val = readl(GFH_PLL_CTRL1_ADDR);
			if (reg_val & PLL_DSM_EN_BIT) {
				frac_mode_en = 1;
				break;
			}
		}

		if (frac_mode_en) {
			printf("Scenario 1: Fractional mode (dmsen) enabled and PLL locked successfully \n");
		} else {
			printf("Scenario 1: Timeout waiting for fractional mode (dmsen) enable \n");
		}
	} else {
		printf("Scenario 1 PLL initialization and locked failed with error code: %d\n", status);
	}
}

/**** --- pll_basic_lock ---- ****/
/* 
 * @brief - Basic PLL iniitialisation and Lock - Single Output
 *
 */
void pll_lock(void) {
	printf("\n *** --- pll_basic_lock test -> TC_002 --- *** \n");
	/*** --- Scenario 2 -> Input - 100 MHz, Output - up to 1 GHz --- ***/
	printf("\n *** --- Scenario 2: 100MHz input, Up to 1GHz output --- *** \n");
	float output_freqs_gfh2[] = {1000.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh2, 1, 100.0f);
	if (status == PLL_INIT_SUCCESS) {
		printf("Scenario 2 PLL iniitialized and locked successfully\n");
		printf("Expected Output - 1000MHz (can be configured for lower frequencies too)\n");
	} else {
		printf("Scenario 2 PLL initialization and locked failed with error code: %d\n", status);
	}
}

/**** ---- pll_edge_case_lock_high_input ---- ****/
/* 
 * @brief - PLL initialisation with edge case - High input frequency 
 *
 */
void pll_edge_case_lock_high_input(void) {
	printf("\n *** --- pll_edge_case_lock_high_input test -> TC_003 --- *** \n");
	/*** --- Scenario 4 -> Input - 500 MHz, Outputs - 1000 MHz, 500 MHz, 250 MHz --- ***/
	printf("\n *** --- Scenario 4: 500MHz input, [1000MHz, 500MHz, 250MHz] outputs --- *** \n");
	float output_freqs_gfh4[] = {1000.0f, 500.0f, 250.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh4, 3, 500.0f);
	if (status == PLL_INIT_SUCCESS) {
		printf("Scenario 4 PLL intialized and locked successfully\n");
		printf("Expected Output - 1000MHz, 500MHz, 250MHz\n");
	} else {
		printf("Scenario 4 PLL initialized and locked failed with error code: %d\n", status);
	}
}

/**** ---- pll_edge_case_lock_low_input ---- ****/
/*
 * @brief - PLL initialisation with edge case - Low input frequency 
 *
 */
void pll_edge_case_lock_low_input(void) {
	printf("\n *** --- pll_edge_case_lock_low_input test -> TC_004 --- *** \n");
	/*** --- Scenario 5 -> Input - 10 MHz, Output - 1000 MHz --- ***/
	printf("\n *** --- Scenario 5: 10MHz input, [1000MHz] output --- *** \n");
	float output_freqs_gfh5[] = {1000.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh5, 1, 10.0f);
	if (status == PLL_INIT_SUCCESS) {
		printf("Scenario 5 PLL initialized and locked successfully\n");
	} else {
		printf("Scenario 5 PLL initialized and locked failed with error code: %d\n", status);
	}
}

/**** ---- pll_invalid_input_case_below_min ---- ****/
/*
 * @brief - Invalid input reference frequency - below min
 *
 */
void pll_invalid_input_case_below_min(void) {
	printf("\n *** --- pll_invalid_input_case_below_min test -> TC_005 --- *** \n");
	/*** --- Scenario 6 -> Input - 7 MHz, Output - 100 MHz --- ***/
	printf("\n *** --- Scenario 6: No valid config found --- *** \n");
	float output_freqs_gfh6[] = {100.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh6, 1, 7.0f);
	if (status == PLL_INVALID_PARAMS) {
		printf("Scenario 6 returned %d\n", status);
	} else {
		printf("Scenario 6 falied with error code: %d\n", status);
	}
}

/**** ---- pll_invalid_case_above_max ---- ****/
/*
 * @brief - Invalid input reference frequency - above max 
 *
 */
void pll_invalid_input_case_above_max(void) {
	printf("\n *** --- pll_invalid_input_case_above_max test -> TC_006 --- *** \n");
	/*** --- Scenario 7 -> Input - 700 MHz, Output - 1000 MHz --- ***/
	printf("\n *** --- Scenario 7: 700MHz input, [1000MHz] output --- *** \n");
	float output_freqs_gfh7[] = {1000.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh7, 1, 700.0f);
	if (status == PLL_INVALID_PARAMS) {
		printf("Scenario 7 returned %d\n", status);
	} else {
		printf("Scenario 7 PLL falied with error code: %d\n", status);
	}
}

/**** ---- pll_invalid_output_case_below_min ---- ****/
/* 
 * @brief - Invalid desired output frequency - below min
 *
 */
void pll_invalid_output_case_below_min(void) {
	printf("\n *** --- pll_invalid_output_case_below_min test -> TC_007 --- *** \n");
	/*** --- Scenario 8 -> Input - 100 MHz, Output - 19 MHz --- ***/
	printf("\n *** --- Scenario 8: 100MHz input, [19MHz] output --- *** \n");
	float output_freqs_gfh8[] = {19.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh8, 1, 100.0f);
	if (status == PLL_FREQ_OUT_OF_RANGE) {
		printf("Scenario 8 returned %d\n", status);
	} else {
		printf("Scenario 8 falied with error code: %d\n", status);
	}
}

/**** ---- pll_invalid_output_case_above_max ---- ****/
/*
 * @brief - Invalid desired output frequnency - above max 
 *
 */
void pll_invalid_output_case_above_max(void) {
	printf("\n *** --- pll_invalid_output_case_above_max test -> TC_008 --- *** \n");
	/*** --- Scenario 9 -> Input - 100 MHz, Output - 9000 MHz --- ***/
	printf("\n *** --- Scenario 9: 100MHz input, [9000MHz] output --- *** \n");
	float output_freqs_gfh9[] = {9000.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh9, 1, 100.0f);
	if (status == PLL_FREQ_OUT_OF_RANGE) {
		printf("Scenario 9 returned %d\n", status);
	} else {
		printf("Scenario 9 falied with error code: %d\n", status);
	}
}

/**** ---- pll_invalid_config_case_vco_range_mismatch ---- ****/
/*
 * @brief - NO valid config found - VCO range mismatch
 *
 */
void pll_invalid_config_case_vco_range_mismatch(void) {
	printf("\n *** --- pll_invalid_config_case_vco_range_mismatch test -> TC_009 --- *** \n");
	/*** --- Scenario 12 -> Input - 100 MHz, Output - 50 MHz --- ***/
	printf("\n *** --- Scenario 12: 100MHz input, [50MHz] output --- *** \n");
	float output_freqs_gfh12[] = {50.0f};
	pll_init_status_t status = pll_init_gfh(output_freqs_gfh12, 1, 100.0f);
	if (status == PLL_NO_VALID_CONFIG) {
		printf("Scenario 12 returned %d\n", status);
	} else {
		printf("Scenario 12 falied with error code: %d\n", status);
	}
}

int main(void) {
	void pll_frac_mode_lock(void);
	void pll_lock(void); 
	void pll_edge_case_lock_high_input(void); 
	void pll_edge_case_lock_low_input(void); 
	void pll_invalid_input_case_below_min(void); 
	void pll_invalid_input_case_above_max(void);
	void pll_invalid_output_case_below_min(void); 
	void pll_invalid_output_case_above_max(void); 
	void pll_invalid_config_case_vco_range_mismatch(void); 
}
