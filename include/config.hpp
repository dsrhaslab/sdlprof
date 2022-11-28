

namespace config{

enum log_formats { pretty_print, json };

enum log_formats log_type = json;
std::string dir = "/home/gsd/logs/";
std::string machine_name = "";
std::string log_name = "";
std::string pid = "";
int reset_pid_per_op = 0;

}// namespace config

