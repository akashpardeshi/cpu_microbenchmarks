#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define to_us(time)     ((time) * 1E6)

#define NUM_ITER        1E3

int main()
{
        const int max_pages = 512;      /* 512 for L1 TLB, 4096 for L2 TLB */
        int num_pages;
        const int page_size = getpagesize();
        int i, j;
        clock_t start, end;
        double time;
        uint8_t *buf[max_pages / 32 + 1];

        printf("title: TLB Capacity\n");
        printf("x_scale: linear\n");
        printf("y_scale: linear\n");

        for (num_pages = max_pages; num_pages >= 1; num_pages -= 32) {
                buf[num_pages / 32] = (uint8_t *) malloc(num_pages * page_size);
                start = clock();
                for (i = 0; i < NUM_ITER; i++) {
                        for (j = 0; j < num_pages; j++)
                                buf[num_pages / 32][(rand() % num_pages) * page_size]++;
                }
                end = clock();

                time = end - start;
                time /= CLOCKS_PER_SEC;
                printf("number of pages: %d, access time per page (us): %lf, total time (s): %lf\n",
                                num_pages, to_us(time) / num_pages, time);
        }

        for (num_pages = max_pages; num_pages >= 1; num_pages -= 32)
                free(buf[num_pages / 32]);

        return 0;
}
