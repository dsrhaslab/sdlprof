
#include <posix_passthrough.hpp>

namespace profiler {

std::string log_name = "";

void PosixPassthrough::logger(std::string str, std::string type){
    //printf("%s\n",type.c_str());
    if(profiler::log_name.empty()){
        auto time = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(time);
        log_name = "/home/gsd/logs/log_" + std::string(std::ctime(&end_time)) + ".txt";
        std::replace( log_name.begin(), log_name.end(), ' ', '_');
        log_name.erase(std::remove(log_name.begin(), log_name.end(), '\n'), log_name.cend());
        //printf("-------------------%s\n", log_name.c_str());
        
    }
    int fd_for_write = ((libc_open_variadic_t)dlsym (RTLD_NEXT, "open")) (log_name.c_str(), O_CREAT | O_RDWR | O_APPEND, S_IRWXU);

    if(fd_for_write > 0){
        int written = ((libc_write_t)dlsym(RTLD_NEXT, "write"))(fd_for_write, str.c_str (), str.size ());
        int close_fd = ((libc_close_t)dlsym(RTLD_NEXT, "close"))(fd_for_write);
        //printf("%d_%d_%d\n",fd_for_write,written,close_fd);
    } 
    else printf("Problem openning log file.\n");

}

// passthrough_posix_read call. (...)
ssize_t PosixPassthrough::passthrough_posix_read (int fd, void* buf, size_t counter)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_read_t)dlsym (RTLD_NEXT, "read")) (fd, buf, counter);

    std::string str = "[" + timestamp + "] read(" + std::to_string(fd) + ", " + std::to_string(counter)
    + ", ..., " + std::to_string(result) + ")" + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "read");

    return result;
}

// passthrough_posix_write call. (...)
ssize_t PosixPassthrough::passthrough_posix_write (int fd, const void* buf, size_t counter)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_write_t)dlsym (RTLD_NEXT, "write")) (fd, buf, counter);

    std::string str = "[" + timestamp + "] write(" + std::to_string(fd) + ", "  + std::to_string(counter) +
    ", ...," + std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "write");

    return result;
}

// passthrough_posix_pread call. (...)
ssize_t PosixPassthrough::passthrough_posix_pread (int fd, void* buf, size_t counter, off_t offset)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pread_t)dlsym (RTLD_NEXT, "pread")) (fd, buf, counter, offset);

    std::string str = "[" + timestamp + "] pread(" + std::to_string(fd) + ", " + 
    std::to_string(counter) + ", " + std::to_string(offset) + ", ..., " + std::to_string(result) + 
    ")" + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "pread");
    return result;
}

// passthrough_posix_pwrite call. (...)
ssize_t PosixPassthrough::passthrough_posix_pwrite (int fd, const void* buf, size_t counter, off_t offset)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pwrite_t)dlsym (RTLD_NEXT, "pwrite")) (fd, buf, counter, offset);

    std::string str = "[" + timestamp + "] pwrite(" + std::to_string(fd) + ", "  + std::to_string(counter) + ", " + 
    std::to_string(offset) + ", ...," + std::to_string(result) +  "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "pwrite");

    return result;
}

// passthrough_posix_pread64 call. (...)
#if defined(__USE_LARGEFILE64)
ssize_t PosixPassthrough::passthrough_posix_pread64 (int fd, void* buf, size_t counter, off64_t offset)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pread64_t)dlsym (RTLD_NEXT, "pread64")) (fd, buf, counter, offset);

    std::string str = "[" + timestamp + "] pread64(" + std::to_string(fd) + ", " + 
    std::to_string(counter) + ", " + std::to_string(offset) + ", ..., " + std::to_string(result) + 
    ")" + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "pread64");

    return result;
}
#endif

// passthrough_posix_pwrite64 call. (...)
#if defined(__USE_LARGEFILE64)
ssize_t PosixPassthrough::passthrough_posix_pwrite64 (int fd, const void* buf, size_t counter, off64_t offset)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pwrite64_t)dlsym (RTLD_NEXT, "pwrite64")) (fd, buf, counter, offset);

    std::string str = "[" + timestamp + "] pwrite64(" + std::to_string(fd) + ", "  + std::to_string(counter) + ", "  + 
    std::to_string(offset) + ", ...," + std::to_string(result) +  "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "pwrite64");

    return result;
}
#endif

