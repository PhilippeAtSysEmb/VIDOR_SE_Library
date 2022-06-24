#ifndef __VIDOR_SE_SOUND__
#define __VIDOR_SE_SOUND__

#include "VidorSECore.hpp"

#define SID_VOICE1_FREQ_LO  0
#define SID_VOICE1_FREQ_HI  1
#define SID_VOICE1_PULSE_LO 2
#define SID_VOICE1_PULSE_HI 3
#define SID_VOICE1_CTRG   4
#define SID_VOICE1_ATTACK 5
#define SID_VOICE1_SUSTAIN  6

#define SID_VOICE2_FREQ_LO  7
#define SID_VOICE2_FREQ_HI  8
#define SID_VOICE2_PULSE_LO 9
#define SID_VOICE2_PULSE_HI 10
#define SID_VOICE2_CTRG   11
#define SID_VOICE2_ATTACK 12
#define SID_VOICE2_SUSTAIN  13

#define SID_VOICE3_FREQ_LO  14
#define SID_VOICE3_FREQ_HI  15
#define SID_VOICE3_PULSE_LO 16
#define SID_VOICE3_PULSE_HI 17
#define SID_VOICE3_CTRG   18
#define SID_VOICE3_ATTACK 19
#define SID_VOICE3_SUSTAIN  20

#define SID_FILTER_FC_LO  21
#define SID_FILTER_FC_HI  22
#define SID_FILTER_RES    23
#define SID_FILTER_VOL    24

#define SID_SELECT_LEFT   0
#define SID_SELECT_RIGHT  32

#define SID_RESET     64

#define SID_REGISTER_VAL(chan, reg, val) (((chan|reg)<<8)|val)

#define VIDOR_SE_SID_REG_MAX_LEN	(102)

#define VIDOR_SE_COMMAND_SOUND_WRITE_SID_REG (8)
#define VIDOR_SE_COMMAND_SOUND_SET_STEREO_MODE (0x01)

#define VIDOR_SE_SOUND_STEREO (0)
#define VIDOR_SE_SOUND_MONO (1)

class VidorSESound
{
	public:
		uint8_t WriteSIDRegisters(uint16_t* pu16Values, uint8_t u8Size);
    uint8_t WriteUniqueSIDRegister(uint8_t u8Chan, uint8_t u8Reg, uint8_t u8Value);
    uint8_t SetStereoMode(uint8_t u8Mode);

	
};

extern VidorSESound FPGASound;
#endif
