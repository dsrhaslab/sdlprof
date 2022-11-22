
#include <posix_passthrough.hpp>
#include "config.hpp"
#include "log_formats/pretty_print_log.hpp"
#include "log_formats/json_log.hpp"

namespace profiler {

void log_name_setter(){
    auto time = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(time);

    if(config::log_type == config::json){
        config::log_name = config::dir + "log_" + config::pid + "_" + std::string(std::ctime(&end_time)) + ".json" ;
    }
    else{
        config::log_name = config::dir + "log_" /*+ config::pid + "log_"*/ + std::string(std::ctime(&end_time)) + ".txt" ;
    }
    std::replace(config::log_name.begin(), config::log_name.end(), ' ', '_');
    config::log_name.erase(std::remove(config::log_name.begin(), config::log_name.end(), '\n'), config::log_name.cend());
    //printf("-------------------%s\n", log_name.c_str());
}

void PosixPassthrough::logger(std::string str, std::string type){
    //printf("%s\n",type.c_str());
    if(config::log_name.empty()){
        profiler::log_name_setter();
    }
    
    int fd_for_write = ((libc_open_variadic_t)dlsym (RTLD_NEXT, "open")) (config::log_name.c_str(), O_CREAT | O_RDWR | O_APPEND, S_IRWXU);

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
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_read_t)dlsym (RTLD_NEXT, "read")) (fd, buf, counter);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_read(timestamp, fd, counter, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_read(timestamp, fd, counter, result, config::pid);
    }

    PosixPassthrough::logger(str, "read");

    return result;
}

// passthrough_posix_write call. (...)
ssize_t PosixPassthrough::passthrough_posix_write (int fd, const void* buf, size_t counter)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_write_t)dlsym (RTLD_NEXT, "write")) (fd, buf, counter);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_write(timestamp, fd, counter, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_write(timestamp, fd, counter, result, config::pid);
    }
    PosixPassthrough::logger(str, "write");

    return result;
}

// passthrough_posix_pread call. (...)
ssize_t PosixPassthrough::passthrough_posix_pread (int fd, void* buf, size_t counter, off_t offset)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pread_t)dlsym (RTLD_NEXT, "pread")) (fd, buf, counter, offset);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_pread(timestamp, fd, counter, result, offset, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_pread(timestamp, fd, counter, result, offset, config::pid);
    }
   
    PosixPassthrough::logger(str, "pread");
    return result;
}

// passthrough_posix_pwrite call. (...)
ssize_t PosixPassthrough::passthrough_posix_pwrite (int fd, const void* buf, size_t counter, off_t offset)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pwrite_t)dlsym (RTLD_NEXT, "pwrite")) (fd, buf, counter, offset);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_pwrite(timestamp, fd, counter, result, offset, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_pwrite(timestamp, fd, counter, result, offset, config::pid);
    }

    PosixPassthrough::logger(str, "pwrite");

    return result;
}

// passthrough_posix_pread64 call. (...)
#if defined(__USE_LARGEFILE64)
ssize_t PosixPassthrough::passthrough_posix_pread64 (int fd, void* buf, size_t counter, off64_t offset)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pread64_t)dlsym (RTLD_NEXT, "pread64")) (fd, buf, counter, offset);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_pread64(timestamp, fd, counter, result, offset, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_pread64(timestamp, fd, counter, result, offset, config::pid);
    }
    PosixPassthrough::logger(str, "pread64");

    return result;
}
#endif

// passthrough_posix_pwrite64 call. (...)
#if defined(__USE_LARGEFILE64)
ssize_t PosixPassthrough::passthrough_posix_pwrite64 (int fd, const void* buf, size_t counter, off64_t offset)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_pwrite64_t)dlsym (RTLD_NEXT, "pwrite64")) (fd, buf, counter, offset);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_pwrite64(timestamp, fd, counter, result, offset, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_pwrite64(timestamp, fd, counter, result, offset, config::pid);
    }

    PosixPassthrough::logger(str, "pwrite64");

    return result;
}
#endif

// pass_through_posix_mmap call. (...)
void* PosixPassthrough::passthrough_posix_mmap (void* addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    void* result = ((libc_mmap_t)dlsym (RTLD_NEXT, "mmap")) (addr, length, prot, flags, fd, offset);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_mmap(timestamp, addr, length, prot, flags, fd, offset, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_mmap(timestamp, addr, length, prot, flags, fd, offset, config::pid);
    }
    PosixPassthrough::logger(str, "mmap");

    return result;
}

