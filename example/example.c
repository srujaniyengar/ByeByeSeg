#include "../include/safealloc.h"
#include <stdio.h>

int main() {
    // Allocate memory for an array of 10 integers
    int *arr = (int *)safe_alloc(10 * sizeof(int));

    // Populate the array with squares of indices
    for (int i = 0; i < 10; i++) {
        arr[i] = i * i;
    }

    // Print the original array
    printf("Original array:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Reallocate memory to expand the array to 20 integers
    arr = (int *)safe_realloc(20 * sizeof(int), arr);

    // Populate the newly allocated space
    for (int i = 10; i < 20; i++) {
        arr[i] = i * i;
    }

    // Print the expanded array
    printf("Expanded array:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free allocated memory to prevent leaks
    free_alloc(arr);

    return 0;
}
