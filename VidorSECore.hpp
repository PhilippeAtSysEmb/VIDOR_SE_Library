#ifndef __VIDOR_SE_CORE__
#define __VIDOR_SE_CORE__

#include <arduino.h>
#include <SPI.h>

#define SPISPEED 2000000

#define VIDOR_SE_SPI_MAX_MSG_SIZE (256 + 8)
#define SPI_WRITE_COMMAND                (1<<7)

#define VIDOR_SE_SPI_ADDR_RESET          (7<<3)
#define VIDOR_SE_SPI_ADDR_NEO430_OUT     (9<<3)
#define VIDOR_SE_API_ADDR_NEO430_IN      (10<<3)

#define VIDOR_SE_COMMAND_TYPE_SYSTEM	(0)
#define VIDOR_SE_COMMAND_TYPE_GRAPHIC  (1)
#define VIDOR_SE_COMMAND_TYPE_CAMERA  (2)
#define VIDOR_SE_COMMAND_TYPE_SOUND		(6)


#define VIDOR_SE_COMMAND_SYSTEM_READ_SDRAM (1)
#define VIDOR_SE_COMMAND_SYSTEM_WRITE_SDRAM (2)
#define VIDOR_SE_COMMAND_SYSTEM_SET_MODE (4)

#define VIDOR_SE_NOERROR	(0)
#define VIDOR_SE_ERR	(1)
#define VIDOR_SE_ERR_INVALID_PARAM	(2)
#define VIDOR_SE_ERR_TIMEOUT	(3)
#define VIDOR_SE_ERR_NO_MSG	(4)

#define VIDOR_SE_HDMI_MODE (0x8000)

#define VIDOR_SE_DVI_INV_HPOL (1)
#define VIDOR_SE_DVI_INV_VPOL (2)


// For High level functions such as pinMode or digitalWrite, you have to use FPGA_xxx
// Low level functions (in jtag.c file) use other kind of #define (TDI,TDO,TCK,TMS) with different values
#define FPGA_TDI                            (26u)
#define FPGA_TDO                            (29u)
#define FPGA_TCK                            (27u)
#define FPGA_TMS                            (28u)



// Clock send by SAMD21 to the FPGA
#define FPGA_CLOCK                        (30u)

// SAMD21 to FPGA control signal (interrupt ?)
#define FPGA_MB_INT                       (6u)

// FPGA to SAMD21 control signal (interrupt ?)
#define FPGA_INT                          (33u) //B2 N2

#define PA02_B1C2_J4_2                    (15u)
#define PB02_B8C3_J4_3                    (16u)

const int slaveSelectPin = FPGA_MB_INT;

#define VIDOR_SE_PUT8(u,v,w) { \
					(u)[(w)++] = (v);\
					}
#define VIDOR_SE_PUT16(u,v,w) {	\
					(u)[(w)++] = ((v) >> 8) & 0xFF; \
					(u)[(w)++] = (v) & 0xFF;\
					}

#define VIDOR_SE_PUT32(u,v,w) {	\
					(u)[(w)++] = ((v) >> 24) & 0xFF; \
					(u)[(w)++] = ((v) >> 16) & 0xFF; \
					(u)[(w)++] = ((v) >> 8) & 0xFF; \
					(u)[(w)++] = (v) & 0xFF;\
					}

typedef struct {
  uint16_t u16PixelFrequency;
  uint16_t u16VIDEO_ID;
  
  uint16_t u16ScreenHorizTot;
  uint16_t u16ScreenVertTot;
  
  uint16_t u16ScreenHoriz;
  uint16_t u16ScreenVert;
  
  uint16_t u16ScreenHorizSyncStart;
  uint16_t u16ScreenHorizSyncEnd;
  
  uint16_t u16ScreenVertSyncStart;
  uint16_t u16ScreenVertSyncEnd;
  
  uint16_t u16Polarity;
} sVideoMode_t;

#define VIDOR_SE_PIXEL_FREQ_25200   (0)
#define VIDOR_SE_PIXEL_FREQ_27000   (1)
#define VIDOR_SE_PIXEL_FREQ_54000   (2)
#define VIDOR_SE_PIXEL_FREQ_59400   (3)
#define VIDOR_SE_PIXEL_FREQ_74250   (4)
#define VIDOR_SE_PIXEL_FREQ_65000   (5)


