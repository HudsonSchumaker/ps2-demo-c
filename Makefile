# Dodoi-lab - Research and Development Laboratory
#
# PS2 Game Development Makefile with SDL2 PS2 graphics and C17
# This Makefile is designed to work inside the ps2dev Docker container
# Include PS2SDK rules FIRST
#
# @author Hudson Schumaker
# Copyright (c) 2025 dodoi-lab. All rights reserved.
#

EE_BIN  = bin/ps2game.elf
SRCS    := $(shell find src -name '*.c')
EE_OBJS := $(patsubst %.c, build/%.o, $(notdir $(SRCS)))
VPATH   := $(sort $(dir $(SRCS)))

# PS2SDK and compiler settings
EE_LIBS := -L${PS2DEV}/gsKit/lib -L${PS2SDK}/ports/lib
EE_LIBS += -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
EE_LIBS += -lxmp -lpng -lz -lfreetype -lpatches -lgskit -ldmakit -lps2_drivers
EE_LIBS += -lmodplug -laudsrv -lpad -lstdc++ -latomic -lvorbis -lvorbisfile -logg
EE_LIBS += -lmad -lmpg123 -lc -lm

EE_INCS := -I${PS2SDK}/ports/include
EE_CFLAGS += -DPS2 -Dmain=SDL_main -DHAVE_SDL2 -std=c17

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal

# Create build directory and custom object compilation rules
build/%.o: %.c
	@mkdir -p build
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c $< -o $@

# ISO creation variables and rules AFTER includes
ISO_DIR = dvdrom
ISO_FILE = bin/dd-ps2-c-demo.iso

$(ISO_FILE): $(EE_BIN)
	@mkdir -p $(ISO_DIR)/DATA
	@mkdir -p $(dir $(ISO_FILE))
	@cp $(EE_BIN) $(ISO_DIR)/BOOT.ELF
	@cp -r assets/* $(ISO_DIR)/DATA/ 2>/dev/null || true
	@echo "BOOT2 = cdrom0:\\BOOT.ELF;1" > $(ISO_DIR)/SYSTEM.CNF
	@echo "VER = 1.00" >> $(ISO_DIR)/SYSTEM.CNF
	@echo "VMODE = NTSC" >> $(ISO_DIR)/SYSTEM.CNF
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
