

namespace json_format_log{

std::string json_format_log(std::string operation, std::string* data, std::string* labels, int size){
    std::string str;

    str = "{\""; str.append(operation); str.append("\":{"); 
    for(int i=0; i<size;i++){
        if(i==0) str.append("\"");
        else str.append(",\"");
        str.append(labels[i]);
        str.append("\":\"");
        str.append(data[i]);
        str.append(",\"");
    }
    str.append("}\n");

    return str;
}

// json_log_read call. (...)
std::string json_log_read (std::string timestamp, int fd, size_t counter, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"read\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"counter\":"); str.append(std::to_string(counter));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_write call. (...)
std::string json_log_write (std::string timestamp, int fd, size_t counter, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"write\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"counter\":"); str.append(std::to_string(counter));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    return str;
}

// json_log_pread call. (...)
std::string json_log_pread (std::string timestamp, int fd, size_t counter, off_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"pread\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"counter\":"); str.append(std::to_string(counter));
    str.append( ",\"offset\":"); str.append(std::to_string(offset));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_pwrite call. (...)
std::string json_log_pwrite (std::string timestamp, int fd, size_t counter, off_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"pwrite\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"counter\":"); str.append(std::to_string(counter));
    str.append( ",\"offset\":"); str.append(std::to_string(offset));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    return str;
}

// json_log_pread64 call. (...)
#if defined(__USE_LARGEFILE64)
std::string json_log_pread64 (std::string timestamp, int fd, size_t counter, off64_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"pread64\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"counter\":"); str.append(std::to_string(counter));
    str.append( ",\"offset\":"); str.append(std::to_string(offset));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
   
    return str;
}
#endif

// json_log_pwrite64 call. (...)
#if defined(__USE_LARGEFILE64)
std::string json_log_pwrite64 (std::string timestamp, int fd, size_t counter, off64_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"pwrite64\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"counter\":"); str.append(std::to_string(counter));
    str.append( ",\"offset\":"); str.append(std::to_string(offset));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}
#endif

