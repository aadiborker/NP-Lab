#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    int data[32], i, j, k, p, n, m, r, count, error_bit;
    printf("Enter the number of bits in the data: ");
    scanf("%d", &n);

    // Calculate the number of redundant bits
    for(m = 1; pow(2, m) <= n + m + 1; m++);
    r = m;

    // Calculate the total number of bits
    count = n + r;

    printf("Enter the data bits: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }

    // Calculate the parity bits
    for(i = 0, j = 1; i < r; i++, j *= 2) {
        count--;
        for(k = j - 1; k < n; k += j * 2) {
            for(p = k; p < k + j && p < n; p++) {
                if(data[p] == 1) {
                    count++;
                }
            }
        }
        data[j - 1] = (count % 2 == 0) ? 0 : 1;
        count = n + r - i - 1;
    }

    printf("The Hamming code is: ");
    for(i = 0; i < n + r; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Enter the received code: ");
    for(i = 0; i < n + r; i++) {
        scanf("%d", &data[i]);
    }

    // Check for errors
    count = n + r;
    error_bit = 0;
    for(i = 0, j = 1; i < r; i++, j *= 2) {
        count--;
        for(k = j - 1; k < n + r; k += j * 2) {
            for(p = k; p < k + j && p < n + r; p++) {
                if(data[p] == 1) {
                    count++;
                }
            }
        }
        if(count % 2 != data[j - 1]) {
            error_bit += j;
        }
        count = n + r - i - 1;
    }

    if(error_bit != 0) {
        printf("Error at bit %d\n", error_bit);
        data[error_bit - 1] = (data[error_bit - 1] == 0) ? 1 : 0;
        printf("Corrected code is: ");
        for(i = 0; i < n + r; i++) {
            printf("%d ", data[i]);
        }
    } else {
        printf("No errors detected\n");
    }

    return 0;
}
