/* This file contains API for PLL Initialization based on PLLTS12FFCFRACF for Goldfinch (GFH) */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#include "pll_init_gfh.h"

/**** ---- Check PLL LOCK Bit Status ---- ****/
/*
 * @brief - Checks the PLL lock status by reading the desginated status register
 *
 * This function simulates PLL lock by checking the PLL_LOCKED_BIT in GFH_PLL_CTRL1_ADDR (0x26000100)
 *
 * @return - 1 if PLL is locked, 0 otherwise
 *
 */
static int check_pll_lock(void) {
	return (readl(GFH_PLL_CTRL1_ADDR) & PLL_LOCKED_BIT) ? 1 : 0;
}

/**** ---- PLL Configuration Found ---- ****/
/*
 * @brief - Print the PLL Configuration
 *
 * @param[in] - input_ref_freq_mhz - The input refrence clock frequency in MHz to the PLL
 *
 * @param[in] - desired_output_freq_mhz[] - An array of desired output frequencies in MHz for each PLL output.
 * The size of this array should coorespond to the number of PLL outputs being configured
 *
 * @param[in] - num_outputs - The number of PLL outputs to configure
 *
 * @param[in] - pll_cfg - structure pointer for pll_config_t, which consists of ref_div, fb_div, post_div_out_0, post_div_out_1, post_div_out_2, post_div_out_3 
 *
 * @param[in] - F_PFD - Input reference frequency divided by the pre-divider M
 *
 * @param[in] - vco_freq_mhz - Output frequency from the VCO
 *
 * @param[in] - fractional_mode_en - 1 to enable delta-sigma mode (fractional), 0 to disable delta-sigma mode (integer)
 *
 */
static void pll_configuration(float input_ref_freq_mhz, const float desired_output_freq_mhz[], uint32_t num_outputs, const pll_config_t* pll_cfg, float F_PFD, float vco_freq_mhz, int fractional_mode_en) {
	printf("PLL Configuration Found - \n\r");
	printf("	- INPUTS: \n\r");
	printf("		Fref: %.2f MHz\n\r", input_ref_freq_mhz);
	printf("	- OUTPUTS: \n\r");
	for (uint32_t i = 0; i < num_outputs; i++) {
		printf("		Desired Fout[%u]: %.2f MHz\n\r", i, desired_output_freq_mhz[i]);
	}
	printf("	- CALCULATED PLL PARAMETERS: \n\r");	
	printf("		F_PFD (Fref / M): %.2f MHz\n\r", F_PFD);
	printf("		VCO_Freq: %.2f MHz\n\r", vco_freq_mhz);
	printf("		Fractional mode Enabled: %s\n\r", fractional_mode_en ? "Yes" : "No");
	printf("	- CALCULATED DIVIDERS: \n\r");
	printf("		ref_div (M): %u\n\r", pll_cfg->ref_div);
	printf("		fb_div (N): %.2f\n\r", pll_cfg->fb_div);
	if (num_outputs > 0) printf("		PostDiv0 (P0): %u\n\r", pll_cfg->post_div_out_0);
	if (num_outputs > 1) printf("		PostDiv1 (P1): %u\n\r", pll_cfg->post_div_out_1);
	if (num_outputs > 2) printf("		PostDiv2 (P2): %u\n\r", pll_cfg->post_div_out_2);
	if (num_outputs > 3) printf("		PostDiv3 (P3): %u\n\r", pll_cfg->post_div_out_3);
}

