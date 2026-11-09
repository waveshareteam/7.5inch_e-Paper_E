#!/usr/bin/python
# -*- coding:utf-8 -*-
import logging
import os
import sys
import time

from PIL import Image, ImageDraw, ImageFont

picdir = os.path.join(
    os.path.dirname(os.path.dirname(os.path.realpath(__file__))), "pic"
)
libdir = os.path.join(
    os.path.dirname(os.path.dirname(os.path.realpath(__file__))), "lib"
)
if os.path.exists(libdir):
    sys.path.append(libdir)

from waveshare_epd import epd7in5e

logging.basicConfig(level=logging.DEBUG)

try:
    logging.info("epd7in5e Demo")
    epd = epd7in5e.EPD()

    logging.info("init and Clear")
    epd.init()
    epd.Clear()

    font24 = ImageFont.truetype(os.path.join(picdir, "Font.ttc"), 24)
    font40 = ImageFont.truetype(os.path.join(picdir, "Font.ttc"), 40)

    logging.info("read bmp file")
    epd.init()
    Himage = Image.open(os.path.join(picdir, "7in5e_1.bmp")).convert("RGB")
    if Himage.size != (epd.width, epd.height):
        Himage = Himage.resize((epd.width, epd.height))
    epd.display(epd.getbuffer(Himage))
    time.sleep(3)

    logging.info("Drawing on the image...")
    epd.init()
    Himage = Image.new("RGB", (epd.width, epd.height), epd.WHITE)
    draw = ImageDraw.Draw(Himage)
    draw.rectangle([(0, 0), (50, 50)], outline=epd.BLACK)
    draw.rectangle([(55, 0), (100, 50)], fill=epd.RED)
    draw.line([(0, 0), (50, 50)], fill=epd.YELLOW, width=1)
    draw.line([(0, 50), (50, 0)], fill=epd.YELLOW, width=1)
    draw.pieslice((55, 60, 95, 100), 90, 180, outline=epd.RED)
    draw.pieslice((55, 60, 95, 100), 270, 360, fill=epd.BLACK)
    draw.chord((10, 60, 50, 100), 0, 360, fill=epd.YELLOW)
    draw.ellipse((55, 60, 95, 100), outline=epd.RED)
    draw.polygon([(110, 0), (110, 50), (150, 25)], outline=epd.BLACK)
    draw.polygon([(190, 0), (190, 50), (150, 25)], fill=epd.BLACK)
    draw.text((10, 120), "7.5 e-Paper (E)", font=font24, fill=epd.BLUE)
    draw.text((10, 150), u'微雪电子', font = font24, fill = epd.BLACK)
    draw.text((175, 50), "Waveshare", font=font24, fill=epd.BLACK)
    draw.text((175, 70), "Waveshare", font=font24, fill=epd.BLUE)
    draw.text((175, 90), "Waveshare", font=font24, fill=epd.GREEN)
    draw.text((175, 110), "Waveshare", font=font24, fill=epd.YELLOW)
    draw.text((175, 130), "Waveshare", font=font24, fill=epd.RED)
    epd.display(epd.getbuffer(Himage))
    time.sleep(3)

    logging.info("Clear...")
    epd.init()
    epd.Clear()

    logging.info("Goto Sleep...")
    epd.sleep()
    
    logging.info("close 5V, Module enters 0 power consumption ...")
    epd.EPD_END()

except IOError as e:
    logging.info(e)

except KeyboardInterrupt:
    logging.info("ctrl + c:")
    epd7in5e.epdconfig.module_exit(cleanup=True)
    exit()
