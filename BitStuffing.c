#include <stdio.h>
#include <stdlib.h>

#define FLAG 0x7E
#define ESCAPE 0x7D

void bit_stuffing(unsigned char *data, int *length) {
    int i, j;
    int count = 0;
    int new_length = *length;
    unsigned char *new_data = (unsigned char *) malloc(new_length + 1);

    new_data[0] = FLAG;

    for (i = 0, j = 1; i < *length; i++, j++) {
        if (data[i] == FLAG || data[i] == ESCAPE) {
            new_data[j] = ESCAPE;
            new_data[j+1] = data[i] ^ 0x20;
            j += 2;
            new_length++;
        } else {
            new_data[j] = data[i];
        }
    }

    new_data[new_length] = FLAG;
    *length = new_length;
    free(data);
    data = new_data;
}

void print_data(unsigned char *data, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char data[] = { 0x01, 0x02, 0x03, 0x7E, 0x04, 0x05, 0x7D, 0x06, 0x07 };
    int length = sizeof(data) / sizeof(data[0]);
    printf("Original data: ");
    print_data(data, length);
    bit_stuffing(data, &length);
    printf("Stuffed data: ");
    print_data(data, length);
    return 0;
}
