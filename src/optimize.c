#include "libspr2/vm.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  /* open file or stdin */
  FILE *file = stdin;

  if (argc > 1) {
    if (strcmp(argv[1], "-") != 0) {
      file = fopen(argv[1], "r");

      if (file == NULL) {
        printf("error: couldn't read file %s\n", argv[1]);
        return -1;
      }
    }
  }

  /* create VM for the initial execution */
  spr2_vm vm;
  spr2_vm_init(&vm);

  /* read input line by line, decoding and execuing along the way */
  char buffer[12];
  spr2_op op;
  int ops_read = 0;

  while (fgets(buffer, 12, file)) {
    /* remove trailing whitespace  */
    buffer[strcspn(buffer, "\n")] = 0;

    /* decode operation */
    if (spr2_op_decode(buffer, &op) != 0)
      return -1;

    /* execute on VM */
    spr2_vm_exec(&vm, &op);

    ops_read++;
  }

  /* print VM memory */
  printf("Target Memory: [");

  for (int i = 0; i < VM_MEMORY; i++) {
    printf("%d", vm.memory[i]);

    if (i != VM_MEMORY - 1) {
      printf(", ");
    }
  }

  printf("]\n");

  /* generate all possible programs */
  int min_length = 2;
  int max_length = 8;

  int min_val = 1;
  int max_val = 12;

  for (int length = min_length; length < max_length; length++) {
  }

  return 0;
}
