/*
 * Examples of usage: 
 * https://home.et.utwente.nl/slootenvanf/?s=oled
 * 
 * You must install the u8g2 library before you use this sketch:
 * Select Tools > Manage Libraries, then search for "U8g2" and install the library.
 * 
 * Learn more about the use of library U8g2:
 * https://github.com/olikraus/u8g2/wiki/u8x8reference
 * This example is based on the original "hello world" example which comes with the library
 * (File > Examples > U8g2 > u8x8 > HelloWorld)
 * 
 * Connections (hardware i2c):
 * Display: Arduino:
 * GND      GND
 * VCC      VCC (3.3 or 5V)
 * SDA      SDA (pin A4)
 * SCL      SCL (pin A5)
 */
#include <U8g2lib.h>

// software i2c:
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(7, 8, U8X8_PIN_NONE);
// hardware i2c:
U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

char buf[10]; // text buffer; to be able to use draw2x2String to show the value

void setup() {
  display.begin();
  display.setPowerSave(0);

  display.setFont(u8x8_font_pxplusibmcgathin_f);
  display.drawString(0,0,"Hello World v1!"); // print a String on line 0 (the first line)
  //display.drawString(0,6,"1234567890123456");
  display.drawString(0,7,"Hello World 2025"); // print a String on line 7 (the last line)
}

void loop() {
  unsigned int distance = 0; // we will use this variable later to get the distance from a sensor
  
  // displaying variable distance in a large (2x2) font:
  snprintf(buf, 10, "%2d", distance); // put distance variable in string buffer buf; %2d means we have two decimal places (because our value is always between 0 - 30)
  display.draw2x2String(0,1,"Distance");
  display.draw2x2String(0,4,buf);
  // alternative: display using print (simpler, no text buffer needed, but cannot use large 2x2 font)
  //display.setCursor(7, 1);
  //display.print(distance);
  delay(1000); // wait one second
}
