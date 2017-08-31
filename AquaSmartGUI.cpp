#include "Arduino.h"
#include "AquaSmartGUI.h"
// #include "U8glib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <ImagesAdafruit.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);

#define SCREEN_WIDTH            128
#define MENU_SIZE               32
#define TOP_TEXT_POS            6
#define MIDDLE_TEXT_POS         10
#define BOTTOM_TEXT_POS         19
#define BOTTOM_RIGHT_ICON_SIZE  32

int fan = 0;

AquaSmartGUI::AquaSmartGUI() {
  // u8g.setRot180();
  progress = 0;
}

void AquaSmartGUI::setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  // display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
}

void display_logo() {
  display.drawBitmap(60, 0, logo, 48, 30, 1);
  // u8g.drawXBMP(80, 0, 48, 30, logo);
}

void display_text() {
  // u8g.setFont(u8g_font_8x13B);
  // u8g.setPrintPos(0, 10);
  // u8g.println("AquaSmart");
  // display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);
  display.setCursor(0,4);
  display.print("AquaSmart");

  display.setFont();

  display.setCursor(92, 25);
  display.print("v1.0");
  display.display();
  //
  // u8g.setFont(u8g_font_04b_03);
  // u8g.setFontPosTop();
  // u8g.drawStr(114, 25, "v1.0");
}

void display_progress(int value) {
  display.drawRoundRect(0, 18, 58, 9, 3, 1);
  display.drawRect(3, 21, value, 3, 1);
  display.display();
  // u8g.drawRFrame(0,18,72,9,3);
  // u8g.drawBox(3,21,value,3);
}

void AquaSmartGUI::draw_start(boolean& finish) {
  display_text();
  display_logo();
  if (progress <= 52) {
    progress = progress + 1;
    display_progress(progress);
  } else {
    display_progress(52);
    finish = true;
  }
}

// Preview screen with the name and icon
void AquaSmartGUI::draw_menu_item(int item_index, const char *item_name) {
  const uint8_t *icon;
  if (item_index == 0) {
    icon = menu_temp;
  } else if (item_index == 1) {
    icon = menu_level;
  } else if (item_index == 2) {
    icon = menu_light;
  } else if (item_index == 3) {
    icon = menu_aeration;
  } else {
    icon = out_menu_temp;
  }

  display.clearDisplay();

  display.drawBitmap(0, 0, icon, MENU_SIZE, MENU_SIZE, 1);
  display.setCursor(MENU_SIZE+5, 10);
  display.print(item_name);
  display.display();
}

void draw_top_menu(int current_index, int total_elements) {
  int distance = 1;
  int element_width = SCREEN_WIDTH / total_elements;
  int x_pos = 0;
  // Draw top menu
  for ( int i = 0; i < total_elements; i = i + 1 ) {
    x_pos = i * (element_width + distance);
    int item_height = i == current_index ? 2 : 1;
    display.drawRect(x_pos, 0, element_width - distance, item_height, 1);
  }
}

void AquaSmartGUI::draw_temperature(boolean fanIsOn, int fan_mode, float temp, boolean temp_is_growing, int current_index, int total_elements) {
  update_fan();
  display.clearDisplay();
  // display.display();
  draw_top_menu(current_index, total_elements);

  // u8g.setFont(u8g_font_8x13B);
  // u8g.setFontPosTop();
  // https://stackoverflow.com/questions/27651012/arduino-sprintf-float-not-formatting
  char temperature[10];
  char str_temp[6];
  dtostrf(temp, 4, 1, str_temp);
  sprintf(temperature,"T:%s\xB0""C", str_temp);
  // sprintf(temperature,"%s F", str_temp);

  // float temp = 10.55;
  // sprintf (buf, "temp: %f C", t);
  // u8g.drawStr(0, 3, F("temp: 22.6\xB0""C"));
  display.setCursor(0, TOP_TEXT_POS);
  display.println(temperature);

  const uint8_t *arrow_bitmap = up;
  if (temp_is_growing) {
    arrow_bitmap = up;
  } else {
    arrow_bitmap = down;
  }
  display.drawBitmap(118, 7, arrow_bitmap, 32, 32, 1);

  char fan_mode_status[10];
  String result = "FAN: ";

  if (fanIsOn) {
    const uint8_t *bitmap = fan_on0;
    if (fan == 0) {
      bitmap = fan_on0;
    } else if (fan == 1) {
      bitmap = fan_on1;
    } else if (fan == 2) {
      bitmap = fan_on2;
    } else if (fan == 3) {
      bitmap = fan_on3;
    } else {
      bitmap = fan_on0;
    }
    result = result + "ON";

    display.drawBitmap(115, 15, bitmap, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, 1);
  } else {
    result = result + "OFF";
    display.drawBitmap(115, 15, fan_off, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, 1);
  }
  // display.display();

  if (fan_mode == 1 || fan_mode == 2) {
    result = result + "(M)";
  } else {
    result = result + "(A)";
  }
  result.toCharArray(fan_mode_status, 50);
  display.setCursor(0, BOTTOM_TEXT_POS);
  display.println(fan_mode_status);
  display.display();
}

void AquaSmartGUI::draw_water_level(int level, int current_index, int total_elements) {
  display.clearDisplay();
  draw_top_menu(current_index, total_elements);
  display.setCursor(0, BOTTOM_TEXT_POS);

  char water_level[10];
  sprintf(water_level,"LEVEL: %d CM", level);
  display.print(water_level);
  display.drawBitmap(115, 15, water_level1, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, 1);
  display.display();

}

void AquaSmartGUI::draw_light(boolean light_is_on, int current_index, int total_elements) {
  display.clearDisplay();
  draw_top_menu(current_index, total_elements);

  const uint8_t *light_bitmap = light_on;
  if (light_is_on) {
    light_bitmap = light_on;
  } else {
    light_bitmap = light_off;
  }
  display.drawBitmap(115, 15, light_bitmap, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, 1);

  display.setCursor(0, BOTTOM_TEXT_POS);
  if (light_is_on) {
    display.print("LIGHT: ON");
  } else {
    display.print("LIGHT: OFF");
  }
  display.display();
}

void AquaSmartGUI::draw_aeration(boolean aeration_on, int current_index, int total_elements) {
  display.clearDisplay();
  draw_top_menu(current_index, total_elements);

  display.drawBitmap(115, 15, aeration, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, 1);

  display.setCursor(0, BOTTOM_TEXT_POS);
  if (aeration_on) {
    display.print("AERATION: ON");
  } else {
    display.print("AERATION: OFF");
  }
  display.display();
}

// Private
void AquaSmartGUI::update_fan() {
  fan++;
  if (fan == 4) {
    fan = 0;
  }
}
