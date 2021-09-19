/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "esp8266WifiOled_menu.h"
#include "ThemeMonoInverse.h"

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "ESP8266 Greenhouse", "01b9cb76-c108-4be3-a133-6159f8f1c9c1" };
TcMenuRemoteServer remoteServer(applicationInfo);
IoAbstractionRef ioexp_io8574 = ioFrom8574(0x20, 12);
ArduinoEEPROMAbstraction glArduinoEeprom(&EEPROM);
EepromAuthenticatorManager authManager(6);
U8G2_SH1106_128X64_NONAME_F_HW_I2C gfx(U8G2_R0, 16, U8X8_PIN_NONE, U8X8_PIN_NONE);
U8g2Drawable gfxDrawable(&gfx, &Wire);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);
WiFiServer server(3333);
EthernetInitialisation ethernetInitialisation(&server);
EthernetTagValTransport ethernetTransport;
TagValueRemoteServerConnection ethernetConnection(ethernetTransport, ethernetInitialisation);

// Global Menu Item declarations
const PROGMEM char pgmStrAuthenticatorText[] = { "Authenticator" };
EepromAuthenticationInfoMenuItem menuAuthenticator(pgmStrAuthenticatorText, NO_CALLBACK, 18, NULL);
const PROGMEM char pgmStrIoTMonitorText[] = { "IoT Monitor" };
RemoteMenuItem menuIoTMonitor(pgmStrIoTMonitorText, 17, &menuAuthenticator);
RENDERING_CALLBACK_NAME_INVOKE(fnIpAddressRtCall, ipAddressRenderFn, "IpAddress", -1, NO_CALLBACK)
IpAddressMenuItem menuIpAddress(fnIpAddressRtCall, 10, &menuIoTMonitor);
RENDERING_CALLBACK_NAME_INVOKE(fnPwdRtCall, textItemRenderFn, "Pwd", 23, NO_CALLBACK)
TextMenuItem menuPwd(fnPwdRtCall, 12, 15, &menuIpAddress);
RENDERING_CALLBACK_NAME_INVOKE(fnSSIDRtCall, textItemRenderFn, "SSID", 8, NO_CALLBACK)
TextMenuItem menuSSID(fnSSIDRtCall, 11, 15, &menuPwd);
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityRtCall, backSubItemRenderFn, "Connectivity", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoConnectivity = { "Connectivity", 9, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackConnectivity(fnConnectivityRtCall, &menuSSID);
SubMenuItem menuConnectivity(&minfoConnectivity, &menuBackConnectivity, NULL);
const PROGMEM AnyMenuInfo minfoLoadFiles = { "Load Files", 15, 0xffff, 0, onLoadFiles };
ActionMenuItem menuLoadFiles(&minfoLoadFiles, &menuConnectivity);
extern const char* fileChoicesArray;
RENDERING_CALLBACK_NAME_INVOKE(fnFileRtCall, enumItemRenderFn, "File", -1, onFileChoice)
ScrollChoiceMenuItem menuFile(14, fnFileRtCall, 0, fileChoicesArray, 10, 1, &menuLoadFiles);
const PROGMEM BooleanMenuInfo minfoSecretEntry = { "Secret Entry", 13, 0xffff, 1, NO_CALLBACK, NAMING_TRUE_FALSE };
BooleanMenuItem menuSecretEntry(&minfoSecretEntry, false, &menuFile);
const PROGMEM AnyMenuInfo minfoSaveAll = { "Save All", 8, 0xffff, 0, onSaveAll };
ActionMenuItem menuSaveAll(&minfoSaveAll, &menuSecretEntry);
const char enumStrWinOpening_0[] PROGMEM = "NARROW";
const char enumStrWinOpening_1[] PROGMEM = "WIDE";
const char enumStrWinOpening_2[] PROGMEM = "CLOSED";
const char* const enumStrWinOpening[] PROGMEM  = { enumStrWinOpening_0, enumStrWinOpening_1, enumStrWinOpening_2 };
const PROGMEM EnumMenuInfo minfoWinOpening = { "Win Opening", 7, 6, 2, onWindowOpening, enumStrWinOpening };
EnumMenuItem menuWinOpening(&minfoWinOpening, 0, &menuSaveAll);
const char enumStrHeaterPower_0[] PROGMEM = "LOW";
const char enumStrHeaterPower_1[] PROGMEM = "MEDIUM";
const char enumStrHeaterPower_2[] PROGMEM = "HIGH";
const char* const enumStrHeaterPower[] PROGMEM  = { enumStrHeaterPower_0, enumStrHeaterPower_1, enumStrHeaterPower_2 };
const PROGMEM EnumMenuInfo minfoHeaterPower = { "Heater Power", 6, 4, 2, onHeaterPower, enumStrHeaterPower };
EnumMenuItem menuHeaterPower(&minfoHeaterPower, 0, &menuWinOpening);
RENDERING_CALLBACK_NAME_INVOKE(fnSetupRtCall, backSubItemRenderFn, "Setup", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoSetup = { "Setup", 5, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSetup(fnSetupRtCall, &menuHeaterPower);
SubMenuItem menuSetup(&minfoSetup, &menuBackSetup, NULL);
const PROGMEM BooleanMenuInfo minfoLockDoor = { "Lock Door", 16, 38, 1, onLockDoor, NAMING_YES_NO };
BooleanMenuItem menuLockDoor(&minfoLockDoor, false, &menuSetup);
const PROGMEM BooleanMenuInfo minfoElectricHeater = { "Electric Heater", 4, 3, 1, onElectricHeater, NAMING_ON_OFF };
BooleanMenuItem menuElectricHeater(&minfoElectricHeater, false, &menuLockDoor);
const PROGMEM AnalogMenuInfo minfoCucumberTemp = { "Cucumber Temp", 2, 0xffff, 255, NO_CALLBACK, -20, 4, "C" };
AnalogMenuItem menuCucumberTemp(&minfoCucumberTemp, 0, &menuElectricHeater);
const PROGMEM AnalogMenuInfo minfoTomatoTemp = { "Tomato Temp", 1, 0xffff, 255, NO_CALLBACK, -20, 4, "C" };
AnalogMenuItem menuTomatoTemp(&minfoTomatoTemp, 0, &menuCucumberTemp);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    menuMgr.setEepromRef(&glArduinoEeprom);
    authManager.initialise(menuMgr.getEepromAbstraction(), 100);
    menuMgr.setAuthenticator(&authManager);
    // Now add any readonly, non-remote and visible flags.
    menuTomatoTemp.setReadOnly(true);
    menuIpAddress.setReadOnly(true);
    menuCucumberTemp.setReadOnly(true);
    menuPwd.setLocalOnly(true);
    menuSSID.setLocalOnly(true);
    menuSecretEntry.setVisible(false);

    // Code generated by plugins.
    gfx.begin();
    renderer.setUpdatesPerSecond(10);
    switches.initialise(internalDigitalIo(), true);
    menuMgr.initForEncoder(&renderer, &menuTomatoTemp, 13, 12, 14);
    remoteServer.addConnection(&ethernetConnection);
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_FIRST_ROW);
    renderer.setUseSliderForAnalog(false);
    installMonoInverseTitleTheme(renderer, MenuFontDef(nullptr, 1), MenuFontDef(u8g2_font_sirclivethebold_tr, 1), true);

    // We have an IoT monitor, register the server
    menuIoTMonitor.setRemoteServer(remoteServer);
}

