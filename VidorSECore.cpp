#include <arduino.h>
#include "jtag.h"
#include "VidorSECore.hpp"

VidorSECore FPGACore;
extern void enableFpgaClock(void);



const uint16_t CRC16_table[] = {
0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011, 0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072, 0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2, 0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1, 0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192, 0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1, 0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151, 0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132, 0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312, 0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371, 0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1, 0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2, 0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291, 0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2, 0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252, 0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231, 0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202};


uint8_t VidorSECore::SetVideoMode(uint16_t u16Mode) 
{

  uint8_t u8Busy;
  uint8_t au8LocBuffer[22];
  uint8_t u8Count = 0;
  uint16_t u16Tmp ;

  if (u16Mode > VIDOR_SE_VIDEO_MODE_LAST) return VIDOR_SE_ERR_INVALID_PARAM;

  digitalWrite(slaveSelectPin, LOW);

  do u8Busy = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Busy & 0x04);

  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_SYSTEM, u8Count);
  VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_SYSTEM_SET_MODE, u8Count);


  u16Tmp  = VidorSE_VideoModes[u16Mode].u16PixelFrequency << 12; 
  u16Tmp |= VidorSE_VideoModes[u16Mode].u16Polarity << 10; 
  u16Tmp |= VidorSE_VideoModes[u16Mode].u16VIDEO_ID & 0xFF; 
   
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16VIDEO_ID & 0x8000, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, u16Tmp, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenHoriz, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenHorizSyncStart, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenHorizSyncEnd, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenHorizTot, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenVert, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenVertSyncStart, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenVertSyncEnd, u8Count);
  VIDOR_SE_PUT16(au8LocBuffer, VidorSE_VideoModes[u16Mode].u16ScreenVertTot, u8Count);

  u8Busy = FPGACore.SendFrameMsg(au8LocBuffer, 22);

  digitalWrite(slaveSelectPin, HIGH);
  
  return u8Busy;
  
}

void VidorSECore::InitSPI(void)
{
  
  pinMode (slaveSelectPin, OUTPUT);
  
  SPI.begin();
  SPI.beginTransaction(SPISettings(SPISPEED, MSBFIRST, SPI_MODE0));

  digitalWrite(slaveSelectPin, HIGH);

}

uint8_t VidorSECore::InitCore(void)
{
  int ret;
  uint32_t ptr[1];
  uint8_t u8Tmp;
  
  // Give it delay
  delay(2000);

  enableFpgaClock();
 
  //Init Jtag Port
  ret = jtagInit();
  mbPinSet();

  // Load FPGA user configuration
  ptr[0] = 0 | 3;
  mbEveSend(ptr, 1);

  // Give it delay
  delay(1000);
  // Disable all JTAG Pins (usefull for USB BLASTER connection)
  pinMode(FPGA_TDO, INPUT);
  pinMode(FPGA_TMS, INPUT);
  pinMode(FPGA_TDI, INPUT);
  pinMode(FPGA_TCK, INPUT);

  //delay(10000); // Give a delay for downloading new configuration with USB Blaster
  InitSPI();

  // Configure other share pins as input too
  pinMode(FPGA_INT, INPUT);

  // Reset NEO430
  digitalWrite(slaveSelectPin, LOW);
  do u8Tmp = SPI.transfer(VIDOR_SE_SPI_ADDR_RESET); while(u8Tmp & 0x04);
  SPI.transfer(1);
  digitalWrite(slaveSelectPin, HIGH);

  // Give it delay  ICI il faudrait attendre le retour de la trame d'init du 430
  delay(1000);

  return VIDOR_SE_NOERROR;

}


VidorSECore::VidorSECore(void)
{
  u8Active = 0;
  u16Capabilities = 0;
  u16MsgNumber = 0;
  
}

