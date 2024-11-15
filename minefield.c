/* minefield game

   Copyright (C) 2024 Ivan Guerreschi <ivan.guerreschi.dev@gmail.com>.

   minefield is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   minefield is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with minefield.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* minefield with a size 10x10 */
#define ROWSCOLS 10

/* Number of mines */
#define MINES 5

/* buffer size */
#define MAX 2

/* map sprite */
#define MAPSYMBOL '*'

/* arrive data structure */
typedef struct
{
  char	symbol;
  int	y;
  int	x;
} arrive;

/* hero data structure */
typedef struct
{
  char	symbol;
  int	y;
  int	x;
} hero;

/* mine data structure */
typedef struct
{
  char	symbol;
  int	y;
  int	x;
} mine;


/* Build new map */
char *
build_map (arrive a)
{
  char *map = malloc (ROWSCOLS * ROWSCOLS * sizeof (char));

  if (map == NULL)
    {
      return NULL;
    }

  for (int i = 0; i < ROWSCOLS; i++)
    {
      for (int j = 0; j < ROWSCOLS; j++)
	{
	  map[i * ROWSCOLS + j] = MAPSYMBOL;
	}
    }

  map[a.y * ROWSCOLS + a.x] = a.symbol;

  return map;
}

/* Clear console and print map */
void
print_map (char *map, hero h)
{
  if (system ("clear") != 0)
    {
      fprintf (stderr, "Error call system (\"clear\")");
      exit (EXIT_FAILURE);
    }

  puts ("Vim command to move(hjkl) and exit(q)");

  map[h.y * ROWSCOLS + h.x] = h.symbol;

  for (int i = 0; i < ROWSCOLS; i++)
    {
      for (int j = 0; j < ROWSCOLS; j++)
	{
	  printf ("%c", map[i * ROWSCOLS + j]);
	}

      printf ("\n");
    }

  map[h.y * ROWSCOLS + h.x] = MAPSYMBOL;
}

/* generate x, y integer random */
void
random_numbers (int *x, int *y)
{
  srand ((unsigned int) time (NULL));

  *x = rand () % ROWSCOLS;
  *y = rand () % ROWSCOLS;

  while (*x == *y)
    {
      *y = rand () % ROWSCOLS;
    }
}

/* Create 5 mines */
void
create_mines (mine m[])
{
  srand ((unsigned int) time (NULL));

  for (int i = 0; i < MINES; i++)
    {
      m[i].symbol = 'X';
      m[i].x = rand () % ROWSCOLS;
      m[i].y = rand () % ROWSCOLS;
    }
}

int
main (void)
{
  /* Create random x and y for arrive */
  int x = 0;
  int y = 0;

  random_numbers (&x, &y);

  /* Create arrive */
  arrive a = { 'P', y, x };

  /* Create hero */
  hero h = { '@', 0, 0 };

  /* Build map */
  char *map = build_map (a);
  if (map == NULL)
    {
      fprintf (stderr, "Error: failed to allocate memory");
      exit (EXIT_FAILURE);
    }

  /* Create mines */
  mine m[MINES];
  create_mines (m);

  print_map (map, h);

  /* Logic game */
  bool loop = true;

  while (loop)
    {
      char buffer[MAX];

      if (fgets (buffer, (sizeof (char) * MAX), stdin) == NULL)
	{
	  fprintf (stderr, "Error read command");
	  loop = false;
	  break;
	}

      if (strcmp (buffer, "w") != 0 || strcmp (buffer, "h") != 0 ||
	  strcmp (buffer, "j") != 0 || strcmp (buffer, "k") != 0 ||
	  strcmp (buffer, "l") != 0)
	{
	  print_map (map, h);
	}

      if (strcmp (buffer, "q") == 0)
	{
	  loop = false;
	  break;
	}

      if (strcmp (buffer, "l") == 0)
	{
	  h.x += 1;
	  if (h.x > 9)
	    {
	      h.x = 9;
	    }
	  print_map (map, h);
	}

      if (strcmp (buffer, "h") == 0)
	{
	  h.x -= 1;
	  if (h.x < 0)
	    {
	      h.x = 0;
	    }
	  print_map (map, h);
	}

      if (strcmp (buffer, "k") == 0)
	{
	  h.y += 1;
	  if (h.y > 9)
	    {
	      h.y = 9;
	    }
	  print_map (map, h);
	}

      if (strcmp (buffer, "j") == 0)
	{
	  h.y -= 1;
	  if (h.y < 0)
	    {
	      h.y = 0;
	    }
	  print_map (map, h);
	}

      if (h.x == a.x && h.y == a.y)
	{
	  puts ("Win!!");
	  loop = false;
	  break;
	}

      for (int i = 0; i < MINES; i++)
	{
	  if (h.x == m[i].x && h.y == m[i].y)
	    {
	      h.symbol = m[i].symbol;
	      print_map (map, h);
	      puts ("Game Over!!");
	      loop = false;
	      break;
	    }
	}
    }

  /* Free map allocation memory */
  free (map);

  return EXIT_SUCCESS;
}
