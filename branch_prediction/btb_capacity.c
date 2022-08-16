#include <time.h>
#include <stdio.h>

#define NUM_ITER        1E5

void foo() {}

/*
 * Branch Target Buffer (BTB) Capacity Test:
 *
 * The BTB is a structure used to cache branch target addresses so that subsequent
 * instructions can be fetched as soon as possible. The BTB is organized as a
 * set-associative cache.
 *
 * This test aims to measure the number of entries in the BTB.
 *
 * Suppose the BTB has N entries. If we execute k branches at sequential addresses, we
 * will sequentially fill k entries in the BTB. When k > N, k - N branches will be
 * capacity misses and will evict older entries from the BTB. This causes those earlier
 * branches to miss in the BTB, resulting in front-end stalls which slows down program
 * execution. By measuring at which value of k program execution starts to slow down,
 * we can estimate the value of N.
 */
int main()
{
        const int num_branches = 1;  /* vary from 1..8192 */
        int i;
        clock_t start, end;
        double time;

        start = clock();
        for (i = 0; i < NUM_ITER; i++) {
                /* update .rept to match num_branches */
                asm (".rept     1\n"
                     "bl        _foo\n"
                     ".endr" 
                );

        }
        end = clock();

        time = end - start;
        time /= CLOCKS_PER_SEC;
        printf("number of branches: %d, time per branch (s): %lf, total time (s): %lf\n",
                        num_branches, time / num_branches, time);

        return 0;
}
