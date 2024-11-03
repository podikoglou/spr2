#include "libspr2/vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_VAL 0
#define MAX_VAL 8

#define MIN_ADDR 0
#define MAX_ADDR VM_MEMORY

#define BUF_SIZE 12

int randr(int min, int max) { return rand() % (max - min + 1) + min; }

int main(int argc, char **argv) {
  // seed rng
  srand(time(NULL));

  char buf[BUF_SIZE];

  for (;;) {
    // get random opcode
    int opcode = randr(1, 4);
    spr2_op op = {.opcode = opcode};

    // get random operands depending on opcode
    switch (opcode) {
    case OP_LOAD:
      op.operands.value = randr(MIN_VAL, MAX_VAL);
      break;
    case OP_INC:
      op.operands.addr1 = randr(MIN_ADDR, MAX_ADDR);
      break;
    case OP_SWAP:
    case OP_XOR:
      op.operands.addr1 = randr(MIN_ADDR, MAX_ADDR);
      op.operands.addr2 = randr(MIN_ADDR, MAX_ADDR);
      break;
    default:
      return -1;
    }

    // encode opcode to string
    spr2_op_encode(op, buf, BUF_SIZE);

    puts(buf);
  }

  return 0;
}
