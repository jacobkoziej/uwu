# Make uwu
# Copyright (C) 2020  Jacob Koziej <jacobkoziej@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

PROGRAM_NAME = uwu
PREFIX ?= /usr/local
IBIN_DIR = $(PREFIX)/bin

CC = gcc
CFLAGS = -g -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

ifdef DEBUG
	CFLAGS += -DDEBUG
endif

ifneq ($(PREFIX), /usr/local)
	CFLAGS += -D PREFIX=\"$(PREFIX)\"
endif

uwu: $(OBJ_DIR)/*.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$(PROGRAM_NAME)

obj/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^
	@mkdir -p $(OBJ_DIR)
	@mv *.o $(OBJ_DIR)/

install: uwu
	@install -v -m 0755 $(BIN_DIR)/$(PROGRAM_NAME) $(IBIN_DIR)/$(PROGRAM_NAME)

uninstall:
	@rm -rvf $(IBIN_DIR)/$(PROGRAM_NAME)

clean:
	@rm -vrf $(BIN_DIR) $(OBJ_DIR)

.PHONY: install uninstall clean
