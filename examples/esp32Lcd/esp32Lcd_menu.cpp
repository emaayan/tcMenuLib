/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "esp32Lcd_menu.h"

// Global variable declarations

const PROGMEM  ConnectorLocalInfo applicationInfo = { "Esp32Lcd", "7833942f-2ef4-486f-9713-045552b747e8" };
LiquidCrystal lcd(0, 1, 2, 4, 5, 6, 7);
LiquidCrystalRenderer renderer(lcd, 20, 4);

// Global Menu Item declarations

RENDERING_CALLBACK_NAME_INVOKE(fnRGBRtCall, rgbAlphaItemRenderFn, "RGB", -1, NO_CALLBACK)
Rgb32MenuItem menuRGB(5, fnRGBRtCall, false, NULL);
ListRuntimeMenuItem menuMyList(4, 0, fnMyListRtCall, &menuRGB);
const PROGMEM BooleanMenuInfo minfoPeeled = { "Power", 3, 0xffff, 1, NO_CALLBACK, NAMING_ON_OFF };
BooleanMenuItem menuPeeled(&minfoPeeled, false, &menuMyList);
const char enumStrFoods_0[] PROGMEM = "Apples";
const char enumStrFoods_1[] PROGMEM = "Bananas";
const char enumStrFoods_2[] PROGMEM = "Oranges";
const char enumStrFoods_3[] PROGMEM = "Grapes";
const char* const enumStrFoods[] PROGMEM  = { enumStrFoods_0, enumStrFoods_1, enumStrFoods_2, enumStrFoods_3 };
const PROGMEM EnumMenuInfo minfoFoods = { "Foods", 2, 0xffff, 3, NO_CALLBACK, enumStrFoods };
EnumMenuItem menuFoods(&minfoFoods, 0, &menuPeeled);
const PROGMEM AnalogMenuInfo minfoPercentage = { "Percentage", 1, 0xffff, 100, NO_CALLBACK, 0, 1, "%" };
AnalogMenuItem menuPercentage(&minfoPercentage, 0, &menuFoods);

// Set up code

void setupMenu() {
    Wire.begin();
    lcd.setIoAbstraction(ioFrom8574(0x27, 0xff, &Wire));
    lcd.begin(20, 4);
    renderer.setUpdatesPerSecond(2);
    lcd.configureBacklightPin(3);
    lcd.backlight();
    switches.initialiseInterrupt(internalDigitalIo(), true);
    menuMgr.initForEncoder(&renderer, &menuPercentage, 26, 36, 21);
}