// pass_through_posix_mmap call. (...)
void* PosixPassthrough::passthrough_posix_mmap (void* addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    void* result = ((libc_mmap_t)dlsym (RTLD_NEXT, "mmap")) (addr, length, prot, flags, fd, offset);

    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str = "[" + timestamp + "] mmap(" + addr_name + ", "  + std::to_string(length) + 
    ", " + std::to_string(prot) + ", " + std::to_string(flags) + ", " + std::to_string(fd) + 
    ", " + std::to_string(offset) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "mmap");

    return result;
}

// pass_through_posix_munmap call. (...)
int PosixPassthrough::passthrough_posix_munmap (void* addr, size_t length)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_munmap_t)dlsym (RTLD_NEXT, "munmap")) (addr, length);

    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str = "[" + timestamp + "] munmap(" + addr_name + ", "  + std::to_string(length) +
    ", ...," + std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "munmap");

    return result;
}

// passthrough_posix_open call. (...)
int PosixPassthrough::passthrough_posix_open (const char* path, int flags, mode_t mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open_variadic_t)dlsym (RTLD_NEXT, "open")) (path, flags, mode);

    std::string str = "[" + timestamp + "] open(" + std::string(path) + ") = " + 
    std::to_string(result) + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "open");

    return result;
}

// passthrough_posix_open call. (...)
int PosixPassthrough::passthrough_posix_open (const char* path, int flags)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open_t)dlsym (RTLD_NEXT, "open")) (path, flags);

    std::string str = "[" + timestamp + "] open(" + std::string(path) + ") = " + 
    std::to_string(result) + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "open");

    return result;
}

// passthrough_posix_creat call. (...)
int PosixPassthrough::passthrough_posix_creat (const char* path, mode_t mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    PosixPassthrough::logger("PosixPassthrough::passthrough_posix_creat\n", "creat");
    int result = ((libc_creat_t)dlsym (RTLD_NEXT, "creat")) (path, mode);

    std::string str = "[" + timestamp + "] creat(" + std::string(path) + ", ..., " + 
    std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "creat");

    return result;
}

// passthrough_posix_creat64 call. (...)
int PosixPassthrough::passthrough_posix_creat64 (const char* path, mode_t mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_creat64_t)dlsym (RTLD_NEXT, "creat64")) (path, mode);

    std::string str = "[" + timestamp + "] creat64(" + std::string(path) + ", ...,  " + 
    std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "creat64");

    return result;
}

// passthrough_posix_openat call. (...)
int PosixPassthrough::passthrough_posix_openat (int dirfd, const char* path, int flags, mode_t mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_openat_variadic_t)dlsym (RTLD_NEXT, "openat")) (dirfd, path, flags, mode);

    std::string str = "[" + timestamp + "] openat(" + std::string(path) + ") = " + 
    std::to_string(result) + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "openat");

    return result;
}

// passthrough_posix_openat call. (...)
int PosixPassthrough::passthrough_posix_openat (int dirfd, const char* path, int flags)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_openat_t)dlsym (RTLD_NEXT, "openat")) (dirfd, path, flags);

    std::string str = "[" + timestamp + "] openat(" + std::string(path) + ") = " + 
    std::to_string(result) + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "openat");

    return result;
}

// passthrough_posix_open64 call. (...)
int PosixPassthrough::passthrough_posix_open64 (const char* path, int flags, mode_t mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open64_variadic_t)dlsym (RTLD_NEXT, "open64")) (path, flags, mode);

    std::string str = "[" + timestamp + "] open64(" + std::string(path) + ") = " + 
    std::to_string(result) + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "open64");

    return result;
}

// passthrough_posix_open64 call. (...)
int PosixPassthrough::passthrough_posix_open64 (const char* path, int flags)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open64_t)dlsym (RTLD_NEXT, "open64")) (path, flags);
    
    std::string str = "[" + timestamp + "] open64(" + std::string(path) + ") = " + 
    std::to_string(result) + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "open64");

    return result;
}

