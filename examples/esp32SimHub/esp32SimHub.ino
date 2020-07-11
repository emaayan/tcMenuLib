/**
 * This example shows how to use the simhub connector to produce a realistic steering wheel simulation.
 * In this case we use a SH1106 display and a Jostick encoder to control the menu, but using the tcMenu
 * Designer you could change the display and input to whatever was more suitable for your design.
 *
 * We provide an example of how to make a custom dashboard view similiar to those found on custom
 * racing steering wheels. The view comes into play when the menu has been left inactive for more
 * than around 30 seconds. You can change this by configuring the renderer's reset interval.
 *
 * Quick instructions (see the link below for more detailed instructions).
 *
 * * Enable the custom serial protocol from SimHub settings
 * * In Custom Serial, configure the serial port and baud to match your settings.
 * * In the "after connection established" enter exactly: 'simhubStart\n'
 * * In the "before disconnect" enter exactly: 'simhubEnd\n'
 *
 * We now need to map each menu item ID to a SimHub statistic:
 *
 * * Add a new Update entry and enter: '1=' + [RPM] + '\n'
 * * Add a new Update entry and enter: '2=' + [MPH] + '\n'
 * * Add a new Update entry and enter: '4=' + [Gear] + '\n'
 *
 * See the Simhub guide for full instructions:
 * https://www.thecoderscorner.com/products/arduino-libraries/tc-menu/tcmenu-plugins/simhub-connector/
 */

#include "esp32SimHub_menu.h"
#include <tcMenuU8g2.h>
#include <Wire.h>
#include <JoystickSwitchInput.h>
#include <IoLogging.h>

#define PULSATING_LED_PIN 13

// used by the custom renderer, to work out the width of the text being drawn
int width = 20;
// used to indicate that this is the first time in to the custom renderer
bool startedCustomRender = false;

// Display variable that we earlier referred to in the designer
// Here we've used and SH1106, but you could just as easily used an SSD1306 too (or even any other supported display).
U8G2_SH1106_128X64_NONAME_F_HW_I2C gfx(U8G2_R0, 16, 15, 4);

// forward declaration of the custom rendering function for when we take over the display
void simulatorRendering(unsigned int currentValue, RenderPressMode userClicked);

void setup() {
    // we up the clock speed on the i2c bus to high speed setting 1, 400KHz and start the display
    gfx.setBusClock(400000);
    gfx.begin();

    // we start the serial bus at 115200 so it's ready for our connector to use
    Serial.begin(115200);

    // initialise the menu library, the following line was automatically added to setup by tcMenu.
    setupMenu();

    // here we calibrate the joystick to set the mid point, change the calibration to match your joystick.
    // This MUST be done AFTER setupMenu
    reinterpret_cast<JoystickSwitchInput*>(switches.getEncoder())->setTolerance(0.436, 0.01);

    // If we want to have a custom display when the menu is not active, we must provide a reset callback, it
    // is called whenever the menu times out and would otherwise reset to main menu.
    renderer.setResetCallback([] {
        startedCustomRender = false;
        renderer.takeOverDisplay(simulatorRendering);
    });

    // and we start on our custom screen by taking the display off the menu
    renderer.takeOverDisplay(simulatorRendering);

    menuGear.setTextValue("N");
}

// All IoAbstraction and TcMenu sketches need the runLoop to be called very frequently, preferably in the loop
// method with nothing else in the loop that can cause delays.
void loop() {
    taskManager.runLoop();

}

//
// Custom Rendering starts here
// Here we present a simple custom display for 128x64 displays as an example of things that you could do
// Think of this as a starting point for your own custom rendering.
//

/**
 * On the right hand side we present a few statistics, each statistic is printed using this method. It
 * determines with width of 5 digits, blanks the previous value and then renders the new value.
 * @param status the statistic to be printed as an integer
 * @param y the vertical baseline position
 */
void printIntStatusOnRight(int status, int y) {
    char sz[10];
    auto strWidth = gfx.getStrWidth("00000");
    auto x = 128 - (strWidth + width + 3);
    ltoaClrBuff(sz, status, 5, ' ', sizeof sz);
    gfx.setColorIndex(0);
    gfx.drawBox(x, y, strWidth, 14);
    gfx.setColorIndex(1);
    gfx.drawStr(x, y, sz);
}

/**
 * This is the custom rendering routine, that is called back in a game loop by the renderer. It is our
 * job to render any changes since last time to the screen in this loop.
 * @param currentValue This is the encoder position if the menu is using an encoder
 * @param userClicked this represents the status of the select button, see RenderPressMode for more details
 */
void simulatorRendering(unsigned int currentValue, RenderPressMode userClicked) {
    // if the user presses the select button, give the display back to the menu
    if(userClicked) {
        renderer.giveBackDisplay();
    }

    // we created a global boolean to determine the first time we hit this renderer, because remember that
    // only one task should render to the screen at once. So never draw anything outside of the custom
    // rendering callback.
    if(!startedCustomRender) {
        startedCustomRender = true;
        gfx.clear();

        // draw some discs at the top of the screen similar to the LED's on a racing wheel
        for(int i=0;i<8;i++) {
            if(i%2==1) // you could use some better logic here to determine which ones are on and off
                gfx.drawCircle((i * 16) + 7 , 7, 7);
            else
                gfx.drawDisc((i * 16) + 7, 7, 7);
        }

        // now draw the static text that never changes
        gfx.setFontPosBottom();
        gfx.setFont(u8g2_font_6x10_tf);
        width = gfx.getStrWidth("MPH");
        gfx.drawStr(128 - width, 32, "MPH");
        gfx.drawStr(128 - width, 46, "RPM");
        gfx.drawStr(128 - width, 58, "RND"); // change to any value you want..
    }

    // First we draw the gear indicator, it's in a large font on the left.
    gfx.setFont(u8g2_font_inr38_mf);
    gfx.drawStr(0, 72, menuGear.getTextValue());
    gfx.setFont(u8g2_font_6x10_tf);

    printIntStatusOnRight(menuSpeed.getCurrentValue(), 32);
    printIntStatusOnRight(menuRPM.getCurrentValue(), 46);
    printIntStatusOnRight((int)random(80), 58); // change to any value you want..

    gfx.sendBuffer();
}

//
// Callback functions
//

void CALLBACK_FUNCTION onConnectionChange(int id) {
    // we registered a call back on the simhub link menu item
    // this is the menu item that gets set/cleared by simhub.
    // you can take custom action on it here if needed.
    serdebugF2("Simhub connection", menuSimHubLink.getBoolean());
}
