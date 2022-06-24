#ifndef __VIDOR_SE_GRAPHIC__
#define __VIDOR_SE_GRAPHIC__

#include "VidorSECore.hpp"

#define VIDOR_SE_COMMAND_GRAPHIC_SET_MODE    (0x00)
#define VIDOR_SE_COMMAND_GRAPHIC_DRAW_LINE     (0x01)
#define VIDOR_SE_COMMAND_GRAPHIC_DRAW_CIRCLE      (0x02)
#define VIDOR_SE_COMMAND_GRAPHIC_FILL_CIRCLE  (0x03)
#define VIDOR_SE_COMMAND_GRAPHIC_FILL_RECT    (0x04)
#define VIDOR_SE_COMMAND_GRAPHIC_SET_ALPHA     (0x05)
#define VIDOR_SE_COMMAND_GRAPHIC_SELECT_FONT   (0x06)
#define VIDOR_SE_COMMAND_GRAPHIC_DRAW_CHAR   (0x07)
#define VIDOR_SE_COMMAND_GRAPHIC_DRAW_BITMAP   (0x08)
#define VIDOR_SE_COMMAND_GRAPHIC_COPY_BITMAP   (0x09)
#define VIDOR_SE_COMMAND_GRAPHIC_SET_ADDR   (0x0A)
#define VIDOR_SE_COMMAND_GRAPHIC_DRAW_TEXT    (0x0B)
#define VIDOR_SE_COMMAND_GRAPHIC_DRAW_ROUNDRECT  (0x0C)
#define VIDOR_SE_COMMAND_GRAPHIC_FILL_ROUNDRECT (0x0D)
#define VIDOR_SE_COMMAND_GRAPHIC_DRAW_BITMAP_FROM_FLASH (0x0E)
#define VIDOR_SE_COMMAND_GRAPHIC_SET_PICTURE_MODE  (0x0F)
#define VIDOR_SE_COMMAND_GRAPHIC_SET_PALETTE_CLR (0x10)


#define ARGB(al,r,g,b) ((al<<15)|((r&0xF8)<<7)|((g&0xF8)<<2)|((b&0xF8)>>3))
#define RGB(r,g,b) ((1<<15)|((r&0xF8)<<7)|((g&0xF8)<<2)|((b&0xF8)>>3))

class VidorSEGraphic
{
	public:
	
		uint8_t SelectFont(uint16_t u16Font);
		uint8_t DrawBitmap(uint8_t u8Screen, uint32_t u32Addr, int16_t i16X, int16_t i16Y, uint16_t u16W, uint16_t u16H, uint8_t u8Mode);
		uint8_t DrawText(uint8_t u8Screen, int16_t i16X, int16_t i16Y, uint16_t u16Color, uint16_t u16FontSize, uint8_t *pu8Text, uint8_t u8Len);
		uint8_t CopyBitmap(uint8_t u8ScrSrc, uint8_t u8ScrDst, int16_t i16XSrc, int16_t i16YSrc, uint16_t u16W, uint16_t u16H, int16_t i16XDst, int16_t i16YDst);
		uint8_t SetScreenAddr(uint32_t u32Addr1, uint32_t u32Addr2);
		uint8_t SetVideoMode(uint16_t u16Mode, uint16_t u16Width, uint16_t u16Height,uint16_t u16VirtWidth,uint16_t u16VirtHeight,uint16_t u16PosX,uint16_t u16PosY) ;
		uint8_t DrawLine(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, int16_t i16X2, int16_t i16Y2, uint16_t u16Color) ;
		uint8_t FillRect(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Width, int16_t u16Height, uint16_t u16Color) ;
		uint8_t DrawRoundRect(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Width, uint16_t u16Height, uint16_t u16Radius, uint16_t u16Color) ;
		uint8_t FillRoundRect(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Width, uint16_t u16Height, uint16_t u16Radius, uint16_t u16Color) ;
		uint8_t DrawChar(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Char, uint16_t u16FontSize, uint16_t u16Color) ;
		uint8_t DrawBitmapFromFlash(uint8_t u8Screen, uint16_t u16BitmapNumber, int16_t i16X1, int16_t i16Y1) ;
		uint8_t DrawCircle(uint8_t u8Screen, uint8_t u8Fill, int16_t i16X1, int16_t i16Y1, uint16_t u16Radius, uint16_t u16Color) ;
		uint8_t SetAlpha(uint8_t u8Mode, uint8_t u8Alpha1, uint8_t u8Alpha2, uint8_t u8Alpha3) ;
    uint8_t SetPictureMode(uint16_t u16Mode,  uint16_t u16Width, uint16_t u16Height, uint16_t u16VirtWidth, uint16_t u16VirtHeight, uint16_t u16PosX, uint16_t u16PosY) ;
    uint8_t SetPaletteColor(uint8_t u8PaletteNumber,uint8_t u8ColorNumber, uint32_t u32Color);

};

extern VidorSEGraphic FPGAGraphic;
#endif
