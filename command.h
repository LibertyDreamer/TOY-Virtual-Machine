#ifndef COMMAND_H
#define COMMAND_H
#include <inttypes.h>

struct RR {
  uint16_t source_t : 4;
  uint16_t source_s : 4;
  uint16_t destination : 4;
  uint16_t opcode : 4;
};

struct A {
  uint16_t address : 8;
  uint16_t destination : 4;
  uint16_t opcode : 4;
};

union Command {
  uint16_t raw;
  RR rr;
  A a;
};

#endif // COMMAND_H
