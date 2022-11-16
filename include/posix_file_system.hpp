/**
 *   Written by Ricardo Macedo.
 *   Copyright (c) 2021 INESC TEC.
 **/

#ifndef PROFILER_POSIX_FILE_SYSTEM_H
#define PROFILER_POSIX_FILE_SYSTEM_H

#include <cstdarg>
#include <cstring>
#include <posix_passthrough.hpp>
#include <unistd.h>



/**
 * read:
 * @param fd
 * @param buf
 * @param size
 * @return
 */
extern "C" ssize_t read (int fd, void* buf, size_t size);

/**
 * write:
 * @param fd
 * @param buf
 * @param size
 * @return
 */
extern "C" ssize_t write (int fd, const void* buf, size_t size);

/**
 * pread:
 * @param fd
 * @param buf
 * @param size
 * @param offset
 * @return
 */
extern "C" ssize_t pread (int fd, void* buf, size_t size, off_t offset);

/**
 * pwrite:
 * @param fd
 * @param buf
 * @param size
 * @param offset
 * @return
 */
extern "C" ssize_t pwrite (int fd, const void* buf, size_t size, off_t offset);

/**
 * pread64:
 * @param fd
 * @param buf
 * @param size
 * @param offset
 * @return
 */
#if defined(__USE_LARGEFILE64)
extern "C" ssize_t pread64 (int fd, void* buf, size_t size, off64_t offset);
#endif

/**
 * pwrite64:
 * @param fd
 * @param buf
 * @param size
 * @param offset
 * @return
 */
#if defined(__USE_LARGEFILE64)
extern "C" ssize_t pwrite64 (int fd, const void* buf, size_t size, off64_t offset);
#endif

/**
 * mmap:
 * @param addr
 * @param length
 * @param prot
 * @param flags
 * @param fd
 * @param offset
 * @return
 */
extern "C" void* mmap (void* addr, size_t length, int prot, int flags, int fd, off_t offset);

/**
 * munmap:
 * @param addr
 * @param length
 * @return
 */
extern "C" int munmap (void* addr, size_t length);

/**
 * open:
 * @param path
 * @param flags
 * @param ...
 * @return
 */
extern "C" int open (const char* path, int flags, ...);

/**
 * creat:
 * @param path
 * @param mode
 * @return
 */
extern "C" int creat (const char* path, mode_t mode);

/**
 * creat64:
 * @param path
 * @param mode
 * @return
 */
extern "C" int creat64 (const char* path, mode_t mode);

/**
 * openat:
 * @param dirfd
 * @param path
 * @param flags
 * @param ...
 * @return
 */
extern "C" int openat (int dirfd, const char* path, int flags, ...);

/**
 * open64:
 * @param path
 * @param flags
 * @param ...
 * @return
 */
extern "C" int open64 (const char* path, int flags, ...);

/**
 * close:
 * @param fd
 * @return
 */
extern "C" int close (int fd);

/**
 * sync:
 */
extern "C" void sync ();

/**
 * statfs:
 * @param path
 * @param buf
 * @return
 */
extern "C" int statfs (const char* path, struct statfs* buf);

/**
 * fstatfs:
 * @param fd
 * @param buf
 * @return
 */
extern "C" int fstatfs (int fd, struct statfs* buf);

/**
 * statfs64:
 * @param path
 * @param buf
 * @return
 */
extern "C" int statfs64 (const char* path, struct statfs64* buf);

/**
 * fstatfs64:
 * @param fd
 * @param buf
 * @return
 */
extern "C" int fstatfs64 (int fd, struct statfs64* buf);

/**
 * unlink:
 * @param path
 * @return
 */
extern "C" int unlink (const char* path);

/**
 * unlinkat:
 * @param dirfd
 * @param pathname
 * @param flags
 * @return
 */
extern "C" int unlinkat (int dirfd, const char* pathname, int flags);

