PROJECT :=

.PHONY: install
install: ${HOME}/bin/arduino-cli

.PHONY: config
config: ${HOME}/.arduino15/arduino-cli.yaml

.PHONY: d1mini
d1mini:
	arduino-cli core update-index
	arduino-cli core install esp8266:esp8266

${HOME}/bin/arduino-cli:
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/bin sh

${HOME}/.arduino15/arduino-cli.yaml:
	arduino-cli config init --additional-urls http://arduino.esp8266.com/stable/package_esp8266com_index.json

.PHONY: compile
compile:
	arduino-cli compile -b esp8266:esp8266:d1_mini $(PROJECT)

.PHONY: burn
burn: compile
	arduino-cli upload -b esp8266:esp8266:d1_mini -p /dev/ttyUSB0 $(PROJECT)

.PHONY: monitor
monitor:
	arduino-cli monitor -p /dev/ttyUSB0
