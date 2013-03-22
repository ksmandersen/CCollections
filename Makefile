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
TEST_FILES=src/tests/test_${TEST}.c src/tests/runners/runner_${TEST}.c

ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q build\* && del /F /Q $(TARGET)
else
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET)
endif

all: clean documentation test

documentation:
	doxygen Doxyfile

test:
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) ${TEST_FILES} -o $(TARGET)
	./$(TARGET)

clean:
	$(CLEANUP)