// passthrough_posix_close call. (...)
int PosixPassthrough::passthrough_posix_close (int fd)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_close_t)dlsym (RTLD_NEXT, "close")) (fd);

    std::string str = "[" + timestamp + "] close(" + std::to_string(fd) + ") = " + std::to_string(result)
    + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "close");

    return result;
}

// passthrough_posix_sync call. (...)
void PosixPassthrough::passthrough_posix_sync ()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    std::string str = "[" + timestamp + "] sync(). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "sync");
    return ((libc_sync_t)dlsym (RTLD_NEXT, "sync")) ();
}

// passthrough_posix_statfs call. (...)
int PosixPassthrough::passthrough_posix_statfs (const char* path, struct statfs* buf)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_statfs_t)dlsym (RTLD_NEXT, "statfs")) (path, buf);

    std::string str = "[" + timestamp + "] statfs(" + std::to_string(result) +
    "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "statfs");

    return result;
}

// passthrough_posix_fstatfs call. (...)
int PosixPassthrough::passthrough_posix_fstatfs (int fd, struct statfs* buf)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_fstatfs_t)dlsym (RTLD_NEXT, "fstatfs")) (fd, buf);

    std::string str = "[" + timestamp + "] fstatfs(" + std::to_string(result) +
    "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "fstatfs");

    return result;
}

// passthrough_posix_statfs64 call. (...)
int PosixPassthrough::passthrough_posix_statfs64 (const char* path, struct statfs64* buf)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_statfs64_t)dlsym (RTLD_NEXT, "statfs64")) (path, buf);

    std::string str = "[" + timestamp + "] statfs64(" + std::to_string(result) + 
    "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "statfs64");

    return result;
}

// passthrough_posix_fstatfs64 call. (...)
int PosixPassthrough::passthrough_posix_fstatfs64 (int fd, struct statfs64* buf)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_fstatfs64_t)dlsym (RTLD_NEXT, "fstatfs64")) (fd, buf);

    std::string str = "[" + timestamp + "] fstatfs64(" + std::to_string(result) + 
    "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "fstatfs64");

    return result;
}

// passthrough_posix_unlink call. (...)
int PosixPassthrough::passthrough_posix_unlink (const char* old_path)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_unlink_t)dlsym (RTLD_NEXT, "unlink")) (old_path);

    std::string str = "[" + timestamp + "] unlink(" + std::string(old_path) + 
    ", ..., " + std::to_string(result)  + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "unlink");

    return result;
}

// passthrough_posix_unlinkat call. (...)
int PosixPassthrough::passthrough_posix_unlinkat (int dirfd, const char* pathname, int flags)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_unlinkat_t)dlsym (RTLD_NEXT, "unlinkat")) (dirfd, pathname, flags);

    std::string str = "[" + timestamp + "] unlinkat(" + std::string(pathname) + ", ..., " + 
    std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "unlinkat");

    return result;
}

// passthrough_posix_rename call. (...)
int PosixPassthrough::passthrough_posix_rename (const char* old_path, const char* new_path)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_rename_t)dlsym (RTLD_NEXT, "rename")) (old_path, new_path);

    std::string str = "[" + timestamp + "] rename(" + std::string(old_path) + ", " + 
    std::string(new_path) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "rename");

    return result;
}

// passthrough_posix_renameat call. (...)
int PosixPassthrough::passthrough_posix_renameat (int olddirfd, const char* old_path, int newdirfd, const char* new_path)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_renameat_t)dlsym (RTLD_NEXT, "renameat")) (olddirfd, old_path, newdirfd, new_path);

    std::string str = "[" + timestamp + "] renameat(" + std::string(old_path) + ", " +
    std::string(new_path) + ", ..., " + std::to_string(result)+ "). PID= " + 
    std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "renameat");

    return result;
}

