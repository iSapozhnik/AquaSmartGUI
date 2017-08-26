#include "Arduino.h"
#include "AquaSmartGUI.h"
#include "U8glib.h"

U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);

#define MENU_SIZE               32
#define TOP_TEXT_POS            3
#define MIDDLE_TEXT_POS         10
#define BOTTOM_TEXT_POS         16
#define BOTTOM_RIGHT_ICON_SIZE  13

const uint8_t logo[] PROGMEM = {
  0x0E, 0x00, 0x00, 0x00, 0x03, 0x00, 0x19, 0x00, 0x00, 0x80, 0x06, 0x00,
  0x19, 0x00, 0x01, 0x80, 0x07, 0x00, 0x1F, 0x80, 0x02, 0x00, 0x13, 0x00,
  0x0E, 0x00, 0x01, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x08, 0x00, 0x82, 0x02,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x30, 0x00, 0x00, 0x00, 0x18, 0x86,
  0x68, 0x00, 0x00, 0x00, 0x24, 0xD8, 0x78, 0x00, 0x00, 0x00, 0x52, 0xA0,
  0x30, 0x00, 0x02, 0x00, 0x22, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x04, 0xD8,
  0x02, 0x00, 0x00, 0x00, 0x18, 0x86, 0x05, 0x00, 0x00, 0x00, 0xE0, 0x03,
  0x82, 0x0F, 0x00, 0x00, 0x00, 0x06, 0x60, 0x70, 0x08, 0x30, 0x00, 0x0C,
  0x19, 0x80, 0x01, 0x28, 0x00, 0x00, 0xC4, 0x00, 0x06, 0x24, 0x00, 0x00,
  0xA2, 0x01, 0x38, 0x13, 0x00, 0x00, 0xE2, 0x01, 0xC0, 0x20, 0x00, 0x00,
  0xC1, 0x00, 0x00, 0x10, 0x00, 0x00, 0x01, 0x00, 0x00, 0x20, 0x00, 0x00,
  0x02, 0x09, 0xC0, 0x10, 0x00, 0x00, 0x02, 0x12, 0x38, 0x23, 0x00, 0x00,
  0x04, 0x1C, 0x06, 0x24, 0x00, 0x00, 0x18, 0x80, 0x01, 0x28, 0x00, 0x00,
  0x60, 0x70, 0x00, 0x30, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x00, 0x00, 0x00,
  };

