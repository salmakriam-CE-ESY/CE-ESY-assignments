#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buffer;
    int head;
    int tail;
    int size;
    int count;
} CircularBuffer;

void init_buffer(CircularBuffer *cb, int size) {
    cb->size = size;
    cb->buffer = (char *)malloc(size * sizeof(char));
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int isFull(CircularBuffer *cb) {
    return cb->count == cb->size;
}

int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

void write_cb(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("[Error] Buffer Overflow! Cannot add: %c\n", data);
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % cb->size;
    cb->count++;
}

char read_cb(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        return '\0'; 
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % cb->size;
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    int bufferSize;
    char name[100];
    char finalString[110];

    printf("Enter Buffer Size: ");
    if (scanf("%d", &bufferSize) != 1) return 1;
    getchar(); 

    init_buffer(&cb, bufferSize);

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 

    strcpy(finalString, name);
    strcat(finalString, " CE-ESY");

    printf("\nProcessing String: %s\n", finalString);
    printf("----------------------------------\n");

    for (int i = 0; i < strlen(finalString); i++) {
        write_cb(&cb, finalString[i]);
    }

    printf("\nBuffer Content: ");
    while (!isEmpty(&cb)) {
        printf("%c", read_cb(&cb));
    }

    if (isEmpty(&cb)) {
        printf("\n\nCheck: Buffer is now empty.\n");
    }

    free(cb.buffer);
    return 0;
}
