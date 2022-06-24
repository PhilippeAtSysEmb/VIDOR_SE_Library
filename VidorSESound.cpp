#include "VidorSESound.hpp"

VidorSESound FPGASound;

uint8_t VidorSESound::WriteSIDRegisters(uint16_t* pu16Values, uint8_t u8Size)
{
	uint8_t u8Tmp;
	uint8_t au8LocBuffer[VIDOR_SE_SID_REG_MAX_LEN];
	uint8_t u8Count = 0;

	if ((pu16Values == NULL) || (u8Size*2 + 2 > VIDOR_SE_SID_REG_MAX_LEN )) return VIDOR_SE_ERR_INVALID_PARAM;
	
	digitalWrite(slaveSelectPin, LOW);

	do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_SOUND, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_SOUND_WRITE_SID_REG, u8Count);

	for (u8Tmp = 0; u8Tmp < u8Size; u8Tmp++)
		VIDOR_SE_PUT16(au8LocBuffer, pu16Values[u8Tmp], u8Count);

	u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, u8Size*2+2);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Tmp;
}

uint8_t VidorSESound::WriteUniqueSIDRegister(uint8_t u8Chan, uint8_t u8Reg, uint8_t u8Value)
{
  uint16_t u16SIDReg;

  u16SIDReg = SID_REGISTER_VAL(u8Chan, u8Reg, u8Value);
    
  return WriteSIDRegisters(&u16SIDReg, 1);
  
}

uint8_t VidorSESound::SetStereoMode(uint8_t u8Mode) 
{
  uint8_t u8Tmp;
  uint8_t au8LocBuffer[4];
  uint8_t u8Count = 0;

  digitalWrite(slaveSelectPin, LOW);

  do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_SOUND, u8Count);
  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_SOUND_SET_STEREO_MODE, u8Count);

  VIDOR_SE_PUT16(au8LocBuffer, u8Mode, u8Count);

  u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, 4);

  digitalWrite(slaveSelectPin, HIGH);

  return u8Tmp;
}
