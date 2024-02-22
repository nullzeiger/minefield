# Makefile minefield
#
# Copyright (C) 2024 Ivan Guerreschi <ivan.guerreschi.dev@gmail.com>
#
# minefield is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# minefield is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with minefield.  If not, see <http://www.gnu.org/licenses/>.

CC = gcc
CFLAGS = -O2 -Wall -Werror -ggdb -fanalyzer

minefield: minefield.c
	$(CC) $(CFLAGS) minefield.c -o minefield

clean:
	rm -f minefield

# Emacs Flymake
check-syntax:
	$(CC) -o /dev/null -S ${CHK_SOURCES} || true

.PHONY: check-syntax
