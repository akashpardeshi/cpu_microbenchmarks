#include <time.h>
#include <stdio.h>

#define NUM_ITER        1E6

void foo() {}

/*
 * Branch Target Buffer (BTB) Associativity Test:
 *
 * The BTB is a structure used to cache branch target addresses so that subsequent
 * instructions can be fetched as soon as possible. The BTB is organized as a
 * set-associative cache.
 *
 * This test aims to measure the associativity of the BTB.
 *
 * Suppose the BTB has S sets and W ways. If we execute a sequence of branches
 * at various stride distances from each other, we will fill different BTB entries.
 * When the stride is equal to S, all branches will map to the same set, and if we
 * execute enough branches, will cause conflict misses in the BTB which slows down
 * program execution. By measuring at which stride conflict misses first occur, we
 * can estimate the value of S and W.
 */
int main()
{
        const int stride = 1;         /* vary from 1..1024 */
        int i;
        clock_t start, end;
        double time;

        start = clock();
        for (i = 0; i < NUM_ITER; i++) {
                /* update inner .rept to match stride - 1 */
                asm (".rept     64\n"
                     "bl        _foo\n"
                     ".rept     1 - 1\n"
                     "nop\n"
                     ".endr\n"
                     ".endr" 
                );

        }
        end = clock();

        time = end - start;
        time /= CLOCKS_PER_SEC;
        printf("stride: %d, total time (s): %lf\n", stride, time);

        return 0;
}
