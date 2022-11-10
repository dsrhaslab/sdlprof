#include <stdarg.h>
#include "profiler.cpp"

bool dlopen_library_handle (){    
    return profiler_dlopen_library_handle();
}

extern "C" ssize_t read (int fd, void* buf, size_t size) {
    printf("entrou");
    return profiler_read(fd, buf, size);
}

extern "C" ssize_t pread (int fd, void* buf, size_t size, off_t offset) {
    return profiler_pread(fd, buf, size, offset);
}

extern "C" ssize_t pread64 (int fd, void* buf, size_t size, off64_t offset) {
    return profiler_pread64 (fd, buf, size, offset);
}

extern "C" ssize_t write (int fd, const void* buf, size_t size) {
    printf("entrou");
    return profiler_write(fd, buf, size);
}

extern "C" ssize_t pwrite (int fd, const void* buf, size_t size, off_t offset) {
    return profiler_pwrite (fd, buf, size, offset);
}

extern "C" ssize_t pwrite64 (int fd, const void* buf, size_t size, off64_t offset) {
    return profiler_pwrite64 (fd, buf, size, offset);
}

extern "C" void* mmap (void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
    return profiler_mmap (addr, length, prot, flags, fd, offset);
}

extern "C" int munmap (void* addr, size_t length) {
    return profiler_munmap (addr, length);
}

extern "C" int mprotect (void *addr, size_t len, int prot) {
    return profiler_mprotect (addr, len, prot);
}

extern "C" ssize_t getxattr (const char* path, const char* name, void* value, size_t size) {
    return profiler_getxattr (path, name, value, size);
}

extern "C" ssize_t lgetxattr (const char* path, const char* name, void* value, size_t size) {
    return profiler_lgetxattr (path, name, value, size);
}

extern "C" ssize_t fgetxattr (int fd, const char* name, void* value, size_t size) {
    return profiler_fgetxattr (fd, name, value, size);
}

extern "C" int close (int fd) {
    printf("entrou");
    return profiler_close (fd);
}

extern "C" int fclose (FILE* stream) {
    return profiler_fclose (stream);
}

extern "C" int openat (int dirfd, const char* path, int flags, ...) {
    if (flags & O_CREAT) {
        va_list args;

        va_start (args, flags);
        auto mode = static_cast<mode_t> (va_arg (args, int));
        va_end (args);

        return profiler_openat_4 (dirfd, path, flags, mode);
    } else {
        return profiler_openat_3 (dirfd, path, flags);
    }
}

extern "C" int open (const char* path, int flags, ...) {
    printf("entrou");
    if (flags & O_CREAT) {
        va_list args;

        va_start (args, flags);
        auto mode = static_cast<mode_t> (va_arg (args, int));
        va_end (args);

        return profiler_open_3 (path, flags, mode);
    } else {
        return profiler_open_2 (path, flags);
    }
}

extern "C" int open64 (const char* path, int flags, ...) {
    printf("entrou");
    if (flags & O_CREAT) {
        va_list args;

        va_start (args, flags);
        auto mode = static_cast<mode_t> (va_arg (args, int));
        va_end (args);

        return profiler_open64_3 (path, flags, mode);
    } else {
        return profiler_open64_2 (path, flags);
    }
}

extern "C" FILE* fopen (const char* pathname, const char* mode) {
    return profiler_fopen (pathname, mode);
}

extern "C" FILE* fopen64 (const char* pathname, const char* mode) {
    return profiler_fopen64 (pathname, mode);
}