/**** ---- PLL Initialization API Function ---- ****/
/*
 * @brief - Initializes and configures the PLL to generate the desired output clocks for any valid Fref, by dynamically calculating the divider values
 *
 * This function contains a generic algorithm to determine the necessary ref_div, fb_div and post_div_out_X values based on the input reference frequency, num_outputs and the array of desired output frequencies.
 * It attempts to find a valid configuration that allows the PLL to lock and generate the specified outputs.
 * It also includes error checking for input parameters and PLL lock status.
 *
 * @brief - ref_div - reference divider (M) (divide F_REF by this)
 *
 * @brief - fb_div - feedback divider (N) (F_VCO = F_REF * fb_div / ref_div)
 *
 * @brief - fractional_mode_en - 1 to enable delta-sigma mode (fractional), 0 to disable delta-sigma mode (integer)
 *
 * @brief - pos_div_out_0, pos_div_out_1, pos_div_out_2, pos_div_out_3, pos_div_out_4 - output post dividers (P0, P1, P2, P3, P4)
 *
 * @param[in] - desired_output_freq_mhz[] - An array of desired output frequencies in MHz for each PLL output.
 * The size of this array should correspond to the number of PLL outputs being configured.
 *
 * @param[in] - num_outputs - The number of PLL outputs to configure.
 *
 * @param[in] - input_ref_freq_mhz - The input reference clock frequency in MHz to the PLL.
 *
 * @return - pll_init_status_t - Status of the PLL initialization, including lock status.
 * 			       - Return PLL_INIT_SUCCESS on successful initialization and lock, or respective error code otherwise.
 *
 * Formulae - F_VCO = F_REF * (N / M)
 * 	    - F_OUT = F_VCO / Px
 * 	    - F_VCO_min = smallest_output_freq * POSDIV_MIN
 * 	    - F_VCO_max = largest_output_freq * POSDIV_MAX
 *
 */
