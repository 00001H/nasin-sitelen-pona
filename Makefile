COMPOPT := -std=c++26 -flto -fuse-linker-plugin -Wall -Wextra -Wpedantic -m64 -O3 -I"/usr/include/Fcitx5/Core" -I"/usr/include/Fcitx5/Config"  -I"/usr/include/Fcitx5/Utils"
FINALOPT := $(COMPOPT) -s
HEADERS := $(wildcard src/*.hpp)
install: bin/main.so src/ime.conf src/addon.conf src/icon.svg src/default.txt
	sudo cp src/addon.conf /usr/share/fcitx5/addon/nasin-sitelen-pona.conf
	sudo cp src/ime.conf /usr/share/fcitx5/inputmethod/nasin-sitelen-pona.conf
	sudo cp bin/main.so /usr/lib/fcitx5/nasin-sitelen-pona.so
	sudo cp --update=none src/default.txt $(HOME)/nsp-map
	sudo cp src/icon.svg /usr/share/icons/hicolor/scalable/status/fcitx-sitelen-lili-pi-nasin-sitelen-pona.svg
	@echo [32mInstallation completed successfully. Reboot system to load the IME icon[0m
bin/main.so: src/main.cpp $(HEADERS)
	g++ -fPIC --shared $< -o $@ $(FINALOPT)
.PHONY: install
	