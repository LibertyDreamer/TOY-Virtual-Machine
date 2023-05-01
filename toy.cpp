#include "toy.h"

void Toy::fetch() {
  ir_.raw = memory_[pc_];
  state_ = INCREMENT;
}

void Toy::increment() {
  pc_++;
  state_ = EXECUTE;
}

void Toy::execute() {
#define d ir_.rr.destination
#define s ir_.rr.source_s
#define t ir_.rr.source_t
#define addr ir_.a.address
#define R registers_
#define mem memory_
  // clang-format off
    switch (ir_.a.opcode) {
    case  0: pc_--;                       break;    // halt
    case  1: R[d] = R[s] +  R[t];         break;    // add
    case  2: R[d] = R[s] -  R[t];         break;    // subtract
    case  3: R[d] = R[s] &  R[t];         break;    // bitwise and
    case  4: R[d] = R[s] ^  R[t];         break;    // bitwise xor
    case  5: R[d] = R[s] << R[t];         break;    // shift left
    case  6: R[d] = R[s] >> R[t];         break;    // shift right
    case  7: R[d] = addr;                 break;    // load address
    case  8: R[d] = mem[addr];            break;    // load
    case  9: mem[addr] = R[d];            break;    // store
    case 10: R[d] = mem[R[t]];            break;    // load indirect
    case 11: mem[R[t]] = R[d];            break;    // store indirect
    case 12: if (R[d] == 0) pc_ = addr;   break;    // branch if zero
    case 13: if (R[d] > 0) pc_ = addr;    break;    // branch if positive
    case 14: pc_ = R[d];                  break;    // jump indirect
    case 15: R[d] = pc_; pc_ = addr;      break;    // jump and link
    }
  // clang-format on
  state_ = POST_EXECUTE;

#undef d
#undef s
#undef t
#undef t
#undef addr
#undef R
#undef mem
}

void Toy::post_execute() {
  registers_[0] = 0;
  state_ = FETCH;
}

Toy::Toy() { hard_reset(); }

void Toy::hard_reset() {
  pc_ = 0x10;
  std::memset(&memory_, 0, sizeof(memory_));
  std::memset(&registers_, 0, sizeof(registers_));
  ir_.raw = 0;
  state_ = FETCH;
}

std::array<uint16_t, 16> Toy::get_registers() { return registers_; }

std::array<uint16_t, 256> Toy::get_memory() { return memory_; }

Command Toy::get_command() { return ir_; }

uint8_t Toy::get_pc() { return pc_; }

ToyState Toy::get_state() { return state_; }

bool Toy::save_memory_dump(const std::string &path) const {
  std::ofstream file(path);

  if (!file.is_open())
    return false;

  uint16_t line = 0;
  for (auto &it : memory_) {
    file << std::hex << std::uppercase << line++ << ": " << std::hex
         << std::uppercase << it << std::endl;
  }

  return true;
}

bool Toy::load_memory_dump(const std::string &path) {
  std::ifstream file(path);

  if (!file.is_open())
    return false;

  uint16_t number;
  char ch;
  for (auto &it : memory_) {
    file >> std::hex >> number >> ch >> std::hex >> it;
  }

  return true;
}
