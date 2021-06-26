.PHONY: compile
compile:
	arduino-cli compile -b esp8266:esp8266:d1_mini .

.PHONY: burn
burn: compile
	arduino-cli upload -b esp8266:esp8266:d1_mini -p /dev/ttyUSB0 .