// pass_through_posix_mmap call. (...)
std::string json_log_mmap (std::string timestamp, void* addr, size_t length, int prot, int flags, int fd, off_t offset, std::string pid)
{
    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str;
    str =       "{\"sys_call_name\":\"mmap\"";
    str.append(  ",\"timestamp\":"); str.append(timestamp);
    str.append(  ",\"addr\":\""); str.append(addr_name);
    str.append("\",\"length\":"); str.append(std::to_string(length));
    str.append(  ",\"prot\":"); str.append(std::to_string(prot));
    str.append(  ",\"flags\":"); str.append(std::to_string(flags));
    str.append(  ",\"fd\":"); str.append(std::to_string(fd));
    str.append(  ",\"offset\":"); str.append(std::to_string(offset));
    str.append(  ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    //printf("%s\n", str.data());
    return str;
}

// pass_through_posix_munmap call. (...)
std::string json_log_munmap (std::string timestamp, void* addr, size_t length, int result, std::string pid)
{
    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str;
    str =       "{\"sys_call_name\":\"munmap\"";
    str.append(  ",\"timestamp\":"); str.append(timestamp);
    str.append(  ",\"addr\":\""); str.append(addr_name);
    str.append("\",\"length\":"); str.append(std::to_string(length));
    str.append(  ",\"result\":"); str.append(std::to_string(result));
    str.append(  ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    //printf("%s\n", str.data());
    return str;
}

// json_log_open call. (...)
std::string json_log_open (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"open\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"path\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_creat call. (...)
std::string json_log_creat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"creat\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"path\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_creat64 call. (...)
std::string json_log_creat64 (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"creat64\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"path\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    return str;
}

// json_log_openat call. (...)
std::string json_log_openat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"openat\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"path\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_open64 call. (...)
std::string json_log_open64 (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"open64\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"path\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    return str;
}

// json_log_close call. (...)
std::string json_log_close (std::string timestamp, int fd, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"close\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_sync call. (...)
std::string json_log_sync (std::string timestamp, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"sync\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_statfs call. (...)
std::string json_log_statfs (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"statfs\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_fstatfs call. (...)
std::string json_log_fstatfs (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"fstatfs\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
   
    return str;
}

// json_log_statfs64 call. (...)
std::string json_log_statfs64 (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"statfs64\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");
    
    return str;
}

// json_log_fstatfs64 call. (...)
std::string json_log_fstatfs64 (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"fstatfs64\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    return str;
}

// json_log_unlink call. (...)
std::string json_log_unlink (std::string timestamp, const char* old_path, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"unlink\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"old_path\":\""); str.append(std::string(old_path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    return str;
}

// json_log_unlinkat call. (...)
std::string json_log_unlinkat (std::string timestamp, const char* pathname, int result, std::string pid)
{
    std::string str;
    str =       "{\"sys_call_name\":\"unlinkat\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(pathname));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append( "}\n");

    return str;
}

// json_log_rename call. (...)
std::string json_log_rename (std::string timestamp, const char* old_path, const char* new_path, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"rename\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"old_path\":\""); str.append(std::string(old_path));
    str.append( "\",\"new_path\":\""); str.append(std::string(new_path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_renameat call. (...)
std::string json_log_renameat (std::string timestamp, const char* old_path, const char* new_path, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"renameat\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"old_path\":\""); str.append(std::string(old_path));
    str.append( "\",\"new_path\":\""); str.append(std::string(new_path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");
    
    return str;
}

// json_log_fopen call. (...)
std::string json_log_fopen (std::string timestamp, const char* pathname, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"fopen\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(pathname));
    str.append( "\",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_fopen64 call. (...)
std::string json_log_fopen64 (std::string timestamp, const char* pathname, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"fopen64\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(pathname));
    str.append( "\",\"pid\":"); str.append(pid);
    str.append("}\n");
    
    return str;
}

// json_log_fclose call. (...)
std::string json_log_fclose (std::string timestamp, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"fclose\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_mkdir call. (...)
std::string json_log_mkdir (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"mkdir\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_mkdirat call. (...)
std::string json_log_mkdirat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"mkdirat\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_rmdir call. (...)
std::string json_log_rmdir (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"rmdir\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_mknod call. (...)
std::string json_log_mknod (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"mknod\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");
    
    return str;
}

// json_log_mknodat call. (...)
std::string json_log_mknodat (std::string timestamp, const char*  path, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"mknod\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_getxattr call. (...)
std::string json_log_getxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str =      "{\"sys_call_name\":\"getxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"name\":\""); str.append(std::string(name));
    str.append( "\",\"value\":\""); str.append(valor);
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");
    
    return str;
}

// json_log_lgetxattr call. (...)
std::string json_log_lgetxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str =      "{\"sys_call_name\":\"lgetxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"name\":\""); str.append(std::string(name));
    str.append( "\",\"value\":\""); str.append(valor);
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");
    
    return str;
}

// json_log_fgetxattr call. (...)
std::string json_log_fgetxattr (std::string timestamp, int fd, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str =      "{\"sys_call_name\":\"fgetxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"name\":\""); str.append(std::string(name));
    str.append( "\",\"value\":\""); str.append(valor);
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_setxattr call. (...)
std::string json_log_setxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str =      "{\"sys_call_name\":\"setxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"name\":\""); str.append(std::string(name));
    str.append( "\",\"value\":\""); str.append(valor);
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_lsetxattr call. (...)
std::string json_log_lsetxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str =      "{\"sys_call_name\":\"lsetxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"name\":\""); str.append(std::string(name));
    str.append( "\",\"value\":\""); str.append(valor);
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_fsetxattr call. (...)
std::string json_log_fsetxattr (std::string timestamp, int fd, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str =      "{\"sys_call_name\":\"fsetxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"name\":\""); str.append(std::string(name));
    str.append( "\",\"value\":\""); str.append(valor);
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_listxattr call. (...)
std::string json_log_listxattr (std::string timestamp, const char* path, size_t size, ssize_t result, std::string pid)
{   
    std::string str;
    str =      "{\"sys_call_name\":\"listxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_llistxattr call. (...)
std::string json_log_llistxattr (std::string timestamp, const char* path, size_t size, ssize_t result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"llistxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"pathname\":\""); str.append(std::string(path));
    str.append( "\",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_flistxattr call. (...)
std::string json_log_flistxattr (std::string timestamp, int fd, size_t size, ssize_t result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"flistxattr\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"fd\":"); str.append(std::to_string(fd));
    str.append( ",\"size\":"); str.append(std::to_string(size));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");

    return str;
}

// json_log_socket call. (...)
std::string json_log_socket (std::string timestamp, int domain, int type, int protocol, int result, std::string pid)
{
    std::string str;
    str =      "{\"sys_call_name\":\"socket\"";
    str.append( ",\"timestamp\":"); str.append(timestamp);
    str.append( ",\"domain\":"); str.append(std::to_string(domain));
    str.append( ",\"type\":"); str.append(std::to_string(type));
    str.append( ",\"protocol\":"); str.append(std::to_string(protocol));
    str.append( ",\"result\":"); str.append(std::to_string(result));
    str.append( ",\"pid\":"); str.append(pid);
    str.append("}\n");
    
    return str;
}

} // namespace json_format_log



/*
namespace json_format_log{

std::string json_format_log(std::string operation, std::string* data, std::string* labels, int size){
    std::string str;

    str = "{\""; str.append(operation); str.append("\":{"); 
    for(int i=0; i<size;i++){
        if(i==0) str.append("\"");
        else str.append(",\"");
        str.append(labels[i]);
        str.append("\":\"");
        str.append(data[i]);
        str.append(",\"");
    }
    str.append("}}\n");

    return str;
}

// json_log_read call. (...)
std::string json_log_read (std::string timestamp, int fd, size_t counter, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"read\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"fd\":"); str.append(std::to_string(fd));
    str.append(           ",\"counter\":"); str.append(std::to_string(counter));
    str.append(           ",\"result\":"); str.append(std::to_string(result));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_write call. (...)
std::string json_log_write (std::string timestamp, int fd, size_t counter, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"write\":{\"timestamp\":"; str.append(timestamp);
    str.append(            ",\"fd\":"); str.append(std::to_string(fd));
    str.append(            ",\"counter\":"); str.append(std::to_string(counter));
    str.append(            ",\"result\":"); str.append(std::to_string(result));
    str.append(            ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_pread call. (...)
std::string json_log_pread (std::string timestamp, int fd, size_t counter, off_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"pread\":{\"timestamp\":"; str.append(timestamp);
    str.append(            ",\"fd\":"); str.append(std::to_string(fd));
    str.append(            ",\"counter\":"); str.append(std::to_string(counter));
    str.append(            ",\"offset\":"); str.append(std::to_string(offset));
    str.append(            ",\"result\":"); str.append(std::to_string(result));
    str.append(            ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_pwrite call. (...)
std::string json_log_pwrite (std::string timestamp, int fd, size_t counter, off_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"pwrite\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"fd\":"); str.append(std::to_string(fd));
    str.append(             ",\"counter\":"); str.append(std::to_string(counter));
    str.append(             ",\"offset\":"); str.append(std::to_string(offset));
    str.append(             ",\"result\":"); str.append(std::to_string(result));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_pread64 call. (...)
#if defined(__USE_LARGEFILE64)
std::string json_log_pread64 (std::string timestamp, int fd, size_t counter, off64_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"pread64\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"fd\":"); str.append(std::to_string(fd));
    str.append(              ",\"counter\":"); str.append(std::to_string(counter));
    str.append(              ",\"offset\":"); str.append(std::to_string(offset));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
   
    return str;
}
#endif

// json_log_pwrite64 call. (...)
#if defined(__USE_LARGEFILE64)
std::string json_log_pwrite64 (std::string timestamp, int fd, size_t counter, off64_t offset, ssize_t result, std::string pid)
{
    std::string str;
    str =       "{\"pwrite64\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"fd\":"); str.append(std::to_string(fd));
    str.append(              ",\"counter\":"); str.append(std::to_string(counter));
    str.append(              ",\"offset\":"); str.append(std::to_string(offset));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(               ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}
#endif

// pass_through_posix_mmap call. (...)
std::string json_log_mmap (std::string timestamp, void* addr, size_t length, int prot, int flags, int fd, off_t offset, std::string pid)
{
    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str;
    str =       "{\"pwrite\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"addr\":"); str.append(addr_name);
    str.append(             ",\"length\":"); str.append(std::to_string(length));
    str.append(             ",\"prot\":"); str.append(std::to_string(prot));
    str.append(             ",\"flags\":"); str.append(std::to_string(flags));
    str.append(             ",\"fd\":"); str.append(std::to_string(fd));
    str.append(             ",\"offset\":"); str.append(std::to_string(offset));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// pass_through_posix_munmap call. (...)
std::string json_log_munmap (std::string timestamp, void* addr, size_t length, int result, std::string pid)
{
    std::ostringstream address;
    address << addr;
    std::string addr_name = address.str();

    std::string str;
    str =       "{\"munmap\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"addr\":"); str.append(addr_name);
    str.append(             ",\"length\":"); str.append(std::to_string(length));
    str.append(             ",\"result\":"); str.append(std::to_string(result));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_open call. (...)
std::string json_log_open (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"open\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"path\":"); str.append(std::string(path));
    str.append(           ",\"result\":"); str.append(std::to_string(result));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_creat call. (...)
std::string json_log_creat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"creat\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"path\":"); str.append(std::string(path));
    str.append(           ",\"result\":"); str.append(std::to_string(result));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_creat64 call. (...)
std::string json_log_creat64 (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"creat64\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"path\":"); str.append(std::string(path));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_openat call. (...)
std::string json_log_openat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"openat\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"path\":"); str.append(std::string(path));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_open64 call. (...)
std::string json_log_open64 (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =       "{\"open64\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"path\":"); str.append(std::string(path));
    str.append(             ",\"result\":"); str.append(std::to_string(result));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_close call. (...)
std::string json_log_close (std::string timestamp, int fd, int result, std::string pid)
{
    std::string str;
    str =       "{\"close\":{\"timestamp\":"; str.append(timestamp);
    str.append(            ",\"fd\":"); str.append(std::to_string(fd));
    str.append(            ",\"result\":"); str.append(std::to_string(result));
    str.append(            ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_sync call. (...)
std::string json_log_sync (std::string timestamp, std::string pid)
{
    std::string str;
    str =       "{\"sync\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_statfs call. (...)
std::string json_log_statfs (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"statfs\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"result\":"); str.append(std::to_string(result));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_fstatfs call. (...)
std::string json_log_fstatfs (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"fstatfs\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
   
    return str;
}

// json_log_statfs64 call. (...)
std::string json_log_statfs64 (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"statfs64\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append( "}}\n");
    
    return str;
}

// json_log_fstatfs64 call. (...)
std::string json_log_fstatfs64 (std::string timestamp, int result, std::string pid)
{
    std::string str;
    str =       "{\"fstatfs64\":{\"timestamp\":"; str.append(timestamp);
    str.append(                ",\"result\":"); str.append(std::to_string(result));
    str.append(                ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_unlink call. (...)
std::string json_log_unlink (std::string timestamp, const char* old_path, int result, std::string pid)
{
    std::string str;
    str =       "{\"unlink\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"old_path\":"); str.append(std::string(old_path));
    str.append(             ",\"result\":"); str.append(std::to_string(result));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_unlinkat call. (...)
std::string json_log_unlinkat (std::string timestamp, const char* pathname, int result, std::string pid)
{
    std::string str;
    str =       "{\"unlinkat\":{\"timestamp\":"; str.append(timestamp);
    str.append(               ",\"pathname\":"); str.append(std::string(pathname));
    str.append(               ",\"result\":"); str.append(std::to_string(result));
    str.append(               ",\"pid\":"); str.append(pid);
    str.append( "}}\n");

    return str;
}

// json_log_rename call. (...)
std::string json_log_rename (std::string timestamp, const char* old_path, const char* new_path, int result, std::string pid)
{
    std::string str;
    str =      "{\"rename\":{\"timestamp\":"; str.append(timestamp);
    str.append(            ",\"old_path\":"); str.append(std::string(old_path));
    str.append(            ",\"new_path\":"); str.append(std::string(new_path));
    str.append(            ",\"result\":"); str.append(std::to_string(result));
    str.append(            ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_renameat call. (...)
std::string json_log_renameat (std::string timestamp, const char* old_path, const char* new_path, int result, std::string pid)
{
    std::string str;
    str =      "{\"renameat\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"old_path\":"); str.append(std::string(old_path));
    str.append(              ",\"new_path\":"); str.append(std::string(new_path));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append("}}\n");
    
    return str;
}

// json_log_fopen call. (...)
std::string json_log_fopen (std::string timestamp, const char* pathname, std::string pid)
{
    std::string str;
    str =      "{\"fopen\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"pathname\":"); str.append(std::string(pathname));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_fopen64 call. (...)
std::string json_log_fopen64 (std::string timestamp, const char* pathname, std::string pid)
{
    std::string str;
    str =      "{\"fopen64\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"pathname\":"); str.append(std::string(pathname));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append("}}\n");
    
    return str;
}

// json_log_fclose call. (...)
std::string json_log_fclose (std::string timestamp, std::string pid)
{
    std::string str;
    str =      "{\"fclose\":{\"timestamp\":"; str.append(timestamp);
    str.append(            ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_mkdir call. (...)
std::string json_log_mkdir (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"mkdir\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"pathname\":"); str.append(std::string(path));
    str.append(           ",\"result\":"); str.append(std::to_string(result));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_mkdirat call. (...)
std::string json_log_mkdirat (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"mkdirat\":{\"timestamp\":"; str.append(timestamp);
    str.append(             ",\"pathname\":"); str.append(std::string(path));
    str.append(             ",\"result\":"); str.append(std::to_string(result));
    str.append(             ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_rmdir call. (...)
std::string json_log_rmdir (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"rmdir\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"pathname\":"); str.append(std::string(path));
    str.append(           ",\"result\":"); str.append(std::to_string(result));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_mknod call. (...)
std::string json_log_mknod (std::string timestamp, const char* path, int result, std::string pid)
{
    std::string str;
    str =      "{\"mknod\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"pathname\":"); str.append(std::string(path));
    str.append(           ",\"result\":"); str.append(std::to_string(result));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append("}}\n");
    
    return str;
}

// json_log_mknodat call. (...)
std::string json_log_mknodat (std::string timestamp, const char*  path, int result, std::string pid)
{
    std::string str;
    str =      "{\"mknod\":{\"timestamp\":"; str.append(timestamp);
    str.append(           ",\"pathname\":"); str.append(std::string(path));
    str.append(           ",\"result\":"); str.append(std::to_string(result));
    str.append(           ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_getxattr call. (...)
std::string json_log_getxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str =      "{\"getxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"pathname\":"); str.append(std::string(path));
    str.append(              ",\"name\":"); str.append(std::string(name));
    str.append(              ",\"value\":"); str.append(valor);
    str.append(              ",\"size\":"); str.append(std::to_string(size));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append("}}\n");
    
    return str;
}

// json_log_lgetxattr call. (...)
std::string json_log_lgetxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str =      "{\"lgetxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(               ",\"pathname\":"); str.append(std::string(path));
    str.append(               ",\"name\":"); str.append(std::string(name));
    str.append(               ",\"value\":"); str.append(valor);
    str.append(               ",\"size\":"); str.append(std::to_string(size));
    str.append(               ",\"result\":"); str.append(std::to_string(result));
    str.append(               ",\"pid\":"); str.append(pid);
    str.append("}}\n");
    
    return str;
}

// json_log_fgetxattr call. (...)
std::string json_log_fgetxattr (std::string timestamp, int fd, const char* name, const void* value, size_t size, ssize_t result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str =      "{\"fgetxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(               ",\"fd\":"); str.append(std::to_string(fd));
    str.append(               ",\"name\":"); str.append(std::string(name));
    str.append(               ",\"value\":"); str.append(valor);
    str.append(               ",\"size\":"); str.append(std::to_string(size));
    str.append(               ",\"result\":"); str.append(std::to_string(result));
    str.append(               ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_setxattr call. (...)
std::string json_log_setxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str =      "{\"setxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"pathname\":"); str.append(std::string(path));
    str.append(              ",\"name\":"); str.append(std::string(name));
    str.append(              ",\"value\":"); str.append(valor);
    str.append(              ",\"size\":"); str.append(std::to_string(size));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_lsetxattr call. (...)
std::string json_log_lsetxattr (std::string timestamp, const char* path, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();
    
    std::string str;
    str =      "{\"lsetxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(               ",\"pathname\":"); str.append(std::string(path));
    str.append(               ",\"name\":"); str.append(std::string(name));
    str.append(               ",\"value\":"); str.append(valor);
    str.append(               ",\"size\":"); str.append(std::to_string(size));
    str.append(               ",\"result\":"); str.append(std::to_string(result));
    str.append(               ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_fsetxattr call. (...)
std::string json_log_fsetxattr (std::string timestamp, int fd, const char* name, const void* value, size_t size, int result, std::string pid)
{
    std::ostringstream val;
    val << value;
    std::string valor = val.str();

    std::string str;
    str =      "{\"fsetxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(              ",\"fd\":"); str.append(std::to_string(fd));
    str.append(              ",\"name\":"); str.append(std::string(name));
    str.append(              ",\"value\":"); str.append(valor);
    str.append(              ",\"size\":"); str.append(std::to_string(size));
    str.append(              ",\"result\":"); str.append(std::to_string(result));
    str.append(              ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_listxattr call. (...)
std::string json_log_listxattr (std::string timestamp, const char* path, size_t size, ssize_t result, std::string pid)
{   
    std::string str;
    str =      "{\"listxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(               ",\"pathname\":"); str.append(std::string(path));
    str.append(               ",\"size\":"); str.append(std::to_string(size));
    str.append(               ",\"result\":"); str.append(std::to_string(result));
    str.append(               ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_llistxattr call. (...)
std::string json_log_llistxattr (std::string timestamp, const char* path, size_t size, ssize_t result, std::string pid)
{
    std::string str;
    str =      "{\"llistxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(                ",\"pathname\":"); str.append(std::string(path));
    str.append(                ",\"size\":"); str.append(std::to_string(size));
    str.append(                ",\"result\":"); str.append(std::to_string(result));
    str.append(                ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_flistxattr call. (...)
std::string json_log_flistxattr (std::string timestamp, int fd, size_t size, ssize_t result, std::string pid)
{
    std::string str;
    str =      "{\"flistxattr\":{\"timestamp\":"; str.append(timestamp);
    str.append(                ",\"fd\":"); str.append(std::to_string(fd));
    str.append(                ",\"size\":"); str.append(std::to_string(size));
    str.append(                ",\"result\":"); str.append(std::to_string(result));
    str.append(                ",\"pid\":"); str.append(pid);
    str.append("}}\n");

    return str;
}

// json_log_socket call. (...)
std::string json_log_socket (std::string timestamp, int domain, int type, int protocol, int result, std::string pid)
{
    std::string str;
    str =      "{\"socket\":{\"timestamp\":"; str.append(timestamp);
    str.append(            ",\"domain\":"); str.append(std::to_string(domain));
    str.append(            ",\"type\":"); str.append(std::to_string(type));
    str.append(            ",\"protocol\":"); str.append(std::to_string(protocol));
    str.append(            ",\"result\":"); str.append(std::to_string(result));
    str.append(            ",\"pid\":"); str.append(pid);
    str.append("}}\n");
    
    return str;
}

} // namespace json_format_log

*/
