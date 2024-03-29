// SEBELUM DI UPLOAD DI HARAPKAN UNTUK MENGINSTALL LIBRARY MD_Parola.h DAN MD_MAX72xx.h TERLEBIH DAHULU PADA ARDUINO IDE YANG DIGUNAKAN

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW //KODE HARDWARE
#define MAX_DEVICES 4 //JUMLAH 1C YANG DIGUNAKAN
#define CLK_PIN   13 //PIN DETAK
#define DATA_PIN  11 //PIN DATA
#define CS_PIN    10 // PIN PEMILIHAN PIN PADA IC


MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 70;    // JEDA WAKTU JALAN NYA TEXT
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_CENTER;
uint16_t scrollPause = 125; // JEDA WAKTU SETELAH SEMUA TEXT SELESAI DI TAMPILKAN

#define  BUF_SIZE  140 //PANJANG TULISAN
char curMessage[BUF_SIZE] = { "Rancang Bangun Teks Berjalan Pada Modul LED Dot Matrix 32 x 8 Berbasis Arduino Nano" }; //TULISAN UNTUK PERTAMA KALI ARDUINO DI HIDUPKAN
char newMessage[BUF_SIZE] = { "Anggota Kelompok : Rahmad Mujaki, Dave Adonia Hizkia dan Adib Al-Sunni" }; //TULISAN YANG AKAN DI TAMPILKAN BERKALI KALI
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
