#include "VidorSECamera.hpp"


struct regval_list {
  unsigned short  addr;
  unsigned char  data;
};

static struct regval_list cam_640x480[] = {
  {0x0100, 0x00}, 
  {0x0103, 0x01}, 
  {0x3034, 0x08}, 
  {0x3035, 0x41}, 
  {0x3036, 0x46}, 
  {0x303c, 0x11},
  {0x3106, 0xf5}, 
  {0x3821, 0x07}, 
  {0x3820, 0x41},
  {0x3827, 0xec},
  {0x370c, 0x0f},
  {0x3612, 0x59}, 
  {0x3618, 0x00}, 
  {0x5000, 0x06}, 
  {0x5001, 0x00}, 
  {0x5002, 0x40}, 
  {0x5003, 0x08}, 
  {0x5a00, 0x08}, 
  {0x3000, 0x00}, 
  {0x3001, 0x00}, 
  {0x3002, 0x00}, 
  {0x3016, 0x08}, 
  {0x3017, 0xe0}, 
  {0x3018, 0x44}, 
  {0x301c, 0xf8}, 
  {0x301d, 0xf0}, 
  {0x3a18, 0x00}, 
  {0x3a19, 0xf8}, 
  {0x3c01, 0x80},
  {0x3b07, 0x0c}, 
  {0x380c, 0x07},
  {0x380d, 0x68}, 
  {0x380e, 0x03}, 
  {0x380f, 0xd8}, 
  {0x3814, 0x31},
  {0x3815, 0x31},
  {0x3708, 0x64}, 
  {0x3709, 0x52}, 
  
  {0x3808, 0x02}, // DVP output Horiz width
  {0x3809, 0x80}, // DVP output Horiz width = 640
  {0x380a, 0x01}, // DVP output Vert width
  {0x380b, 0xe0}, // DVP output Vert width = 480
  
  //{0x3808, 0x03}, // DVP output Horiz width
  //{0x3809, 0x20}, // DVP output Horiz width = 800
  //{0x380a, 0x02}, // DVP output Vert width
  //{0x380b, 0x58}, // DVP output Vert width = 600
  
  {0x3800, 0x00}, 
  {0x3801, 0x00}, 
  {0x3802, 0x00}, 
  {0x3803, 0x00}, 
  {0x3804, 0x0a}, 
  {0x3805, 0x3f}, 
  {0x3806, 0x07}, 
  {0x3807, 0xa1},
  {0x3811, 0x08}, 
  {0x3813, 0x02}, 
  {0x3630, 0x2e}, 
  {0x3632, 0xe2}, 
  {0x3633, 0x23}, 
  {0x3634, 0x44}, 
  {0x3636, 0x06}, 
  {0x3620, 0x64}, 
  {0x3621, 0xe0}, 
  {0x3600, 0x37}, 
  {0x3704, 0xa0}, 
  {0x3703, 0x5a}, 
  {0x3715, 0x78}, 
  {0x3717, 0x01}, 
  {0x3731, 0x02}, 
  {0x370b, 0x60}, 
  {0x3705, 0x1a}, 
  {0x3f05, 0x02}, 
  {0x3f06, 0x10},
  {0x3f01, 0x0a}, 
  {0x3a08, 0x01}, 
  {0x3a09, 0x27}, 
  {0x3a0a, 0x00}, 
  {0x3a0b, 0xf6}, 
  {0x3a0d, 0x04}, 
  {0x3a0e, 0x03}, 
  {0x3a0f, 0x58}, 
  {0x3a10, 0x50}, 
  {0x3a1b, 0x58}, 
  {0x3a1e, 0x50}, 
  {0x3a11, 0x60}, 
  {0x3a1f, 0x28}, 
  {0x4001, 0x02}, 
  {0x4004, 0x02}, 
  {0x4000, 0x09}, 
  {0x4837, 0x24}, 
  {0x4050, 0x6e}, 
  {0x4051, 0x8f}, 
  {0x4800, 0x14}, // End of line packet MUST be add to standard configuration !!
  {0x503d, 0x00}, 
  {0x0100, 0x01}, 
};


VidorSECamera FPGACamera;

uint8_t VidorSECamera::SetWindowAlpha(uint8_t u8Alpha) 
{
	uint8_t u8Tmp;
	uint8_t au8LocBuffer[4];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_CAMERA, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_CAMERA_ALPHA, u8Count);

	VIDOR_SE_PUT16(au8LocBuffer, u8Alpha, u8Count);

	u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, 4);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Tmp;
}


uint8_t VidorSECamera::WriteRegister(uint8_t u8Address, uint16_t u16Register, uint8_t u8Data ) 
{

	uint8_t u8Tmp;
	uint8_t au8LocBuffer[6];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_CAMERA, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_CAMERA_REGISTER, u8Count);

	VIDOR_SE_PUT16(au8LocBuffer, u16Register, u8Count);

	VIDOR_SE_PUT8(au8LocBuffer, u8Address, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, u8Data, u8Count);

	u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, 6);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Tmp;
  
}

uint8_t VidorSECamera::SetWindowPos(uint16_t u16PosX, uint16_t u16PosY) 
{

	uint8_t u8Tmp;
	uint8_t au8LocBuffer[6];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_CAMERA, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_CAMERA_SET_POS, u8Count);

	VIDOR_SE_PUT16(au8LocBuffer, u16PosX, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16PosY, u8Count);

	u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, 6);

	digitalWrite(slaveSelectPin, HIGH);
	
	return u8Tmp;

}

uint8_t VidorSECamera::SetWindowAddr(uint32_t Addr) 
{

	uint8_t u8Tmp;
	uint8_t au8LocBuffer[6];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_CAMERA, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_CAMERA_SET_ADDR, u8Count);

	VIDOR_SE_PUT32(au8LocBuffer, Addr, u8Count);

	u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, 6);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Tmp;
  
}

uint8_t VidorSECamera::SetPower(uint8_t u8PowerOn) 
{

	uint8_t u8Tmp;
	uint8_t au8LocBuffer[2];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_CAMERA, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, u8PowerOn & 0x01, u8Count);

	u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, 2);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Tmp;
  
}

uint8_t VidorSECamera::Init(uint8_t u8Mode, uint32_t Addr) 
{

  uint8_t u8Tmp;

  // Camera buffer addresse must be set before initialization
  SetWindowAddr(Addr);
   
  switch (u8Mode)
  {
    case VIDOR_SE_CAM_MODE_640_480 :
    
      for (uint16_t u16Count = 0; u16Count < sizeof(cam_640x480)/sizeof(struct regval_list); u16Count++) 
      {
        u8Tmp = FPGACamera.WriteRegister(0x6C, cam_640x480[u16Count].addr, cam_640x480[u16Count].data);
        if (u8Tmp != VIDOR_SE_NOERROR) return u8Tmp;
      }
      break;
      
    default:
      return VIDOR_SE_ERR_INVALID_PARAM;
      break;
  }

  return u8Tmp;
  
}

uint8_t VidorSECamera::SetDisplayMode(uint8_t u8Mode) 
{
  uint8_t u8Tmp;
  uint8_t au8LocBuffer[4];
  uint8_t u8Count = 0;

  digitalWrite(slaveSelectPin, LOW);

  do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_CAMERA, u8Count);
  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_CAMERA_SET_DISPLAY_MODE, u8Count);

  VIDOR_SE_PUT16(au8LocBuffer, u8Mode, u8Count);

  u8Tmp = FPGACore.SendFrameMsg(au8LocBuffer, 4);

  digitalWrite(slaveSelectPin, HIGH);

  return u8Tmp;
}
