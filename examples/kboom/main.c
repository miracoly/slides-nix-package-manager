#include "mylib.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function declarations */
static void print_help(const char *prog);
static int parse_uint(const char *arg, unsigned int *out);

static void print_help(const char *prog) {
  printf("kboom — big-integer maths demo (GNU MP powered)\n\n"
         "Usage:\n"
         "  %s factorial | fa   <n>\n"
         "  %s fibonacci | fi   <n>\n"
         "  %s sumsquare | s    <n>\n"
         "  %s h | help\n\n"
         "<n> must be a non-negative integer (GMP handles arbitrarily large "
         "values).\n",
         prog, prog, prog, prog);
}

static int parse_uint(const char *arg, unsigned int *out) {
  char *end = NULL;
  unsigned long v = strtoul(arg, &end, 10);
  if (*end || v > 0xFFFFFFFFul) /* fits in 32-bit for simplicity */
    return 0;
  *out = (unsigned int)v;
  return 1;
}

int main(int argc, char **argv) {
  /* Handle “no args” or help flags */
  if (argc == 1 || !strcmp(argv[1], "h") || !strcmp(argv[1], "help")) {
    print_help(argv[0]);
    return 0;
  }

  if (argc != 3) {
    print_help(argv[0]);
    return 1;
  }

  const char *cmd = argv[1];
  unsigned int n;
  if (!parse_uint(argv[2], &n)) {
    fputs("Error: <n> must be a non-negative integer (≤ 4 294 967 295)\n",
          stderr);
    return 1;
  }

  /* Prepare an mpz_t to hold the result */
  mpz_t res;
  mpz_init(res);

  /* Dispatch sub-commands */
  if (!strcmp(cmd, "factorial") || !strcmp(cmd, "fa")) {
    kb_factorial(n, res);

  } else if (!strcmp(cmd, "fibonacci") || !strcmp(cmd, "fi")) {
    kb_fibonacci_mpz(n, res);

  } else if (!strcmp(cmd, "sumsquare") || !strcmp(cmd, "s")) {
    kb_sumsquare_mpz(n, res);

  } else {
    fprintf(stderr, "Unknown command '%s'\n", cmd);
    print_help(argv[0]);
    mpz_clear(res);
    return 1;
  }

  /* Print result in base-10 */
  gmp_printf("%Zd\n", res);
  mpz_clear(res);
  return 0;
}
