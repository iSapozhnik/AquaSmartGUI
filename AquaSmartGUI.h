#ifndef AquaSmartGUI_h
#define AquaSmartGUI_h

#include "Arduino.h"

class AquaSmartGUI
{
  public:
    AquaSmartGUI();
    void setup();
    void draw_logo();
    void draw_something();
    void draw_start(boolean& finish);
    void draw_loading();
    void draw_end_loading();
    void draw_temperature(boolean fanIsOn, int fan_mode, float temp, boolean temp_is_growing, int current_index, int total_elements);
    void draw_water_level(int level, int current_index, int total_elements);
    void draw_light(boolean light_is_on, int current_index, int total_elements);
    void draw_aeration(boolean aeration_on, int current_index, int total_elements);
    void draw_settings(String address, int current_index, int total_elements);
    void draw_menu_item(int item_index, const char *item_name); // Menu item preview
  private:
  	int progress;
    void update_fan();
    void update_wifi();
};

#endif
