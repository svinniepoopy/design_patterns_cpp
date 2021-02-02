#include "singleton.h"

#include <fstream>
#include <string>

// To illustrate the use of singleton we'll create two objects that use
// a single instance of a logger to log something to

// single instance of a logger
class logger : public singleton<logger> {
  public:
    void log(const std::string& data) {
      ofs << data; 
    }

    logger(const std::string& filename):ofs{filename, std::ios::out} {}

  private:
    std::ofstream ofs;
};

// users of the logger singleton
class log_user {
  public:
    void write(logger& l, const std::string& data) {
      l.log(data);
    }    
};

class log_user1:public log_user {};

class log_user2:public log_user{};

int main() {

  const std::string logfile{"logfile.log"};
  logger& logger = logger::get(logfile);

  log_user1 l1, l2;

  l1.write(logger, "log_user1 start\n");
  l2.write(logger, "log_user2 start\n");

  l1.write(logger, "log_user1 end\n");
  l2.write(logger, "log_user2 end\n");

  return 0;
}
