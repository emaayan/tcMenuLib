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
#include <RuntimeMenuItem.h>
#include "tcMenuTfteSpi.h"
#include <graphics/MenuTouchScreenEncoder.h>
#include "EthernetTransport.h"
#include <RemoteConnector.h>
#include <ScrollChoiceMenuItem.h>

void setupMenu();  // forward reference of the menu setup function.
extern const PROGMEM ConnectorLocalInfo applicationInfo;  // defines the app info to the linker.

// Global variables that need exporting

extern TFT_eSPI tft;
extern TfteSpiDrawable tftDrawable;
extern GraphicsDeviceRenderer renderer;
extern MenuResistiveTouchScreen touchScreen;
extern WiFiServer server;

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

// Global Menu Item exports

extern TextMenuItem menuConnectivityPasscode;
extern TextMenuItem menuConnectivitySSID;
extern IpAddressMenuItem menuConnectivityIPAddress;
extern SubMenuItem menuConnectivity;
void CALLBACK_FUNCTION onShowDialogs(int id);
extern ActionMenuItem menuStatusShowDialogs;
extern AnalogMenuItem menuStatusRightVU;
extern AnalogMenuItem menuStatusLeftVU;
extern EnumMenuItem menuStatusAmpStatus;
extern SubMenuItem menuStatus;
extern AnalogMenuItem menuSettingsValveHeating;
extern AnalogMenuItem menuSettingsWarmUpTime;
extern AnalogMenuItem menuSettingsLine3Adj;
extern AnalogMenuItem menuSettingsLine2Adj;
extern AnalogMenuItem menuSettingsLine1Adj;
extern SubMenuItem menuSettingsChannelNames;
extern SubMenuItem menuSettings;
void CALLBACK_FUNCTION onMuteSound(int id);
extern BooleanMenuItem menuMute;
void CALLBACK_FUNCTION onAudioDirect(int id);
extern BooleanMenuItem menuDirect;
void CALLBACK_FUNCTION onChannelChanged(int id);
extern ScrollChoiceMenuItem menuChannels;
void CALLBACK_FUNCTION onVolumeChanged(int id);
extern AnalogMenuItem menuVolume;

#endif // MENU_GENERATED_CODE_H
