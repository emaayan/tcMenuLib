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

#include <LiquidCrystalIO.h>
#include "EthernetTransport.h"
#include <RemoteConnector.h>
#include <RuntimeMenuItem.h>
#include <ScrollChoiceMenuItem.h>
#include <EditableLargeNumberMenuItem.h>
#include "tcMenuLiquidCrystal.h"

// all define statements needed
#define LCD_WIDTH 20
#define LCD_HEIGHT 4
#define LCD_EN 9
#define LCD_RS 8
#define LCD_D4 10
#define LCD_D5 11
#define LCD_D6 12
#define LCD_D7 13
#define LCD_BACKLIGHT -1
#define LCD_PWM_PIN -1
#define LCD_IO_DEVICE io23017
#define UPDATES_PER_SEC 4
#define PULLUP_LOGIC true
#define INTERRUPT_SWITCHES false
#define SWITCH_IODEVICE io23017
#define ENCODER_PIN_A 6
#define ENCODER_PIN_B 7
#define ENCODER_PIN_OK 5
#define LIBRARY_TYPE ETHERNET_2
#define LISTEN_PORT 3333

// all variables that need exporting
extern IoAbstractionRef io23017;
extern LiquidCrystal lcd;
extern LiquidCrystalRenderer renderer;
extern IoAbstractionRef io23017;
extern EthernetServer server;

// all menu item forward references.
extern ActionMenuItem menuRomChoicesSave;
extern TextMenuItem menuRomChoicesValue;
extern ScrollChoiceMenuItem menuRomChoicesItemNum;
extern BackMenuItem menuBackRomChoices;
extern SubMenuItem menuRomChoices;
extern ListRuntimeMenuItem menuAdditionalCountList;
extern ScrollChoiceMenuItem menuAdditionalNumChoices;
extern ScrollChoiceMenuItem menuAdditionalRomChoice;
extern Rgb32MenuItem menuAdditionalRGB;
extern BackMenuItem menuBackAdditional;
extern SubMenuItem menuAdditional;
extern ActionMenuItem menuConnectivitySaveToEEPROM;
extern TextMenuItem menuConnectivityText;
extern IpAddressMenuItem menuConnectivityIpAddress;
extern TextMenuItem menuConnectivityChangePin;
extern BackMenuItem menuBackConnectivity;
extern SubMenuItem menuConnectivity;
extern EnumMenuItem menuFruits;
extern AnalogMenuItem menuFiths;
extern EditableLargeNumberMenuItem menuLargeNum;
extern AnalogMenuItem menuDecimalTens;
extern AnalogMenuItem menuInteger;
extern BooleanMenuItem menuHiddenItem;
extern AnalogMenuItem menuAnalog1;
extern TimeFormattedMenuItem menuTime;
extern const ConnectorLocalInfo applicationInfo;

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

int fnAdditionalCountListRtCall(RuntimeMenuItem* item, uint8_t row, RenderFnMode mode, char* buffer, int bufferSize);
int fnAdditionalNumChoicesRtCall(RuntimeMenuItem* item, uint8_t row, RenderFnMode mode, char* buffer, int bufferSize);
void CALLBACK_FUNCTION onAnalog1(int id);
void CALLBACK_FUNCTION onChangePin(int id);
void CALLBACK_FUNCTION onFiths(int id);
void CALLBACK_FUNCTION onInteger(int id);
void CALLBACK_FUNCTION onItemChange(int id);
void CALLBACK_FUNCTION onSaveToEeprom(int id);
void CALLBACK_FUNCTION onSaveValue(int id);

void setupMenu();

#endif // MENU_GENERATED_CODE_H
