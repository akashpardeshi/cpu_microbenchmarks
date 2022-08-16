#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define to_us(time)     ((time) * 1E6)

#define NUM_ITER        1E6

/*
 * Translation Lookaside Buffer (TLB) Associativity Test:
 *
 * The TLB is a structure used to cache virtual-to-physical address translations
 * to avoid slow page table walks. The TLB is organized as a set-associative cache.
 *
 * This test aims to measure the associativity of the L1 data TLB.
 *
 * Suppose the TLB has S sets and W ways. If we access a sequence of pages in virtual
 * memory at various stride distances from each other, we will fill different TLB entries.
 * When the stride is equal to S, all pages will map to the same set, and if we access
 * enough pages, will cause conflict misses in the TLB which slows down program execution.
 * Note that TLB prefetching may spoil this approach. By measuring at which stride conflict
 * misses first occur, we can estimate the value of S and W.
 */
int main()
{
        const int page_size = getpagesize();
        const int num_pages = 64;       /* must be > L1 TLB associativity */
        const int max_stride = 256;     /* must be approx equal to number of sets in L1 TLB */
        int stride;
        int i;
        clock_t start, end;
        double time;
        uint8_t *buf;

        printf("title: TLB Associativity\n");
        printf("x_scale: log\n");
        printf("y_scale: linear\n");

        for (stride = max_stride; stride >= 1; stride /= 2) {
                buf = (uint8_t *) malloc(num_pages * page_size * stride);
                start = clock();
                for (i = 0; i < NUM_ITER; i++) {
                        buf[(rand() % num_pages) * stride * page_size]++;
                }
                end = clock();
                free(buf);

                time = end - start;
                time /= CLOCKS_PER_SEC;
                printf("stride: %d, total time (s): %lf\n", stride, time);
        }

        return 0;
}
