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
 * 
 **/ 

// Function to initialize the WM8904 codec in loopback mode
int32_t WM8904_InitLoopback(WM8904_Object_t *pObj)
{
    WM8904_Init_t codec_init;
    int32_t ret;
    uint16_t reg_value;

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

    // Write 0x3 to register 12 (0x0C) to enable left and right input PGAs
    reg_value = 0x3;
    ret = wm8904_write_reg(&pObj->Ctx, 0x0C, &reg_value, 2U); // TODO: Replace 0x0C with WM8904_PWR_MANAGEMENT0
    if (ret != WM8904_OK) {
        return ret;
    }

    // Write 0x54 to register 46 (0x2E) to select analogue input configuration for left channel
    reg_value = 0x54;
    ret = wm8904_write_reg(&pObj->Ctx, 0x2E, &reg_value, 2U); // TODO: Replace 0x2E with WM8904_ANALOG_LEFT_INPUT1
    if (ret != WM8904_OK) {
        return ret;
    }   

    // Write 0x54 to register 47 (0x2F) to select analogue input configuration for right channel
    reg_value = 0x54;
    ret = wm8904_write_reg(&pObj->Ctx, 0x2F, &reg_value, 2U); // TODO: Replace 0x2F with WM8904_ANALOG_RIGHT_INPUT1
    if (ret != WM8904_OK) {
        return ret;
    }

    // Write 0xC to register 61 (0x3D) to enable analog bypass paths for headphone outputs
    reg_value = 0xC;
    ret = wm8904_write_reg(&pObj->Ctx, 0x3D, &reg_value, 2U); // TODO: Replace 0x3D with WM8904_ANALOG_OUTPUT12_ZC
    if (ret != WM8904_OK) {
        return ret;
    }

    // Write 0x39 to register 57 (0x39) to set volume level for left channel
    reg_value = 0x39;
    ret = wm8904_write_reg(&pObj->Ctx, 0x39, &reg_value, 2U); // TODO: Replace 0x39 with WM8904_ANALOG_OUTPUT1_LEFT
    if (ret != WM8904_OK) {
        return ret;
    }
    
    // Write 0x39 to register 58 (0x3A) to set volume level for right channel
    reg_value = 0x39;
    ret = wm8904_write_reg(&pObj->Ctx, 0x3A, &reg_value, 2U); // TODO: Replace 0x3A with WM8904_ANALOG_OUTPUT1_RIGHT
    if (ret != WM8904_OK) {
        return ret;
    }

    // Write 0x3 to register 14 (0x0E) to enable left and right output channels
    reg_value = 0x3;
    ret = wm8904_write_reg(&pObj->Ctx, 0x0E, &reg_value, 2U); // TODO: Replace 0x0E with WM8904_PWR_MANAGEMENT2
    if (ret != WM8904_OK) {
        return ret;
    }
    
    // Initialize the codec with the specified parameters
    ret = WM8904_Init(pObj, &codec_init);
    if (ret != WM8904_OK) {
        return ret;
    }

    return WM8904_OK;
}