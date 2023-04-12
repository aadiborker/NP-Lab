#include <stdio.h>
#include <string.h>

#define MAX_FRAME_SIZE 1024

typedef struct {
    unsigned int length;
    char data[MAX_FRAME_SIZE];
} Frame;

void sender(Frame *frame) {
    printf("Enter the data to be sent: ");
    fgets(frame->data, MAX_FRAME_SIZE, stdin);
    frame->length = strlen(frame->data);
    printf("Number of bytes in the frame: %d\n", frame->length);
}

void receiver(Frame *frame) {
    printf("Received frame: %s", frame->data);
}

int main() {
    Frame frame;
    sender(&frame);
    receiver(&frame);
    return 0;
}
