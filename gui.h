#ifndef GUI_H
#define GUI_H
#include "toy.h"
#include <array>
#include <ncurses.h>
#include <string>
#include <unistd.h>

class InitNcurse {
public:
  WINDOW *win;

  InitNcurse() {
    win = initscr();
    halfdelay(1);
    noecho();
    curs_set(FALSE);
  }
  ~InitNcurse() { endwin(); }
} inline ncurse_init;

void print_status_counter(const int y_pos, const int x_pos);

void set_fetch_status();
void set_increment_status();
void set_execute_status();
void set_post_execute_status();

void print_clock(uint64_t clock);
void print_instruction(uint16_t cmd);
void print_status(ToyState state);
void print_registers(const std::array<uint16_t, 16> &registers);
void print_memory(const std::array<uint16_t, 256> &memory, uint8_t pc);

int get_char();

void update_screen();
void clear_screen();

void show_help();

#endif // GUI_H
