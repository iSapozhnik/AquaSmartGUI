#ifndef AquaSmartGUI_h
#define AquaSmartGUI_h

#include "Arduino.h"

class AquaSmartGUI
{
  public:
    AquaSmartGUI();
    void draw_logo();
    void draw_start(boolean& finish);
    void draw_temperature(boolean fanIsOn, float temp, boolean temp_is_growing, int fan, int current_index, int total_elements);
    void draw_water_level(int level, int current_index, int total_elements);
    void draw_light(boolean light_is_on, int current_index, int total_elements);
    void draw_menu_item(int item_index, char *item_name); // Menu item preview
  private:
  	int progress;
};

#endif
