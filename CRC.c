#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POLYNOMIAL 0xEDB88320

unsigned int crc32(unsigned char *data, int length) {
    unsigned int crc = 0xFFFFFFFF;
    int i, j;

    for (i = 0; i < length; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ POLYNOMIAL;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc ^ 0xFFFFFFFF;
}

void print_data(unsigned char *data, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char data[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    int length = sizeof(data) / sizeof(data[0]);
    printf("Original data: ");
    print_data(data, length);

    unsigned int crc = crc32(data, length);
    printf("CRC: %08X\n", crc);

    // introduce error
    data[2] ^= 0xFF;
    printf("Corrupted data: ");
    print_data(data, length);

    unsigned int crc_check = crc32(data, length);
    printf("CRC check: %08X\n", crc_check);

    if (crc_check == crc) {
        printf("Data transmission successful.\n");
    } else {
        printf("Data transmission failed.\n");
    }

    return 0;
}
