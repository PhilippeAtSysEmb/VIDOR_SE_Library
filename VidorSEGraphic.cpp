#include "VidorSEGraphic.hpp"

VidorSEGraphic FPGAGraphic;

uint8_t VidorSEGraphic::SetPaletteColor(uint8_t u8PaletteNumber,uint8_t u8ColorNumber, uint32_t u32Color)
{
  uint8_t u8Busy;

  digitalWrite(slaveSelectPin, LOW);

  uint8_t au8LocBuffer[8];
  uint8_t u8Count = 0;

  do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
  VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_SET_PALETTE_CLR << 3), u8Count);

  VIDOR_SE_PUT8(au8LocBuffer, u8PaletteNumber, u8Count);
  VIDOR_SE_PUT8(au8LocBuffer, u8ColorNumber, u8Count);

  VIDOR_SE_PUT32(au8LocBuffer, u32Color, u8Count);

  u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 8);

  digitalWrite(slaveSelectPin, HIGH);

  return u8Busy;
}

uint8_t VidorSEGraphic::SelectFont(uint16_t u16Font)
{
  uint8_t u8Busy;

  digitalWrite(slaveSelectPin, LOW);

  uint8_t au8LocBuffer[4];
  uint8_t u8Count = 0;

  do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

  au8LocBuffer[u8Count++] = VIDOR_SE_COMMAND_TYPE_GRAPHIC; 
  au8LocBuffer[u8Count++] = (VIDOR_SE_COMMAND_GRAPHIC_SELECT_FONT << 3) ; 

  au8LocBuffer[u8Count++] = (u16Font >> 8) & 0xFF;
  au8LocBuffer[u8Count++] = u16Font & 0xFF;

  u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 4);

  digitalWrite(slaveSelectPin, HIGH);

  return u8Busy;
}


uint8_t VidorSEGraphic::DrawBitmap(uint8_t u8Screen, uint32_t u32Addr, int16_t i16X, int16_t i16Y, uint16_t u16W, uint16_t u16H, uint8_t u8Mode)
{
	uint8_t u8Busy;

	uint8_t au8LocBuffer[16];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_DRAW_BITMAP << 3) | u8Screen, u8Count);
	VIDOR_SE_PUT32(au8LocBuffer, u32Addr, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16W, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16H, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u8Mode, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 16);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}

uint8_t VidorSEGraphic::DrawText(uint8_t u8Screen, int16_t i16X, int16_t i16Y, uint16_t u16Color, uint16_t u16FontSize, uint8_t *pu8Text, uint8_t u8Len)
{
	uint8_t u8Busy;
	uint8_t au8LocBuffer[256 + 12];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_DRAW_TEXT<<3) | u8Screen, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Color, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16FontSize, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u8Len, u8Count);

	memcpy(&(au8LocBuffer[u8Count]), pu8Text, u8Len);
	u8Count += u8Len;
	if (u8Len&1) u8Count++;

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, u8Count);

	digitalWrite(slaveSelectPin, HIGH);
   
	return u8Busy;
}

uint8_t VidorSEGraphic::CopyBitmap(uint8_t u8ScrSrc, uint8_t u8ScrDst, int16_t i16XSrc, int16_t i16YSrc, uint16_t u16W, uint16_t u16H, int16_t i16XDst, int16_t i16YDst)
{
	uint8_t u8Busy;
	uint8_t au8LocBuffer[16];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_GRAPHIC_COPY_BITMAP << 3, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, ((u8ScrSrc & 0x07) << 4) | (u8ScrDst & 0x07), u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16XSrc, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16YSrc, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16W, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16H, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16XDst, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16YDst, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 16);

	digitalWrite(slaveSelectPin, HIGH);
 
	return u8Busy;
}

uint8_t VidorSEGraphic::SetScreenAddr(uint32_t u32Addr1, uint32_t u32Addr2)
{
	uint8_t u8Busy;
	uint8_t au8LocBuffer[10];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_GRAPHIC_SET_ADDR << 3, u8Count);
	VIDOR_SE_PUT32(au8LocBuffer, u32Addr1, u8Count);
	VIDOR_SE_PUT32(au8LocBuffer, u32Addr2, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 10);

	digitalWrite(slaveSelectPin, HIGH);
	
	return u8Busy;
 
}


