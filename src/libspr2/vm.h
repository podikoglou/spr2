#ifndef __SPR2_VM_H
#define __SPR2_VM_H

#include <stddef.h>

/* opcodes of the oprations */
#define OP_LOAD 0x01
#define OP_INC 0x02
#define OP_SWAP 0x03
#define OP_XOR 0x04

/* size of the VM, in bytes */
#define VM_MEMORY 32

/* an address, which is basically the index in the memory array */
typedef size_t spr2_address;

/* an operation, containing its opcode and its operands */
typedef struct {
  int opcode;

  union {
    /* these are used for operations involving an action between two locations
     * in the memory, such as SWAP and XOR. */
    spr2_address addr1, addr2;

    /* this is used for operations involving a single value, such as LOAD and
     * INC */
    unsigned char value;
  } operands;
} spr2_op;

/* the vm struct itself, simply containing the memory */
typedef struct {
  unsigned char memory[VM_MEMORY];
} spr2_vm;

void spr2_vm_init(spr2_vm *vm);
void spr2_vm_reset(spr2_vm *vm);
int spr2_vm_exec(spr2_vm *vm, const spr2_op operation);

/* NOTE: A good buffer size for an instruction is 11 chars,
         but it ultimately depends on VM_MEMORY. */

int spr2_op_decode(const char *buf, const spr2_op operation);
int spr2_op_encode(const spr2_op operation, char *buf, size_t buf_size);

#endif
