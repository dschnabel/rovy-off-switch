#include <iostream>

#include <wiringpi/wiringPi.h>

using namespace std;

#define PIN_SWITCH	29
#define PIN_SWITCH_BCM "21"

int main(int argc, char *argv[]) {
	wiringPiSetup();
	pinMode(PIN_SWITCH, INPUT);

	// workaround to set pull-up resistor (pullUpDnControl doesn't work on PI4)
	system("raspi-gpio set " PIN_SWITCH_BCM " ip pu");

	int pressed_count = 0;
	while (1) {
		if (!digitalRead(PIN_SWITCH)) {
			pressed_count++;
		} else {
		    if (pressed_count > 0) {
		        system("screen_toggle");
		    }
		    pressed_count = 0;
		}

		if (pressed_count >= 20) {
			system("halt");
		}

		delay(200);
	}

	return 0;
}
