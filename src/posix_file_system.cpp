
//#include <posix_passthrough.hpp>
#include <posix_file_system.hpp>


/**
 * read:
 * @param fd
 * @param buf
 * @param size
 * @return
 */
extern "C" ssize_t read (int fd, void* buf, size_t size)
{
    return profiler::PosixPassthrough::passthrough_posix_read (fd, buf, size);
}

/**
 * write:
 * @param fd
 * @param buf
 * @param size
 * @return
 */
extern "C" ssize_t write (int fd, const void* buf, size_t size)
{
    return profiler::PosixPassthrough::passthrough_posix_write (fd, buf, size);
}

/**
 * pread:
 * @param fd
 * @param buf
 * @param size
 * @param offset
 * @return
 */
extern "C" ssize_t pread (int fd, void* buf, size_t size, off_t offset)
{
    return profiler::PosixPassthrough::passthrough_posix_pread (fd, buf, size, offset);
}

/**
 * pwrite:
 * @param fd
 * @param buf
 * @param size
 * @param offset
 * @return
 */
extern "C" ssize_t pwrite (int fd, const void* buf, size_t size, off_t offset)
{
    return profiler::PosixPassthrough::passthrough_posix_pwrite (fd, buf, size, offset);
}

/**
 * pread64:
 * @param fd
 * @param buf
 * @param size
 * @param offset
 * @return
 */
#if defined(__USE_LARGEFILE64)
extern "C" ssize_t pread64 (int fd, void* buf, size_t size, off64_t offset)
{
    return profiler::PosixPassthrough::passthrough_posix_pread64 (fd, buf, size, offset);
}
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
extern "C" ssize_t pwrite64 (int fd, const void* buf, size_t size, off64_t offset)
{
    return profiler::PosixPassthrough::passthrough_posix_pwrite64 (fd, buf, size, offset);
}
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
extern "C" void* mmap (void* addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    return profiler::PosixPassthrough::passthrough_posix_mmap (addr, length, prot, flags, fd, offset);
}

/**
 * munmap:
 * @param addr
 * @param length
 * @return
 */
extern "C" int munmap (void* addr, size_t length)
{    
    return profiler::PosixPassthrough::passthrough_posix_munmap (addr, length);
}

/**
 * open:
 * @param path
 * @param flags
 * @param ...
 * @return
 */
extern "C" int open (const char* path, int flags, ...)
{
    if (flags & O_CREAT) {
        va_list args;

        va_start (args, flags);
        auto mode = static_cast<mode_t> (va_arg (args, int));
        va_end (args);

        return profiler::PosixPassthrough::passthrough_posix_open (path, flags, mode);
    } else {
        return profiler::PosixPassthrough::passthrough_posix_open (path, flags);
    }
}

/**
 * creat:
 * @param path
 * @param mode
 * @return
 */
extern "C" int creat (const char* path, mode_t mode)
{
    return profiler::PosixPassthrough::passthrough_posix_creat (path, mode);
}

/**
 * creat64:
 * @param path
 * @param mode
 * @return
 */
extern "C" int creat64 (const char* path, mode_t mode)
{
    return profiler::PosixPassthrough::passthrough_posix_creat64 (path, mode);
}

/**
 * openat:
 * @param dirfd
 * @param path
 * @param flags
 * @param ...
 * @return
 */
extern "C" int openat (int dirfd, const char* path, int flags, ...)
{
    if (flags & O_CREAT) {
        va_list args;

        va_start (args, flags);
        auto mode = static_cast<mode_t> (va_arg (args, int));
        va_end (args);

        return profiler::PosixPassthrough::passthrough_posix_openat (dirfd, path, flags, mode);
    } else {
        return profiler::PosixPassthrough::passthrough_posix_openat (dirfd, path, flags);
    }
}

/**
 * open64:
 * @param path
 * @param flags
 * @param ...
 * @return
 */
