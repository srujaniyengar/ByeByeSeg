#ifndef MEMLOCK_H
#define MEMLOCK_H
#include <stdio.h>
#include <stdlib.h>
/* THIS LIBRARY IS TO ADD BORROW CHECKER FEATURE FOR C 
 * THESE ARE DESIGNED TO AVOID PHANTOM READ/WRITE
 * Ensures memory safety without needing a garbage collector. It enforces strict rules 
 * about how references to data are used, preventing issues like dangling pointers, 
 * data races, and double frees at compile time.
 */

// Borrow Checker Enum
enum Mutability {
    mut,   // Mutable reference
    immut  // Immutable reference
};

// TO BE ADDED AT THE BEGINNING OF ANY FUNCTION
void start_check(); 

// TO BE ADDED AT THE END OF ANY FUNCTION
void end_check();  

// TO BORROW MEMORY IN A FUNCTION
void borrow(void* ptr, enum Mutability mut);  

// TO RELEASE BORROWED MEMORY
void release(void* ptr);  

// CHECKS IF THERE IS A BORROW CONFLICT
int is_conflict(void* ptr, enum Mutability mut);  

#endif // MEMLOCK_H
