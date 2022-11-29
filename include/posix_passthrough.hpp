
#ifndef PROFILER_POSIX_PASSTHROUGH_HPP
#define PROFILER_POSIX_PASSTHROUGH_HPP

#define __USE_GNU
#define _GNU_SOURCE

#include <dlfcn.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sstream>
#include <cassert>

#include <algorithm>
#include <chrono>
#include <sys/vfs.h> 
//#include  <sys/statfs.h>

namespace profiler {

/**
 * Metadata calls.
 */
using libc_open_variadic_t = int (*) (const char*, int, ...);
using libc_open_t = int (*) (const char*, int);
using libc_creat_t = int (*) (const char*, mode_t);
using libc_creat64_t = int (*) (const char*, mode_t);
using libc_openat_variadic_t = int (*) (int, const char*, int, ...);
using libc_openat_t = int (*) (int, const char*, int);
using libc_open64_variadic_t = int (*) (const char*, int, ...);
using libc_open64_t = int (*) (const char*, int);
using libc_close_t = int (*) (int);
using libc_sync_t = void (*) ();
using libc_statfs_t = int (*) (const char*, struct statfs*);
using libc_fstatfs_t = int (*) (int, struct statfs*);
using libc_statfs64_t = int (*) (const char*, struct statfs64*);
using libc_fstatfs64_t = int (*) (int, struct statfs64*);
using libc_unlink_t = int (*) (const char*);
using libc_unlinkat_t = int (*) (int, const char*, int);
using libc_rename_t = int (*) (const char*, const char*);
using libc_renameat_t = int (*) (int, const char*, int, const char*);
using libc_fopen_t = FILE* (*)(const char*, const char*);
using libc_fopen64_t = FILE* (*)(const char*, const char*);
using libc_fclose_t = int (*) (FILE*);

/**
 * Data calls.
 */
using libc_read_t = ssize_t (*) (int, void*, size_t);
using libc_write_t = ssize_t (*) (int, const void*, size_t);
using libc_pread_t = ssize_t (*) (int, void*, size_t, off_t);
using libc_pwrite_t = ssize_t (*) (int, const void*, size_t, off_t);
#if defined(__USE_LARGEFILE64)
using libc_pread64_t = ssize_t (*) (int, void*, size_t, off64_t);
using libc_pwrite64_t = ssize_t (*) (int, const void*, size_t, off64_t);
#endif
using libc_mmap_t = void* (*)(void*, size_t, int, int, int, off_t);
using libc_munmap_t = int (*) (void*, size_t);

/**
 * Directory calls.
 */
using libc_mkdir_t = int (*) (const char*, mode_t);
using libc_mkdirat_t = int (*) (int, const char*, mode_t);
using libc_rmdir_t = int (*) (const char*);
using libc_mknod_t = int (*) (const char*, mode_t, dev_t);
using libc_mknodat_t = int (*) (int, const char*, mode_t, dev_t);

/**
 * Extended attributes calls.
 */
using libc_getxattr_t = ssize_t (*) (const char*, const char*, void*, size_t);
using libc_lgetxattr_t = ssize_t (*) (const char*, const char*, void*, size_t);
using libc_fgetxattr_t = ssize_t (*) (int, const char*, void*, size_t);
using libc_setxattr_t = int (*) (const char*, const char*, const void*, size_t, int);
using libc_lsetxattr_t = int (*) (const char*, const char*, const void*, size_t, int);
using libc_fsetxattr_t = int (*) (int, const char*, const void*, size_t, int);
using libc_listxattr_t = ssize_t (*) (const char*, char*, size_t);
using libc_llistxattr_t = ssize_t (*) (const char*, char*, size_t);
using libc_flistxattr_t = ssize_t (*) (int, char*, size_t);

/**
 * Special POSIX calls supported by PADLL for well functioning.
 */
using libc_socket_t = int (*) (int, int, int);
using libc_fcntl_t = int (*) (int, int, void*);







class PosixPassthrough {

public:


    static void logger(std::string str, std::string type);


