#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <inttypes.h>

class Controller {
  class Toy *toy;

  uint64_t clock;

  enum State : char {
    STOP = 's',
    RUN = 'r',
    PAUSE = 'p',
    NEXT = 'n',
    SHOW_HELP = 'h',
  } state;

  void get_input();

  void draw();

public:
  Controller(Toy *toy) : toy(toy), clock(0), state(PAUSE) {}

  bool is_alive();

  void do_it();
};

#endif // CONTROLLER_H
