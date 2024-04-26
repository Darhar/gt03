<h2>Intro</h2>
<p>Ive stripped down the code for GameTiger (https://github.com/codetiger/GameTiger-Console) open source handheld game console for pico to use the pico res 2.8 lcd screen, Funduino Joystick shield and pico board. I liked the speed, organisation of the c++ code and versitility of this project so Im going to use bits of it to run my setup as the input/output of pico projects. Im using a double pico extender board to plug in the pico, screen and joystick interface board for development purposes with the idea of adding another pico via i2c, spi or serial adding more cpu and memory.</p> 

<h2>Parts</h2>
<h3>LCD </h3>
<p>Im using the Waveshare Pico-Res-Touch-LCD-2.8, a cheap, easy to get, touch screen module made for the Pi Pico. </p>
<ul>
	<li>320 × 240 Pixels</li>
	<li>SPI</li>
	<li>ST7789VW controller</li>
	<li>262K RGB</li>
	<li>MicoSD card slot</li>
	<li>RGB565, and RGB666</li>
</ul>
<p>You can just plug the pico into this board, connect usb cable, compile, load up this code and you are off.</p>
<h3>Joystick</h3>
<p>I needed buttons to control the games/menus, initially I put together an interface board using a few tiny surface mounted buttons which turned out to be terrible.  Then I found the Funduino Joystick shield, it had Arduino header pins but also had a pinout for all the button, +5v, +3.3v and GND, so I removed all the arduino pins and made an interface board so I could connect it to the pico via the dev board.</p>

<h3>Dev board</h3>
<p>I use the dual/quad GPIO expander for Raspberry Pi Pico for development, the things are awesome they allow you to plug multiple module/interface boards to a pico and have a usb socket and reset button.  I mount mine on a wooden board so they sit nice.</p>

<h2>Background</h2>
<p>Most of the programming examples are written in Python, I want to use C++ and want fast graphics, after a lot of searching and trying smale code for the ST7789 it was looking like Id have to settle with slow graphics or python.  Then I found GameTiger (https://github.com/codetiger/GameTiger-Console), a retro console project using the Pico and ST7789vw display written in C++ using the pico SDK and CMake, its built on a custom board with more Flash storage but I changed a bit of the code and got it running. For some reason the display was inverted.</p>
<p>Initally I was going to have a go at writing a game using the PixelAdventure code and resources supplied with the code, so I isolated this part of the console and started working out how it all worked.  After awhile I realised I was not coding and did not actually have a game idea, so I though maybe Ill use bits of the project to create a "graphic card/input interface" for other pico projects. So Ill use one pico to handle graphics and input control and connect another pico via spi/i2c/uart allowing me to utilise all the resources of this pico.</p>
<h2>Development</h2>
<p>I stripped down the code again to the basic functions I needed, keeping alot of other stuff I may need/want, then started adding other functions. It has pixels, lines, rectangles, triangles and bitmaps that can be created in the framebuffer, I feel we all need circles to play with and why not procedural spheres.</p>

