#include <time.h>
#include <stdio.h>

#define NUM_ITER        1E6

void foo() {}

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
