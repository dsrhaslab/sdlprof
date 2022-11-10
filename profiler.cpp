#include <mutex>
#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

typedef ssize_t (*libc_read_t) (int, void*, size_t);
typedef ssize_t (*libc_pread_t) (int, void*, size_t, off_t);
typedef ssize_t (*libc_pread64_t) (int, void*, size_t, off64_t);

typedef ssize_t (*libc_write_t)(int fd, const void *buf, size_t count);
typedef ssize_t (*libc_pwrite_t)(int fd, const void *buf, size_t count, off_t offset);
typedef ssize_t (*libc_pwrite64_t)(int fd, const void *buf, size_t count, off_t offset);

typedef void* (*libc_mmap_t) (void*, size_t, int, int, int, off_t);
typedef int (*libc_munmap_t) (void *addr, size_t length);
typedef int (*libc_mprotect_t) (void *addr, size_t len, int prot);

typedef ssize_t (*libc_getxattr_t)(const char *path, const char *name, void *value, size_t size);
typedef ssize_t (*libc_lgetxattr_t)(const char *path, const char *name, void *value, size_t size);
typedef ssize_t (*libc_fgetxattr_t)(int fd, const char *name, void *value, size_t size);

typedef int (*libc_close_t) (int);
typedef int (*libc_fclose_t) (FILE *);

typedef int (*libc_openat_variadic_t)(int fildes, const char *path, int oflag, ...);
typedef int (*libc_open_variadic_t) (const char*, int, ...);
typedef int (*libc_open64_variadic_t) (const char*, int, ...);
typedef FILE* (*libc_fopen_t) (const char *, const char *);
typedef FILE* (*libc_fopen64_t) (const char *, const char *);


std::string m_lib_name = "libc.so.6";
void* m_lib_handle = nullptr;
std::string log_name = "/home/gsd/log2.txt";



bool profiler_dlopen_library_handle (){
    m_lib_handle = ::dlopen (m_lib_name.data (), RTLD_LAZY);
    
    return (m_lib_handle != nullptr);
}

void logger(std::string str, std::string type){
    printf("%s",type.c_str());
    int fd_for_write =((libc_open_variadic_t)dlsym(RTLD_NEXT, "open"))(log_name.c_str (), O_CREAT | O_RDWR | O_APPEND);
    int written = ((libc_write_t)dlsym(RTLD_NEXT, "write"))(fd_for_write, str.c_str (), str.size ());
    int close_fd = ((libc_close_t)dlsym(RTLD_NEXT, "close"))(fd_for_write);
    printf("_%d_%d_%d\n",fd_for_write,written,close_fd);
}

ssize_t profiler_read(int fd, void *buf, size_t count){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t size = ((libc_read_t)dlsym(RTLD_NEXT, "read"))(fd, buf, count);
    const char * c = "res"; 
    char* t = new char[3];
    std::strncpy(t, c, 3); buf=t;

    std::string str = "[" + timestamp + "] read(" + std::to_string(fd) + ", ..., " + std::to_string(count)
    + ", ..., " + std::to_string(size) + ")" + ". PID= " + std::to_string(getpid()) + "\n";
    
    printf("Read");
    logger(str, "Read");

    return size;
}

ssize_t profiler_pread(int fildes, void *result, size_t nbyte, off_t offset){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t size = ((libc_pread_t)dlsym(RTLD_NEXT, "pread"))(fildes, result, nbyte, offset);
    const char * c = "res"; 
    char* t = new char[3];
    std::strncpy(t, c, 3); result=t;

    std::string str = "[" + timestamp + "] pread(" + std::to_string(fildes) + ", ..., " + std::to_string(nbyte)
    + ", ..., " + std::to_string(size) + ", "
    + std::to_string(offset) + ")" + ". PID= " + std::to_string(getpid()) + "\n";

    logger(str, "pRead64");

    return size;
}

ssize_t profiler_pread64(int fildes, void *result, size_t nbyte, off_t offset){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t size = ((libc_pread_t)dlsym(RTLD_NEXT, "pread64"))(fildes, result, nbyte, offset);

    std::string str = "[" + timestamp + "] pread(" + std::to_string(fildes) + ", ..., " + std::to_string(nbyte)
    + ", ..., " + std::to_string(size) + ", "
    + std::to_string(offset) + ")" + ". PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "pRead64");

    return size;
}