uint8_t VidorSECore::SendFrameMsg(uint8_t *pu8Buffer, uint16_t u16Size)
{
  uint8_t u8Busy;
  uint16_t u16Crc16 = 0;


  this->u16MsgNumber = (this->u16MsgNumber + 1) & 0x7FFF; // Bit 15 is reserved for system messages.

  // Add 2 bytes for Size, 2 for MessageNumber and 2 for CRC16
  u16Size += 6; 

  do {u8Busy = SPI.transfer((u16Size>>8) | 0x80); } while(u8Busy & 0x80); 
  if (u8Busy != 0) goto error;
  u16Crc16 = (u16Crc16 << 8) ^ (CRC16_table[(u16Crc16 >> 8) ^ ((u16Size>>8) | 0x80)]); 

  do {u8Busy = SPI.transfer(u16Size & 0xFF);} while(u8Busy & 0x80); 
  if (u8Busy != 0) goto error;

  u16Crc16 = (u16Crc16 << 8) ^ (CRC16_table[(u16Crc16 >> 8) ^ (u16Size & 0xFF)]); 

  do {u8Busy = SPI.transfer((this->u16MsgNumber >>8)); } while(u8Busy & 0x80); 
  if (u8Busy != 0) goto error;
  u16Crc16 = (u16Crc16 << 8) ^ (CRC16_table[(u16Crc16 >> 8) ^ ((this->u16MsgNumber >> 8) | 0x80)]);  

  
  do {u8Busy = SPI.transfer(this->u16MsgNumber & 0xFF);}while(u8Busy & 0x80); 
  if (u8Busy != 0) goto error;

  u16Crc16 = (u16Crc16 << 8) ^ (CRC16_table[(u16Crc16 >> 8) ^ (this->u16MsgNumber & 0xFF)]);  

  for (int cpt = 0; cpt < u16Size - 6; cpt++)
  {
    do {u8Busy = SPI.transfer(pu8Buffer[cpt]);} while(u8Busy & 0x80);
	if (u8Busy != 0) goto error;	
    u16Crc16 = (u16Crc16 << 8) ^ (CRC16_table[(u16Crc16 >> 8) ^ (pu8Buffer[cpt])]);  

  }

  do {u8Busy = SPI.transfer(u16Crc16 >> 8);  } while(u8Busy & 0x80); 
  if (u8Busy != 0) goto error;
  do {u8Busy = SPI.transfer(u16Crc16 & 0xFF); } while(u8Busy & 0x80); 
  if (u8Busy != 0) goto error;


  // Continue until FPGA set EOF Flag
  do {u8Busy = SPI.transfer(0x00);} while((u8Busy & 0x40) == 0);   

  return (VIDOR_SE_NOERROR);

  error :
	return (VIDOR_SE_ERR); 
}


uint16_t VidorSECore::GetCurrentMsgNumber(void)
{
	return this->u16MsgNumber;
}

uint8_t VidorSECore::ManageSystemMsg(uint16_t u16MsgNumber, uint16_t u16SizeMsg)
{
	sSysMsg_t sSystemMsg;
  uint16_t u16Crc16;
	
	if (u16MsgNumber & 0x8000 == 0) return VIDOR_SE_ERR;

	for (uint16_t u16Count = 0; u16Count < u16SizeMsg - 6; u16Count++)
	{
		uint8_t	u8Data;
		u8Data  = SPI.transfer(0x00); 
		if (!digitalRead(FPGA_INT)) return VIDOR_SE_ERR;
		if (u16Count < sizeof(sSysMsg_t)) ((uint8_t*)(&sSystemMsg))[u16Count] = u8Data;  
	}

	switch (u16MsgNumber)
	{
		case 0x8000: // Reset Msg
			this->u16Capabilities = sSystemMsg.Status;
			this->u8Active = true;
			this->u16MsgNumber = 0;
			break;
			
		default:
			break;
	}

	if (u16SizeMsg & 1) SPI.transfer(0x00); 
	if (!digitalRead(FPGA_INT)) return VIDOR_SE_ERR;
	
	u16Crc16 = (SPI.transfer(0x00) << 8);
	if (!digitalRead(FPGA_INT)) return VIDOR_SE_ERR;	
	
	u16Crc16 |= (SPI.transfer(0x00)); 
	// No CRC verification for now

	return VIDOR_SE_NOERROR;

}

