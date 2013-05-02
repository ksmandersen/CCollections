C_COMPILER=clang
TARGET_BASE=build/test
ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION=.exe
else
	TARGET_EXTENSION=.out
endif
TARGET = $(TARGET_BASE)$(TARGET_EXTENSION)
SRC_FILES=src/lib/unity/src/unity.c  src/ccollections/**/*.c
INC_DIRS=-Isrc/ccollections
SYMBOLS=-DTEST -lgc

ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q build\* && del /F /Q $(TARGET)
else
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET)
endif

all: clean documentation test

documentation:
	doxygen Doxyfile

test:
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) src/tests/test_*.c src/tests/runners/runner_all.c -o $(TARGET)
	./$(TARGET)

clean:
	$(CLEANUP)