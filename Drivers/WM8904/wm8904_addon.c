#include "wm8904.h"

/**
 * ---------------------------------------------------------------------
 * Loopback mode for IN2L/R input (aka audio bypass) - Steps to do it.
 * ---------------------------------------------------------------------
 * 1. Enable left and right input PGAs
 * 	R12=0b11 (0x3)			# INL_ENA=INR_ENA=1
 * 	
 * 2. Select Analogue Input configuration
 * 	R46=0b1010100 (0x54)	# L_MODE=00 (single ended), L_IP_SEL_N=L_IP_SEL_P=01 (set analogue input signal path to IN2L), INL_CM_ENA=1 (default value)
 * 	R47=0b1010100 (0x54)	# R_MODE=00 (single ended), R_IP_SEL_N=R_IP_SEL_P=01 (set analogue input signal path to IN2R), INR_CM_ENA=1 (default value)
 * 
 * 3. Enable analog bypass paths for headphone outputs
 * 	R61=0b1100 (0xC)		# HPL_BYP_ENA=1 Left input PGA (analogue bypass)
 * 							# HPR_BYP_ENA=1 Right input PGA (analogue bypass)
 * 	
 * 4. Set volume levels for left and right channels through registers R57, R58
 * 	R57=0b000111001 (0x39)	# HPOUTL_VOL=10 1101 (left output volume set to 0 db)
 * 	R58=0b000111001 (0x39)	# HPOUTR_VOL=10 1101 (right output volume set to 0 db)
 * 
 * 5. Enable left and right output channels
 * 	R14=0b11 (0x3)			# HPL_PGA_ENA=1 HPR_PGA_ENA=1 
 **/ Function to initialize the WM8904 codec in loopback mode


int32_t WM8904_InitLoopback(WM8904_Object_t *pObj)
{
    WM8904_Init_t codec_init;

    // Set the input device to MIC1 and MIC2
    codec_init.InputDevice = WM8904_IN_MIC1_MIC2;

    // Set the output device to headphones
    codec_init.OutputDevice = WM8904_OUT_HEADPHONE;

    // Set the audio frequency (e.g., 44.1 kHz)
    codec_init.Frequency = WM8904_FREQUENCY_44K;

    // Set the audio resolution (e.g., 16-bit)
    codec_init.Resolution = WM8904_RESOLUTION_16B;

    // Set the volume (e.g., 50%)
    codec_init.Volume = 50;

    // Initialize the codec with the specified parameters
    return WM8904_Init(pObj, &codec_init);
}