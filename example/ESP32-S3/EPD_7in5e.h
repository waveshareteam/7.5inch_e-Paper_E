/*****************************************************************************
* | File       :   EPD_7IN5E.h
* | Function   :   7.5 inch 6-color e-Paper
******************************************************************************/
#ifndef _EPD_7IN5E_H_
#define _EPD_7IN5E_H_

#include "DEV_Config.h"

#define EPD_7IN5E_WIDTH        1024
#define EPD_7IN5E_HEIGHT       600
#define EPD_7IN5E_IMAGE_SIZE   ((EPD_7IN5E_WIDTH * EPD_7IN5E_HEIGHT) / 2)

#define EPD_7IN5E_BLACK        0x00
#define EPD_7IN5E_WHITE        0x01
#define EPD_7IN5E_YELLOW       0x02
#define EPD_7IN5E_RED          0x03
#define EPD_7IN5E_BLUE         0x05
#define EPD_7IN5E_GREEN        0x06

void EPD_7IN5E_Init(void);
void EPD_7IN5E_Clear(UBYTE color);
void EPD_7IN5E_Display(const UBYTE *Image);
void EPD_7IN5E_Sleep(void);

#endif
