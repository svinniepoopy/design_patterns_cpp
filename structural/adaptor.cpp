#include <algorithm>
#include <vector>
#include <cassert>
#include <iterator>
#include <iostream>
#include <stdexcept>

/*
 *  Create an Adapter for this class such that you can apply the STL 
 *  algorithm for_each( ) to the elements of the TStack, using your 
 *  adapter. Create a TStack of string, fill it with strings and use 
 *  for_each( ) to count all the letters in all the strings in the TStack.
 */

template<class T>
class StackTemplate {
public:
  StackTemplate(int sz=100) : sz{sz}, pos{-1} {
    stack = new T[sz];
  }

  ~StackTemplate() {
    delete[] stack;
  }

  void push(const T& val) {
    if (pos < sz) {
      stack[++pos] = val;
    }
  }

  T top() {
    try {
      if (empty()) {
	throw std::runtime_error{"stack empty"};
      }

    } catch (const std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }
    return stack[pos--];
  }

  void pop() {
    if (!empty()) {
      pos = pos-1;
    }
  }

  bool empty() { return pos==-1; } 
  int size() const { return pos+1; }

  friend class iterator;
  class iterator : public std::iterator<std::input_iterator_tag, StackTemplate<T>> {
    private:
      StackTemplate<T>& st;
      int start_pos;
    public:
      // using value_type = int;
      iterator(StackTemplate<T>& t, int start):
	st{t}, start_pos{start} {}
      bool operator==(const iterator& o) const {
	return st.stack[start_pos] == o.st.stack[o.st.pos+1]; 
      }
      bool operator!=(const iterator& o) const {
	return !(*this == o);
      }
      T operator*() const {
	// std::cout << st.stack[start_pos] << '\n';
	return st.stack[start_pos];
      }
      iterator& operator++() {
	++start_pos;
	return *this;
      }
  };

  iterator begin() {
    return iterator(*this, 0);
  }

  iterator end() {
    return iterator(*this, pos+1);
  }


private:
  int sz;
  int pos; 
  T* stack;
};


void test_stack() {
  {
    StackTemplate<int> stk;
    assert(stk.empty());
    assert(stk.size()==0);
  }
  {
    StackTemplate<int> stk{3};
    assert(stk.empty());
    stk.push(1);
    assert(!stk.empty());
    stk.push(2);
    assert(!stk.empty());
    stk.push(3);
    assert(stk.size() == 3);
  }
  {
    try {
      StackTemplate<int> stk;
      int val = stk.top();
    } catch (const std::runtime_error& e){
      std::cout << "Error: " << e.what() << '\n';
    }
  }
}

struct CharCounter {
  CharCounter():count{0}{}
  void operator()(const std::string& s) {
    count += s.size();
  }
  int count;
};

void test_for_each() {
  StackTemplate<std::string> stk;
  std::vector<std::string> A{"abc", "def", "def", "blahblah"};
  for (auto& s:A) {
    stk.push(s);
  }
  CharCounter c;
  auto cc = std::for_each(stk.begin(), stk.end(), CharCounter());
  auto cc2 = std::for_each(A.begin(), A.end(), CharCounter());
  assert(cc.count == cc2.count);
}

int main() {
  // test_stack();
  test_for_each();
  return 0;
}