    /**
     * passthrough_posix_read:
     *  https://linux.die.net/man/2/read
     * @param fd
     * @param buf
     * @param counter
     * @return
     */
    static  ssize_t passthrough_posix_read (int fd, void* buf, size_t counter);

    /**
     * passthrough_posix_write:
     *  https://linux.die.net/man/2/write
     * @param fd
     * @param buf
     * @param counter
     * @return
     */
    static ssize_t passthrough_posix_write (int fd, const void* buf, size_t counter);

    /**
     * passthrough_posix_pread:
     *  https://linux.die.net/man/2/pread
     * @param fd
     * @param buf
     * @param counter
     * @param offset
     * @return
     */
    static  ssize_t passthrough_posix_pread (int fd, void* buf, size_t counter, off_t offset);

    /**
     * passthrough_posix_pwrite:
     *  https://linux.die.net/man/2/pwrite
     * @param fd
     * @param buf
     * @param counter
     * @param offset
     * @return
     */
    static ssize_t passthrough_posix_pwrite (int fd, const void* buf, size_t counter, off_t offset);

    /**
     * passthrough_posix_pread64:
     *  https://linux.die.net/man/2/pread64
     *  https://www.mkssoftware.com/docs/man3/read.3.asp
     * @param fd
     * @param buf
     * @param counter
     * @param offset
     * @return
     */
#if defined(__USE_LARGEFILE64)
    static ssize_t passthrough_posix_pread64 (int fd, void* buf, size_t counter, off64_t offset);
#endif

    /**
     * passthrough_posix_pwrite64:
     *  https://linux.die.net/man/2/pwrite64
     *  https://www.mkssoftware.com/docs/man3/write.3.asp
     * @param fd
     * @param buf
     * @param counter
     * @param offset
     * @return
     */
#if defined(__USE_LARGEFILE64)
    static ssize_t passthrough_posix_pwrite64 (int fd, const void* buf, size_t counter, off64_t offset);
#endif

    /**
     * passthrough_posix_mmap:
     * @param addr
     * @param length
     * @param prot
     * @param flags
     * @param fd
     * @param offset
     * @return
     */
    static void* passthrough_posix_mmap (void* addr, size_t length, int prot, int flags, int fd, off_t offset);

    /**
     * passthrough_posix_munmap:
     * @param addr
     * @param length
     * @return
     */
    static int passthrough_posix_munmap (void* addr, size_t length);

    /**
     * passthrough_posix_open:
     *  https://linux.die.net/man/2/open
     * Notes:
     *  https://github.com/fritzw/ld-preload-open/blob/master/path-mapping.c
     *  https://github.com/poliva/ldpreloadhook/blob/master/hook.c
     * @param path
     * @param flags
     * @param mode
     * @return
     */
    static int passthrough_posix_open (const char* path, int flags, mode_t mode);

    /**
     * passthrough_posix_open:
     *  https://linux.die.net/man/2/open
     * @param path
     * @param flags
     * @return
     */
    static int passthrough_posix_open (const char* path, int flags);

    /**
     * passthrough_posix_creat:
     *  https://linux.die.net/man/2/creat
     * @param path
     * @param mode
     * @return
     */
    static int passthrough_posix_creat (const char* path, mode_t mode);

    /**
     * passthrough_posix_creat64:
     *  https://www.unix.com/man-page/hpux/2/creat64/
     * @param path
     * @param mode
     * @return
     */
    static int passthrough_posix_creat64 (const char* path, mode_t mode);

    /**
     * passthrough_posix_openat:
     *  https://linux.die.net/man/2/openat
     * @param dirfd
     * @param path
     * @param flags
     * @param mode
     * @return
     */
    static int passthrough_posix_openat (int dirfd, const char* path, int flags, mode_t mode);

    /**
     * passthrough_posix_openat:
     *  https://linux.die.net/man/2/openat
     * @param dirfd
     * @param path
     * @param flags
     * @return
     */
    static int passthrough_posix_openat (int dirfd, const char* path, int flags);

