/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "esp32SimHub_menu.h"
#include "../ThemeCoolBlueTraditional.h"
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "SimHub Link", "4db9fbfe-9fab-4759-b8ff-3e0c6700f475" };
TcMenuRemoteServer remoteServer(applicationInfo);

Adafruit_ILI9341 gfx(22, 17, 16);
AdafruitDrawable gfxDrawable(&gfx, 40);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);
ESP32TouchKeysAbstraction esp32Touch(300, TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
SimHubRemoteConnection simhubConnection(&Serial, 3);

// Global Menu Item declarations
const PROGMEM AnyMenuInfo minfoEngineV836S = { "V8 3.6S", 20, 0xffff, 0, onEngineHasChanged };
ActionMenuItem menuEngineV836S(&minfoEngineV836S, NULL, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoEngineV630T = { "V6 3.0T", 19, 0xffff, 0, onEngineHasChanged };
ActionMenuItem menuEngineV630T(&minfoEngineV630T, &menuEngineV836S, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoEngineI420T = { "I4 2.0T", 18, 0xffff, 0, onEngineHasChanged };
ActionMenuItem menuEngineI420T(&minfoEngineI420T, &menuEngineV630T, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoCardsI416T = { "I4 1.6T", 17, 0xffff, 0, onEngineHasChanged };
ActionMenuItem menuCardsI416T(&minfoCardsI416T, &menuEngineI420T, INFO_LOCATION_PGM);
const PROGMEM SubMenuInfo minfoEngine = { "Engine", 16, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackEngine(&minfoEngine, &menuCardsI416T, INFO_LOCATION_PGM);
SubMenuItem menuEngine(&minfoEngine, &menuBackEngine, NULL, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoShowDashboard = { "Show dashboard", 9, 0xffff, 0, onShowDash };
ActionMenuItem menuShowDashboard(&minfoShowDashboard, &menuEngine, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoLap = { "Lap", 10, 0xffff, 999, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuLap(&minfoLap, 0, &menuShowDashboard, INFO_LOCATION_PGM);
const char enumStrDashboard_0[] PROGMEM = "F1 Wheel";
const char enumStrDashboard_1[] PROGMEM = "GT3 Wheel";
const char enumStrDashboard_2[] PROGMEM = "Custom";
const char* const enumStrDashboard[] PROGMEM  = { enumStrDashboard_0, enumStrDashboard_1, enumStrDashboard_2 };
const PROGMEM EnumMenuInfo minfoDashboard = { "Dashboard", 8, 0xffff, 2, onDashChanged, enumStrDashboard };
EnumMenuItem menuDashboard(&minfoDashboard, 0, &menuLap, INFO_LOCATION_PGM);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsNewLargeNumberRtCall, largeNumItemRenderFn, "New Large Number", -1, NO_CALLBACK)
EditableLargeNumberMenuItem menuSettingsNewLargeNumber(fnSettingsNewLargeNumberRtCall, LargeFixedNumber(4, 1, 0U, 0U, false), 15, true, NULL);
const PROGMEM char pgmStrSettingsIoTMonitorText[] = { "IoT Monitor" };
RemoteMenuItem menuSettingsIoTMonitor(pgmStrSettingsIoTMonitorText, 14, &menuSettingsNewLargeNumber);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsLargeTestRtCall, largeNumItemRenderFn, "LargeTest", -1, NO_CALLBACK)
EditableLargeNumberMenuItem menuSettingsLargeTest(fnSettingsLargeTestRtCall, LargeFixedNumber(12, 4, 0U, 0U, false), 13, true, &menuSettingsIoTMonitor);
const PROGMEM BooleanMenuInfo minfoSettingsOverboost = { "Overboost", 12, 0xffff, 1, NO_CALLBACK, NAMING_ON_OFF };
BooleanMenuItem menuSettingsOverboost(&minfoSettingsOverboost, false, &menuSettingsLargeTest, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoSettingsShowDialogs = { "Show Dialogs", 11, 0xffff, 0, onShowDialogs };
ActionMenuItem menuSettingsShowDialogs(&minfoSettingsShowDialogs, &menuSettingsOverboost, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoSettingsTestItem1 = { "Test Item 1", 5, 0xffff, 255, NO_CALLBACK, -180, 2, "dB" };
AnalogMenuItem menuSettingsTestItem1(&minfoSettingsTestItem1, 0, &menuSettingsShowDialogs, INFO_LOCATION_PGM);
const PROGMEM SubMenuInfo minfoSettings = { "Settings", 4, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettings(&minfoSettings, &menuSettingsTestItem1, INFO_LOCATION_PGM);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, &menuDashboard, INFO_LOCATION_PGM);
const PROGMEM BooleanMenuInfo minfoSimHubLink = { "SimHub Link", 3, 0xffff, 1, onConnectionChange, NAMING_ON_OFF };
BooleanMenuItem menuSimHubLink(&minfoSimHubLink, false, &menuSettings, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoTyreTemp = { "Tyre Temp", 7, 0xffff, 255, NO_CALLBACK, 0, 1, "C" };
AnalogMenuItem menuTyreTemp(&minfoTyreTemp, 0, &menuSimHubLink, INFO_LOCATION_PGM);
RENDERING_CALLBACK_NAME_INVOKE(fnGearRtCall, textItemRenderFn, "Gear", -1, NO_CALLBACK)
TextMenuItem menuGear(fnGearRtCall, "", 6, 2, &menuTyreTemp);
const PROGMEM AnalogMenuInfo minfoRPM = { "RPM", 2, 0xffff, 32000, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuRPM(&minfoRPM, 0, &menuGear, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoSpeed = { "Speed", 1, 0xffff, 1000, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuSpeed(&minfoSpeed, 0, &menuRPM, INFO_LOCATION_PGM);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    setSizeBasedEEPROMStorageEnabled(false);
    // Now add any readonly, non-remote and visible flags.
    menuSpeed.setReadOnly(true);
    menuTyreTemp.setReadOnly(true);
    menuRPM.setReadOnly(true);

    // Code generated by plugins.
    gfx.begin();
    gfx.setRotation(1);
    renderer.setUpdatesPerSecond(5);
    switches.init(&esp32Touch, SWITCHES_POLL_EVERYTHING, true);
    menuMgr.initFor4WayJoystick(&renderer, &menuSpeed, 7, 5, 2, 6, -1, 35);
    esp32Touch.ensureInterruptRegistered();
    remoteServer.addConnection(&simhubConnection);
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_FIRST_ROW);
    renderer.setUseSliderForAnalog(true);
    renderer.enableTcUnicode();
    installCoolBlueTraditionalTheme(renderer, MenuFontDef(&FreeSans9pt7b, 1), MenuFontDef(&FreeSans12pt7b, 1), true);

    // We have an IoT monitor, register the server
    menuSettingsIoTMonitor.setRemoteServer(remoteServer);
}
