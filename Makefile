##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

# ↓ Binaries
SERVER_NAME := myteams_server
CLIENT_NAME := myteams_cli

SERVER_DIR := src/server
CLIENT_DIR := src/client
SERVER_TARGET := $(SERVER_NAME)
CLIENT_TARGET := $(CLIENT_NAME)

.DEFAULT_GOAL := all
.PHONY: all
.NOTPARALLEL: all
all: $(SERVER_NAME) $(CLIENT_NAME)

# ↓ server
.PHONY: $(SERVER_NAME)
$(SERVER_NAME):
	@ $(MAKE) -s -C $(SERVER_DIR) $(MAKEFLAGS) $(SERVER_TARGET)
	@ cp $(SERVER_DIR)/$(SERVER_TARGET) $@

# ↓ client
.PHONY: $(CLIENT_NAME)
$(CLIENT_NAME):
	@ $(MAKE) -s -C $(CLIENT_DIR) $(MAKEFLAGS) $(CLIENT_TARGET)
	@ cp $(CLIENT_DIR)/$(CLIENT_TARGET) $@

# ↓ Custom binaries
.PHONY: asan
asan: SERVER_TARGET := asan
asan: CLIENT_TARGET := asan
asan: all

.PHONY: prof
prof: SERVER_TARGET := prof
prof: CLIENT_TARGET := prof
prof: all

.PHONY: tests
tests: SERVER_TARGET := tests
tests: CLIENT_TARGET := tests
tests: all
	@ pytest -n 4

# ↓ Cleaning
.PHONY: clean
clean:
	@ $(MAKE) -s -C $(SERVER_DIR) $(MAKEFLAGS) clean
	@ $(MAKE) -s -C $(CLIENT_DIR) $(MAKEFLAGS) clean

.PHONY: fclean
fclean:
	@ $(MAKE) -s -C $(SERVER_DIR) $(MAKEFLAGS) fclean
	@ $(MAKE) -s -C $(CLIENT_DIR) $(MAKEFLAGS) fclean
	@ $(RM) $(SERVER_NAME) $(CLIENT_NAME)

.PHONY: re
.NOTPARALLEL: re
re: fclean all
