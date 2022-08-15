#include <time.h>
#include <stdio.h>

#define NUM_ITER        1E6

void f(int n)
{
        if (n > 1)
                f(n - 1);
        return;
}

int main()
{
        int depth;
        int i;
        clock_t start, end;
        double time;

        printf("title: Return Address Stack Capacity\n");
        printf("x_scale: linear\n");
        printf("y_scale: linear\n");

        for (depth = 64; depth >= 1; depth--) {
                start = clock();
                for (i = 0; i < NUM_ITER; i++)
                        f(depth);
                end = clock();

                time = end - start;
                time /= CLOCKS_PER_SEC;
                printf("call depth: %d, time per call (s): %lf, total time (s): %lf\n",
                                depth, time / depth, time);
        }

        return 0;
}
