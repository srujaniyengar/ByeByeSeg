# ByeByeSeg 🚀

A Custom Memory Allocator with a Built-in Borrow Checker for C/C++

**Features**

✅ Custom allocator using sbrk()✅ Borrow-checker-inspired memory tracking✅ Safe malloc and free alternatives✅ Explicit memory ownership rules✅ Prevents use-after-free & double-free errors

**Usage**

```
gcc -o example example.c safealloc.c
./example 
```
**OR**
```
make
./example
```
**API**
```
void* safe_alloc(size_t size);  // Allocate memory
void* safe_realloc(size_t size, void* ptr); // Resize memory
void* free_alloc(void* ptr); // Free memory
```
**Roadmap 🚀**

🔹 Thread safety (pthread_mutex)🔹 Custom memory pools🔹 Embedded system optimization

 
 

**Contributing**

PRs are welcome!

💡 **Say goodbye to segmentation faults with ByeByeSeg!** 🚀

