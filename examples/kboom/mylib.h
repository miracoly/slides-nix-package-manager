#ifndef MYLIB_H
#define MYLIB_H

#include <gmp.h> /* external dependency */

/**
 * @brief Compute @f$ n! @f$ (factorial) using GMP integers.
 *
 * @param n   Non-negative input value.
 * @param[out] rop  Resulting factorial stored here.
 *
 * Complexity:  **O(n)** multiplications.
 * Behaviour is undefined if @p n is negative (but the type prevents that).
 */
void kb_factorial(unsigned int n, mpz_t rop);

/**
 * @brief Compute the @p n-th Fibonacci number.
 *
 * @param n   Index in the Fibonacci sequence (0 → 0, 1 → 1).
 * @param[out] rop  Resulting Fibonacci value.
 *
 * Complexity:  **O(n)** additions (iterative method).
 */
void kb_fibonacci_mpz(unsigned int n, mpz_t rop);

/**
 * @brief Compute the sum of squares @f$1^2 + 2^2 + \dots + n^2@f$.
 *
 * Uses the closed-form formula @f$\frac{n(n+1)(2n+1)}{6}@f$.
 *
 * @param n   Upper bound of the range (must be ≥ 0).
 * @param[out] rop  Result of the summation.
 *
 * Complexity:  **O(1)** (constant-time arithmetic on big ints).
 */
void kb_sumsquare_mpz(unsigned int n, mpz_t rop);

#endif /* MYLIB_H */
