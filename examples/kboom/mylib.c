#include "mylib.h"

void kb_factorial(unsigned int n, mpz_t rop) {
  mpz_set_ui(rop, 1); /* rop = 1 */
  for (unsigned int i = 2; i <= n; ++i)
    mpz_mul_ui(rop, rop, i); /* rop *= i */
}

void kb_fibonacci_mpz(unsigned int n, mpz_t rop) {
  mpz_t a, b;
  mpz_init_set_ui(a, 0); /* a = 0 */
  mpz_init_set_ui(b, 1); /* b = 1 */

  if (n == 0) {
    mpz_set_ui(rop, 0);
    goto done;
  }
  if (n == 1) {
    mpz_set_ui(rop, 1);
    goto done;
  }

  for (unsigned int i = 2; i <= n; ++i) {
    mpz_add(a, a, b); /* a = a + b */
    mpz_swap(a, b);   /* rotate (a, b) -> (b, a) */
  }
  mpz_set(rop, b); /* rop = b (nth Fibonacci) */

done:
  mpz_clear(a);
  mpz_clear(b);
}

void kb_sumsquare_mpz(unsigned int n, mpz_t rop) {
  mpz_t tmp1, tmp2;
  mpz_inits(tmp1, tmp2, NULL);

  mpz_set_ui(tmp1, n);         /* tmp1 = n            */
  mpz_add_ui(tmp2, tmp1, 1);   /* tmp2 = n + 1        */
  mpz_mul(rop, tmp1, tmp2);    /* rop  = n(n+1)       */
  mpz_set_ui(tmp2, 2 * n + 1); /* tmp2 = 2n + 1       */
  mpz_mul(rop, rop, tmp2);     /* rop  = n(n+1)(2n+1) */
  mpz_fdiv_q_ui(rop, rop, 6);  /* divide by 6         */

  mpz_clears(tmp1, tmp2, NULL);
}
