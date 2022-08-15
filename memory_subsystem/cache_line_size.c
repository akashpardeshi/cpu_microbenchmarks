#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define to_us(time)     ((time) * 1E6)

#define NUM_ITER        1E6

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
