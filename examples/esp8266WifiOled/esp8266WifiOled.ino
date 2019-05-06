/**
 * This example shows a very basic home automation system, in this case we simulate a greenhouse
 * growing tomatoes and cucumbers. We can check the temprature of the areas, check if windows
 * are opened, open the window, configure the heater and see if it's on.
 * 
 * It is not a full working automation project, but rather designed to show how easily such a thing
 * could be achieved with TcMenu.
 * 
 * The circuit uses a PCF8574 with both the input via rotary encoder and the outputs for the heater
 * and window opener driven by it too.
 */

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "esp8266WifiOled_menu.h"
#include <ESP8266WiFi.h>
#include <IoAbstractionWire.h>
#include <ArduinoEEPROMAbstraction.h>

// here we define the heater and window pins on the PCF8574
// 0, 1 are A and B from encoder, 2 is OK button.
#define WINDOW_PIN 3
#define HEATER_PIN 4

// this is the interrupt pin connection from the PCF8574 back to the ESP8266 board.
#define IO_INTERRUPT_PIN 2

//
// We create an adafruit 1306 display driver and also the tcMenu display configuration options
//
Adafruit_SSD1306 gfx(128, 32, &Wire, 16);
AdaColorGfxMenuConfig config;
IoAbstractionRef io8574 = ioFrom8574(0x20, IO_INTERRUPT_PIN);

//
// state used later on by the heater and window control functions
//
bool heaterOn;
bool windowOpen;

//
// here we prepare the configuration used by the adafruit display renderer with our custom
// settings. We can rely on the defaults, but they don't always suit the display in question.
// As the 1306 (128x32) has a slighly unusual ratio it needs custom configuration.
//
void prepareOledDisplayConfig() {
	makePadding(config.titlePadding, 1, 1, 1, 1);
	makePadding(config.itemPadding, 1, 1, 1, 1);
	makePadding(config.widgetPadding, 2, 2, 0, 2);

	config.bgTitleColor = WHITE;
	config.fgTitleColor = BLACK;
	config.titleFont = NULL;
	config.titleBottomMargin = 1;
	config.widgetColor = BLACK;
	config.titleFontMagnification = 1;

	config.bgItemColor = BLACK;
	config.fgItemColor = WHITE;
	config.bgSelectColor = BLACK;
	config.fgSelectColor = WHITE;
	config.itemFont = NULL;
	config.itemFontMagnification = 1;

    config.editIcon = loResEditingIcon;
    config.activeIcon = loResActiveIcon;
    config.editIconHeight = 6;
    config.editIconWidth = 8;
}

//
// here we just start serial for debugging and try to initialise the display and menu
//
void setup() {
    Serial.begin(115200);

    // start up the display.
    if(!gfx.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println("Display not allocated - check connections");
        for(;;) yield();
    }
	gfx.clearDisplay();
    gfx.display();

    // initialise the rendering configuration, must be done before calling setupMenu().
    prepareOledDisplayConfig();

    // this sketch assumes you've successfully connected to the Wifi before, does not
    // call begin.. You can initialise the wifi whichever way you wish here.
    Serial.println("Waiting for WiFi connection");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());


    // initialise the menu.
    setupMenu();
    // we don't want to be able to edit the status tempratures.
    menuTomatoTemp.setReadOnly(true);
    menuCucumberTemp.setReadOnly(true);

    //
    // here we simulate the temprature changing.
    // temprature doesn't change that often, even 5 seconds is probably too short.
    // in a normal system you'd probably do something other than call random..
    //
    taskManager.scheduleFixedRate(5000, [] {
        menuTomatoTemp.setCurrentValue(random(255));
        menuCucumberTemp.setCurrentValue(random(255));
    });

    //
    // Now we configure our simulated heater and window.. We use inverse
    // logic on the 8574 because it's better at pulling down to GND than up.
    //
    ioDevicePinMode(io8574, WINDOW_PIN, OUTPUT);
    ioDevicePinMode(io8574, HEATER_PIN, OUTPUT);
    ioDeviceDigitalWrite(io8574, WINDOW_PIN, HIGH);
    ioDeviceDigitalWriteS(io8574, HEATER_PIN, HIGH);

    //
    // Initialise 512 bytes of ROM then load back values from eeprom
    // If this is the first time, there is protection in the library to
    // avoid loading garbage.
    //
    EEPROM.begin(512);
    ArduinoEEPROMAbstraction eepromWrapper(&EEPROM);
    menuMgr.load(eepromWrapper);
}

//
// as with all apps based off IoAbstraction's taskManager we must call loop
// very frequently. On ESP8266 it's absolutely essential that you don't do
// anything here that takes a long time as the board will get reset by it's
// internal watchdog.
//
void loop() {
    taskManager.runLoop();
}


//
// here we have the function that is called initially when the window is open
// and then repeatedly called by rescheduling itself until the window is closed
//
void windowOpenFn() {
    if(menuWindowOpen.getBoolean()) {
        windowOpen = !windowOpen;
        // 0 is narrow opening, 1 is wide. We simulate this by adjusting the speed of the call.
        int windowDelay = menuWinOpening.getCurrentValue() == 0 ? 500 : 250;
        taskManager.scheduleOnce(windowDelay, windowOpenFn);
    }
    else windowOpen = false;

    ioDeviceDigitalWriteS(io8574, WINDOW_PIN, windowOpen);
}

void heaterOnFn() {
    if(menuElectricHeater.getBoolean()) {
        heaterOn = !heaterOn;
        // the power is low medium or high. We simulate by changing the delay
        int heaterDelay = (menuHeaterPower.getCurrentValue() + 1) * 500;
        taskManager.scheduleOnce(heaterDelay, heaterOnFn);
    }
    else heaterOn = false;

    ioDeviceDigitalWriteS(io8574, HEATER_PIN, heaterOn);
}

//
// Below are the call back methods that are executed when a menu item changes.
//

void CALLBACK_FUNCTION onWindowOpen(int /*id*/) {
    Serial.print("Window is ");
    Serial.println(menuWindowOpen.getBoolean() ? "Open" : "Closed");
    if(menuWindowOpen.getBoolean()) {
        windowOpenFn();
    }
}

void CALLBACK_FUNCTION onHeaterPower(int /*id*/) {
    Serial.print("Heater power setting changed to ");
    Serial.println(menuHeaterPower.getCurrentValue());
}

void CALLBACK_FUNCTION onWindowOpening(int /*id*/) {
    Serial.print("Window setting changed");
    Serial.println(menuWinOpening.getCurrentValue());
}

void CALLBACK_FUNCTION onElectricHeater(int /*id*/) {
    Serial.print("Electric heater ");
    Serial.println(menuElectricHeater.getBoolean() ? "ON" : "OFF");
    if(menuElectricHeater.getBoolean()) {
        heaterOnFn();
    }
}

void CALLBACK_FUNCTION onSaveAll(int id) {
    Serial.println("Saving values to EEPROM");
    ArduinoEEPROMAbstraction eepromWrapper(&EEPROM);
    menuMgr.save(eepromWrapper);
    // on esp you must commit after calling save.
    EEPROM.commit();
}