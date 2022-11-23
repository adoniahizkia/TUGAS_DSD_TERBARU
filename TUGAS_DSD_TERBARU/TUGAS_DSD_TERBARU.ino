// Use the Parola library to scroll text on the display
//
// Demonstrates the use of the scrolling function to display text received
// from the serial interface
//
// User can enter text on the serial monitor and this will display as a
// scrolling message on the display.
// Speed for the display is controlled by a pot on SPEED_IN analog in.
// Scrolling direction is controlled by a switch on DIRECTION_SET digital in.
// Invert ON/OFF is set by a switch on INVERT_SET digital in.
//
// UISwitch library can be found at https://github.com/MajicDesigns/MD_UISwitch
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW //KODE HARDWARE
#define MAX_DEVICES 4 //JUMLAH 1C YANG DIGUNAKAN
#define CLK_PIN   13 //PIN DETAK
#define DATA_PIN  11 //PIN DATA
#define CS_PIN    10 // PIN PEMILIHAN PIN PADA IC

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// SOFTWARE SPI
//MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 125;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_CENTER;
uint16_t scrollPause = 125; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
#define	BUF_SIZE	14 //PANJANG TULISAN
char curMessage[BUF_SIZE] = { "Teks Berjalan" };
char newMessage[BUF_SIZE] = { "Teks Berjalan" };
bool newMessageAvailable = true;
int contrast = 0; // atur kecerahan
void setup()
{
  P.begin();
  P.setIntensity(contrast);
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect); 
}
void loop()
{
    if (P.displayAnimate())
    {
      if (newMessageAvailable)
      {
        strcpy(curMessage, newMessage);
        newMessageAvailable = false;
      }
      P.displayReset();
    }
}
