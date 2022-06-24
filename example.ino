#include <arduino.h>
#include "VidorSECore.hpp"
#include "VidorSEGraphic.hpp"
#include "VidorSECamera.hpp"
#include "VidorSESound.hpp"

#define no_data    0xFF, 0xFF, 0xFF, 0xFF, \
          0xFF, 0xFF, 0xFF, 0xFF, \
          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
          0xFF, 0xFF, 0xFF, 0xFF, \
          0x00, 0x00, 0x00, 0x00  \

#define NO_BOOTLOADER   no_data
#define NO_APP        no_data
#define NO_USER_DATA    no_data

__attribute__ ((used, section(".fpga_bitstream_signature")))
const unsigned char signatures[4096] = {
  //#include "signature.ttf"
  NO_BOOTLOADER,

0x00, 0x00, 0x08, 0x00,
0x00, 0x00, 0x08, 0x00,
0xA0, 0x90, 0xd7, 0x38, 0x28, 0xe3, 0x55, 0x9c, 0xbd, 0x26, 0x9f, 0x3d, 0x9d, 0x76, 0x5b, 0xa9, 0x93, 0x1a, 0x85, 0x2a, 0xbc, 0x2f, 0xb2, 0x8d, 0x42, 0x39, 0x4c, 0x02, 0x26, 0x19, 0xdb, 0xf3,
0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, // force flag, change to 1 if needed

  NO_USER_DATA,

};
__attribute__ ((used, section(".fpga_bitstream")))
const unsigned char bitstream[] = {
  #include "app.h"
  #include "user.h"
};


#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

const char Title1[] = "VIDOR_SE Library example";


// the loop function runs over and over again forever
void loop() {

  // Manage FPGA system message. The FIFO must be emptied.
  FPGACore.GetMsg(0,0, 0x8000);

};


// the setup function runs once when you press reset or power the board
void setup() {

  FPGACore.InitCore();
  FPGACore.GetMsg(0,0, 0x8000);


  FPGACore.SetVideoMode(VIDOR_SE_VIDEO_MODE_640x480_60HZ);
 
  FPGAGraphic.SetVideoMode(0x02, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);  // 0, 1, 3, 
  FPGAGraphic.SetScreenAddr(0,0);

  FPGAGraphic.SetAlpha(7, 50, 255, 255);

  // Clear screen.
  // In this mode (3), layer 0 has 15 bits colors, layer 1 and 2 have 8 bits colors (Palette)                
  FPGAGraphic.FillRect(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(0,0,0));
  FPGAGraphic.FillRect(1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  FPGAGraphic.FillRect(2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  
  // There are 48 fonts stored in FLASH "user.h"
  FPGAGraphic.SelectFont(27);
  FPGAGraphic.DrawText(1, 10, 60, 0xFE, 0x0101 , (uint8_t*)Title1, strlen(Title1)); 
  
  // Transparency is set with ARGB(0, RED, GREEN, BLUE) for 15 bits color or 
  // using color #0 (standard palettes) for 8 bits color
  FPGAGraphic.FillRect(0, 0, 0, SCREEN_WIDTH, 100, ARGB(0,255,0,0));
  
  //FPGAGraphic.DrawLine(0, 0, 0, 0, 480,  RGB(255,0,0)) ;

  
  FPGAGraphic.DrawCircle(2, 1, 250, 200, 20, 25);
  FPGAGraphic.DrawCircle(1, 1, 250, 200, 50, 255);

 // Initialize camera registers (OV5647)
 // Set also camera buffer address. 0x300000 is just after Screen buffer.
 FPGACamera.Init(VIDOR_SE_CAM_MODE_640_480, 0x300000);
 // Set position of window overlay
 FPGACamera.SetWindowPos(250, 200);
 // Enable camera window overlay
 FPGACamera.SetDisplayMode(VIDOR_SE_CAM_DISPLAY_ON);
 // Transparency OFF
 FPGACamera.SetWindowAlpha(255);




}
