#include "EPD_7in5e.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "ImageData.h"

void setup() {
    Debug("EPD_7IN5E_test Demo\r\n");
    DEV_Module_Init();

    Debug("e-Paper Init and Clear...\r\n");
    EPD_7IN5E_Init();
    EPD_7IN5E_Clear(EPD_7IN5E_WHITE); 
    DEV_Delay_ms(2000);

    //Create a new image cache
    UBYTE *Image;
    UDOUBLE Imagesize = ((EPD_7IN5E_WIDTH % 2 == 0)? (EPD_7IN5E_WIDTH / 2 ): (EPD_7IN5E_WIDTH / 2 + 1)) * EPD_7IN5E_HEIGHT;
    if((Image = (UBYTE *)malloc(Imagesize/4)) == NULL) {
        Debug("Failed to apply for black memory...\r\n");
    }

    Debug("Paint_NewImage\r\n");
    Paint_NewImage(Image, EPD_7IN5E_WIDTH/2, EPD_7IN5E_HEIGHT/2, 0, WHITE);
    Paint_SetScale(6);

#if 1   // show bmp
    Debug("show bmp--------------\r\n");
    EPD_7IN5E_Display(Image6color);
    DEV_Delay_ms(3000);
#endif

#if 1   // Drawing on the image
    Paint_NewImage(Image, EPD_7IN5E_WIDTH/2, EPD_7IN5E_HEIGHT/2, 0, EPD_7IN5E_WHITE);
    Paint_SetScale(6);
    // 1.Select Image
    Debug("SelectImage:BlackImage\r\n");
    Paint_SelectImage(Image);
    Paint_Clear(EPD_7IN5E_WHITE);

    // 2.Drawing on the image
    Debug("Drawing:BlackImage\r\n");
    Paint_DrawPoint(10, 55, EPD_7IN5E_RED, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 65, EPD_7IN5E_BLUE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 75, EPD_7IN5E_GREEN, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 45, 70, 95, EPD_7IN5E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 45, 20, 95, EPD_7IN5E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 45, 70, 95, EPD_7IN5E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 45, 130, 95, EPD_7IN5E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(45, 70, 20, EPD_7IN5E_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(105, 70, 20, EPD_7IN5E_WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 70, 125, 70, EPD_7IN5E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 50, 105, 90, EPD_7IN5E_YELLOW, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawString_CN(300, 120, "你好abc", &Font12CN, EPD_7IN5E_BLACK, EPD_7IN5E_WHITE);
    Paint_DrawString_CN(10, 100, "微雪电子", &Font24CN, EPD_7IN5E_WHITE, EPD_7IN5E_BLACK);
    Paint_DrawNum(10, 5, 123456789, &Font12, EPD_7IN5E_BLACK, EPD_7IN5E_WHITE);
    Paint_DrawNum(10, 22, 987654321, &Font16, EPD_7IN5E_WHITE, EPD_7IN5E_BLACK);
    Paint_DrawString_EN(145, 10, "Waveshare", &Font16, EPD_7IN5E_BLACK, EPD_7IN5E_WHITE);
    Paint_DrawString_EN(145, 30, "Waveshare", &Font16, EPD_7IN5E_GREEN, EPD_7IN5E_WHITE);
    Paint_DrawString_EN(145, 50, "Waveshare", &Font16, EPD_7IN5E_BLUE, EPD_7IN5E_WHITE);
    Paint_DrawString_EN(145, 70, "Waveshare", &Font16, EPD_7IN5E_RED, EPD_7IN5E_WHITE);
    Paint_DrawString_EN(145, 90, "Waveshare", &Font16, EPD_7IN5E_YELLOW, EPD_7IN5E_WHITE);

    Debug("EPD_Display\r\n");
    EPD_7IN5E_DisplayPart(Image, 0, 0 ,EPD_7IN5E_WIDTH/2,EPD_7IN5E_HEIGHT/2);
    DEV_Delay_ms(3000);
#endif

    Debug("Clear...\r\n");
    EPD_7IN5E_Init();
    EPD_7IN5E_Clear(EPD_7IN5E_WHITE);
    DEV_Delay_ms(500);
    Debug("Goto sleep...\r\n");
    EPD_7IN5E_Sleep();
    free(Image);
    Image = NULL;
    DEV_Delay_ms(2000);
    // close 5V
    Debug("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

}

void loop() {
  

}
