#include "logfile.h"

std::ofstream& logfile() {
  static std::ofstream ofs{"logfile.log"};
  return ofs;
}