uint8_t VidorSEGraphic::SetVideoMode(uint16_t u16Mode, uint16_t u16Width, uint16_t u16Height, uint16_t u16VirtWidth, uint16_t u16VirtHeight, uint16_t u16PosX, uint16_t u16PosY) 
{

  uint8_t u8Busy;
  uint8_t au8LocBuffer[16];
  uint8_t u8Count = 0;

  digitalWrite(slaveSelectPin, LOW);

  do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_GRAPHIC_SET_MODE << 3, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16Mode, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16Width, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16Height, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16VirtWidth, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16VirtHeight, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16PosX, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16PosY, u8Count);

  u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 16);

  digitalWrite(slaveSelectPin, HIGH);
  
  return u8Busy;
  
}


uint8_t VidorSEGraphic::SetPictureMode(uint16_t u16Mode,  uint16_t u16Width, uint16_t u16Height, uint16_t u16VirtWidth, uint16_t u16VirtHeight, uint16_t u16PosX, uint16_t u16PosY) 
{

  uint8_t u8Busy;
  uint8_t au8LocBuffer[16];
  uint8_t u8Count = 0;

  digitalWrite(slaveSelectPin, LOW);

  do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_GRAPHIC_SET_PICTURE_MODE << 3, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16Mode, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16Width, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16Height, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16VirtWidth, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16VirtHeight, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16PosX, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16PosY, u8Count);

  u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 16);

  digitalWrite(slaveSelectPin, HIGH);
  
  return u8Busy;
  
}



uint8_t VidorSEGraphic::DrawLine(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, int16_t i16X2, int16_t i16Y2, uint16_t u16Color) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[14];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_DRAW_LINE << 3) | (u8Screen & 0x07), u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X2, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y2, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Color, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, 0, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 14);

	digitalWrite(slaveSelectPin, HIGH);
	
	return u8Busy;
}

uint8_t VidorSEGraphic::FillRect(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Width, int16_t u16Height, uint16_t u16Color) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[14];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_FILL_RECT << 3) | (u8Screen & 0x07), u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Width, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Height, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Color, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, 0, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 14);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}

uint8_t VidorSEGraphic::DrawRoundRect(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Width, uint16_t u16Height, uint16_t u16Radius, uint16_t u16Color) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[14];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_DRAW_ROUNDRECT << 3) | (u8Screen & 0x07), u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Width, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Height, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Radius, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Color, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 14);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}

uint8_t VidorSEGraphic::FillRoundRect(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Width, uint16_t u16Height, uint16_t u16Radius, uint16_t u16Color) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[14];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_FILL_ROUNDRECT << 3) | (u8Screen & 0x07), u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Width, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Height, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Radius, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Color, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 14);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}


uint8_t VidorSEGraphic::DrawChar(uint8_t u8Screen, int16_t i16X1, int16_t i16Y1, uint16_t u16Char, uint16_t u16FontSize, uint16_t u16Color) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[12];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_DRAW_CHAR << 3) | (u8Screen & 0x07), u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Char, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Color, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16FontSize, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 12);
	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}


uint8_t VidorSEGraphic::DrawBitmapFromFlash(uint8_t u8Screen, uint16_t u16BitmapNumber, int16_t i16X1, int16_t i16Y1) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[8];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_DRAW_BITMAP_FROM_FLASH << 3) | (u8Screen & 0x07), u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16BitmapNumber, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16X1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y1, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 8);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}


uint8_t VidorSEGraphic::DrawCircle(uint8_t u8Screen, uint8_t u8Fill, int16_t i16X1, int16_t i16Y1, uint16_t u16Radius, uint16_t u16Color) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[12];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);

	if (u8Fill)
	{
		VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_FILL_CIRCLE << 3) | (u8Screen & 0x07), u8Count);
	}
	else
	{
		VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_DRAW_CIRCLE << 3) | (u8Screen & 0x07), u8Count);
	}
	
	VIDOR_SE_PUT16(au8LocBuffer, i16X1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, i16Y1, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Radius, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Color, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, 0, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 12);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}



uint8_t VidorSEGraphic::SetAlpha(uint8_t u8Mode, uint8_t u8Alpha1, uint8_t u8Alpha2, uint8_t u8Alpha3) 
{

	uint8_t u8Busy;
	uint8_t au8LocBuffer[6];
	uint8_t u8Count = 0;

	digitalWrite(slaveSelectPin, LOW);

	do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_GRAPHIC, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, (VIDOR_SE_COMMAND_GRAPHIC_SET_ALPHA << 3) | u8Mode, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, u8Alpha2, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, u8Alpha1, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, u8Alpha3, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, u8Alpha3, u8Count);

	u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 6);

	digitalWrite(slaveSelectPin, HIGH);

	return u8Busy;
}
