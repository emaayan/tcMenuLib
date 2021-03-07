/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
*/

#include <Arduino.h>
#include <tcMenu.h>
#include "esp32SimHub_menu.h"
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

// Global variable declarations

const PROGMEM ConnectorLocalInfo applicationInfo = { "SimHub Link", "4db9fbfe-9fab-4759-b8ff-3e0c6700f475" };
Adafruit_ILI9341 gfx(22, 17, 16);
AdafruitDrawable gfxDrawable(&gfx);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);
ESP32TouchKeysAbstraction esp32Touch(800, TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
SimhubConnector connector;

// Global Menu Item declarations

const AnyMenuInfo PROGMEM minfoShowDashboard = { "Show dashboard", 9, 0xFFFF, 0, onShowDash };
ActionMenuItem menuShowDashboard(&minfoShowDashboard, NULL);
const AnalogMenuInfo PROGMEM minfoLap = { "Lap", 10, 0xFFFF, 999, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuLap(&minfoLap, 0, &menuShowDashboard);
const char enumStrDashboard_0[] PROGMEM  = "F1 Wheel";
const char enumStrDashboard_1[] PROGMEM  = "GT3 Wheel";
const char enumStrDashboard_2[] PROGMEM  = "Custom";
const char* const enumStrDashboard[] PROGMEM  = { enumStrDashboard_0, enumStrDashboard_1, enumStrDashboard_2 };
const EnumMenuInfo PROGMEM minfoDashboard = { "Dashboard", 8, 0xFFFF, 2, onDashChanged, enumStrDashboard };
EnumMenuItem menuDashboard(&minfoDashboard, 0, &menuLap);
const AnyMenuInfo PROGMEM minfoSettingsShowDialogs = { "Show Dialogs", 11, 0xFFFF, 0, onShowDialogs };
ActionMenuItem menuSettingsShowDialogs(&minfoSettingsShowDialogs, NULL);
const AnalogMenuInfo PROGMEM minfoSettingsTestItem1 = { "Test Item 1", 5, 0xFFFF, 100, NO_CALLBACK, 0, 2, "" };
AnalogMenuItem menuSettingsTestItem1(&minfoSettingsTestItem1, 0, &menuSettingsShowDialogs);
const SubMenuInfo PROGMEM minfoSettings = { "Settings", 4, 0xFFFF, 0, NO_CALLBACK };
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsRtCall, backSubItemRenderFn, "Settings", -1, NO_CALLBACK)
BackMenuItem menuBackSettings(fnSettingsRtCall, &menuSettingsTestItem1);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, &menuDashboard);
const BooleanMenuInfo PROGMEM minfoSimHubLink = { "SimHub Link", 3, 0xFFFF, 1, onConnectionChange, NAMING_ON_OFF };
BooleanMenuItem menuSimHubLink(&minfoSimHubLink, false, &menuSettings);
const AnalogMenuInfo PROGMEM minfoTyreTemp = { "Tyre Temp", 7, 0xFFFF, 255, NO_CALLBACK, 0, 1, "C" };
AnalogMenuItem menuTyreTemp(&minfoTyreTemp, 0, &menuSimHubLink);
RENDERING_CALLBACK_NAME_INVOKE(fnGearRtCall, textItemRenderFn, "Gear", -1, NO_CALLBACK)
TextMenuItem menuGear(fnGearRtCall, 6, 2, &menuTyreTemp);
const AnalogMenuInfo PROGMEM minfoRPM = { "RPM", 2, 0xFFFF, 32000, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuRPM(&minfoRPM, 0, &menuGear);
const AnalogMenuInfo PROGMEM minfoSpeed = { "Speed", 1, 0xFFFF, 1000, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuSpeed(&minfoSpeed, 0, &menuRPM);


// Set up code

void setupMenu() {
    menuSpeed.setReadOnly(true);
    menuRPM.setReadOnly(true);
    menuTyreTemp.setReadOnly(true);

    gfx.begin();
    gfx.setRotation(1);
    renderer.setUpdatesPerSecond(5);
    renderer.prepareDisplay(false, &FreeSans9pt7b, 1, &FreeSans18pt7b, 1, true);
    switches.initialiseInterrupt(&esp32Touch, false);
    menuMgr.initForUpDownOk(&renderer, &menuSpeed, 7, 5, 6);
    esp32Touch.ensureInterruptRegistered();
    connector.begin(&Serial, 3);
}
