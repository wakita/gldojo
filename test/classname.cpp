#include <iostream>
#include <typeinfo>

class ClassName {
  public:
    ClassName() {
      // std::cout << typeid(this) << std::endl;
    }
};

int main() {
  ClassName cn();
  return 0;
}