ssize_t profiler_write(int fd, const void *buf, size_t count){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t size = ((libc_write_t)dlsym(RTLD_NEXT, "write"))(fd, buf, count);
    //ssize_t size = ((libc_write_t)dlsym(RTLD_NEXT, "write"))(fd, "buf", 3);

    std::string str = "[" + timestamp + "] write(" + std::to_string(fd) + ", "  + std::to_string(count) +
    ", ...," + std::to_string(size) + "). PID= " + std::to_string(getpid()) + "\n";
    
    printf("Write");
    logger(str, "Write");
    
    return size;
}

ssize_t profiler_pwrite(int fd, const void *buf, size_t count, off_t offset){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    //ssize_t size = ((libc_pwrite_t)dlsym(RTLD_NEXT, "pwrite"))(fd, buf, count, offset);
    ssize_t size = ((libc_pwrite_t)dlsym(RTLD_NEXT, "pwrite"))(fd, "buf", 3, 0);

    std::string str = "[" + timestamp + "] pwrite(" + std::to_string(fd) + ", "  + std::to_string(count) + ", "  + 
    std::to_string(offset) + ", ...," + std::to_string(size) +  "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "pwrite");
    
    return size;
}

ssize_t profiler_pwrite64(int fd, const void *buf, size_t count, off_t offset){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    ssize_t size = ((libc_pwrite_t)dlsym(RTLD_NEXT, "pwrite64"))(fd, buf, count, offset);

    std::string str = "[" + timestamp + "] pwrite(" + std::to_string(fd) + ", "  + std::to_string(count) + ", "  + 
    std::to_string(offset) + ", ...," + std::to_string(size) +  "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "pwrite64");
    
    return size;
}

void * profiler_mmap (void *addr, size_t length, int prot, int flags, int fd, off_t offset){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    void* ret = ((libc_mmap_t)dlsym(RTLD_NEXT, "mmap"))(addr, length, prot, flags, fd, offset);

    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str = "[" + timestamp + "] mmap(" + addr_name + ", "  + std::to_string(length) + ", ..., " + std::to_string(prot) + ", "
    + std::to_string(flags) + ", " + std::to_string(fd) + ", " + std::to_string(offset) +
    "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "mmap");
    
    return ret;
}

int profiler_munmap(void *addr, size_t length){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int res = ((libc_munmap_t)dlsym(RTLD_NEXT, "munmap"))(addr, length);

    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str = "[" + timestamp + "] munmap(" + addr_name + ", "  + std::to_string(length) +
    "..." + std::to_string(res) + "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "munmap");
    
    return res;
}

int profiler_mprotect(void *addr, size_t len, int prot){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int res = ((libc_mprotect_t)dlsym(RTLD_NEXT, "mprotect"))(addr, len, prot);

    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str = "[" + timestamp + "] mprotect(" + addr_name + ", "  + std::to_string(len) + ", " + std::to_string(prot) +
    "..." + std::to_string(res) + "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "mprotect");
    
    return res;
}

ssize_t profiler_getxattr(const char *path, const char *name, void *value, size_t size){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);
    
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    ssize_t ret = ((libc_getxattr_t)dlsym(RTLD_NEXT, "getxattr"))(path, name, value, size);

    std::string str = "[" + timestamp + "] getxattr(" + std::string(path) + ", "  + std::string(name) + "," + valor + ", " + std::to_string(size) +
    "..." + std::to_string(ret) + "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "getxattr");
    
    return ret;
}

ssize_t profiler_lgetxattr(const char *path, const char *name, void *value, size_t size){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);
    
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    ssize_t ret = ((libc_lgetxattr_t)dlsym(RTLD_NEXT, "lgetxattr"))(path, name, value, size);

    std::string str = "[" + timestamp + "] lgetxattr(" + std::string(path) + ", "  + std::string(name) + "," + valor + ", " + std::to_string(size) +
    "..." + std::to_string(ret) + "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "lgetxattr");
    
    return ret;
}