extern "C" int open64 (const char* path, int flags, ...)
{
    if (flags & O_CREAT) {
        va_list args;

        va_start (args, flags);
        auto mode = static_cast<mode_t> (va_arg (args, int));
        va_end (args);

        return profiler::PosixPassthrough::passthrough_posix_open64 (path, flags, mode);
    } else {
        return profiler::PosixPassthrough::passthrough_posix_open64 (path, flags);
    }
}

/**
 * close:
 * @param fd
 * @return
 */
extern "C" int close (int fd)
{
    return profiler::PosixPassthrough::passthrough_posix_close (fd);
}

/**
 * sync:
 */
/*extern "C" void sync ()
{
    return profiler::PosixPassthrough::passthrough_posix_sync ();
}*/

/**
 * statfs:
 * @param path
 * @param buf
 * @return
 */
/*extern "C" int statfs (const char* path, struct statfs* buf)
{
    return profiler::PosixPassthrough::passthrough_posix_statfs (path, buf);
}*/

/**
 * fstatfs:
 * @param fd
 * @param buf
 * @return
 */
/*extern "C" int fstatfs (int fd, struct statfs* buf)
{
    return profiler::PosixPassthrough::passthrough_posix_fstatfs (fd, buf);
}*/

/**
 * statfs64:
 * @param path
 * @param buf
 * @return
 */
/*extern "C" int statfs64 (const char* path, struct statfs64* buf)
{
    return profiler::PosixPassthrough::passthrough_posix_statfs64 (path, buf);
}*/

/**
 * fstatfs64:
 * @param fd
 * @param buf
 * @return
 */
/*extern "C" int fstatfs64 (int fd, struct statfs64* buf)
{
    return profiler::PosixPassthrough::passthrough_posix_fstatfs64 (fd, buf);
}*/

/**
 * unlink:
 * @param path
 * @return
 */
/*extern "C" int unlink (const char* path)
{
    return profiler::PosixPassthrough::passthrough_posix_unlink (path);
}*/

/**
 * unlinkat:
 * @param dirfd
 * @param pathname
 * @param flags
 * @return
 */
/*extern "C" int unlinkat (int dirfd, const char* pathname, int flags)
{
    return profiler::PosixPassthrough::passthrough_posix_unlinkat (dirfd, pathname, flags);
}*/

/**
 * rename:
 *  https://man7.org/linux/man-pages/man2/rename.2.html
 * @param old_path
 * @param new_path
 * @return
 */
/*extern "C" int rename (const char* old_path, const char* new_path)
{
    return profiler::PosixPassthrough::passthrough_posix_rename (old_path, new_path);
}*/

/**
 * renameat:
 *  https://man7.org/linux/man-pages/man2/renameat.2.html
 * @param olddirfd
 * @param old_path
 * @param newdirfd
 * @param new_path
 * @return
 */
/*extern "C" int renameat (int olddirfd, const char* old_path, int newdirfd, const char* new_path)
{
    return profiler::PosixPassthrough::passthrough_posix_renameat (olddirfd, old_path, newdirfd, new_path);
}*/

/**
 * fopen:
 * @param pathname
 * @param mode
 * @return
 */
// extern "C" FILE* fopen (const char* pathname, const char* mode)
// {
//     return profiler::PosixPassthrough::passthrough_posix_fopen (pathname, mode);
// }

/**
 * fopen64:
 * @param pathname
 * @param mode
 * @return
 */
// extern "C" FILE* fopen64 (const char* pathname, const char* mode)
// {
//     return profiler::PosixPassthrough::passthrough_posix_fopen64 (pathname, mode);
// }

/**
 * fclose:
 * @param stream
 * @return
 */
// extern "C" int fclose (FILE* stream)
// {
//     return profiler::PosixPassthrough::passthrough_posix_fclose (stream);
// }

/**
 * mkdir:
 * @param path
 * @param mode
 * @return
 */
// extern "C" int mkdir (const char* path, mode_t mode)
// {
//     return profiler::PosixPassthrough::passthrough_posix_mkdir (path, mode);
// }