const uint8_t menu_temp[] PROGMEM = {
  0x80, 0x03, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x40, 0x0C, 0x00, 0x00,
  0x41, 0x04, 0x00, 0x80, 0x41, 0x0C, 0x00, 0x80, 0x41, 0x05, 0x00, 0x80,
  0x41, 0x0D, 0x00, 0x80, 0x5F, 0xE5, 0xFF, 0xFF, 0x41, 0x0D, 0x00, 0x80,
  0x41, 0x05, 0x00, 0x80, 0x41, 0x0D, 0x00, 0x80, 0x41, 0x05, 0x00, 0x80,
  0x61, 0x0D, 0xC0, 0x83, 0xB1, 0x1B, 0xE0, 0x81, 0x51, 0x16, 0xF8, 0x80,
  0x51, 0x16, 0x06, 0xA3, 0xD1, 0x17, 0x0D, 0xB4, 0xB1, 0x9B, 0x0C, 0xA8,
  0x61, 0x8C, 0x00, 0xA0, 0xC1, 0x87, 0x00, 0xA8, 0x01, 0x00, 0x01, 0xB4,
  0x01, 0x00, 0x06, 0xA3, 0x01, 0x00, 0xF8, 0x83, 0x01, 0x00, 0x80, 0x87,
  0x01, 0x00, 0x00, 0x8F, 0x03, 0x00, 0x00, 0xC0, 0x02, 0x00, 0x00, 0x40,
  0x0C, 0x00, 0x00, 0x30, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t menu_level[] PROGMEM = {
  0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0xA0, 0x02,
  0x01, 0x00, 0xA0, 0x82, 0x01, 0x00, 0xA0, 0x82, 0x01, 0x00, 0xA0, 0x82,
  0x01, 0x00, 0xA0, 0x82, 0xFF, 0xFF, 0xAF, 0xFA, 0x01, 0x00, 0xA0, 0x82,
  0x01, 0x00, 0xA0, 0x82, 0x01, 0x00, 0xA0, 0x82, 0x01, 0x00, 0xA0, 0x82,
  0xE1, 0x03, 0xA0, 0x82, 0xC1, 0x07, 0xA0, 0x82, 0x81, 0x1F, 0xB8, 0x8E,
  0xC5, 0x30, 0xD0, 0x85, 0x2D, 0x58, 0xA0, 0x82, 0x15, 0x98, 0x40, 0x81,
  0x05, 0x80, 0x80, 0x80, 0x15, 0x80, 0x00, 0x80, 0x2D, 0x40, 0x00, 0x80,
  0xC5, 0x30, 0x00, 0x80, 0x81, 0x1F, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80,
  0x01, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x40,
  0x0C, 0x00, 0x00, 0x30, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t menu_light[] PROGMEM = {
  0x00, 0xE0, 0x07, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x0C, 0x30, 0x00,
  0x01, 0x06, 0x60, 0x80, 0x01, 0x02, 0x40, 0x80, 0x01, 0x01, 0x80, 0x80,
  0x01, 0x01, 0x80, 0x80, 0x7F, 0x01, 0x83, 0xFE, 0x01, 0x41, 0x85, 0x80,
  0x01, 0xA1, 0x84, 0x80, 0x01, 0x21, 0x84, 0x80, 0x01, 0x22, 0x44, 0x80,
  0x01, 0x26, 0x64, 0x80, 0x01, 0x4C, 0x32, 0x80, 0x01, 0x58, 0x1A, 0x80,
  0x01, 0xF0, 0x0F, 0x80, 0x01, 0x10, 0x08, 0x80, 0x01, 0x10, 0x0E, 0x80,
  0x01, 0xD0, 0x09, 0x80, 0x01, 0x10, 0x0E, 0x80, 0x01, 0xD0, 0x09, 0x80,
  0x01, 0x10, 0x08, 0x80, 0x01, 0xF0, 0x0F, 0x80, 0x01, 0x40, 0x02, 0x80,
  0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x00, 0xC0, 0x02, 0x00, 0x00, 0x40,
  0x0C, 0x00, 0x00, 0x30, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t up[] PROGMEM = {
  0x08, 0x1C, 0x3E, 0x7F,
};

const uint8_t down[] PROGMEM = {
  0x7F, 0x3E, 0x1C, 0x08,
};

const uint8_t water_level1[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x01, 0x10, 0xFF, 0x1F, 0x01, 0x10,
  0x45, 0x14, 0x01, 0x10, 0x11, 0x11, 0x01, 0x10, 0x45, 0x14, 0x01, 0x10,
  0xFE, 0x0F,
};

const uint8_t light_on[] PROGMEM = {
  0xF1, 0x11, 0xFA, 0x0B, 0xFC, 0x07, 0xFC, 0x07, 0x5D, 0x17, 0xAC, 0x06,
  0xEC, 0x06, 0x58, 0x03, 0x52, 0x09, 0xE1, 0x10, 0xE0, 0x00, 0xE0, 0x00,
  0xE0, 0x00,
};

const uint8_t light_off[] PROGMEM = {
  0xF0, 0x01, 0x08, 0x02, 0x04, 0x04, 0xA4, 0x04, 0x54, 0x05, 0x14, 0x05,
  0xA4, 0x04, 0xA8, 0x02, 0xF0, 0x01, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x00,
  0xE0, 0x00,
};

const uint8_t fan_off[] PROGMEM = {
  0xE0, 0x00, 0x10, 0x01, 0x10, 0x01, 0xA0, 0x00, 0xE6, 0x0C, 0x59, 0x13,
  0xB1, 0x11, 0x59, 0x13, 0xE6, 0x0C, 0xA0, 0x00, 0x10, 0x01, 0x10, 0x01,
  0xE0, 0x00,
};

const uint8_t fan_on0[] PROGMEM = {
  0xE0, 0x00, 0xF0, 0x01, 0xF0, 0x01, 0xE0, 0x00, 0xE6, 0x0C, 0x59, 0x13,
  0xB1, 0x11, 0x59, 0x13, 0xE6, 0x0C, 0xA0, 0x00, 0x10, 0x01, 0x10, 0x01,
  0xE0, 0x00,
};

const uint8_t fan_on1[] PROGMEM = {
  0xE0, 0x00, 0x10, 0x01, 0x10, 0x01, 0xA0, 0x00, 0xE6, 0x0C, 0x59, 0x1F,
  0xB1, 0x1F, 0x59, 0x1F, 0xE6, 0x0C, 0xA0, 0x00, 0x10, 0x01, 0x10, 0x01,
  0xE0, 0x00,
};

const uint8_t fan_on2[] PROGMEM = {
  0xE0, 0x00, 0x10, 0x01, 0x10, 0x01, 0xA0, 0x00, 0xE6, 0x0C, 0x59, 0x13,
  0xB1, 0x11, 0x59, 0x13, 0xE6, 0x0C, 0xE0, 0x00, 0xF0, 0x01, 0xF0, 0x01,
  0xE0, 0x00,
};

const uint8_t fan_on3[] PROGMEM = {
  0xE0, 0x00, 0x10, 0x01, 0x10, 0x01, 0xA0, 0x00, 0xE6, 0x0C, 0x5F, 0x13,
  0xBF, 0x11, 0x5F, 0x13, 0xE6, 0x0C, 0xA0, 0x00, 0x10, 0x01, 0x10, 0x01,
  0xE0, 0x00,
};

AquaSmartGUI::AquaSmartGUI()
{
  u8g.setRot180();
  progress = 0;
}

void AquaSmartGUI::draw_logo()
{

}

void display_logo() {
  u8g.drawXBMP(80, 0, 48, 30, logo);
}

void display_text() {
  u8g.setFont(u8g_font_8x13B);
  u8g.setPrintPos(0, 10);
  u8g.println("AquaSmart");

  u8g.setFont(u8g_font_04b_03);
  u8g.setFontPosTop();
  u8g.drawStr(114, 25, "v1.0");
}

void display_progress(int value) {
  u8g.drawRFrame(0,18,72,9,3);
  u8g.drawBox(3,21,value,3);
}

void AquaSmartGUI::draw_start(boolean& finish) {
  u8g.firstPage();
  do {
    display_logo();
    display_text();

    if (progress <= 66) {
      progress = progress + 1;
      display_progress(progress);
    } else {
      display_progress(66);
      finish = true;
    }
  } while( u8g.nextPage());
}

// Preview screen with the name and icon
void AquaSmartGUI::draw_menu_item(int item_index, char *item_name) {
  const uint8_t *icon;
  if (item_index == 0) {
    icon = menu_temp;
  } else if (item_index == 1) {
    icon = menu_level;
  } else {
    icon = menu_light;
  }

  u8g.firstPage();
  do {
    u8g.drawXBMP(0, 0, MENU_SIZE, MENU_SIZE, icon);
    u8g.setFont(u8g_font_8x13B);
    u8g.setFontPosTop();
    u8g.drawStr(MENU_SIZE+5, 10, item_name);
  } while( u8g.nextPage());
}

void draw_top_menu(int current_index, int total_elements) {
  int distance = 1;
  int total_width = u8g.getWidth();
  int element_width = total_width / total_elements;
  int x_pos = 0;
  // Draw top menu
  for ( int i = 0; i < total_elements; i = i + 1 ) {
    x_pos = i * (element_width + distance);
    int item_height = i == current_index ? 2 : 1;
    u8g.drawBox(x_pos, 0, element_width - distance, item_height);
  }
}

void AquaSmartGUI::draw_temperature(boolean fanIsOn, float temp, boolean temp_is_growing, int fan, int current_index, int total_elements) {
  u8g.firstPage();
  do {
    draw_top_menu(current_index, total_elements);

    u8g.setFont(u8g_font_8x13B);
    u8g.setFontPosTop();
    // https://stackoverflow.com/questions/27651012/arduino-sprintf-float-not-formatting
    char temperature[10];
    char str_temp[6];
    dtostrf(temp, 4, 1, str_temp);
    sprintf(temperature,"temp: %s\xB0""C", str_temp);
    // sprintf(temperature,"%s F", str_temp);

    // float temp = 10.55;
    // sprintf (buf, "temp: %f C", t);
    // u8g.drawStr(0, 3, F("temp: 22.6\xB0""C"));
    u8g.drawStr(0, TOP_TEXT_POS, temperature);

    const uint8_t *arrow_bitmap = up;
    if (temp_is_growing) {
    	arrow_bitmap = up;
    } else {
    	arrow_bitmap = down;
    }
    u8g.drawXBMP(118, 6, 7, 4, arrow_bitmap);

    u8g.setFont(u8g_font_8x13B);
    u8g.setFontPosTop();

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

      u8g.drawStr(0, BOTTOM_TEXT_POS, "fan: ON");
      u8g.drawXBMP(115, 15, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, bitmap);
    } else {
      u8g.drawStr(0, BOTTOM_TEXT_POS, "fan: OFF");
      u8g.drawXBMP(115, 15, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, fan_off);
    }
  } while( u8g.nextPage());
}

void AquaSmartGUI::draw_water_level(int level, int current_index, int total_elements) {
  u8g.firstPage();
  do {
    draw_top_menu(current_index, total_elements);
    u8g.setFont(u8g_font_8x13B);
    u8g.setFontPosTop();

    char water_level[10];
    sprintf(water_level,"level: %d cm", level);
    u8g.drawStr(0, MIDDLE_TEXT_POS, water_level);
    u8g.drawXBMP(115, 15, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, water_level1);
  } while( u8g.nextPage());
}

void AquaSmartGUI::draw_light(boolean light_is_on, int current_index, int total_elements) {
  u8g.firstPage();
  do {
    draw_top_menu(current_index, total_elements);

    const uint8_t *light_bitmap = light_on;
    if (light_is_on) {
    	light_bitmap = light_on;
    } else {
    	light_bitmap = light_off;
    }
    u8g.drawXBMP(115, 15, BOTTOM_RIGHT_ICON_SIZE, BOTTOM_RIGHT_ICON_SIZE, light_bitmap);

    u8g.setFont(u8g_font_8x13B);
    u8g.setFontPosTop();
    if (light_is_on) {
      u8g.drawStr(0, MIDDLE_TEXT_POS, "light: ON");
    } else {
      u8g.drawStr(0, MIDDLE_TEXT_POS, "light: OFF");
    }
  } while( u8g.nextPage());
}