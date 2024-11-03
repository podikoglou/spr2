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

  /* create VM */
  spr2_vm vm;
  spr2_vm_init(&vm);

  /* read input line by line, decoding along the way */
  char buffer[12];
  spr2_op op;

  while (fgets(buffer, 12, file)) {
    /* remove trailing whitespace  */
    buffer[strcspn(buffer, "\n")] = 0;

    /* decode operation */
    if (spr2_op_decode(buffer, &op) != 0)
      return -1;

    /* execute on VM */
    spr2_vm_exec(&vm, &op);
  }

  /* print VM memory */
  printf("[");

  for (int i = 0; i < VM_MEMORY; i++) {
    printf("%d", vm.memory[i]);

    if (i != VM_MEMORY - 1) {
      printf(", ");
    }
  }

  printf("]\n");

  return 0;
}
