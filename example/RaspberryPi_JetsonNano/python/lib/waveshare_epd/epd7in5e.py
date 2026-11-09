# *****************************************************************************
# * | File        :   epd7in5e.py
# * | Function    :   7.5inch e-Paper (E) driver
# *****************************************************************************

import logging

from PIL import Image

from . import epdconfig

EPD_WIDTH = 1024
EPD_HEIGHT = 600
EPD_IMAGE_SIZE = EPD_WIDTH * EPD_HEIGHT // 2
EPD_BLOCK_SIZE = 256

logger = logging.getLogger(__name__)


class EPD:
    def __init__(self):
        self.reset_pin = epdconfig.RST_PIN
        self.dc_pin = epdconfig.DC_PIN
        self.busy_pin = epdconfig.BUSY_PIN
        self.cs_m_pin = epdconfig.CS_M_PIN
        self.cs_s_pin = epdconfig.CS_S_PIN
        self.width = EPD_WIDTH
        self.height = EPD_HEIGHT
        self.BLACK = 0x000000
        self.WHITE = 0xFFFFFF
        self.YELLOW = 0x00FFFF
        self.RED = 0x0000FF
        self.BLUE = 0xFF0000
        self.GREEN = 0x00FF00
        if (epdconfig.module_init() != 0):
            return -1

    def reset(self):
        epdconfig.digital_write(self.reset_pin, 1)
        epdconfig.delay_ms(20)
        epdconfig.digital_write(self.reset_pin, 0)
        epdconfig.delay_ms(20)
        epdconfig.digital_write(self.reset_pin, 1)
        epdconfig.delay_ms(20)

    def _send(self, cs_pin, dc_value, data):
        epdconfig.digital_write(self.dc_pin, dc_value)
        if cs_pin == self.cs_s_pin:
            if isinstance(data, int):
                epdconfig.spi_writebyte_1([data])
            else:
                epdconfig.spi_writebyte2_1(data)
        else:
            if isinstance(data, int):
                epdconfig.spi_writebyte_0([data])
            else:
                epdconfig.spi_writebyte2_0(data)

    def send_command_0(self, command):
        self._send(self.cs_m_pin, 0, command)

    def send_command_1(self, command):
        self._send(self.cs_s_pin, 0, command)

    def send_command_all(self, command):
        epdconfig.digital_write(self.dc_pin, 0)
        epdconfig.spi_writebyte_0([command])
        epdconfig.spi_writebyte_1([command])

    def send_data_0(self, data):
        self._send(self.cs_m_pin, 1, data)

    def send_data_1(self, data):
        self._send(self.cs_s_pin, 1, data)

    def send_data_all(self, data):
        epdconfig.digital_write(self.dc_pin, 1)
        epdconfig.spi_writebyte_0([data])
        epdconfig.spi_writebyte_1([data])

    def ReadBusy(self):
        logger.debug("e-Paper busy")
        while epdconfig.digital_read(self.busy_pin) == 0:
            epdconfig.delay_ms(10)
        epdconfig.delay_ms(10)
        logger.debug("e-Paper busy release")

    def TurnOnDisplay(self):
        logger.debug("Write PON")
        self.send_command_all(0x04)
        epdconfig.delay_ms(100)
        self.ReadBusy()

        logger.debug("Write DRF")
        self.send_command_all(0x12)
        self.send_data_all(0x00)
        epdconfig.delay_ms(100)
        self.ReadBusy()

        logger.debug("Write POF")
        self.send_command_all(0x02)
        self.send_data_all(0x00)
        epdconfig.delay_ms(100)
        self.ReadBusy()
        logger.debug("Display Done")

    def init(self):

        self.reset()

        self.send_command_all(0xAA)
        self.send_data_all(0x49)
        self.send_data_all(0x55)
        self.send_data_all(0x20)
        self.send_data_all(0x08)
        self.send_data_all(0x09)
        self.send_data_all(0x18)

        self.send_command_all(0x00)
        self.send_data_all(0x5F)
        self.send_data_all(0x69)
        self.ReadBusy()

        self.send_command_all(0xE0)
        self.send_data_all(0x01)
        self.ReadBusy()

        self.send_command_all(0x01)
        self.send_data_all(0x3F)

        self.send_command_all(0x03)
        self.send_data_all(0x00)
        self.send_data_all(0x54)
        self.send_data_all(0x00)
        self.send_data_all(0x44)

        self.send_command_all(0x05)
        self.send_data_all(0x40)
        self.send_data_all(0x1F)
        self.send_data_all(0x1F)
        self.send_data_all(0x2C)

        self.send_command_all(0x06)
        self.send_data_all(0x6F)
        self.send_data_all(0x1F)
        self.send_data_all(0x16)
        self.send_data_all(0x25)

        self.send_command_all(0x08)
        self.send_data_all(0x6F)
        self.send_data_all(0x1F)
        self.send_data_all(0x1F)
        self.send_data_all(0x22)

        self.send_command_all(0x13)
        self.send_data_all(0x00)
        self.send_data_all(0x04)

        self.send_command_all(0x30)
        self.send_data_all(0x08)

        self.send_command_all(0x41)
        self.send_data_all(0x00)

        self.send_command_all(0x50)
        self.send_data_all(0x3F)

        self.send_command_all(0x60)
        self.send_data_all(0x02)
        self.send_data_all(0x00)

        self.send_command_all(0x61)
        self.send_data_all(self.width // 2 // 256)
        self.send_data_all(self.width // 2 % 256)
        self.send_data_all(self.height // 256)
        self.send_data_all(self.height % 256)
        self.ReadBusy()

        self.send_command_all(0x84)
        self.send_data_all(0x01)

        self.send_command_all(0x86)
        self.send_data_all(0x00)

        self.send_command_all(0xE3)
        self.send_data_all(0x2F)

        self.send_command_all(0xE5)
        self.send_data_all(0x00)

        return 0

    def getbuffer(self, image):
        pal_image = Image.new("P", (1, 1))
        pal_image.putpalette(
            (
                0, 0, 0,
                255, 255, 255,
                255, 255, 0,
                255, 0, 0,
                0, 0, 0,
                0, 0, 255,
                0, 255, 0,
            )
            + (0, 0, 0) * 249
        )

        imwidth, imheight = image.size
        if imwidth % 2 != 0:
            raise ValueError("Image width must be even")

        if imwidth == self.width and imheight == self.height:
            image_temp = image
        elif imwidth == self.height and imheight == self.width:
            image_temp = image.rotate(90, expand=True)
        else:
            image_temp = image

        image_6color = image_temp.convert("RGB").quantize(palette=pal_image)
        buf_6color = bytearray(image_6color.tobytes("raw"))

        buf = [0x00] * (image_temp.size[0] * image_temp.size[1] // 2)
        for index in range(0, len(buf_6color), 2):
            buf[index // 2] = (buf_6color[index] << 4) | buf_6color[index + 1]

        return buf

    def display(self, image):
        image_master = []
        image_slave = []

        for offset in range(0, EPD_IMAGE_SIZE, EPD_BLOCK_SIZE):
            block = image[offset:offset + EPD_BLOCK_SIZE]
            if ((offset // EPD_BLOCK_SIZE) & 0x01) == 0:
                image_master.extend(block)
            else:
                image_slave.extend(block)

        self.send_command_0(0x10)
        self.send_data_0(image_master)

        self.send_command_1(0x10)
        self.send_data_1(image_slave)

        self.TurnOnDisplay()

    def Clear(self, color=0x01):
        data = ((color & 0x0F) << 4) | (color & 0x0F)
        line = [data] * 4096

        self.send_command_0(0x10)
        for _ in range((EPD_IMAGE_SIZE // 2) // len(line)):
            self.send_data_0(line)
        remain = (EPD_IMAGE_SIZE // 2) % len(line)
        if remain:
            self.send_data_0(line[:remain])

        self.send_command_1(0x10)
        for _ in range((EPD_IMAGE_SIZE // 2) // len(line)):
            self.send_data_1(line)
        if remain:
            self.send_data_1(line[:remain])

        self.TurnOnDisplay()

    def sleep(self):
        self.send_command_all(0x07)
        self.send_data_all(0xA5)
        epdconfig.delay_ms(2000)

    def EPD_END(self):
        epdconfig.delay_ms(2000)
        epdconfig.module_exit()


### END OF FILE ###
