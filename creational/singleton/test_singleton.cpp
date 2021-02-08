#include "singleton.h"

#include <iostream>

class mysingleton : public singleton<mysingleton> {
  private:
    int v;
  protected:
    friend class singleton<mysingleton>;
    mysingleton():v{0}{}
  public:
    void setValue(int x) {
      v = x;
    }

    int getValue() const {
      return v;
    }
};

int main() {
  mysingleton& m = mysingleton::get();
  std::cout << m.getValue() << '\n';
  m.setValue(1);
  std::cout << m.getValue() << '\n';

  return 0;
}
