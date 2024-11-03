#include "vm.h"
#include <stdio.h>

void spr2_vm_init(spr2_vm *vm) { spr2_vm_reset(vm); }

void spr2_vm_reset(spr2_vm *vm) {
  for (int i = 0; i < VM_MEMORY; i++) {
    vm->memory[i] = 0;
  }
}

int spr2_vm_exec(spr2_vm *vm, const spr2_op operation) {
  switch (operation.opcode) {
  case OP_LOAD: {
    vm->memory[0] = operation.operands.value;
    break;
  }

  case OP_INC: {
    vm->memory[operation.operands.addr1]++;
    break;
  }

  case OP_SWAP: {
    const unsigned char temp = vm->memory[operation.operands.addr1];

    vm->memory[operation.operands.addr1] = vm->memory[operation.operands.addr2];
    vm->memory[operation.operands.addr2] = temp;

    break;
  };

  case OP_XOR:
    vm->memory[operation.operands.addr1] =
        vm->memory[operation.operands.addr1] ^
        vm->memory[operation.operands.addr1];

    break;

  default:
    return -1;
  }

  return 0;
}

int spr2_op_decode(const char *buf, const spr2_op operation) { return -1; }

int spr2_op_encode(const spr2_op operation, char *buf, size_t buf_size) {
  switch (operation.opcode) {
  case OP_LOAD:
    snprintf(buf, buf_size, "LOAD %d", operation.operands.value);
    break;
  case OP_INC:
    snprintf(buf, buf_size, "INC %zu", operation.operands.addr1);
    break;
  case OP_SWAP:
    snprintf(buf, buf_size, "SWAP %zu %zu", operation.operands.addr1,
             operation.operands.addr2);
    break;
  case OP_XOR:
    snprintf(buf, buf_size, "XOR %zu %zu", operation.operands.addr1,
             operation.operands.addr2);
    break;
  default:
    return -1;
  }
  return 0;
}