// passthrough_posix_fopen call. (...)
FILE* PosixPassthrough::passthrough_posix_fopen (const char* pathname, const char* mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    FILE* result = ((libc_fopen_t)dlsym (RTLD_NEXT, "fopen")) (pathname, mode);

    std::string str = "[" + timestamp + "] fopen(" + std::string(pathname) + 
    + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "fopen");

    return result;
}

// passthrough_posix_fopen64 call. (...)
FILE* PosixPassthrough::passthrough_posix_fopen64 (const char* pathname, const char* mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    FILE* result = ((libc_fopen64_t)dlsym (RTLD_NEXT, "fopen64")) (pathname, mode);

    std::string str = "[" + timestamp + "] fopen64(" + std::string(pathname) + 
    + ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "fopen64");

    return result;
}

// passthrough_posix_fclose call. (...)
int PosixPassthrough::passthrough_posix_fclose (FILE* stream)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_fclose_t)dlsym (RTLD_NEXT, "fclose")) (stream);

    std::string str = "[" + timestamp + "] fclose() = " + std::to_string(result) + 
    ". PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "fclose");

    return result;
}

// passthrough_posix_mkdir call. (...)
int PosixPassthrough::passthrough_posix_mkdir (const char* path, mode_t mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_mkdir_t)dlsym (RTLD_NEXT, "mkdir")) (path, mode);

    std::string str = "[" + timestamp + "] mkdir(" + std::string(path) + ", ..., " + 
    std::to_string(result)+ "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "mkdir");

    return result;
}

// passthrough_posix_mkdirat call. (...)
int PosixPassthrough::passthrough_posix_mkdirat (int dirfd, const char* path, mode_t mode)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_mkdirat_t)dlsym (RTLD_NEXT, "mkdirat")) (dirfd, path, mode);

    std::string str = "[" + timestamp + "] mkdirat(" + std::string(path) + ", ..., " + 
    std::to_string(result)+ "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "mkdirat");

    return result;
}

// passthrough_posix_rmdir call. (...)
int PosixPassthrough::passthrough_posix_rmdir (const char* path)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_rmdir_t)dlsym (RTLD_NEXT, "rmdir")) (path);

    std::string str = "[" + timestamp + "] rmdir(" + std::string(path) + ", ..., " + 
    std::to_string(result)+ "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "rmdir");

    return result;
}

// passthrough_posix_mknod call. (...)
int PosixPassthrough::passthrough_posix_mknod (const char* path, mode_t mode, dev_t dev)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_mknod_t)dlsym (RTLD_NEXT, "mknod")) (path, mode, dev);

    std::string str = "[" + timestamp + "] mknod(" + std::string(path) + ", ..., " + 
    std::to_string(result)+ "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "mknod");

    return result;
}

// passthrough_posix_mknodat call. (...)
int PosixPassthrough::passthrough_posix_mknodat (int dirfd, const char* path, mode_t mode, dev_t dev)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    PosixPassthrough::logger("PosixPassthrough::passthrough_posix_mknodat\n", "mknodat");
    int result = ((libc_mknodat_t)dlsym (RTLD_NEXT, "mknodat")) (dirfd, path, mode, dev);

    std::string str = "[" + timestamp + "] mknodat(" + std::string(path) + ", ..., " + 
    std::to_string(result)+ "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "mknodat");

    return result;
}

// passthrough_posix_getxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_getxattr (const char* path, const char* name, void* value, size_t size)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_getxattr_t)dlsym (RTLD_NEXT, "getxattr")) (path, name, value, size);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str = "[" + timestamp + "] getxattr(" + std::string(path) + ", " + std::string(name) + 
    "," + valor + ", " + std::to_string(size) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "getxattr");

    return result;
}

// passthrough_posix_lgetxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_lgetxattr (const char* path, const char* name, void* value, size_t size)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_lgetxattr_t)dlsym (RTLD_NEXT, "lgetxattr")) (path, name, value, size);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str = "[" + timestamp + "] lgetxattr(" + std::string(path) + ", "  + 
    std::string(name) + "," + valor + ", " + std::to_string(size) + ", ...," + 
    std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "lgetxattr");

    return result;
}

