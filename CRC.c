#include <stdio.h>
#include <string.h>

#define N 16

int main() {
    int i, j, k;
    char data[N], key[N], temp[N], crc[N];

    printf("Enter data: ");
    scanf("%s", data);

    printf("Enter key: ");
    scanf("%s", key);

    strcpy(temp, data);

    for(i = 0; i < strlen(key) - 1; i++) {
        strcat(temp, "0");
    }

    for(i = 0; i < strlen(key); i++) {
        crc[i] = temp[i];
    }

    do {
        if(crc[0] == '1') {
            for(j = 1; j < strlen(key); j++) {
                crc[j - 1] = ((crc[j] == key[j]) ? '0' : '1');
            }
        } else {
            for(j = 1; j < strlen(key); j++) {
                crc[j - 1] = crc[j];
            }
        }
        crc[j - 1] = temp[i++];
    } while(i <= strlen(temp));

    printf("CRC bits: %s\n", crc);

    strcpy(temp, data);
    strcat(temp, crc);

    printf("Transmitted data: %s\n", temp);

    printf("Enter received data: ");
    scanf("%s", temp);

    for(i = 0; i < strlen(key) - 1; i++) {
        strcat(temp, "0");
    }

    for(i = 0; i < strlen(key); i++) {
        crc[i] = temp[i];
    }

    do {
        if(crc[0] == '1') {
            for(j = 1; j < strlen(key); j++) {
                crc[j - 1] = ((crc[j] == key[j]) ? '0' : '1');
            }
        } else {
            for(j = 1; j < strlen(key); j++) {
                crc[j - 1] = crc[j];
            }
        }
        crc[j - 1] = temp[i++];
    } while(i <= strlen(temp));

    for(i = 0; i < strlen(crc); i++) {
        if(crc[i] == '1') {
            printf("Error detected\n");
            return 0;
        }
    }

    printf("No errors detected\n");
    return 0;
}