/**
 * mkdirat:
 * @param dirfd
 * @param path
 * @param mode
 * @return
 */
// extern "C" int mkdirat (int dirfd, const char* path, mode_t mode)
// {
//     return profiler::PosixPassthrough::passthrough_posix_mkdirat (dirfd, path, mode);
// }

/**
 * rmdir:
 * @param path
 * @return
 */
// extern "C" int rmdir (const char* path)
// {
//     return profiler::PosixPassthrough::passthrough_posix_rmdir (path);
// }

/**
 * mknod:
 * @param path
 * @param mode
 * @param dev
 * @return
//  */
// extern "C" int mknod (const char* path, mode_t mode, dev_t dev)
// {
//     return profiler::PosixPassthrough::passthrough_posix_mknod (path, mode, dev);
// }

/**
 * mknodat:
 * @param dirfd
 * @param path
 * @param mode
 * @param dev
 * @return
 */
// extern "C" int mknodat (int dirfd, const char* path, mode_t mode, dev_t dev)
// {
//     return profiler::PosixPassthrough::passthrough_posix_mknodat (dirfd, path, mode, dev);
// }

/**
 * getxattr:
 * @param path
 * @param name
 * @param value
 * @param size
 * @return
 */
#ifdef __linux__
extern "C" ssize_t getxattr (const char* path, const char* name, void* value, size_t size)
{
    return profiler::PosixPassthrough::passthrough_posix_getxattr (path, name, value, size);
}
#endif

/**
 * lgetxattr:
 * @param path
 * @param name
 * @param value
 * @param size
 * @return
 */
extern "C" ssize_t lgetxattr (const char* path, const char* name, void* value, size_t size)
{
    return profiler::PosixPassthrough::passthrough_posix_lgetxattr (path, name, value, size);
}

/**
 * fgetxattr:
 * @param fd
 * @param name
 * @param value
 * @param size
 * @return
 */
#ifdef __linux__
extern "C" ssize_t fgetxattr (int fd, const char* name, void* value, size_t size)
{
    return profiler::PosixPassthrough::passthrough_posix_fgetxattr (fd, name, value, size);
}
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
// extern "C" int setxattr (const char* path, const char* name, const void* value, size_t size, int flags)
// {
//     return profiler::PosixPassthrough::passthrough_posix_setxattr (path, name, value, size, flags);
// }
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
// extern "C" int lsetxattr (const char* path, const char* name, const void* value, size_t size, int flags)
// {
//     return profiler::PosixPassthrough::passthrough_posix_lsetxattr (path, name, value, size, flags);
// }

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
// extern "C" int fsetxattr (int fd, const char* name, const void* value, size_t size, int flags)
// {
//     return profiler::PosixPassthrough::passthrough_posix_fsetxattr (fd, name, value, size, flags);
// }
#endif

/**
 * listxattr:
 * @param path
 * @param list
 * @param size
 * @return
 */
#ifdef __linux__
// extern "C" ssize_t listxattr (const char* path, char* list, size_t size)
// {
//     return profiler::PosixPassthrough::passthrough_posix_listxattr (path, list, size);
// }
#endif

/**
 * llistxattr:
 * @param path
 * @param list
 * @param size
 * @return
 */
// extern "C" ssize_t llistxattr (const char* path, char* list, size_t size)
// {
//     return profiler::PosixPassthrough::passthrough_posix_llistxattr (path, list, size);
// }

/**
 * flistxattr:
 * @param fd
 * @param list
 * @param size
 * @return
 */
#ifdef __linux__
// extern "C" ssize_t flistxattr (int fd, char* list, size_t size)
// {
//     return profiler::PosixPassthrough::passthrough_posix_flistxattr (fd, list, size);
// }
#endif

/**
 * socket:
 * @param domain
 * @param type
 * @param protocol
 * @return
 */
// extern "C" int socket (int domain, int type, int protocol)
// {
//     return profiler::PosixPassthrough::passthrough_posix_socket (domain, type, protocol);
// }

