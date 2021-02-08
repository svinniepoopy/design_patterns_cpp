#include <iostream>
#include <memory>

class Printer {
  public:
    virtual ~Printer() {
      std::cout << "~Printer" << std::endl;
    }

    virtual void print() = 0;
};


class PrinterTypeA : public Printer {
  public:
    void print() {
      std::cout << "Type A printing...\n";
    }
};

class ProxyPrinter : public Printer {
  public:
    ProxyPrinter(int user_id):id{user_id} {}

    void print() {
      if (isValidPersonnelId(id)) {
	printer->print();
      } else {
	std::cout << "Check id and try again...\n"; 
      }
    }

  private:

    bool isValidPersonnelId(int id) {
      return id>=5 && id<=10;
    }

    int id;
    std::unique_ptr<Printer> printer = std::make_unique<PrinterTypeA>();
};

int main() {
  
  std::unique_ptr<Printer> p = std::make_unique<ProxyPrinter>(2);
  p->print();

  p = std::make_unique<ProxyPrinter>(7);
  p->print();

  return 0;
}
