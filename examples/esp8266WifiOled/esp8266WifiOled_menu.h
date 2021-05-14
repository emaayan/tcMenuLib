/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#ifndef MENU_GENERATED_CODE_H
#define MENU_GENERATED_CODE_H

#include <Arduino.h>
#include <tcMenu.h>
#include "tcMenuU8g2.h"
#include "EthernetTransport.h"
#include <RemoteConnector.h>
#include <RuntimeMenuItem.h>
#include <ScrollChoiceMenuItem.h>

void setupMenu();  // forward reference of the menu setup function.
extern const PROGMEM ConnectorLocalInfo applicationInfo;  // contains app name and ID

// Global variables that need exporting

extern U8G2_SH1106_128X64_NONAME_F_SW_I2C gfx;
extern GraphicsDeviceRenderer renderer;
extern WiFiServer server;

// Global Menu Item exports

extern IpAddressMenuItem menuIpAddress;
extern TextMenuItem menuPwd;
extern TextMenuItem menuSSID;
extern BackMenuItem menuBackConnectivity;
extern SubMenuItem menuConnectivity;
extern ActionMenuItem menuLoadFiles;
extern ScrollChoiceMenuItem menuFile;
extern BooleanMenuItem menuSecretEntry;
extern ActionMenuItem menuSaveAll;
extern EnumMenuItem menuWinOpening;
extern EnumMenuItem menuHeaterPower;
extern BackMenuItem menuBackSetup;
extern SubMenuItem menuSetup;
extern BooleanMenuItem menuLockDoor;
extern BooleanMenuItem menuElectricHeater;
extern AnalogMenuItem menuCucumberTemp;
extern AnalogMenuItem menuTomatoTemp;

// Provide a wrapper to get hold of the root menu item
inline MenuItem& rootMenuItem() { return menuTomatoTemp; }

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

void CALLBACK_FUNCTION onElectricHeater(int id);
void CALLBACK_FUNCTION onFileChoice(int id);
void CALLBACK_FUNCTION onHeaterPower(int id);
void CALLBACK_FUNCTION onLoadFiles(int id);
void CALLBACK_FUNCTION onLockDoor(int id);
void CALLBACK_FUNCTION onSaveAll(int id);
void CALLBACK_FUNCTION onWindowOpening(int id);

#endif // MENU_GENERATED_CODE_H
