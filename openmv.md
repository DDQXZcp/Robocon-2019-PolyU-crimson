# The way to use openmv to detect line

## First install openmv ide to test

## Line detection code

~~~
enable_lens_corr = True

import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor,RGB565) # grayscale is faster
sensor.set_framesize(sensor,QQVGA)
sensor.skip_frames(30)
clock = time.clock()

while(True):
  clock.tick()
  img = sensor.snapshot()
  # this is L
  for l in img.find_lines(threshold = 1000, theta_margin = 25, rho_margin = 25):# or find_line_segments()
    if (im_degree <= l.theta()) and (l.theta() <= max_degree):
    img.draw_line(l.line(), color = (255,0,0))
    print(l)
  print()
~~~
theta_margin = 25, merge lines that are within 25 degrees
rho_margin = 25, merge lines that are within 25 raw pixels, Related to Hough transform
The format of l is x1, y1, x2, y2, length, 
magnitude: sum of the magnitude of all merge lines
theta: angle of the line
rho: real value

## Transmit data from openmv to stm32

We need to use microPython

Add this sentence in the beginning

~~~
from pyb import UART
~~~
or just:
~~~
import pyb
~~~

Reference: https://docs.openmv.io/openmvcam/tutorial/uart_control.html

Example:

~~~
import pyb

uart = pyb.UART(3, 115200, timeout_char = 1000)

uart.write("Hello World\n")
~~~

For binary case:(selfdom use)

~~~
import ustruct

uart.write(ustruct.pack("<lhb", a_32_bit_value, a_16_bit_value, a_8_bit_value))
~~~

