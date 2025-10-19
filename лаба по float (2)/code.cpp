#include <iostream>

union float_unsigned {
  unsigned Unsigned;
  float Float;
};

void print_binary(unsigned value) {
  auto mask = 1u << 31;
  unsigned n;
  for (auto i = 1u; i <= 32u; i++) {
    std::cout << ((value & mask) != 0);
    mask = mask >> 1;
    if (i % 4 == 0)
      std::cout << ' ';
    if (i % 8 == 0)
      std::cout << ' ';
  }
  std::cout << std::endl;
}

void overflow_mantissa() {
  float_unsigned n;
  n.Float = 10.0;
  for (int i = 0; i < 20; i++) {
    std::cout << "десятичное: " << n.Float << ", двоичное: ";
    print_binary(n.Unsigned);
    std::cout << std::endl;
    n.Float *= 10;
  }
}

void infinite_cycle() {
  float_unsigned n;
  n.Float = 10'000'000.0;
  for (float i = 0; i < 6777230; i++) {
    n.Float += 1;
    std::cout << "десятичное: " << n.Float << ", двоичное: ";
    print_binary(n.Unsigned);
  }
}

int main() {
  /*unsigned n;
  std::cin >> n;
  print_binary(n);*/

  /*float_unsigned fu;
  std::cin >> fu.Float;
  print_binary(fu.Unsigned);*/

  /*std::cout << std::fixed;
  std::cout.precision(2);
  overflow_mantissa();*/

  std::cout << std::fixed;
  std::cout.precision(2);
  infinite_cycle();
}
