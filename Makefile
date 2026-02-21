LIB_DIR = ./Library
APP_DIR = ./App
LIB_FILE = $(LIB_DIR)/liblogger.so
HEADER_FILE = $(LIB_DIR)/journal_api.h
APP_LIB_DIR = $(APP_DIR)/lib
APP_INC_DIR = $(APP_DIR)/src

.PHONY: all lib app clean clean-lib clean-app prepare-app

all: app

lib:
	$(MAKE) -C $(LIB_DIR)

prepare-app: lib
	@mkdir -p $(APP_LIB_DIR) $(APP_INC_DIR)
	@cp $(HEADER_FILE) $(APP_INC_DIR)/
	@cp $(LIB_FILE) $(APP_LIB_DIR)/

app: prepare-app
	$(MAKE) -C $(APP_DIR)

clean-lib:
	$(MAKE) -C $(LIB_DIR) clean

clean-app:
	$(MAKE) -C $(APP_DIR) clean

clean: clean-lib clean-app