ssize_t profiler_fgetxattr(int fd, const char *name, void *value, size_t size){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);
    
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    ssize_t ret = ((libc_fgetxattr_t)dlsym(RTLD_NEXT, "fgetxattr"))(fd, name, value, size);

    std::string str = "[" + timestamp + "] fgetxattr(" +  std::to_string(fd) + ", "  + std::string(name) + "," + valor + ", " + std::to_string(size) +
    "..." + std::to_string(ret) + "). PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "fgetxattr");
    
    return ret;
}

int profiler_close(int fildes){

    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int fd = ((libc_close_t)dlsym(RTLD_NEXT, "close"))(fildes);

    std::string str = "[" + timestamp + "] close(" + std::to_string(fildes) + ") = " + std::to_string(0)
            + ". PID= " + std::to_string(getpid()) + "\n";

    printf("Close");
    logger(str, "Close");
    
    return fd;
}

int profiler_fclose(FILE *stream){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int res = ((libc_fclose_t)dlsym(RTLD_NEXT, "fclose"))(stream);

    std::string str = "[" + timestamp + "] fclose() = " + ". PID= " + std::to_string(getpid()) + "\n";

    logger(str, "FClose");
    
    return res;
}

int profiler_openat_3 (int fildes, const char *path, int oflag){
    logger("", "OpenAt");
    
    return ((libc_openat_variadic_t)dlsym(RTLD_NEXT, "openat"))(fildes, path, oflag);
}

int profiler_openat_4 (int fildes, const char *path, int oflag, mode_t mode){
    logger("", "OpenAt");
     
    return ((libc_openat_variadic_t)dlsym(RTLD_NEXT, "openat"))(fildes, path, oflag, mode);
}

int profiler_open_2 (const char *pathname, int flags){
    printf("Entra2");
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int fd = ((libc_open_variadic_t)dlsym(RTLD_NEXT, "open"))(pathname, flags);

    std::string str = "[" + timestamp + "] open_variadic(" + std::string(pathname) + ") = " + std::to_string(fd)
    + ". PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "Open");
    
    return fd;
}

int profiler_open_3(const char *pathname, int flags, mode_t mode){
    printf("Entra1");
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int fd = ((libc_open_variadic_t)dlsym(RTLD_NEXT, "open"))(pathname, flags, mode);

    std::string str = "[" + timestamp + "] open_variadic(" + std::string(pathname) + ") = " + std::to_string(fd)
    + ". PID= " + std::to_string(getpid()) + "\n";

    logger(str, "Open");
    
    return fd;
}

int profiler_open64_3(const char *pathname, int flags, mode_t mode){
    printf("Entra3");
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    int fd = ((libc_open64_variadic_t)dlsym(RTLD_NEXT, "open64"))(pathname, flags, mode);

    std::string str = "[" + timestamp + "] open_variadic(" + std::string(pathname) + ") = " + std::to_string(fd)
    + ". PID= " + std::to_string(getpid()) + "\n";
    
    logger(str, "Open");
    
    return fd;
}

int profiler_open64_2(const char *pathname, int flags){
    printf("Entra4");
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);

    //int fd = ((libc_open64_t)dlsym(RTLD_NEXT, "open64"))(pathname, flags);
    int fd = ((libc_open64_variadic_t)dlsym(RTLD_NEXT, "open64"))(pathname, flags);

    std::string str = "[" + timestamp + "] open_variadic(" + std::string(pathname) + ") = " + std::to_string(fd)
    + ". PID= " + std::to_string(getpid()) + "\n";
    

    logger(str, "Open");
    
    return fd;
}

FILE * profiler_fopen(const char *filename, const char *mode){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);


    std::string str = "[" + timestamp + "] fopen(" + std::string(filename) + ") = " 
    + ". PID= " + std::to_string(getpid()) + "\n";

    logger(str, "FOpen");
    
    return ((libc_fopen_t)dlsym(RTLD_NEXT, "fopen"))(filename, mode);
}

FILE * profiler_fopen64(const char *filename, const char *mode){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    std::string timestamp = std::to_string(tv.tv_sec*(uint64_t)1000000+tv.tv_usec);


    std::string str = "[" + timestamp + "] fopen(" + std::string(filename) + ") = " 
    + ". PID= " + std::to_string(getpid()) + "\n";

    logger(str, "FOpen");
    
    return ((libc_fopen_t)dlsym(RTLD_NEXT, "fopen"))(filename, mode);
}