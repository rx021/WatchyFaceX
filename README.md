# watchyFace250815-2300

Experiments in creating watchy faces

---

## SYSTEM SETUP: 
- Linux: Fedora 42 + Gnome desktop
- Arduino IDE 2.3.6 downloaded through ZIP file
    - see: https://www.arduino.cc/en/software/

## WATCHY SETUP:
    https://watchy.sqfmi.com/docs/getting-started/
```
## ARDUINO SETUP

Watchy comes pre-loaded with firmware that demonstrates all the basic features. You can also try different watch faces and examples in Arduino.
1. Download and install the latest Arduino IDE
2. Start Arduino and open File > Preferences.
3. Under Additional Board Manager URLs add:
    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

4. Open Tools > Board > Boards Manager and install the latest version of esp32 by Espressif Systems. Check to make sure you did not install Arduino ESP32 Boards by mistake.
5. Under Sketch > Include Library > Manage Libraries, search for Watchy and install the latest version
6. Make sure all the dependencies are installed i.e. GxEPD2 , WiFiManager, rtc_pcf8563,etc.

## Enter Bootloader Mode

1. To upload new firmware/watchfaces to Watchy, you will need to enter bootloader mode
2. Plug in the USB on Watchy
3. Press and hold the top 2 buttons (Back & Up) for more than 4 seconds, then release the Back button first, before releasing the Up button
4. You should now see an ESP32S3 device enumerate a serial port i.e. COM, cu.*

## Uploading New Watchfaces/Firmware

1. Select the serial port for your Watchy
2. If you can't find the serial port, repeat steps above for entering bootloader mode. Also make sure you're using a USB data cable and not a charge-only cable. Try different USB ports as well.
3. Select Tools > Board > ESP32 Arduino > ESP32S3 Dev Module
4. Select Tools > Flash Size > 8MB (64Mb)
5. Select Tools > Partition Scheme > 8M with spiffs...
6. Leave everything else as default
7. Choose an example and click upload
8. After upload is complete, reset Watchy to run the new uploaded firmware

## How to reset Watchy

1. Press and hold the top 2 buttons (Back & Up) for more than 4 seconds, then release the Up button first, before releasing the Back button
2. Watchy should now reset, wait a few seconds for it to boot up and refresh the screen

---

## Wifi Setup

1. Click 'Setup Wifi' from main menu on the watch.
2. Connect to 'Watchy Ap' wifi from another device such as phone or computer / laptop.
3. Open 192.168.4.1 in the browser. (Note: on iphone this page will open automatically.)
4. Click 'Configure WiFi'
5. Enter SSID and password. (Note: SSID can be prefilled from the list of networks at the top of this screen)
6. Hit 'Save' button and wait for Watchy.
7. If connection fails, the watchy will display 'Setup failed & timed out!', otherwise it will display the local ip address and SSID of the connected network with confirmation.

### Troubleshoot Wifi Setup:

1. Click 'Info' from 192.168.4.1 page.
2. Check your router setting to make sure the listed mac address is allowed.
3. If there is still a problem, try clicking 'Erase Wifi Config' from the 'Info' page and wait for Watchy to restart itself. Then try the wifi setup again and it should hopefully work.


```