pll_init_status_t pll_init_gfh(const float desired_output_freq_mhz[], uint32_t num_outputs, float input_ref_freq_mhz) {

	pll_config_t pll_cfg = {0}; // Initialize all members to 0
	uint32_t reg_val;
	uint32_t timeout_counter = 1000000; // Arbitrary timeout for PLL lock
	int fractional_mode_en = 0;

	/*** --- 1. Parameter validation --- ***/

	if ((input_ref_freq_mhz < FREF_MIN_MHZ_INT && input_ref_freq_mhz < FREF_MIN_MHZ_FRAC) || input_ref_freq_mhz > FREF_MAX_MHZ) {
		return PLL_INVALID_PARAMS;
	}

	if (num_outputs < NUM_OUTPUTS_MIN || num_outputs > NUM_OUTPUTS_MAX) {
		return PLL_INVALID_PARAMS;
	}

	for (uint32_t i = 0; i < num_outputs; i++) {
		if (desired_output_freq_mhz[i] < FOUT_MIN_MHZ || desired_output_freq_mhz[i] > FOUT_MAX_MHZ) {
			return PLL_FREQ_OUT_OF_RANGE;
		}
	}

	/*** --- 2. Calculate PLL Divider values --- ***/

	// VCO_freq = Fref * (fb_div / ref_div)
	// Fout = VCO_freq / post_div_out_X

        float vco_freq_mhz = 0.0f;
	int valid_config = 0;
	float F_PFD = 0.0f;

	float max_desired_output = 0.0f;
	float min_desired_output = FOUT_MAX_MHZ + 1.0f;

	for (uint32_t i = 0; i < num_outputs; i++) {
		if (desired_output_freq_mhz[i] > max_desired_output) {
			max_desired_output = desired_output_freq_mhz[i];
		}
		if (desired_output_freq_mhz[i] < min_desired_output) {
			min_desired_output = desired_output_freq_mhz[i];
		}
	}

	// Iterate through possible ref_div (M) values (1 to 63)

	for (pll_cfg.ref_div = REFDIV_MIN; pll_cfg.ref_div <= REFDIV_MAX; pll_cfg.ref_div++) {
		F_PFD = input_ref_freq_mhz / pll_cfg.ref_div;

		if (F_PFD < PFD_FREQ_MIN_MHZ || F_PFD > PFD_FREQ_MAX_MHZ) {
			continue;
		}

		// Iterate through possible common VCO frequencies based on actual PLL VCO range
		// VCO_min = smallest_output_freq * POSDIV_MIN
		// VCO_max = largest_output_freq * POSDIV_MAX
		// Also, candidate_vco must be within PLLs VCO_FREQ_MIN_MHZ and VCO_FREQ_MAX_MHZ

		float current_effective_max_vco = fminf(VCO_FREQ_MAX_MHZ, max_desired_output * POSDIV_MAX);
		float current_effective_min_vco = fmaxf(VCO_FREQ_MIN_MHZ, min_desired_output * POSDIV_MIN);

		// Iterate from PLL_VCO_MIN to current_effective_max_vco or from PLL_VCO_MAX to current_effective_min_vco

		for (float candidate_vco = current_effective_min_vco; candidate_vco <= current_effective_max_vco; candidate_vco += F_PFD) {
			if (candidate_vco < VCO_FREQ_MIN_MHZ || candidate_vco > VCO_FREQ_MAX_MHZ) {
				continue;
			}

			float n_val_float = candidate_vco / F_PFD;
			uint32_t n_val_int = (uint32_t)roundf(n_val_float); // For integer part

			if (n_val_int < FBDIV_MIN_FRAC || n_val_int > FBDIV_MASK) {
				continue;
			}

			int all_outputs_valid = 1;
			int current_fractional_mode_needed = fabsf(n_val_float - n_val_int) > 0.001f;

			for (uint32_t i = 0; i < num_outputs; i++) {
				float post_div = candidate_vco / desired_output_freq_mhz[i];

				// Check for non-integer (with tolerance) or out of range Px

				if (fabsf(post_div - roundf(post_div)) > 0.001f || roundf(post_div) < POSDIV_MIN || roundf(post_div) > POSDIV_MAX) {
					all_outputs_valid = 0;
					break;
				}
			}

			// Also check if the FBDIV is exactly an integer or needs fractional mode

			if (!current_fractional_mode_needed && (n_val_int < FBDIV_MIN_INT || n_val_int > FBDIV_MAX_INT)) { 
				all_outputs_valid = 0;
			}

			if (all_outputs_valid) {
				// If a fractional value is needed for N, and its within fractional FBDIV bounds
				
				fractional_mode_en = current_fractional_mode_needed;
				vco_freq_mhz = candidate_vco;
				pll_cfg.fb_div = n_val_float;
				valid_config = 1;
				break;
			}
		}

		if (valid_config) break;
	}

	if (!valid_config) {
		return PLL_NO_VALID_CONFIG; // Could not find a suitable M, N, Px combination
	}

	// Calculate all post_div_out_X based on the vco_freq_mhz

	pll_cfg.post_div_out_0 = (num_outputs > 0) ? (uint32_t)roundf(vco_freq_mhz / desired_output_freq_mhz[0]) : 0;
	pll_cfg.post_div_out_1 = (num_outputs > 1) ? (uint32_t)roundf(vco_freq_mhz / desired_output_freq_mhz[1]) : 0;
	pll_cfg.post_div_out_2 = (num_outputs > 2) ? (uint32_t)roundf(vco_freq_mhz / desired_output_freq_mhz[2]) : 0;
	pll_cfg.post_div_out_3 = (num_outputs > 3) ? (uint32_t)roundf(vco_freq_mhz / desired_output_freq_mhz[3]) : 0;

	pll_configuration(input_ref_freq_mhz, desired_output_freq_mhz, num_outputs, &pll_cfg, F_PFD, vco_freq_mhz, fractional_mode_en);

	/*** --- 3. Program PLL Registers --- ***/

	uint32_t reg_ctrl1, reg_ctrl2, reg_ctrl3;

	// Program GFH_PLL_CTRL1 (0x26000100) (LOCK_BIT, DSM_EN_BIT, DAC_EN_BIT, ENABLE_BIT) 

	reg_ctrl1 = readl(GFH_PLL_CTRL1_ADDR); 
	writel(reg_ctrl1 & ~PLL_ENABLE_BIT, GFH_PLL_CTRL1_ADDR);

	// Program GFH_PLL_CTRL2 (0x26000104) (REFDIV, FBDIV_INT, POSDIV0, POSDIV1, POSDIV2)
	
	uint32_t fb_div_int = (uint32_t)pll_cfg.fb_div;

	reg_ctrl2 = readl(GFH_PLL_CTRL2_ADDR);

	// Clear all target fields first
	
	reg_ctrl2 &= ~((REFDIV_MASK << REFDIV_SHIFT) | (FBDIV_MASK << FBDIV_SHIFT) | 
			(POSDIV0_MASK << POSDIV0_SHIFT) | (POSDIV1_MASK << POSDIV1_SHIFT) | 
			(POSDIV2_MASK << POSDIV2_SHIFT));

	// Set new values
	
	reg_ctrl2 |= (pll_cfg.ref_div << REFDIV_SHIFT);
	reg_ctrl2 |= (fb_div_int << FBDIV_SHIFT);
	if (num_outputs > 0) reg_ctrl2 |= (pll_cfg.post_div_out_0 << POSDIV0_SHIFT);
	if (num_outputs > 1) reg_ctrl2 |= (pll_cfg.post_div_out_1 << POSDIV1_SHIFT);
	if (num_outputs > 2) reg_ctrl2 |= (pll_cfg.post_div_out_2 << POSDIV2_SHIFT);
	writel(reg_ctrl2, GFH_PLL_CTRL2_ADDR);

	// Program GFH_PLL_CTRL3 (0x26000108) (FRAC, POSDIV3, FOUT_EN)
	
	uint32_t fb_div_fractional_24bit = (fractional_mode_en) ? (uint32_t)((pll_cfg.fb_div - fb_div_int) * (1 << 24)) : 0;

	uint32_t fout_en_mask = (1 << num_outputs) - 1;

	reg_ctrl3 = readl(GFH_PLL_CTRL3_ADDR);

	// Clear all target fields first
	
	reg_ctrl3 &= ~((FRAC_MASK << FRAC_SHIFT) | (POSDIV3_MASK << POSDIV3_SHIFT) | (FOUTEN_MASK << FOUTEN_SHIFT));
	
	// Set new values
	
	reg_ctrl3 |= (fb_div_fractional_24bit << FRAC_SHIFT);
	reg_ctrl3 |= (fout_en_mask << FOUTEN_SHIFT);
	if (num_outputs > 3) reg_ctrl3 |= (pll_cfg.post_div_out_3 << POSDIV3_SHIFT);
	writel(reg_ctrl3, GFH_PLL_CTRL3_ADDR);

	// Program GFH_PLL_CTRL1 (0x26000100) (Fractional mode then enable PLL)
	
	reg_ctrl1 = readl(GFH_PLL_CTRL1_ADDR);
	
	if (fractional_mode_en) {
		reg_ctrl1 |= PLL_DSM_EN_BIT;
		reg_ctrl1 |= PLL_DAC_EN_BIT;
	} else {
		reg_ctrl1 &= ~(PLL_DSM_EN_BIT | PLL_DAC_EN_BIT);
	}
	writel(reg_ctrl1, GFH_PLL_CTRL1_ADDR);

	// Finally enable the PLL
	
	writel(reg_ctrl1 | PLL_ENABLE_BIT, GFH_PLL_CTRL1_ADDR);

	/*** --- 4. Wait for PLL Lock --- ***/

	while (timeout_counter > 0) {
		if (check_pll_lock()) {
			return PLL_INIT_SUCCESS; // PLL Lock successfully
		}
		timeout_counter --;
	}

	return PLL_NOT_LOCKED; // PLL did not lock within timeout
}

int main(void) {
	
	/*** --- 1. Clock Generation of 25MHz for GFH PLL --- ***/
	printf("\n *** --- Clock Generation of 25MHz for GFH PLL --- *** \n");
	printf("\n *** --- Input - 25MHz, Output - 1000MHz, 200MHz, 1000MHz, 1000MHz --- *** \n");
	float gfh_pll_output[] = {1000.0f};
	pll_init_status_t status = pll_init_gfh(gfh_pll_output, 1, 25.0f);
	if (status == PLL_INIT_SUCCESS) {
		printf("GFH PLL initialized and locked successfully\n");
		printf("Expected Output - 1000MHz\n");
	} else {
		printf("GFH PLL initialization and locked failed with error code: %d\n", status);
	}
	
}
