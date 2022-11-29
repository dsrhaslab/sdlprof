

namespace config{

enum log_formats { pretty_print, json };

enum log_formats log_type = json;
std::string dir = "/home/gsd/logs/";
std::string hostname = "";
std::string log_file_name = "";
std::string pid = "";
bool reset_pid_per_op = false;

}// namespace config