uint8_t VidorSECore::GetMsg(uint8_t *pu8Buffer, uint16_t u16SizeBuffer, uint16_t u16SearchMsg)
{

  uint8_t u8Error = VIDOR_SE_ERR_NO_MSG;

  // Message is only available if interrupt line is active.
  if (digitalRead(FPGA_INT))
  {
	u8Error = VIDOR_SE_ERR;
    digitalWrite(slaveSelectPin, LOW);
  
    uint16_t u16SizeMsg;
    uint16_t u16MsgNumber;
    
	// Select module
    SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_API_ADDR_NEO430_IN); 
  
      while(digitalRead(FPGA_INT)) 
      {
		uint16_t u16Crc16;
		
		// Bit 7 always equal 1 for first Msg Byte.
		do u16SizeMsg = SPI.transfer(0x80); while (((u16SizeMsg & 0x80) == 0) || (!digitalRead(FPGA_INT)));
        if (!digitalRead(FPGA_INT)) goto end;
		
        u16SizeMsg = ((u16SizeMsg & 0x7f) << 8) | SPI.transfer(0x00);
        if ((u16SizeMsg<= 6) || (!digitalRead(FPGA_INT))) goto end;
        u16MsgNumber = SPI.transfer(0x00);
        if (!digitalRead(FPGA_INT)) goto end;
        u16MsgNumber = (u16MsgNumber << 8) | SPI.transfer(0x00);
        if (!digitalRead(FPGA_INT)) goto end;
        
		if (u16MsgNumber & 0x8000)
		{
			if (ManageSystemMsg(u16MsgNumber, u16SizeMsg) != VIDOR_SE_ERR) goto end;
		}
		else
		{
			for (uint16_t u16Count = 0; u16Count < u16SizeMsg - 6; u16Count++)
			{
				uint8_t	u8Data;
				u8Data  = SPI.transfer(0x00); 
				if (!digitalRead(FPGA_INT)) goto end;
				if ((pu8Buffer != NULL) && (u16Count < u16SizeBuffer)) pu8Buffer[u16Count] = u8Data;  
			}

			if (u16SizeMsg & 1) SPI.transfer(0x00); 
			if (!digitalRead(FPGA_INT)) goto end;
			
			u16Crc16 = (SPI.transfer(0x00) << 8);
			if (!digitalRead(FPGA_INT)) goto end;	
			
			u16Crc16 |= (SPI.transfer(0x00)); 
			// No CRC verification for now
			if ((u16SizeMsg - 6 <= u16SizeBuffer) && (u16SearchMsg == u16MsgNumber))u8Error = VIDOR_SE_NOERROR;
		}
      };

end:
      digitalWrite(slaveSelectPin, HIGH);
      
  }
  
	return u8Error;
	
}


uint8_t VidorSECore::ReadSDRAM(uint32_t u32Address, uint8_t *pu8Buffer, uint16_t u16Size, uint16_t u16TimeOut) 
{

	uint8_t u8Tmp;
	unsigned long ulTimeOut;
	uint8_t au8LocBuffer[8];
	uint8_t u8Count;

	digitalWrite(slaveSelectPin, LOW);

	u8Count = 0;

	do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_SYSTEM, u8Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_SYSTEM_READ_SDRAM, u8Count);
	VIDOR_SE_PUT32(au8LocBuffer, u32Address, u8Count);
	VIDOR_SE_PUT16(au8LocBuffer, u16Size, u8Count);

	u8Tmp = SendFrameMsg(au8LocBuffer, 8);

	digitalWrite(slaveSelectPin, HIGH);

	if (u8Tmp != VIDOR_SE_NOERROR) return u8Tmp;

	ulTimeOut = millis();

	do
	{
		u8Tmp = GetMsg(pu8Buffer, u16Size, GetCurrentMsgNumber());

		if ((u16TimeOut) && ((millis() - ulTimeOut) > u16TimeOut)) { u8Tmp = VIDOR_SE_ERR_TIMEOUT; break;}

	} while ((u8Tmp != VIDOR_SE_ERR_NO_MSG) && (u8Tmp != VIDOR_SE_NOERROR));
	
	return u8Tmp;
}

uint8_t VidorSECore::WriteSDRAM(uint32_t u32Address, uint8_t *pu8Buffer, uint16_t u16Size)
{

    uint8_t u8Tmp;
    uint8_t au8LocBuffer[VIDOR_SE_SPI_MAX_MSG_SIZE];
    uint16_t u16Count;
	
	u16Count = 0;
	
	if (u16Size > VIDOR_SE_SPI_MAX_MSG_SIZE - 8) return VIDOR_SE_ERR_INVALID_PARAM;

    digitalWrite(slaveSelectPin, LOW);

  
    do u8Tmp = SPI.transfer(SPI_WRITE_COMMAND | VIDOR_SE_SPI_ADDR_NEO430_OUT); while(u8Tmp & 0x04);

	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_TYPE_SYSTEM, u16Count);
	VIDOR_SE_PUT8(au8LocBuffer, VIDOR_SE_COMMAND_SYSTEM_WRITE_SDRAM, u16Count);
	VIDOR_SE_PUT32(au8LocBuffer, u32Address, u16Count);

    memcpy(&(au8LocBuffer[u16Count]), pu8Buffer, u16Size); 
	u16Count += u16Size;
	if (u16Count & 1) u16Count++;
    
    SendFrameMsg(au8LocBuffer, u16Count);

  digitalWrite(slaveSelectPin, HIGH);
  
}
