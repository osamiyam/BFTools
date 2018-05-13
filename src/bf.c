/********************************************
 * Title: A BrainF*ck Interpreter
 * Author: Osami Yamamoto
 * Created at:  Sat Apr  8 09:55:07 JST 2017
 * Modified at: Sat Apr  8 18:04:38 JST 2017
 ********************************************/
#include <stdio.h>
#include <stdlib.h>

static char *init(int mem_size);
static void bf(char *mem, char *prog, size_t prog_size,
	       int mem_size);

static char *init(int mem_size){
  char *ptx = malloc(sizeof(char) * mem_size);
  int i;
  for (i = 0; i < mem_size; i++)
    ptx[i] = 0;
  return ptx;
} /* init */

static void bf(char *mem, char *prog, size_t prog_size,
	       int mem_size){
  char cc;
  int pos = 0, pc = 0, c, level;
  while (pc >=0 && pc < prog_size){
    if (pos < 0 || pos >= mem_size){
      fprintf(stderr, "out of memory!\n");
      exit(1);
    }
    // printf("[%c](%d) pos = %d\n", prog[pc], pc, pos);
    switch(cc = prog[pc]){
    case '>': pos += 1; break;
    case '<': pos -= 1; break;
    case '+': mem[pos] += 1; break;
    case '-': mem[pos] -= 1; break;
    case '.': putchar(mem[pos]); break;
    case ',':
      if ((c = getchar()) != EOF) mem[pos] = c;
      else mem[pos] = 0;
      break;
    case '[':
      if (mem[pos] == 0){
	level = 1;
	pc += 1;
	while (level > 0){ 
	  if (prog[pc] == ']') level -= 1;
	  else if (prog[pc] == '[') level += 1;
	  pc += 1;
	}
	pc -= 1;
      }
      break;
    case ']':
      if (mem[pos] != 0){
	level = 1;
	pc -= 1;
	while (level > 0){
	  if (prog[pc] == '[') level -= 1;
	  else if (prog[pc] == ']') level += 1;
	  pc -= 1;
	}
	pc += 1;
      }
      break;
    }
    // printf("[%c]", cc);
    pc += 1;
  }
} /* bf */

int main(int ac, char *av[]){
  enum {N = 100000 , BUFLEN = 50000};
  char *mem = init(N);
  char buffer[BUFLEN];
  FILE *fp;
  size_t size;
  if (ac != 2){
    fprintf(stderr, "Usage: bf prog.b\n");
    exit(1);
  } /* if */
  fp = fopen(av[1], "r");
  size = fread(buffer, sizeof(char), BUFLEN, fp);
  bf(mem, buffer, size, N);
  putchar('\n');
  free(mem);
  return 0;
} /* main */
