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
CFLAGS = -O2 -march=native -g -ggdb \
         -Wall -Wextra -Werror \
         -Wformat=2 -Wunused \
         -Wconversion -Wmissing-prototypes \
         -Wstrict-prototypes -Wcast-qual \
         -Wnull-dereference -Wduplicated-cond \
         -fstack-protector-strong -pie -fPIE \
         -D_FORTIFY_SOURCE=2 -fno-omit-frame-pointer
LDFLAGS = -Wl,-z,defs -Wl,-z,now -Wl,-z,relro

minefield: minefield.c
	$(CC) $(CFLAGS) $(LDFLAGS) minefield.c -o minefield

clean:
	rm -f minefield
