/*****************************************************************************
* | File       :   EPD_7IN5E.cpp
* | Function   :   7.5 inch 6-color e-Paper
******************************************************************************/
#include "EPD_7in5e.h"
#include "Debug.h"

#define EPD_7IN5E_BLOCK_SIZE  256U

/******************************************************************************
function :  Software reset
parameter:
******************************************************************************/
static void EPD_7IN5E_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(20);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(20);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(20);
}

/******************************************************************************
function :  send command
parameter:
    Reg : Command register
******************************************************************************/
static void EPD_7IN5E_SendCommand_0(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_M_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_M_PIN, 1);
}

static void EPD_7IN5E_SendCommand_1(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_S_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_S_PIN, 1);
}

static void EPD_7IN5E_SendCommand_ALL(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_M_PIN, 0);
    DEV_Digital_Write(EPD_CS_S_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_M_PIN, 1);
    DEV_Digital_Write(EPD_CS_S_PIN, 1);
}

/******************************************************************************
function :  send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_7IN5E_SendData_0(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_M_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_M_PIN, 1);
}

static void EPD_7IN5E_SendData_1(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_S_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_S_PIN, 1);
}

static void EPD_7IN5E_SendData_ALL(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_M_PIN, 0);
    DEV_Digital_Write(EPD_CS_S_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_M_PIN, 1);
    DEV_Digital_Write(EPD_CS_S_PIN, 1);
}

/******************************************************************************
function :  Wait until the busy_pin goes HIGH
parameter:
******************************************************************************/
void EPD_7IN5E_ReadBusy(void)
{
    Debug("e-Paper busy\r\n");
    while(1)
    {
        if(DEV_Digital_Read(EPD_BUSY_PIN) == 1)
            break;
        DEV_Delay_ms(10);
    }
    DEV_Delay_ms(10);
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :  Turn On Display
parameter:
******************************************************************************/
static void EPD_7IN5E_TurnOnDisplay(void)
{
    printf("Write PON \r\n");
    EPD_7IN5E_SendCommand_ALL(0x04);
    DEV_Delay_ms(100);
    EPD_7IN5E_ReadBusy();

    printf("Write DRF \r\n");
    EPD_7IN5E_SendCommand_ALL(0x12);
    EPD_7IN5E_SendData_ALL(0x00);
    DEV_Delay_ms(100);
    EPD_7IN5E_ReadBusy();

    printf("Write POF \r\n");
    EPD_7IN5E_SendCommand_ALL(0x02);
    EPD_7IN5E_SendData_ALL(0x00);
    DEV_Delay_ms(100);
    EPD_7IN5E_ReadBusy();
    printf("Display Done!! \r\n");
}

/******************************************************************************
function :  Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_7IN5E_Init(void)
{
    EPD_7IN5E_Reset();

    EPD_7IN5E_SendCommand_ALL(0xAA);
    EPD_7IN5E_SendData_ALL(0x49);
    EPD_7IN5E_SendData_ALL(0x55);
    EPD_7IN5E_SendData_ALL(0x20);
    EPD_7IN5E_SendData_ALL(0x08);
    EPD_7IN5E_SendData_ALL(0x09);
    EPD_7IN5E_SendData_ALL(0x18);

    EPD_7IN5E_SendCommand_ALL(0x00);
    EPD_7IN5E_SendData_ALL(0x5F);
    EPD_7IN5E_SendData_ALL(0x69);
    EPD_7IN5E_ReadBusy();

    EPD_7IN5E_SendCommand_ALL(0xE0);
    EPD_7IN5E_SendData_ALL(0x01);
    EPD_7IN5E_ReadBusy();

    EPD_7IN5E_SendCommand_ALL(0x01);
    EPD_7IN5E_SendData_ALL(0x3F);

    EPD_7IN5E_SendCommand_ALL(0x03);
    EPD_7IN5E_SendData_ALL(0x00);
    EPD_7IN5E_SendData_ALL(0x54);
    EPD_7IN5E_SendData_ALL(0x00);
    EPD_7IN5E_SendData_ALL(0x44);

    EPD_7IN5E_SendCommand_ALL(0x05);
    EPD_7IN5E_SendData_ALL(0x40);
    EPD_7IN5E_SendData_ALL(0x1F);
    EPD_7IN5E_SendData_ALL(0x1F);
    EPD_7IN5E_SendData_ALL(0x2C);

    EPD_7IN5E_SendCommand_ALL(0x06);
    EPD_7IN5E_SendData_ALL(0x6F);
    EPD_7IN5E_SendData_ALL(0x1F);
    EPD_7IN5E_SendData_ALL(0x16);
    EPD_7IN5E_SendData_ALL(0x25);

    EPD_7IN5E_SendCommand_ALL(0x08);
    EPD_7IN5E_SendData_ALL(0x6F);
    EPD_7IN5E_SendData_ALL(0x1F);
    EPD_7IN5E_SendData_ALL(0x1F);
    EPD_7IN5E_SendData_ALL(0x22);

    EPD_7IN5E_SendCommand_ALL(0x13);
    EPD_7IN5E_SendData_ALL(0x00);
    EPD_7IN5E_SendData_ALL(0x04);

    EPD_7IN5E_SendCommand_ALL(0x30);
    EPD_7IN5E_SendData_ALL(0x08);

    EPD_7IN5E_SendCommand_ALL(0x41);
    EPD_7IN5E_SendData_ALL(0x00);

    EPD_7IN5E_SendCommand_ALL(0x50);
    EPD_7IN5E_SendData_ALL(0x3F);

    EPD_7IN5E_SendCommand_ALL(0x60);
    EPD_7IN5E_SendData_ALL(0x02);
    EPD_7IN5E_SendData_ALL(0x00);

    EPD_7IN5E_SendCommand_ALL(0x61);
    EPD_7IN5E_SendData_ALL(EPD_7IN5E_WIDTH / 2 / 256);
    EPD_7IN5E_SendData_ALL(EPD_7IN5E_WIDTH / 2 % 256);
    EPD_7IN5E_SendData_ALL(EPD_7IN5E_HEIGHT / 256);
    EPD_7IN5E_SendData_ALL(EPD_7IN5E_HEIGHT % 256);
    EPD_7IN5E_ReadBusy();

    EPD_7IN5E_SendCommand_ALL(0x84);
    EPD_7IN5E_SendData_ALL(0x01);

    EPD_7IN5E_SendCommand_ALL(0x86);
    EPD_7IN5E_SendData_ALL(0x00);

    EPD_7IN5E_SendCommand_ALL(0xE3);
    EPD_7IN5E_SendData_ALL(0x2F);

    EPD_7IN5E_SendCommand_ALL(0xE5);
    EPD_7IN5E_SendData_ALL(0x00);
}

/******************************************************************************
function :  Clear screen
parameter:
******************************************************************************/
void EPD_7IN5E_Clear(UBYTE color)
{
    UDOUBLE Width, Height;
    Width = EPD_7IN5E_IMAGE_SIZE / 2;
    Height = 1;
    UBYTE Color = ((color & 0x0F) << 4) | (color & 0x0F);

    EPD_7IN5E_SendCommand_0(0x10);
    for (UDOUBLE j = 0; j < Height; j++) {
        for (UDOUBLE i = 0; i < Width; i++) {
            EPD_7IN5E_SendData_0(Color);
        }
    }

    EPD_7IN5E_SendCommand_1(0x10);
    for (UDOUBLE j = 0; j < Height; j++) {
        for (UDOUBLE i = 0; i < Width; i++) {
            EPD_7IN5E_SendData_1(Color);
        }
    }

    EPD_7IN5E_TurnOnDisplay();
}

/******************************************************************************
function :  Sends the image buffer in RAM to e-Paper and displays
parameter:
    Image : Image data
******************************************************************************/
void EPD_7IN5E_Display(const UBYTE *Image)
{
    UDOUBLE Width, Height;
    Width = EPD_7IN5E_IMAGE_SIZE;
    Height = 1;

    if (Image == NULL) {
        return;
    }

    EPD_7IN5E_SendCommand_ALL(0x10);
    for (UDOUBLE j = 0; j < Height; j++) {
        for (UDOUBLE i = 0; i < Width; i++) {
            if (((i / EPD_7IN5E_BLOCK_SIZE) & 0x01) == 0) {
                EPD_7IN5E_SendData_0(Image[i]);
            } else {
                EPD_7IN5E_SendData_1(Image[i]);
            }
        }
    }

    EPD_7IN5E_TurnOnDisplay();
}

/******************************************************************************
function :  Enter sleep mode
parameter:
******************************************************************************/
void EPD_7IN5E_Sleep(void)
{
    EPD_7IN5E_SendCommand_ALL(0x07);
    EPD_7IN5E_SendData_ALL(0xA5);
    DEV_Delay_ms(100);
}