// pass_through_posix_munmap call. (...)
int PosixPassthrough::passthrough_posix_munmap (void* addr, size_t length)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_munmap_t)dlsym (RTLD_NEXT, "munmap")) (addr, length);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_munmap(timestamp, addr, length, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_munmap(timestamp, addr, length, result, config::pid);
    }

    PosixPassthrough::logger(str, "munmap");

    return result;
}

// passthrough_posix_open call. (...)
int PosixPassthrough::passthrough_posix_open (const char* path, int flags, mode_t mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open_variadic_t)dlsym (RTLD_NEXT, "open")) (path, flags, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_open(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_open(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "open");

    return result;
}

// passthrough_posix_open call. (...)
int PosixPassthrough::passthrough_posix_open (const char* path, int flags)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open_t)dlsym (RTLD_NEXT, "open")) (path, flags);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_open(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_open(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "open");

    return result;
}

// passthrough_posix_creat call. (...)
int PosixPassthrough::passthrough_posix_creat (const char* path, mode_t mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    PosixPassthrough::logger("PosixPassthrough::passthrough_posix_creat\n", "creat");
    int result = ((libc_creat_t)dlsym (RTLD_NEXT, "creat")) (path, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_creat(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_creat(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "creat");

    return result;
}

// passthrough_posix_creat64 call. (...)
int PosixPassthrough::passthrough_posix_creat64 (const char* path, mode_t mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_creat64_t)dlsym (RTLD_NEXT, "creat64")) (path, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_creat64(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_creat64(timestamp, path, result, config::pid);
    }
    PosixPassthrough::logger(str, "creat64");

    return result;
}

// passthrough_posix_openat call. (...)
int PosixPassthrough::passthrough_posix_openat (int dirfd, const char* path, int flags, mode_t mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_openat_variadic_t)dlsym (RTLD_NEXT, "openat")) (dirfd, path, flags, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_openat(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_openat(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "openat");

    return result;
}

// passthrough_posix_openat call. (...)
int PosixPassthrough::passthrough_posix_openat (int dirfd, const char* path, int flags)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_openat_t)dlsym (RTLD_NEXT, "openat")) (dirfd, path, flags);
    
    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_openat(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_openat(timestamp, path, result, config::pid);
    }
    PosixPassthrough::logger(str, "openat");

    return result;
}

// passthrough_posix_open64 call. (...)
int PosixPassthrough::passthrough_posix_open64 (const char* path, int flags, mode_t mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open64_variadic_t)dlsym (RTLD_NEXT, "open64")) (path, flags, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_open64(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_open64(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "open64");

    return result;
}

// passthrough_posix_open64 call. (...)
int PosixPassthrough::passthrough_posix_open64 (const char* path, int flags)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_open64_t)dlsym (RTLD_NEXT, "open64")) (path, flags);
    
    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_open64(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_open64(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "open64");

    return result;
}

// passthrough_posix_close call. (...)
int PosixPassthrough::passthrough_posix_close (int fd)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_close_t)dlsym (RTLD_NEXT, "close")) (fd);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_close(timestamp, fd, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_close(timestamp, fd, result, config::pid);
    }

    PosixPassthrough::logger(str, "close");

    return result;
}

// passthrough_posix_sync call. (...)
void PosixPassthrough::passthrough_posix_sync ()
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_sync(timestamp, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_sync(timestamp, config::pid);
    }
    PosixPassthrough::logger(str, "sync");
    return ((libc_sync_t)dlsym (RTLD_NEXT, "sync")) ();
}

// passthrough_posix_statfs call. (...)
int PosixPassthrough::passthrough_posix_statfs (const char* path, struct statfs* buf)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_statfs_t)dlsym (RTLD_NEXT, "statfs")) (path, buf);
    
    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_statfs(timestamp, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_statfs(timestamp, result, config::pid);
    }

    PosixPassthrough::logger(str, "statfs");

    return result;
}

// passthrough_posix_fstatfs call. (...)
int PosixPassthrough::passthrough_posix_fstatfs (int fd, struct statfs* buf)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_fstatfs_t)dlsym (RTLD_NEXT, "fstatfs")) (fd, buf);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_fstatfs(timestamp, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_fstatfs(timestamp, result, config::pid);
    }

    PosixPassthrough::logger(str, "fstatfs");

    return result;
}

// passthrough_posix_statfs64 call. (...)
int PosixPassthrough::passthrough_posix_statfs64 (const char* path, struct statfs64* buf)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_statfs64_t)dlsym (RTLD_NEXT, "statfs64")) (path, buf);
    
    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_statfs64(timestamp, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_statfs64(timestamp, result, config::pid);
    }

    PosixPassthrough::logger(str, "statfs64");

    return result;
}

