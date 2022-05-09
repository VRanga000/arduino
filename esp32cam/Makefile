.PHONY: esp32
esp32:
	arduino-cli core install esp32:esp32
	pip install pyserial # needed by cam code

.PHONY: board
board:
	arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

.PHONY: compile
compile:
	arduino-cli compile -b esp32:esp32:esp32cam

.PHONY: burn
burn:
	arduino-cli upload -b esp32:esp32:esp32cam -p /dev/ttyUSB0

.PHONY: monitor
monitor:
	arduino-cli monitor -p /dev/ttyUSB0
