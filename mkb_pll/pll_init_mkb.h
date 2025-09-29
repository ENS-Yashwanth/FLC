/* This is the header file for the file containing the API for PLL Initialisation based on PLLTS12FFCFRACF for Mockingbird (MKB) */

#ifndef MKB_PLL
#define MKB_PLL

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>


/* Define status codes for error handling */
typedef enum {
	PLL_INIT_SUCCESS = 0,
	PLL_INVALID_PARAMS,
	PLL_FREQ_OUT_OF_RANGE,
	PLL_NOT_LOCKED,
	PLL_NO_VALID_CONFIG
} pll_init_status_t;

/* PLL configuration parameters */
typedef struct {
	uint32_t ref_div;        // Reference clock divider (REFDIV[5:0]) 
	float    fb_div;         // Feedback divider for VCO (integer / fractional) (FBDIV[11:0]) 
	uint32_t post_div_out_0; // Post divider for Output - 0
	uint32_t post_div_out_1; // Post divider for Output - 1
	uint32_t post_div_out_2; // Post divider for Output - 2
	uint32_t post_div_out_3; // Post divider for Output - 3
} pll_config_t;

/* Base Address for PLL registers */
#define MKB_PLL_CTRL1_ADDR       0x26000100
#define MKB_PLL_CTRL2_ADDR       0x26000104
#define MKB_PLL_CTRL3_ADDR       0x26000108

/* Valid ranges (integer mode / fractional mode) */
#define FREF_MIN_MHZ_INT      8.0f    // Input frequency range 8 MHz (integer mode) (minimum) 
#define FREF_MIN_MHZ_FRAC     10.0f   // Input frequency range 10 MHz (fractional mode) (minimum)
#define FREF_MAX_MHZ          650.0f  // Input frequency range 650 MHz (maximum)
#define FOUT_MIN_MHZ          31.0f   // Output frequency range 31 MHz (minimum)
#define FOUT_MAX_MHZ          8000.0f // Output frequency range 8000 MHz (maximum)
#define VCO_FREQ_MIN_MHZ      2000.0f // VCO frequency range 2000 MHz (minimum)
#define VCO_FREQ_MAX_MHZ      8000.0f // VCO frequency range 8000 MHz (maximum)
#define PFD_FREQ_MIN_MHZ      8.0f    // PFD frequency range 8 MHz (minimum)
#define PFD_FREQ_MAX_MHZ      160.0f  // PFD frequnecy range 160 MHz (maximum)
#define REFDIV_MIN            1       // Reference divider (M) (minimum)
#define REFDIV_MAX            63      // Reference divider (M) (maximum)
#define FBDIV_MIN_INT         16      // Feedback divider (N) (integer mode) (minimum)
#define FBDIV_MAX_INT         1000    // Feedback divider (N) (integer mode) (maximum)
#define FBDIV_MIN_FRAC        20      // Feedback divider (N) (fractional mode) (minimum)
#define FBDIV_MAX_FRAC        1000    // Feedback divider (N) (fractional mode) (maximum)
#define POSDIV_MIN            1       // Post divider (Px) (minimum)
#define POSDIV_MAX            64      // Post divider (Px) (maximum)
#define NUM_OUTPUTS_MIX       0       // Minimum number of outputs generation
#define NUM_OUTPUTS_MAN       5       // Maximum number of outputs generation

/********************************************************************************
 * MKB_PLL_CTRL1 (0x26000100) BITFIELD DEFINITIONS
 ********************************************************************************/

// BITS
#define PLL_LOCKED_BIT          (1 << 30) // 0x40000000
#define PLL_DSM_EN_BIT          (1 << 20) // 0x100000
#define PLL_DAC_EN_BIT          (1 << 1)  // 0x2
#define PLL_ENABLE_BIT          (1 << 0)  // 0x1
/********************************************************************************/

/********************************************************************************
 * MKB_PLL_CTRL2 (0x26000104) BITFIELD DEFINITIONS
 ********************************************************************************/

// SHIFTS
#define POSDIV2_SHIFT           28
#define POSDIV1_SHIFT           24
#define POSDIV0_SHIFT           20
#define FBDIV_SHIFT             6
#define REFDIV_SHIFT            0

// MASKS
#define POSDIV2_MASK            (0xF)   // 4 bits - [31:28]
#define POSDIV1_MASK            (0xF)   // 4 bits - [27:24] 
#define POSDIV0_MASK            (0xF)   // 4 bits - [23:20]
#define FBDIV_MASK              (0xFFF) // 12 bits - [17:6]
#define REFDIV_MASK             (0x3F)  // 6 bits - [5:0]
/********************************************************************************/

/********************************************************************************
 * MKB_PLL_CTRL3 (0x26000108) BITFIELD DEFINITIONS
 ********************************************************************************/

// SHIFTS
#define FOUTEN_SHIFT            28
#define POSDIV3_SHIFT           24
#define FRAC_SHIFT              0

// MASKS
#define FOUTEN_MASK             (0xF)      // 4 bits - [31:28] -> enables/disables PLL outputs
#define POSDIV3_MASK            (0xF)      // 4 bits - [27:24] -> divider for output 3
#define FRAC_MASK               (0xFFFFFF) // 24 bits - [23:0] -> fractional part of feedback divider
/********************************************************************************/

/* 
 * SHIFT - bit starting position of a field
 * 	 - bit position of the least significant bit (LSB) of that field
 * 	 
 * MASK - bit-width mask (before shifting) that limits how many bits are valid for that field
 *      - binary mask (before shifting) for the width of that field
 *
 * To insert a value into a field -> reg |= ((value & MASK) << SHIFT)
 *
 * To extract a value from a field -> field = ((reg >> SHIFT) & MASK)
 */

/* Function prototypes */

static int check_pll_lock(void);
pll_init_status_t pll_init_mkb(const float desired_output_freq_mhz[], uint32_t num_outputs, float input_ref_freq_mhz);
static void pll_configuration(float input_ref_freq_mhz, const float desired_output_freq_mhz[], uint32_t num_outputs, const pll_config_t* pll_cfg, float F_PFD, float vco_freq_mhz, int frac_mode_en);

#endif /* MKB_PLL */