// passthrough_posix_fstatfs64 call. (...)
int PosixPassthrough::passthrough_posix_fstatfs64 (int fd, struct statfs64* buf)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_fstatfs64_t)dlsym (RTLD_NEXT, "fstatfs64")) (fd, buf);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_fstatfs64(timestamp, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_fstatfs64(timestamp, result, config::pid);
    }
    PosixPassthrough::logger(str, "fstatfs64");

    return result;
}

// passthrough_posix_unlink call. (...)
int PosixPassthrough::passthrough_posix_unlink (const char* old_path)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_unlink_t)dlsym (RTLD_NEXT, "unlink")) (old_path);
    
    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_unlink(timestamp, old_path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_unlink(timestamp, old_path, result, config::pid);
    }
    PosixPassthrough::logger(str, "unlink");

    return result;
}

// passthrough_posix_unlinkat call. (...)
int PosixPassthrough::passthrough_posix_unlinkat (int dirfd, const char* pathname, int flags)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_unlinkat_t)dlsym (RTLD_NEXT, "unlinkat")) (dirfd, pathname, flags);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_unlinkat(timestamp, pathname, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_unlinkat(timestamp, pathname, result, config::pid);
    }
    PosixPassthrough::logger(str, "unlinkat");

    return result;
}

// passthrough_posix_rename call. (...)
int PosixPassthrough::passthrough_posix_rename (const char* old_path, const char* new_path)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_rename_t)dlsym (RTLD_NEXT, "rename")) (old_path, new_path);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_rename(timestamp, old_path, new_path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_rename(timestamp, old_path, new_path, result, config::pid);
    }
    PosixPassthrough::logger(str, "rename");

    return result;
}

// passthrough_posix_renameat call. (...)
int PosixPassthrough::passthrough_posix_renameat (int olddirfd, const char* old_path, int newdirfd, const char* new_path)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_renameat_t)dlsym (RTLD_NEXT, "renameat")) (olddirfd, old_path, newdirfd, new_path);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_renameat(timestamp, old_path, new_path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_renameat(timestamp, old_path, new_path, result, config::pid);
    }

    PosixPassthrough::logger(str, "renameat");

    return result;
}

// passthrough_posix_fopen call. (...)
FILE* PosixPassthrough::passthrough_posix_fopen (const char* pathname, const char* mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    FILE* result = ((libc_fopen_t)dlsym (RTLD_NEXT, "fopen")) (pathname, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_fopen(timestamp, pathname, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_fopen(timestamp, pathname, config::pid);
    }

    PosixPassthrough::logger(str, "fopen");

    return result;
}

// passthrough_posix_fopen64 call. (...)
FILE* PosixPassthrough::passthrough_posix_fopen64 (const char* pathname, const char* mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    FILE* result = ((libc_fopen64_t)dlsym (RTLD_NEXT, "fopen64")) (pathname, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_fopen64(timestamp, pathname, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_fopen64(timestamp, pathname, config::pid);
    }

    PosixPassthrough::logger(str, "fopen64");

    return result;
}

// passthrough_posix_fclose call. (...)
int PosixPassthrough::passthrough_posix_fclose (FILE* stream)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_fclose_t)dlsym (RTLD_NEXT, "fclose")) (stream);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_fclose(timestamp, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_fclose(timestamp, config::pid);
    }

    PosixPassthrough::logger(str, "fclose");

    return result;
}

// passthrough_posix_mkdir call. (...)
int PosixPassthrough::passthrough_posix_mkdir (const char* path, mode_t mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_mkdir_t)dlsym (RTLD_NEXT, "mkdir")) (path, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_mkdir(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_mkdir(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "mkdir");

    return result;
}

// passthrough_posix_mkdirat call. (...)
int PosixPassthrough::passthrough_posix_mkdirat (int dirfd, const char* path, mode_t mode)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_mkdirat_t)dlsym (RTLD_NEXT, "mkdirat")) (dirfd, path, mode);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_mkdirat(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_mkdirat(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "mkdirat");

    return result;
}

// passthrough_posix_rmdir call. (...)
int PosixPassthrough::passthrough_posix_rmdir (const char* path)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_rmdir_t)dlsym (RTLD_NEXT, "rmdir")) (path);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_rmdir(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_rmdir(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "rmdir");

    return result;
}

// passthrough_posix_mknod call. (...)
int PosixPassthrough::passthrough_posix_mknod (const char* path, mode_t mode, dev_t dev)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_mknod_t)dlsym (RTLD_NEXT, "mknod")) (path, mode, dev);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_mknod(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_mknod(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "mknod");

    return result;
}

