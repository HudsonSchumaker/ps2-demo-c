# Dodoi-lab - Research and Development Laboratory
# PS2 Game Development Makefile with native PS2 graphics and C11
# This Makefile is designed to work inside the ps2dev Docker container
# Include PS2SDK rules FIRST
#
# @author Hudson Schumaker
# @email hudson.schumaker@me.com
#
# Copyright (c) 2025 dodoi-lab. All rights reserved.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#

EE_BIN = bin/ps2game.elf
EE_OBJS = build/main.o build/de_gfx.o build/de_sfx.o build/de_input.o build/de_list.o \
		  build/de_scene.o build/splash_screen.o build/title_screen.o build/menu_screen.o \

# PS2SDK and compiler settings - use native PS2 graphics libraries
EE_LIBS := -L${PS2DEV}/gsKit/lib -L${PS2SDK}/ports/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer \
	-lxmp -lpng -lz -lfreetype -lpatches -lgskit -ldmakit -lps2_drivers -lmodplug -laudsrv -lpad -lstdc++ -latomic -lm -lc

EE_INCS := -I${PS2SDK}/ports/include -I./include
EE_CFLAGS += -DPS2 -Dmain=SDL_main -DHAVE_SDL2 -std=c11
#EE_CXXFLAGS = $(EE_CFLAGS)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal

# Create build directory and custom object compilation rules
build/%.o: src/%.c
	@mkdir -p build
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c $< -o $@

# ISO creation variables and rules AFTER includes
ISO_DIR = dvdrom
ISO_FILE = bin/ps2game.iso

$(ISO_FILE): $(EE_BIN)
	@mkdir -p $(ISO_DIR)/DATA
	@mkdir -p $(dir $(ISO_FILE))
	@cp $(EE_BIN) $(ISO_DIR)/BOOT.ELF
	@cp -r assets/* $(ISO_DIR)/DATA/ 2>/dev/null || true
	@echo "BOOT2 = cdrom0:\\BOOT.ELF;1" > $(ISO_DIR)/SYSTEM.CNF
	@echo "VER = 1.00" >> $(ISO_DIR)/SYSTEM.CNF
	@echo "VMODE = PAL-G" >> $(ISO_DIR)/SYSTEM.CNF
	@mkisofs -l -o $(ISO_FILE) $(ISO_DIR)

iso: $(ISO_FILE)

clean:
	rm -f bin/*.elf
	rm -f bin/*.iso
	rm -f build/*.o

clean-iso:
	rm -f dvdrom/DATA/*.*
	rm -f dvdrom/*.ELF
	rm -f dvdrom/*.CNF

.PHONY: iso clean-iso
