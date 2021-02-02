#include <iostream>
#include <string>

class CookieFactory {
  public:
    CookieFactory()=delete;
    CookieFactory(const std::string& t):type{t}{}
    void setDomain(const std::string& d) {
      domain = d;
    }
    std::string getDomain() const {
      return domain;
    }
    virtual ~CookieFactory() {}
    
    std::string cookieType() const {
      return type;
    }
  private:
    std::string type;
    std::string domain;    
};

class SessionCookie : public CookieFactory {
  public:
    SessionCookie():CookieFactory{"session-cookie"}{}
};

class SecureCookie : public CookieFactory {
  public:
    SecureCookie():CookieFactory{"secure-cookie"}{}
};

class CookieEnv {
  public:
    CookieEnv(CookieFactory* factory):
      cookie{factory} {
    }
    std::string getType() const {
      return cookie->cookieType();
    }
    ~CookieEnv() {
      delete cookie;
    }
  private:
    CookieFactory* cookie;
};

int main() {
  
  CookieEnv env1{new SessionCookie},
	     env2{new SecureCookie};

  std::cout << env1.getType() << '\n';
  std::cout << env2.getType() << '\n';
 
  return 0;
}
