

namespace pretty_print_format_log{

// pretty_print_log_read call. (...)
std::string pretty_print_log_read (std::string timestamp, int fd, size_t counter, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] read("); str.append(std::to_string(fd)); 
    str.append(", "); str.append(std::to_string(counter)); str.append(", ...,"); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_write call. (...)
std::string pretty_print_log_write (std::string timestamp, int fd, size_t counter, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] write("); str.append(std::to_string(fd)); 
    str.append(", "); str.append(std::to_string(counter)); str.append(", ...,"); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_pread call. (...)
std::string pretty_print_log_pread (std::string timestamp, int fd, size_t counter, off_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] pwrite("); str.append(std::to_string(fd)); 
    str.append(", "); str.append(std::to_string(counter)); str.append(", "); str.append(std::to_string(offset)); 
    str.append(", ...,"); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_pwrite call. (...)
std::string pretty_print_log_pwrite (std::string timestamp, int fd, size_t counter, off_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] pwrite("); str.append(std::to_string(fd)); 
    str.append(", "); str.append(std::to_string(counter)); str.append(", "); str.append(std::to_string(offset)); 
    str.append(", ...,"); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");;

    return str;
}

// pretty_print_log_pread64 call. (...)
#if defined(__USE_LARGEFILE64)
std::string pretty_print_log_pread64 (std::string timestamp, int fd, size_t counter, off64_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] pread64("); str.append(std::to_string(fd)); 
    str.append(", "); str.append(std::to_string(counter)); str.append(", "); str.append(std::to_string(offset)); 
    str.append(", ...,"); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");
   
    return str;
}
#endif

// pretty_print_log_pwrite64 call. (...)
#if defined(__USE_LARGEFILE64)
std::string pretty_print_log_pwrite64 (std::string timestamp, int fd, size_t counter, off64_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] pwrite64("); str.append(std::to_string(fd)); 
    str.append(", "); str.append(std::to_string(counter)); str.append(", "); str.append(std::to_string(offset)); 
    str.append(", ...,"); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}
#endif

// pass_through_posix_mmap call. (...)
std::string pretty_print_log_mmap (std::string timestamp, void* addr, size_t length, int prot, int flags, int fd, off_t offset, std::string pid)
{
    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str;
    str = "["; str.append(timestamp); str.append("] mmap("); str.append(addr_name); str.append(", "); 
    str.append(std::to_string(length)); str.append(", "); str.append(std::to_string(prot)); str.append(", "); 
    str.append(std::to_string(flags)); str.append(", "); str.append(std::to_string(fd)); str.append(", "); 
    str.append(std::to_string(offset)); str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pass_through_posix_munmap call. (...)
std::string pretty_print_log_munmap (std::string timestamp, void* addr, size_t length, int result, std::string pid)
{
    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str;
    str = "["; str.append(timestamp); str.append("] munmap("); str.append(addr_name); 
    str.append(", "); str.append(std::to_string(length)); str.append(", ...,"); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); 
    str.append("\n");

    return str;
}

// pretty_print_log_open call. (...)
std::string pretty_print_log_open (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] open("); str.append(std::string(path));
    str.append(") = "); str.append(std::to_string(result)); str.append(". PID= "); str.append(pid); 
    str.append("\n");

    return str;
}

// pretty_print_log_creat call. (...)
std::string pretty_print_log_creat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] creat("); str.append(std::string(path));
    str.append(", "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); 
    str.append("\n");
    
    return str;
}

// pretty_print_log_creat64 call. (...)
std::string pretty_print_log_creat64 (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] creat64("); str.append(std::string(path));
    str.append(", "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); 
    str.append("\n");


    return str;
}

// pretty_print_log_openat call. (...)
std::string pretty_print_log_openat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] openat("); str.append(std::string(path));
    str.append(") = "); str.append(std::to_string(result)); str.append(". PID= "); str.append(pid); 
    str.append("\n");
    
    return str;
}

// pretty_print_log_open64 call. (...)
std::string pretty_print_log_open64 (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] open64("); str.append(std::string(path));
    str.append(") = "); str.append(std::to_string(result)); str.append(". PID= "); str.append(pid); 
    str.append("\n");

    return str;
}

// pretty_print_log_close call. (...)
std::string pretty_print_log_close (std::string timestamp, int fd, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] close("); str.append(std::to_string(fd));
    str.append(") = "); str.append(std::to_string(result)); str.append(". PID= "); str.append(pid); 
    str.append("\n");
    
    return str;
}

// pretty_print_log_sync call. (...)
std::string pretty_print_log_sync (std::string timestamp, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] sync(). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_statfs call. (...)
std::string pretty_print_log_statfs (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] statfs("); str.append(std::to_string(result));
    str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_fstatfs call. (...)
std::string pretty_print_log_fstatfs (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] fstatfs("); str.append(std::to_string(result));
    str.append("). PID= "); str.append(pid); str.append("\n");
   
    return str;
}

// pretty_print_log_statfs64 call. (...)
std::string pretty_print_log_statfs64 (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] statfs64("); str.append(std::to_string(result));
    str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_fstatfs64 call. (...)
std::string pretty_print_log_fstatfs64 (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"fstatfs64\":{\"timestamp\":"; str.append(timestamp);
    str.append(                ",\"result\":"); str.append(std::to_string(result));
    str.append(                ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    str = "["; str.append(timestamp); str.append("] fstatfs64("); str.append(std::to_string(result));
    str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_unlink call. (...)
std::string pretty_print_log_unlink (std::string timestamp, const char* old_path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] unlink("); str.append(std::string(old_path)); 
    str.append(", ..., "); str.append(std::to_string(result));str.append("). PID= "); 
    str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_unlinkat call. (...)
std::string pretty_print_log_unlinkat (std::string timestamp, const char* pathname, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] unlinkat("); str.append(std::string(pathname)); 
    str.append(", ..., "); str.append(std::to_string(result));str.append("). PID= "); 
    str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_rename call. (...)
std::string pretty_print_log_rename (std::string timestamp, const char* old_path, const char* new_path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] rename("); str.append(std::string(old_path)); str.append(", "); 
    str.append(std::string(new_path)); str.append(", ..., "); str.append(std::to_string(result));str.append("). PID= "); 
    str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_renameat call. (...)
std::string pretty_print_log_renameat (std::string timestamp, const char* old_path, const char* new_path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] renameat("); str.append(std::string(old_path)); str.append(", "); 
    str.append(std::string(new_path)); str.append(", ..., "); str.append(std::to_string(result));str.append("). PID= "); 
    str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_fopen call. (...)
std::string pretty_print_log_fopen (std::string timestamp, const char* pathname, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] fopen("); str.append(std::string(pathname)); 
    str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_fopen64 call. (...)
std::string pretty_print_log_fopen64 (std::string timestamp, const char* pathname, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] fopen64("); str.append(std::string(pathname)); 
    str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_fclose call. (...)
std::string pretty_print_log_fclose (std::string timestamp, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] fclose(). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_mkdir call. (...)
std::string pretty_print_log_mkdir (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"mkdir\":{\"timestamp\":"; str.append(timestamp);
    str = "["; str.append(timestamp); str.append("] mkdir("); str.append(std::string(path)); str.append(", ..., "); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_mkdirat call. (...)
std::string pretty_print_log_mkdirat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] mkdirat("); str.append(std::string(path)); str.append(", ..., "); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_rmdir call. (...)
std::string pretty_print_log_rmdir (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] rmdir("); str.append(std::string(path)); str.append(", ..., "); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_mknod call. (...)
std::string pretty_print_log_mknod (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] mknod("); str.append(std::string(path)); str.append(", ..., "); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");
    
    return str;
}

// pretty_print_log_mknodat call. (...)
std::string pretty_print_log_mknodat (std::string timestamp, const char*  path, int result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] mknodat("); str.append(std::string(path)); str.append(", ..., "); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_getxattr call. (...)
std::string pretty_print_log_getxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str = "["; str.append(timestamp); str.append("] fgetxattr("); str.append(std::string(path)); str.append(", ");
    str.append(std::string(name)); str.append(","); str.append(valor); str.append(", "); str.append(std::to_string(size)); 
    str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid);  str.append("\n");
    
    return str;
}

// pretty_print_log_lgetxattr call. (...)
std::string pretty_print_log_lgetxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str = "["; str.append(timestamp); str.append("] fgetxattr("); str.append(std::string(path)); str.append(", ");
    str.append(std::string(name)); str.append(","); str.append(valor); str.append(", "); str.append(std::to_string(size)); 
    str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid);  str.append("\n");

    return str;
}

// pretty_print_log_fgetxattr call. (...)
std::string pretty_print_log_fgetxattr (std::string timestamp, int fd, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str = "["; str.append(timestamp); str.append("] fgetxattr("); str.append(std::to_string(fd)); str.append(", ");
    str.append(std::string(name)); str.append(","); str.append(valor); str.append(", "); str.append(std::to_string(size)); 
    str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid);  str.append("\n");

    return str;
}

// pretty_print_log_setxattr call. (...)
std::string pretty_print_log_setxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str = "["; str.append(timestamp); str.append("] setxattr("); str.append(std::string(path)); str.append(", "); 
    str.append(std::string(name)); str.append(","); str.append(valor); str.append(", "); str.append(std::to_string(size));
    str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_lsetxattr call. (...)
std::string pretty_print_log_lsetxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str = "["; str.append(timestamp); str.append("] lsetxattr("); str.append(std::string(path)); str.append(", "); 
    str.append(std::string(name)); str.append(","); str.append(valor); str.append(", "); str.append(std::to_string(size));
    str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_fsetxattr call. (...)
std::string pretty_print_log_fsetxattr (std::string timestamp, int fd, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str = "["; str.append(timestamp); str.append("] fsetxattr("); str.append(std::to_string(fd)); str.append(", "); 
    str.append(std::string(name)); str.append(","); str.append(valor); str.append(", "); str.append(std::to_string(size));
    str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n");

    return str;
}

// pretty_print_log_listxattr call. (...)
std::string pretty_print_log_listxattr (std::string timestamp, const char* path, size_t size, ssize_t result, std::string pid)
{   
    std::string str;
    str = "["; str.append(timestamp); str.append("] listxattr("); str.append(std::string(path)); str.append(", "); 
    str.append(std::to_string(size)); str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); 
    str.append(pid) + str.append("\n");

    return str;
}

// pretty_print_log_llistxattr call. (...)
std::string pretty_print_log_llistxattr (std::string timestamp, const char* path, size_t size, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] llistxattr("); str.append(std::string(path)); str.append(", "); 
    str.append(std::to_string(size)); str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); 
    str.append(pid) + str.append("\n");

    return str;
}

// pretty_print_log_flistxattr call. (...)
std::string pretty_print_log_flistxattr (std::string timestamp, int fd, size_t size, ssize_t result, std::string pid)
{
    std::string str;
    str = "["; str.append(timestamp); str.append("] flistxattr("); str.append(std::to_string(fd)); str.append(", "); 
    str.append(std::to_string(size)); str.append(", ..., "); str.append(std::to_string(result)); str.append("). PID= "); 
    str.append(pid); str.append("\n"); 
    return str;
}

// pretty_print_log_socket call. (...)
std::string pretty_print_log_socket (std::string timestamp, int domain, int type, int protocol, int result, std::string pid)
{
    std::string str;
    str = "[" ; str.append(timestamp); str.append("] socket("); str.append(std::to_string(domain)); str.append(", ");
    str.append(std::to_string(type)); str.append(", "); str.append(std::to_string(protocol)); str.append(", ..., "); 
    str.append(std::to_string(result)); str.append("). PID= "); str.append(pid); str.append("\n"); 
    
    return str;
}

} // namespace pretty_print_format_log