#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define to_us(time)     ((time) * 1E6)

#define NUM_ITER        1E6

/*
 * Cache Line Size Test:
 *
 * This test aims to measure the L1 data cache line size.
 *
 * Suppose a cache line is L bytes. If we access memory locations at various
 * stride distances from each other, we will have different cache hit/miss patterns.
 * When the stride is less than L, we will have a miss followed by one or more hits,
 * but when the stride is greater than or equal to L, we will always have misses which
 * slows down program execution. Note that cache prefetching may spoil this approach.
 * By measuring at which stride program execution starts to slow down, we can estimate
 * the value of L.
 */
int main()
{
        const int max_stride = 512;     /* must be larger than line size */
        const int num_accesses = 1024;
        int stride, i, j;
        uint8_t *buf;
        clock_t start, end;
        double time;

        printf("title: Cache Line Size\n");
        printf("x_scale: log\n");
        printf("y_scale: linear\n");

        for (stride = 1; stride <= max_stride; stride *= 2) {
                buf = (uint8_t *) malloc(num_accesses * stride);
                start = clock();
                for (i = 0; i < NUM_ITER; i++) {
                        for (j = 0; j < num_accesses * stride; j += stride)
                                buf[j]++;
                }
                end = clock();
                free(buf);

                time = end - start;
                time /= CLOCKS_PER_SEC;
                printf("stride: %d, time per access (us): %lf\n", stride, to_us(time / num_accesses));
        }

        return 0;
}
