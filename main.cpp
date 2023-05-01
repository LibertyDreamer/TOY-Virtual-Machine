#include "controller.h"
#include "toy.h"

int main() {
  Toy toy;
  toy.load_memory_dump("dump.txt");

  Controller controller(&toy);

  while (controller.is_alive()) {
    controller.do_it();
  }

  return 0;
}
