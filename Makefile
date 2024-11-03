# compiler settings
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -I./include
LDFLAGS = -L$(OUT_DIR) -lspr2

SRC_DIR = src
INC_DIR = include
OUT_DIR = build

# libspr2
LIB_SRCS = $(wildcard $(SRC_DIR)/libspr2/*.c)
LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/libspr2/%.c=$(OUT_DIR)/libspr2/%.o)

# executables
RUN_SRCS = src/run.c
RAND_SRCS = src/rand.c
OPTIMIZE_SRCS = src/optimize.c

RUN_OBJS = $(RUN_SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
RAND_OBJS = $(RAND_SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
OPTIMIZE_OBJS = $(OPTIMIZE_SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

all: dirs $(OUT_DIR)/spr2-run $(OUT_DIR)/spr2-rand $(OUT_DIR)/spr2-optimize

dirs:
	mkdir -p $(OUT_DIR)/libspr2

# libspr2
$(OUT_DIR)/libspr2.a: $(LIB_OBJS)
	ar rcs $@ $^

# executables
$(OUT_DIR)/spr2-run: $(RUN_OBJS) $(OUT_DIR)/libspr2.a
	$(CC) $(RUN_OBJS) -o $@ $(LDFLAGS)

$(OUT_DIR)/spr2-rand: $(RAND_OBJS) $(OUT_DIR)/libspr2.a
	$(CC) $(RAND_OBJS) -o $@ $(LDFLAGS)

$(OUT_DIR)/spr2-optimize: $(OPTIMIZE_OBJS) $(OUT_DIR)/libspr2.a
	$(CC) $(OPTIMIZE_OBJS) -o $@ $(LDFLAGS)

# object files
$(OUT_DIR)/libspr2/%.o: $(SRC_DIR)/libspr2/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OUT_DIR)

.PHONY: all clean dirs
