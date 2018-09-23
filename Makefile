CC       = g++
CFLAGS   = -g -std=gnu++0x -Wall -Wno-reorder #-std=gnu++0x 

LFLAGS = -lSDL2 -lSDL2_image

SRC_DIRS ?= ./src
BUILD_DIR ?= ./objs
HEAD_DIR ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS  := $(SRCS:$(SRC_DIRS)/%.cpp=$(BUILD_DIR)/%.o)
INCLUDES := $(wildcard $(SRC_DIRS)/*.h)

HEADERS = $(shell find $(HEAD_DIR) -name *.hpp)

MAIN = Contra

MKDIR_P ?= mkdir -p

$(BUILD_DIR)/$(MAIN): ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LFLAGS} -o ${MAIN}

$(OBJS): $(BUILD_DIR)/%.o : $(SRC_DIRS)/%.cpp
#$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	${CC} $(LFLAGS) ${CFLAGS} -c $< -o $@

all: ${MAIN}
	@echo   Simple compiler named Contra has been compiled

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

