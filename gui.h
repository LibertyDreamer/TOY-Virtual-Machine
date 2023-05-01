#ifndef GUI_H
#define GUI_H
#include "toy.h"
#include <array>
#include <ncurses.h>
#include <string>
#include <unistd.h>

class GUI {
  WINDOW *win;
  int x, y;

  void print_status_counter(const int y_pos, const int x_pos) {
    printw("--------------STATUS COUNTER---------------\n");
    printw(" FETCH \n");
    printw(" INCREMENT \n");
    printw(" EXECUTE \n");
    printw(" POST EXECUTE \n\n");

    getyx(win, y, x);

    move(y_pos, x_pos);
    printw("<-");
    move(y, x);
  }

  void set_fetch_status() { print_status_counter(7, 7); }
  void set_increment_status() { print_status_counter(8, 11); }
  void set_execute_status() { print_status_counter(9, 9); }
  void set_post_execute_status() { print_status_counter(10, 14); }

public:
  GUI() {
    win = initscr();
    halfdelay(1);
    nodelay(win, TRUE);
    noecho();
    curs_set(FALSE);
  }
  ~GUI() { endwin(); }

  void print_clock(uint64_t clock) {
    printw("-------------------CLOCK-------------------\n");
    printw(" CLOCK [%d]\n\n", clock);
  }
  void print_instruction(uint16_t cmd) {
    printw("----------------INSTRUCTION----------------\n");
    printw(" IR [ 0x%04X ]\n\n", cmd);
  }
  void print_status(ToyState state) {
    switch (state) {
    case FETCH:
      set_fetch_status();
      break;
    case INCREMENT:
      set_increment_status();
      break;
    case EXECUTE:
      set_execute_status();
      break;
    case POST_EXECUTE:
      set_post_execute_status();
      break;
    default:
      break;
    }
  }
  void print_registers(const std::array<uint16_t, 16> &registers) {
    printw("-----------------REGISTER------------------\n");

    for (uint8_t i = 0; i < 16; ++i) {
      printw(" R%X [ %016b ] ( 0x%04X )\n", i, registers[i], registers[i]);
    }

    printw("\n");
  }
  void print_memory(const std::array<uint16_t, 256> &memory, uint8_t pc) {
    printw("------------------MEMORY-------------------\n");

    for (int i = -2; i < 3; ++i) {
      printw(" [0x%02X] [ %016b ] ( 0x%04X )", pc + i, memory[pc + i],
             memory[pc + i]);
      if (i == 0)
        printw(" (PC) ");
      printw("\n");
    }
    printw("\n");

    printw(" [0x%02X] [ %016b ] ( 0x%04X )\n\n", 0xFF, memory[0xFF],
           memory[0xFF]);
    printw("-------------------------------------------\n");
  }

  int get_char() { return getch(); }

  void update_screen() { wrefresh(win); }
  void clear_screen() { wclear(win); }

  void show_help() {
    clear_screen();
    printw("-----------------HELP------------------\n");
    printw("n - go to the next command\n");
    printw("s - quit\n");
    printw("r - run\n");
    printw("h - this help\n");
    printw("p - pause\n");
    printw("press any button for exit\n");

    update_screen();
    getchar_unlocked();
  }
};

#endif // GUI_H
