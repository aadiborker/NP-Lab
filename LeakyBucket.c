#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BUCKET_CAPACITY 100    // maximum bucket size
#define INPUT_RATE 10          // input rate of packets (tokens) in bytes per second

int main() {
    int bucket_size = BUCKET_CAPACITY;
    int tokens = 0;
    time_t t;

    srand((unsigned) time(&t));  // seed random number generator

    while (1) {
        // simulate packet arrival
        int packet_size = rand() % 20 + 1;  // packet size between 1 and 20 bytes
        printf("Packet of size %d bytes arrived\n", packet_size);

        // check if enough tokens are available
        if (packet_size > tokens) {
            printf("Bucket overflow, packet dropped\n");
        } else {
            // consume tokens
            tokens -= packet_size;
            printf("Packet sent, %d tokens remaining\n", tokens);
        }

        // generate tokens at input rate
        tokens += INPUT_RATE;
        if (tokens > bucket_size) {
            tokens = bucket_size;
        }

        sleep(1);  // wait for 1 second before next packet arrival
    }

    return 0;
}