// passthrough_posix_fgetxattr call. (...)
ssize_t
PosixPassthrough::passthrough_posix_fgetxattr (int fd, const char* name, void* value, size_t size)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_fgetxattr_t)dlsym (RTLD_NEXT, "fgetxattr")) (fd, name, value, size);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str = "[" + timestamp + "] fgetxattr(" +  std::to_string(fd) + ", "  + 
    std::string(name) + "," + valor + ", " + std::to_string(size) + ", ..., " + 
    std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n";

    PosixPassthrough::logger(str, "fgetxattr");

    return result;
}

// passthrough_posix_setxattr call. (...)
int PosixPassthrough::passthrough_posix_setxattr (const char* path, const char* name, const void* value, size_t size, int flags)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_setxattr_t)dlsym (RTLD_NEXT, "setxattr")) (path, name, value, size, flags);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str = "[" + timestamp + "] setxattr(" + std::string(path) + ", " + std::string(name) + 
    "," + valor + ", " + std::to_string(size) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n";    

    PosixPassthrough::logger(str, "setxattr");

    return result;
}

// passthrough_posix_lsetxattr call. (...)
int PosixPassthrough::passthrough_posix_lsetxattr (const char* path, const char* name, const void* value, size_t size, int flags)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_lsetxattr_t)dlsym (RTLD_NEXT, "lsetxattr")) (path, name, value, size, flags);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str = "[" + timestamp + "] lsetxattr(" + std::string(path) + ", " + std::string(name) + 
    "," + valor + ", " + std::to_string(size) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n"; 

    PosixPassthrough::logger(str, "lsetxattr");

    return result;
}

// passthrough_posix_fsetxattr call. (...)
int PosixPassthrough::passthrough_posix_fsetxattr (int fd, const char* name, const void* value, size_t size, int flags)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    PosixPassthrough::logger("PosixPassthrough::passthrough_posix_fsetxattr\n", "fsetxattr");
    int result = ((libc_fsetxattr_t)dlsym (RTLD_NEXT, "fsetxattr")) (fd, name, value, size, flags);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str = "[" + timestamp + "] fsetxattr(" + std::to_string(fd) + ", " + std::string(name) + 
    "," + valor + ", " + std::to_string(size) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n"; 

    PosixPassthrough::logger(str, "fsetxattr");

    return result;
}

// passthrough_posix_listxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_listxattr (const char* path, char* list, size_t size)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_listxattr_t)dlsym (RTLD_NEXT, "listxattr")) (path, list, size);

    std::string str = "[" + timestamp + "] listxattr(" + std::string(path) + ", " + 
    std::to_string(size) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n"; 

    PosixPassthrough::logger(str, "listxattr");

    return result;
}

// passthrough_posix_llistxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_llistxattr (const char* path, char* list, size_t size)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_llistxattr_t)dlsym (RTLD_NEXT, "llistxattr")) (path, list, size);

    std::string str = "[" + timestamp + "] llistxattr(" + std::string(path) + ", " + 
    std::to_string(size) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n"; 

    PosixPassthrough::logger(str, "llistxattr");

    return result;
}

// passthrough_posix_flistxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_flistxattr (int fd, char* list, size_t size)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_flistxattr_t)dlsym (RTLD_NEXT, "flistxattr")) (fd, list, size);

    std::string str = "[" + timestamp + "] flistxattr(" + std::to_string(fd) + ", " + 
    std::to_string(size) + ", ..., " + std::to_string(result) + "). PID= " + 
    std::to_string(getpid()) + "\n"; 

    PosixPassthrough::logger(str, "flistxattr");

    return result;
}

// passthrough_posix_socket call. (...)
int PosixPassthrough::passthrough_posix_socket (int domain, int type, int protocol)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_socket_t)dlsym (RTLD_NEXT, "socket")) (domain, type, protocol);

    std::string str = "[" + timestamp + "] socket(" + std::to_string(domain) + ", " + 
    std::to_string(type) + ", " + std::to_string(protocol) + ", ..., " + 
    std::to_string(result) + "). PID= " + std::to_string(getpid()) + "\n"; 

    PosixPassthrough::logger(str, "socket");

    return result;
}

} // namespace profiler