    /**
     * passthrough_posix_open64:
     *  https://code.woboq.org/userspace/glibc/sysdeps/unix/sysv/linux/open64.c.html
     * @param path
     * @param flags
     * @param mode
     * @return
     */
    static int passthrough_posix_open64 (const char* path, int flags, mode_t mode);

    /**
     * passthrough_posix_open64:
     *  https://code.woboq.org/userspace/glibc/sysdeps/unix/sysv/linux/open64.c.html
     * @param path
     * @param flags
     * @return
     */
    static int passthrough_posix_open64 (const char* path, int flags);

    /**
     * passthrough_posix_close:
     *  https://linux.die.net/man/2/close
     * @param fd
     * @return
     */
    static int passthrough_posix_close (int fd);

    /**
     * passthrough_posix_sync:
     *  https://linux.die.net/man/2/sync
     */
    static void passthrough_posix_sync ();

    /**
     * passthrough_posix_statfs:
     *  https://linux.die.net/man/2/statfs
     * @param path
     * @param buf
     * @return
     */
    static int passthrough_posix_statfs (const char* path, struct statfs* buf);

    /**
     * passthrough_posix_fstatfs
     *  https://linux.die.net/man/2/fstatfs
     * @param fd
     * @param buf
     * @return
     */
    static int passthrough_posix_fstatfs (int fd, struct statfs* buf);

    /**
     * passthrough_posix_statfs64:
     *  https://linux.die.net/man/2/statfs64
     *  https://refspecs.linuxbase.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/baselib-statfs64.html
     * @param path
     * @param buf
     * @return
     */
    static int passthrough_posix_statfs64 (const char* path, struct statfs64* buf);

    /**
     * passthrough_posix_fstatfs64
     *  https://linux.die.net/man/2/fstatfs64
     *  https://refspecs.linuxbase.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/baselib-fstatfs64.html
     * @param fd
     * @param buf
     * @return
     */
    static int passthrough_posix_fstatfs64 (int fd, struct statfs64* buf);

    /**
     * passthrough_posix_link:
     *  https://linux.die.net/man/2/link
     * @param old_path
     * @param new_path
     * @return
     */
    static int passthrough_posix_link (const char* old_path, const char* new_path);

    /**
     * passthrough_posix_unlink:
     *  https://linux.die.net/man/2/unlink
     * @param old_path
     * @return
     */
    static int passthrough_posix_unlink (const char* old_path);

    /**
     * passthrough_posix_unlinkat:
     *  https://linux.die.net/man/2/unlinkat
     * @param dirfd
     * @param pathname
     * @param flags
     * @return
     */
    static int passthrough_posix_unlinkat (int dirfd, const char* pathname, int flags);

    /**
     * passthrough_posix_rename:
     *  https://linux.die.net/man/2/rename
     * @param old_path
     * @param new_path
     * @return
     */
    static int passthrough_posix_rename (const char* old_path, const char* new_path);

    /**
     * passthrough_posix_renameat:
     *  https://linux.die.net/man/2/renameat
     * @param olddirfd
     * @param old_path
     * @param newdirfd
     * @param new_path
     * @return
     */
    static int passthrough_posix_renameat (int olddirfd,
        const char* old_path,
        int newdirfd,
        const char* new_path);

    /**
     * passthrough_posix_fopen:
     *  https://linux.die.net/man/3/fopen
     * @param pathname
     * @param mode
     * @return
     */
    static FILE* passthrough_posix_fopen (const char* pathname, const char* mode);

    /**
     * passthrough_posix_fopen64:
     *  https://sites.ualberta.ca/dept/chemeng/AIX-43/share/man/info/C/a_doc_lib/libs/basetrf1/fopen.htm
     * @param pathname
     * @param mode
     * @return
     */
    static FILE* passthrough_posix_fopen64 (const char* pathname, const char* mode);

    /**
     * passthrough_posix_fclose:
     *  https://linux.die.net/man/3/fclose
     * @param stream
     * @return
     */
    static int passthrough_posix_fclose (FILE* stream);

    /**
     * passthrough_posix_mkdir:
     *  https://linux.die.net/man/2/mkdir
     * @param path
     * @param mode
     * @return
     */
    static int passthrough_posix_mkdir (const char* path, mode_t mode);