/**
 * rename:
 *  https://man7.org/linux/man-pages/man2/rename.2.html
 * @param old_path
 * @param new_path
 * @return
 */
extern "C" int rename (const char* old_path, const char* new_path);

/**
 * renameat:
 *  https://man7.org/linux/man-pages/man2/renameat.2.html
 * @param olddirfd
 * @param old_path
 * @param newdirfd
 * @param new_path
 * @return
 */
extern "C" int renameat (int olddirfd, const char* old_path, int newdirfd, const char* new_path);

/**
 * fopen:
 * @param pathname
 * @param mode
 * @return
 */
extern "C" FILE* fopen (const char* pathname, const char* mode);

/**
 * fopen64:
 * @param pathname
 * @param mode
 * @return
 */
extern "C" FILE* fopen64 (const char* pathname, const char* mode);

/**
 * fclose:
 * @param stream
 * @return
 */
extern "C" int fclose (FILE* stream);

/**
 * mkdir:
 * @param path
 * @param mode
 * @return
 */
extern "C" int mkdir (const char* path, mode_t mode);

/**
 * mkdirat:
 * @param dirfd
 * @param path
 * @param mode
 * @return
 */
extern "C" int mkdirat (int dirfd, const char* path, mode_t mode);

/**
 * rmdir:
 * @param path
 * @return
 */
extern "C" int rmdir (const char* path);

/**
 * mknod:
 * @param path
 * @param mode
 * @param dev
 * @return
 */
extern "C" int mknod (const char* path, mode_t mode, dev_t dev);

/**
 * mknodat:
 * @param dirfd
 * @param path
 * @param mode
 * @param dev
 * @return
 */
extern "C" int mknodat (int dirfd, const char* path, mode_t mode, dev_t dev);
/**
 * getxattr:
 * @param path
 * @param name
 * @param value
 * @param size
 * @return
 */
#ifdef __linux__
extern "C" ssize_t getxattr (const char* path, const char* name, void* value, size_t size);
#endif

/**
 * lgetxattr:
 * @param path
 * @param name
 * @param value
 * @param size
 * @return
 */
extern "C" ssize_t lgetxattr (const char* path, const char* name, void* value, size_t size);

/**
 * fgetxattr:
 * @param fd
 * @param name
 * @param value
 * @param size
 * @return
 */
#ifdef __linux__
extern "C" ssize_t fgetxattr (int fd, const char* name, void* value, size_t size);
#endif

/**
 * setxattr:
 * @param path
 * @param name
 * @param value
 * @param size
 * @param flags
 * @return
 */
#ifdef __linux__
extern "C" int
setxattr (const char* path, const char* name, const void* value, size_t size, int flags);
#endif

/**
 * lsetxattr:
 * @param path
 * @param name
 * @param value
 * @param size
 * @param flags
 * @return
 */
extern "C" int
lsetxattr (const char* path, const char* name, const void* value, size_t size, int flags);

/**
 * fsetxattr:
 * @param fd
 * @param name
 * @param value
 * @param size
 * @param flags
 * @return
 */
#ifdef __linux__
extern "C" int fsetxattr (int fd, const char* name, const void* value, size_t size, int flags);
#endif

/**
 * listxattr:
 * @param path
 * @param list
 * @param size
 * @return
 */
#ifdef __linux__
extern "C" ssize_t listxattr (const char* path, char* list, size_t size);
#endif

/**
 * llistxattr:
 * @param path
 * @param list
 * @param size
 * @return
 */
extern "C" ssize_t llistxattr (const char* path, char* list, size_t size);

/**
 * flistxattr:
 * @param fd
 * @param list
 * @param size
 * @return
 */
#ifdef __linux__
extern "C" ssize_t flistxattr (int fd, char* list, size_t size);
#endif

/**
 * socket:
 * @param domain
 * @param type
 * @param protocol
 * @return
 */
extern "C" int socket (int domain, int type, int protocol);


#endif // PROFILER_POSIX_FILE_SYSTEM_H
