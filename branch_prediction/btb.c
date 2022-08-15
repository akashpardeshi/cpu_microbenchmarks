#include <time.h>
#include <stdio.h>

#define NUM_ITER        1E5

void foo() {}

int main()
{
        const int num_branches = 1;  /* vary from 1..8192 */
        int i;
        clock_t start, end;
        double time;

        start = clock();
        for (i = 0; i < NUM_ITER; i++) {
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
