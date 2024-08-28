#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid(pid){
    CpuUtilization();
    Command();
    Ram();
    User();
    UpTime();
}
// TODO: Return this process's ID
int Process::Pid() const{ return pid; }

// TODO: Return this process's CPU utilization
 float Process::CpuUtilization() const{ 
  vector<float> cpu_time = LinuxParser::CpuUtilization(Pid());
  float total_time;
  total_time = cpu_time[0] + cpu_time[1] + cpu_time[2] + cpu_time[3];
  long uptime = LinuxParser::UpTime();
  float seconds = uptime - (cpu_time[4] / sysconf(_SC_CLK_TCK));
  float cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds;
  return cpu_usage*100;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return std::to_string(LinuxParser::Ram(Pid())); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// bool Process::operator<(Process const& a) { 
//   return (CpuUtilization() < a.CpuUtilization());
//  }
