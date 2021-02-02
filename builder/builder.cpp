#include <string>
#include <memory>
#include <iostream>

// product
class Cellphone {
  public:
    void setScreen(const std::string& s) {
      screen = s;
    }
    void setProcessor(const std::string p) {
      processor = p;
    }
    void setBody(const std::string& b) {
      body = b;
    }
    friend std::ostream& operator<<(std::ostream& os, const Cellphone& c) {
      os << "screen: "  << c.screen 
	<< " processor " << c.processor
	<< " body " << c.body << '\n';
      return os;
    }
  private:
    std::string screen;
    std::string processor;
    std::string body;
};

class CellphoneBuilder {
  public:
    CellphoneBuilder(){}
    virtual ~CellphoneBuilder() {}

    void createPhoneBuilder() {
      phone = std::make_unique<Cellphone>();
    }
    const Cellphone* getPhone() {
      return phone.get();
    }

    virtual void buildScreen() = 0;
    virtual void buildProcessor() = 0;
    virtual void buildBody() = 0;

  protected:
    std::unique_ptr<Cellphone> phone;
};


class IphoneBuilder : public CellphoneBuilder {
  public:
    ~IphoneBuilder() override = default; 
    virtual void buildScreen() override {
      phone->setScreen("glass");
    }
    virtual void buildProcessor() override {
      phone->setProcessor("ARM");
    }
    virtual void buildBody() override {
      phone->setBody("aluminium");
    }
};


class BuildPhone {
  public:
    void build(CellphoneBuilder* pbuilder) {
      builder = pbuilder;
      builder->buildScreen();
      builder->buildProcessor();
      builder->buildBody();
    }
  private:
    CellphoneBuilder* builder; 
};


int main() {
  BuildPhone bp;
  IphoneBuilder iphone;
  bp.build(&iphone);
  return 0;
}
