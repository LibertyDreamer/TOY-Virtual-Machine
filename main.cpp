#include "gui.h"
#include "toy.h"
#include <unordered_map>

class Controller {
  Toy *toy;
  GUI *gui;

  uint64_t clock;

  enum State : char {
    STOP = 's',
    RUN = 'r',
    PAUSE = 'p',
    NEXT = 'n',
    SHOW_HELP = 'h',
  } state;

  void get_input() {
    int input = gui->get_char();
    switch (input) {
    case 's':
      state = STOP;
      break;
    case 'r':
      state = RUN;
      break;
    case 'p':
      state = PAUSE;
      break;
    case 'n':
      state = NEXT;
      break;
    case 'h':
      state = SHOW_HELP;
      break;
    default:
      break;
    }
  }

  void draw() {
    gui->clear_screen();

    gui->print_clock(clock / 4);
    gui->print_instruction(toy->get_command().raw);
    gui->print_status(toy->get_state());
    gui->print_registers(toy->get_registers());
    gui->print_memory(toy->get_memory(), toy->get_pc());

    // gui->update_screen(); /// TODO: getchar тоже вызывает апдейт
  }

public:
  Controller(Toy *toy, GUI *gui) : toy(toy), gui(gui), clock(0), state(PAUSE) {}

  bool is_alive() {
    get_input();
    if (state == STOP) {
      return false;
    }
    return true;
  }

  void do_it() {
    if (state == PAUSE) {
      draw();
      return;
    }

    if (state == NEXT)
      state = PAUSE;

    if (state == SHOW_HELP) {
      gui->show_help();
      state = PAUSE;
      return;
    }

    toy->exec();
    draw();
    clock++;
  }
};

int main() {
  Toy toy;
  GUI gui;

  toy.load_memory_dump("dump.txt");

  Controller controller(&toy, &gui);

  while (controller.is_alive()) {
    controller.do_it();
  }

  return 0;
}
