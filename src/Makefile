#
# Copyright (c) 2017 Fält Communications AB, Sweden. All rights reserved.
#
# Reproduction, modification, use or disclosure to third parties without
# express authority is strictly forbidden.
#
# Build environment instructions: http://wiki/dokuwiki/doku.php?id=iweb:it:build_environment
#
# Hint: Build with make V=1 to enable verbose log.

# Version of miipslib to build with.
MIIPSLIB_VERSION ?= faltcom-develop
# Filesystem to link against, 6400 and newer platforms.
TARGET_FILESYSTEM ?= v5_1_1
# 6300 filesystem to link against. Only relevant for 6300 platform.
TARGET_FILESYSTEM_6300 ?= INHOUSE_DELUXE

# Application specific compiler flags (in addition to system wide build environment)
CXXFLAGS += -Wall -O2 -g -std=c++11
CFLAGS += -Wall -pthread -O2 -g
LDFLAGS += -Lmiips_lib/bin
DEFS:= -DBUILD_TARGET=$(BUILD_TARGET)
INCL:=
LIBS:= -lpthread -lmiips-$(BUILD_TARGET) -lssl -lcrypto -lz -lmosquittopp -lmosquitto -ljansson

ifeq ($(BUILD_TARGET),6400)
	LIBS += -luuid -lcares
endif

# Name of the app
FILENAME:= mqtt_client
# File where the variable appversion[] is defined.
APPVERSION_FILENAME:= main.cpp
# Binary output directory
BIN:= bin
# Dependency output directory
DEPDIR:= .dep

# =========== List your source files here =========== #
#     Don't forget trailing '\' on all but last item.
C_SRC:=
CXX_SRC:= \
	main.cpp \
	mqttWrapper.cpp \
	testPublisher.cpp \
	outputHandler.cpp \
	clientHandler.cpp \
	testSubsLoad.cpp

# =============== DO NOT MODIFY BELOW =============== #
CURRENT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
DEPDIR_ABSPATH = $(CURRENT_DIR)/$(DEPDIR)
SYSFS_LIBPATH ?= UNKNOWN
BUILD_TARGET ?= 0

# Generate output filename
VERSION:=$(shell $(FALTCOM_TOOLS)/get_version.sh $(APPVERSION_FILENAME))
TARGET:= "$(BIN)/$(FILENAME)-$(VERSION)-$(BUILD_TARGET)"

ifeq ($(VERSION),)
$(error "Bad app version"))
endif

ifeq ($(BUILD_TARGET),6300)
	TARGET_FILESYSTEM:= $(TARGET_FILESYSTEM_6300)
endif

CURRENT_FILESYSTEM:= $(shell readlink $(SYSFS_LIBPATH) | sed 's/\///g')
TARGET_FILESYSTEM_FULL:= libs-$(TARGET_FILESYSTEM)-$(BUILD_TARGET)

C_OBJ=$(C_SRC:.c=.o)
CXX_OBJ=$(CXX_SRC:.cpp=.o)

SRC=$(C_SRC) $(CXX_SRC)
OBJ=$(C_OBJ) $(CXX_OBJ)

# Ensure necessary directories exist.
$(shell mkdir -p $(BIN) > /dev/null)
$(shell mkdir -p $(DEPDIR_ABSPATH) >/dev/null)

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR_ABSPATH)/$(notdir $*.Td)
# Rename the generated temporary dependency file to the real dependency
# file. We do this in a separate step so that failures during the
# compilation won’t leave a corrupted dependency file.
POSTCOMPILE = @mv -f $(DEPDIR_ABSPATH)/$(notdir $*.Td) $(DEPDIR_ABSPATH)/$(notdir $*.d)

# Find out if compiler target has changed.
PREV_TARGET:=$(shell cat $(DEPDIR_ABSPATH)/target.txt 2> /dev/null)

# Automake style pretty print gcc. Build with make V=1 for wall of compiling text
V = 0
ACTUAL_CC:= $(CC)
CC_0 = @echo "Compiling $<..."; $(ACTUAL_CC)
CC_1 = $(ACTUAL_CC)
CC_TO_USE =$(CC_$(V))
# Automake style pretty print g++
ACTUAL_CXX:= $(CXX)
CXX_0 = @echo "Compiling $<..."; $(ACTUAL_CXX)
CXX_1 = $(ACTUAL_CXX)
CXX_TO_USE = $(CXX_$(V))

.c.o:
	$(CC_TO_USE) -c -o $@ $(DEPFLAGS) $(DEFS) $(INCL) $(CFLAGS) $*.c
	$(POSTCOMPILE)

.cpp.o:
	$(CXX_TO_USE) -c -o $@ $(DEPFLAGS) $(DEFS) $(INCL) $(CXXFLAGS) $*.cpp
	$(POSTCOMPILE)

all: $(TARGET)

$(TARGET): check-env check-fs miips_lib $(OBJ)
	$(CXX_TO_USE) -o $@ $(OBJ) $(LIBS) $(LDFLAGS)
	$(STRIP) $@
	@$(FALTCOM_TOOLS)/finish_binary.sh $(CURRENT_DIR) $(TARGET) $(DEPDIR_ABSPATH)

# Override with this makefile's target filesystem to avoid conflict
miips_lib: check-miipslib
	@TARGET_FILESYSTEM=$(TARGET_FILESYSTEM) \
	TARGET_FILESYSTEM_6300=$(TARGET_FILESYSTEM_6300) \
	$(MAKE) -s -C miips_lib

clean:
	@rm -f $(OBJ)
	@rm -rf $(DEPDIR_ABSPATH)
	@$(MAKE) -s -C miips_lib clean

check-env:
ifeq ($(FALTCOM_TOOLS),)
	$(error Build environment not set up, run setenv_XXXX)
endif
	@$(FALTCOM_TOOLS)/check_env.sh $(DEPDIR_ABSPATH)
dep:
	@$(FALTCOM_TOOLS)/download_sysfs.sh $(TARGET_FILESYSTEM_FULL) $(SYSFS_LIBPATH)
check-fs:
	@$(FALTCOM_TOOLS)/check_fs.sh $(BUILD_TARGET) $(FILENAME) $(VERSION) $(TARGET_FILESYSTEM_FULL) $(CURRENT_FILESYSTEM)
check-miipslib:
	@$(FALTCOM_TOOLS)/git_submodules.sh $(MIIPSLIB_VERSION)

# Normalize source code by changing to unix line endings
fromdos:
	todos -p -v $(SRC)
	fromdos -p -v $(SRC)

# Create a pattern rule with an empty recipe, so that make won’t
# fail if the dependency file doesn’t exist.
$(DEPDIR_ABSPATH)/%.d: ;
# Mark the dependency files precious to make, so they won’t be
# automatically deleted as intermediate files.
.PRECIOUS: $(DEPDIR_ABSPATH)/%.d

-include $(patsubst %,$(DEPDIR_ABSPATH)/%.d,$(basename $(SRC)))
