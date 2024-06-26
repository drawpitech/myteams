##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## common
##

# ↓ Basic variables
CC := gcc
CFLAGS := -std=gnu11 -W -Wall -Wextra -Wunused -Wpedantic
CFLAGS += -Wundef -Wshadow -Wcast-align
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -Waggregate-return -Wcast-qual
CFLAGS += -Wunreachable-code
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -iquote .
CFLAGS += -iquote ..
LDFLAGS :=
LDLIBS := -luuid

# ↓ myteams lib
CFLAGS += -isystem ../../libs
LDFLAGS += -L ../../libs/myteams
LDLIBS += -lmyteams

# ↓ Binaries
NAME ?= a.out
ASAN_NAME := asan
PROF_NAME := prof
TEST_NAME := tests

CFLAGS += -D PROG=$(NAME)

# Source files
SRC := $(shell find . -name '*.c')
SRC += $(shell find .. -maxdepth 1 -name '*.c')

# ↓ Objects
BUILD_DIR := .build
OBJ := $(SRC:%.c=$(BUILD_DIR)/source/%.o)
ASAN_OBJ := $(SRC:%.c=$(BUILD_DIR)/asan/%.o)
PROF_OBJ := $(SRC:%.c=$(BUILD_DIR)/prof/%.o)
TEST_OBJ := $(SRC:%.c=$(BUILD_DIR)/tests/%.o)

# ↓ Dependencies for headers
DEPS_FLAGS := -MMD -MP
DEPS := $(OBJ:.o=.d)
ASAN_DEPS := $(ASAN_OBJ:.o=.d)
PROF_DEPS := $(PROF_OBJ:.o=.d)

DIE := exit 1
# ↓ Colors
ECHO := echo -e
C_RESET := \033[00m
C_BOLD := \e[1m
C_RED := \e[31m
C_GREEN := \e[32m
C_YELLOW := \e[33m
C_BLUE := \e[34m
C_PURPLE := \e[35m
C_CYAN := \e[36m

.DEFAULT_GOAL := all
.PHONY: all
all: $(NAME)

# ↓ Compiling
$(BUILD_DIR)/source/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(LDLIBS) $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(NAME): $(OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) || $(DIE)

# ↓ Unit tests
$(BUILD_DIR)/tests/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(LDLIBS) $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(TEST_NAME): LDLIBS += --coverage
$(TEST_NAME): $(TEST_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) || $(DIE)

# ↓ Asan
$(BUILD_DIR)/asan/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(LDLIBS) $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(ASAN_NAME): LDLIBS += -fsanitize=address,leak,undefined -g3
$(ASAN_NAME): LDLIBS += -fanalyzer
$(ASAN_NAME): CFLAGS += -D DEBUG_MODE
$(ASAN_NAME): $(ASAN_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) || $(DIE)

# ↓ Profiler
$(BUILD_DIR)/prof/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(PROF_NAME): LDFLAGS += -pg
$(PROF_NAME): $(PROF_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $^ $(LDFLAGS) || $(DIE)

# ↓ Cleaning
.PHONY: clean
clean:
	@ $(RM) -r $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	@ $(RM) $(NAME) $(ASAN_NAME) $(PROF_NAME)

.PHONY: re
.NOTPARALLEL: re
re: fclean all

-include $(DEPS)
-include $(ASAN_DEPS)
-include $(PROF_DEPS)
