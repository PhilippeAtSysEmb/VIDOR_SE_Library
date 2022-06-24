#ifndef __VIDOR_SE_CAMERA__
#define __VIDOR_SE_CAMERA__

#include "VidorSECore.hpp"


#define VIDOR_SE_COMMAND_CAMERA_OFF     (0x00)
#define VIDOR_SE_COMMAND_CAMERA_ON     (0x01)
#define VIDOR_SE_COMMAND_CAMERA_REGISTER (0x02)
#define VIDOR_SE_COMMAND_CAMERA_ALPHA  (0x03)
#define VIDOR_SE_COMMAND_CAMERA_SET_ADDR  (0x04)
#define VIDOR_SE_COMMAND_CAMERA_SET_POS  (0x05)
#define VIDOR_SE_COMMAND_CAMERA_SET_DISPLAY_MODE  (0x06)

#define VIDOR_SE_CAM_MODE_640_480 (1)

#define VIDOR_SE_CAM_DISPLAY_OFF (0)
#define VIDOR_SE_CAM_DISPLAY_ON  (1)


class VidorSECamera
{
	public:
		uint8_t SetWindowAlpha(uint8_t u8Alpha) ;
		uint8_t WriteRegister(uint8_t u8Address, uint16_t u16Register, uint8_t u8Data ) ;
		uint8_t SetWindowPos(uint16_t u16PosX, uint16_t u16PosY) ;
		uint8_t SetWindowAddr(uint32_t Addr) ;
		uint8_t SetPower(uint8_t u8PowerOn) ;
    uint8_t Init(uint8_t u8Mode, uint32_t Addr); 
    uint8_t SetDisplayMode(uint8_t u8Mode); 

	
};

extern VidorSECamera FPGACamera;
#endif
