#include "controller.h"
#include "gui.h"

void Controller::get_input() {
  int input = get_char();
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

void Controller::draw() {
  clear_screen();

  print_clock(clock / 4);
  print_instruction(toy->get_command().raw);
  print_status(toy->get_state());
  print_registers(toy->get_registers());
  print_memory(toy->get_memory(), toy->get_pc());

  // gui->update_screen(); /// TODO: getchar тоже вызывает апдейт
}

bool Controller::is_alive() {
  get_input();
  if (state == STOP) {
    return false;
  }
  return true;
}

void Controller::do_it() {
  if (state == PAUSE) {
    draw();
    return;
  }

  if (state == NEXT)
    state = PAUSE;

  if (state == SHOW_HELP) {
    show_help();
    state = PAUSE;
    return;
  }

  toy->exec();
  draw();
  clock++;
}