// passthrough_posix_mknodat call. (...)
int PosixPassthrough::passthrough_posix_mknodat (int dirfd, const char* path, mode_t mode, dev_t dev)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    PosixPassthrough::logger("PosixPassthrough::passthrough_posix_mknodat\n", "mknodat");
    int result = ((libc_mknodat_t)dlsym (RTLD_NEXT, "mknodat")) (dirfd, path, mode, dev);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_mknodat(timestamp, path, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_mknodat(timestamp, path, result, config::pid);
    }

    PosixPassthrough::logger(str, "mknodat");

    return result;
}

// passthrough_posix_getxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_getxattr (const char* path, const char* name, void* value, size_t size)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_getxattr_t)dlsym (RTLD_NEXT, "getxattr")) (path, name, value, size);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_getxattr(timestamp, path, name, value, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_getxattr(timestamp, path, name, value, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "getxattr");

    return result;
}

// passthrough_posix_lgetxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_lgetxattr (const char* path, const char* name, void* value, size_t size)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_lgetxattr_t)dlsym (RTLD_NEXT, "lgetxattr")) (path, name, value, size);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_lgetxattr(timestamp, path, name, value, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_lgetxattr(timestamp, path, name, value, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "lgetxattr");

    return result;
}

// passthrough_posix_fgetxattr call. (...)
ssize_t
PosixPassthrough::passthrough_posix_fgetxattr (int fd, const char* name, void* value, size_t size)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_fgetxattr_t)dlsym (RTLD_NEXT, "fgetxattr")) (fd, name, value, size);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_fgetxattr(timestamp, fd, name, value, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_fgetxattr(timestamp, fd, name, value, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "fgetxattr");

    return result;
}

// passthrough_posix_setxattr call. (...)
int PosixPassthrough::passthrough_posix_setxattr (const char* path, const char* name, const void* value, size_t size, int flags)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_setxattr_t)dlsym (RTLD_NEXT, "setxattr")) (path, name, value, size, flags);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_setxattr(timestamp, path, name, value, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_setxattr(timestamp, path, name, value, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "setxattr");

    return result;
}

// passthrough_posix_lsetxattr call. (...)
int PosixPassthrough::passthrough_posix_lsetxattr (const char* path, const char* name, const void* value, size_t size, int flags)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_lsetxattr_t)dlsym (RTLD_NEXT, "lsetxattr")) (path, name, value, size, flags);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_lsetxattr(timestamp, path, name, value, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_lsetxattr(timestamp, path, name, value, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "lsetxattr");

    return result;
}

// passthrough_posix_fsetxattr call. (...)
int PosixPassthrough::passthrough_posix_fsetxattr (int fd, const char* name, const void* value, size_t size, int flags)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    PosixPassthrough::logger("PosixPassthrough::passthrough_posix_fsetxattr\n", "fsetxattr");
    int result = ((libc_fsetxattr_t)dlsym (RTLD_NEXT, "fsetxattr")) (fd, name, value, size, flags);

    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_fsetxattr(timestamp, fd, name, value, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_fsetxattr(timestamp, fd, name, value, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "fsetxattr");

    return result;
}

// passthrough_posix_listxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_listxattr (const char* path, char* list, size_t size)
{   
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_listxattr_t)dlsym (RTLD_NEXT, "listxattr")) (path, list, size);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_listxattr(timestamp, path, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_listxattr(timestamp, path, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "listxattr");

    return result;
}

// passthrough_posix_llistxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_llistxattr (const char* path, char* list, size_t size)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_llistxattr_t)dlsym (RTLD_NEXT, "llistxattr")) (path, list, size);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_llistxattr(timestamp, path, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_llistxattr(timestamp, path, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "llistxattr");

    return result;
}

// passthrough_posix_flistxattr call. (...)
ssize_t PosixPassthrough::passthrough_posix_flistxattr (int fd, char* list, size_t size)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t result = ((libc_flistxattr_t)dlsym (RTLD_NEXT, "flistxattr")) (fd, list, size);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_flistxattr(timestamp, fd, size, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_flistxattr(timestamp, fd, size, result, config::pid);
    }

    PosixPassthrough::logger(str, "flistxattr");

    return result;
}

// passthrough_posix_socket call. (...)
int PosixPassthrough::passthrough_posix_socket (int domain, int type, int protocol)
{
    std::string str;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int result = ((libc_socket_t)dlsym (RTLD_NEXT, "socket")) (domain, type, protocol);

    if(config::pid.empty() or config::reset_pid_per_op) config::pid=std::to_string(getpid());
    if(config::log_type == config::json){
        str = json_format_log::json_log_socket(timestamp, domain, type, protocol, result, config::pid);
    }
    else{
        str = pretty_print_format_log::pretty_print_log_socket(timestamp, domain, type, protocol, result, config::pid);
    }

    PosixPassthrough::logger(str, "socket");

    return result;
}

} // namespace profiler