#define VIDOR_SE_VIDEO_MODE_640x480_60HZ     (0)
#define VIDOR_SE_VIDEO_MODE_720x576_50HZ     (1)
#define VIDOR_SE_VIDEO_MODE_720x480_60HZ     (2)
#define VIDOR_SE_VIDEO_MODE_720x576_100HZ    (3)
#define VIDOR_SE_VIDEO_MODE_720x480_120HZ    (4)
#define VIDOR_SE_VIDEO_MODE_1024x768_60HZ    (5)
#define VIDOR_SE_VIDEO_MODE_1280x720_24HZ    (6)
#define VIDOR_SE_VIDEO_MODE_1280x720_25HZ    (7)
#define VIDOR_SE_VIDEO_MODE_1280x720_30HZ    (9)
#define VIDOR_SE_VIDEO_MODE_1280x720_50HZ    (9)
#define VIDOR_SE_VIDEO_MODE_1280x720_60HZ    (10)
#define VIDOR_SE_VIDEO_MODE_1680x720_24HZ    (11)
#define VIDOR_SE_VIDEO_MODE_1680x720_25HZ    (12)
#define VIDOR_SE_VIDEO_MODE_1680x720_30HZ    (13)
#define VIDOR_SE_VIDEO_MODE_1920x1080_24HZ   (14)
#define VIDOR_SE_VIDEO_MODE_1920x1080_25HZ   (15)
#define VIDOR_SE_VIDEO_MODE_1920x1080_30HZ   (16)
#define VIDOR_SE_VIDEO_MODE_LAST             (16)

const sVideoMode_t VidorSE_VideoModes[] = {

  {VIDOR_SE_PIXEL_FREQ_25200,  1,  800,  525,  640,  480,  656,  752,  490,  492,  VIDOR_SE_DVI_INV_HPOL | VIDOR_SE_DVI_INV_VPOL},
  {VIDOR_SE_PIXEL_FREQ_27000, 17,  864,  625,  720,  576,  732,  796,  581,  586,  VIDOR_SE_DVI_INV_HPOL | VIDOR_SE_DVI_INV_VPOL},
  {VIDOR_SE_PIXEL_FREQ_27000,  2,  858,  525,  720,  480,  736,  798,  489,  495,  VIDOR_SE_DVI_INV_HPOL | VIDOR_SE_DVI_INV_VPOL},
  {VIDOR_SE_PIXEL_FREQ_54000, 42,  864,  625,  720,  576,  732,  796,  581,  586,  VIDOR_SE_DVI_INV_HPOL | VIDOR_SE_DVI_INV_VPOL},
  {VIDOR_SE_PIXEL_FREQ_54000, 48,  858,  525,  720,  480,  736,  798,  489,  495,  VIDOR_SE_DVI_INV_HPOL | VIDOR_SE_DVI_INV_VPOL},
  {VIDOR_SE_PIXEL_FREQ_65000,VIDOR_SE_HDMI_MODE |    0, 1344,  806, 1024,  768, 1048, 1184,  771,  777,  0},
  {VIDOR_SE_PIXEL_FREQ_59400, 60, 3300,  750, 1280,  720, 3040, 3080,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_74250, 61, 3960,  750, 1280,  720, 3700, 3740,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_74250, 62, 3300,  750, 1280,  720, 3040, 3080,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_74250, 19, 1980,  750, 1280,  720, 1720, 1760,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_74250,  4, 1650,  750, 1280,  720, 1390, 1430,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_59400, 79, 3300,  750, 1680,  720, 3040, 3080,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_59400, 80, 3168,  750, 1680,  720, 2908, 2948,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_59400, 81, 2640,  750, 1680,  720, 2380, 2420,  725,  730,  0},
  {VIDOR_SE_PIXEL_FREQ_74250, 32, 2750, 1125, 1920, 1080, 2558, 2602, 1084, 1089,  0},
  {VIDOR_SE_PIXEL_FREQ_74250, 33, 2640, 1125, 1920, 1080, 2448, 2492, 1084, 1089,  0},
  {VIDOR_SE_PIXEL_FREQ_74250, 34, 2200, 1125, 1920, 1080, 2008, 2052, 1084, 1089,  0},
  
  //{VIDOR_SE_PIXEL_FREQ_65000, VIDOR_SE_HDMI_MODE | 0, 1344,  806, 1024,  768, 1048, 1184,  771,  777,  0},
};

typedef struct {
	uint16_t	Status;
} sSysMsg_t;

class VidorSECore
{
	public:
	
  uint8_t  u8Active;
  uint16_t u16Capabilities;
  uint16_t u16MsgNumber;
  
    VidorSECore(void);
		uint16_t GetCurrentMsgNumber(void);
		uint8_t ManageSystemMsg(uint16_t u16MsgNumber, uint16_t u16SizeMsg);
		uint8_t GetMsg(uint8_t *pu8Buffer, uint16_t u16SizeBuffer, uint16_t u16SearchMsg);
		void InitSPI(void);
		uint8_t SendFrameMsg(uint8_t *pu8Buffer, uint16_t u16Size);
		uint8_t ReadSDRAM(uint32_t u32Address, uint8_t *pu8Buffer, uint16_t u16Size, uint16_t u16TimeOut);
		uint8_t WriteSDRAM(uint32_t u32Address, uint8_t *pu8Buffer, uint16_t u16Size); 
    uint8_t InitCore(void);
    uint8_t SetVideoMode(uint16_t u16Mode);
};

extern VidorSECore FPGACore;
#endif
