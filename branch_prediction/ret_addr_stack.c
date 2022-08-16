#include <time.h>
#include <stdio.h>

#define NUM_ITER        1E6

void f(int n)
{
        if (n > 1)
                f(n - 1);
        return;
}

/*
 * Return Address Stack (RAS) Capacity Test:
 *
 * The RAS is a stack-like structure used to predict function return addresses.
 * When calling a function (bl/blr), the processor pushes the return address onto
 * the RAS. When returning from a function (ret), the processor pops from the RAS
 * and uses this as the predicted target address for the return.
 *
 * This test aims to measure the number of entries in the RAS.
 *
 * Suppose the RAS has N entries. If we execute a chain of k nested function calls,
 * each call pushes its return address to the RAS. When k > N, k - N addresses will
 * not fit into the RAS and will overwrite older entries. This causes those earlier
 * function return addresses to be predicted incorrectly which slows down program
 * execution. By measuring at which value of k program execution starts to slow down,
 * we can estimate the value of N.
 */
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
