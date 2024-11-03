#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        vm->memory[operation.operands.addr2];

    break;

  default:
    return -1;
  }

  return 0;
}

int spr2_op_parse(const char *str, int *opcode) {
  if (strcmp(str, "LOAD") == 0) {
    *opcode = OP_LOAD;
    return 0;
  }

  if (strcmp(str, "INC") == 0) {
    *opcode = OP_INC;
    return 0;
  }

  if (strcmp(str, "SWAP") == 0) {
    *opcode = OP_SWAP;
    return 0;
  }

  if (strcmp(str, "XOR") == 0) {
    *opcode = OP_XOR;
    return 0;
  }

  return -1;
}

int spr2_address_parse(const char *str, size_t *addr) {
  int parsed = atoi(str);

  if (parsed < 0)
    return -1;

  if (parsed > VM_MEMORY - 1)
    return -1;

  *addr = (size_t)parsed;

  return 0;
}

int spr2_value_parse(const char *str, unsigned char *addr) {
  int parsed = atoi(str);

  if (parsed < 0)
    return -1;

  if (parsed > 256)
    return -1;

  *addr = (size_t)parsed;

  return 0;
}

int spr2_load_op_parse(const char *str, spr2_op *operation) {
  char *value_str = strtok(NULL, " ");
  unsigned char value;

  if (spr2_value_parse(value_str, &value) != 0) {
    return -1;
  }

  operation->opcode = OP_LOAD;
  operation->operands.value = value;

  return 0;
}

int spr2_inc_op_parse(const char *str, spr2_op *operation) {
  char *addr_str = strtok(NULL, "");
  size_t addr;

  if (spr2_address_parse(addr_str, &addr) != 0) {
    return -1;
  }

  operation->opcode = OP_INC;
  operation->operands.addr1 = addr;

  return 0;
}

int spr2_swap_op_parse(const char *str, spr2_op *operation) {
  /* parse address 1 */
  char *addr1_str = strtok(NULL, " ");
  size_t addr1;

  if (spr2_address_parse(addr1_str, &addr1) != 0) {
    return -1;
  }

  /* parse address 2 */
  char *addr2_str = strtok(NULL, " ");
  size_t addr2;

  if (spr2_address_parse(addr2_str, &addr2) != 0) {
    return -1;
  }

  operation->opcode = OP_SWAP;
  operation->operands.addr1 = addr1;
  operation->operands.addr2 = addr2;

  return 0;
}

int spr2_xor_op_parse(const char *str, spr2_op *operation) {
  /* parse address 1 */
  char *addr1_str = strtok(NULL, " ");
  size_t addr1;

  if (spr2_address_parse(addr1_str, &addr1) != 0) {
    return -1;
  }

  /* parse address 2 */
  char *addr2_str = strtok(NULL, " ");
  size_t addr2;

  if (spr2_address_parse(addr2_str, &addr2) != 0) {
    return -1;
  }

  operation->opcode = OP_XOR;
  operation->operands.addr1 = addr1;
  operation->operands.addr2 = addr2;

  return 0;
}

int spr2_op_decode(char *buf, spr2_op *operation) {
  /* parse opcode */
  char *op_name = strtok(buf, " ");
  int opcode;

  if (spr2_op_parse(op_name, &opcode) != 0) {
    return -1;
  }

  /* parse operands of the operation */
  switch (opcode) {
  case OP_LOAD:
    return spr2_load_op_parse(buf, operation);
  case OP_INC:
    return spr2_inc_op_parse(buf, operation);
  case OP_SWAP:
    return spr2_swap_op_parse(buf, operation);
  case OP_XOR:
    return spr2_xor_op_parse(buf, operation);
  }

  return -1;
}

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