    /**
     * passthrough_posix_mkdirat:
     *  https://linux.die.net/man/2/mkdirat
     * @param dirfd
     * @param path
     * @param mode
     * @return
     */
    static int passthrough_posix_mkdirat (int dirfd, const char* path, mode_t mode);

    /**
     * passthrough_posix_rmdir:
     *  https://linux.die.net/man/3/rmdir
     * @param path
     * @return
     */
    static int passthrough_posix_rmdir (const char* path);

    /**
     * passthrough_posix_mknod:
     *  https://linux.die.net/man/2/mknod
     * @param path
     * @param mode
     * @param dev
     * @return
     */
    static int passthrough_posix_mknod (const char* path, mode_t mode, dev_t dev);

    /**
     * passthrough_posix_mknodat:
     *  https://linux.die.net/man/2/mknodat
     * @param dirfd
     * @param path
     * @param mode
     * @param dev
     * @return
     */
    static int passthrough_posix_mknodat (int dirfd, const char* path, mode_t mode, dev_t dev);

    /**
     * passthrough_posix_getxattr:
     *  https://linux.die.net/man/2/getxattr
     * @param path
     * @param name
     * @param value
     * @param size
     * @return
     */
    static ssize_t passthrough_posix_getxattr (const char* path, const char* name, void* value, size_t size);

    /**
     * passthrough_posix_lgetxattr:
     *  https://linux.die.net/man/2/lgetxattr
     * @param path
     * @param name
     * @param value
     * @param size
     * @return
     */
    static ssize_t passthrough_posix_lgetxattr (const char* path, const char* name, void* value, size_t size);

    /**
     * passthrough_posix_fgetxattr:
     *  https://linux.die.net/man/2/fgetxattr
     * @param fd
     * @param name
     * @param value
     * @param size
     * @return
     */
    static ssize_t passthrough_posix_fgetxattr (int fd, const char* name, void* value, size_t size);

    /**
     * passthrough_posix_setxattr:
     *  https://linux.die.net/man/2/setxattr
     * @param path
     * @param name
     * @param value
     * @param size
     * @param flags
     * @return
     */
    static int passthrough_posix_setxattr (const char* path,
        const char* name,
        const void* value,
        size_t size,
        int flags);

    /**
     * passthrough_posix_lsetxattr:
     *  https://linux.die.net/man/2/lsetxattr
     * @param path
     * @param name
     * @param value
     * @param size
     * @param flags
     * @return
     */
    static int passthrough_posix_lsetxattr (const char* path,
        const char* name,
        const void* value,
        size_t size,
        int flags);

    /**
     * passthrough_posix_fsetxattr:
     *  https://linux.die.net/man/2/fsetxattr
     * @param fd
     * @param name
     * @param value
     * @param size
     * @param flags
     * @return
     */
    static int passthrough_posix_fsetxattr (int fd,
        const char* name,
        const void* value,
        size_t size,
        int flags);

    /**
     * passthrough_posix_listxattr:
     *  https://linux.die.net/man/2/listxattr
     * @param path
     * @param list
     * @param size
     * @return
     */
    static ssize_t passthrough_posix_listxattr (const char* path, char* list, size_t size);

    /**
     * passthrough_posix_llistxattr:
     *  https://linux.die.net/man/2/llistxattr
     * @param path
     * @param list
     * @param size
     * @return
     */
    static ssize_t passthrough_posix_llistxattr (const char* path, char* list, size_t size);

    /**
     * passthrough_posix_flistxattr:
     *  https://linux.die.net/man/2/flistxattr
     * @param fd
     * @param list
     * @param size
     * @return
     */
    static ssize_t passthrough_posix_flistxattr (int fd, char* list, size_t size);

    /**
     * passthrough_posix_socket:
     * @param domain
     * @param type
     * @param protocol
     */
    static int passthrough_posix_socket (int domain, int type, int protocol);

};
} // namespace profiler

#endif // PROFILER_POSIX_PASSTHROUGH_HPP
