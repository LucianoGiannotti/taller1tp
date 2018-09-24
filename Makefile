CC       = g++
CFLAGS   = -g -std=c++14 -Wall -Wno-reorder  #-std=gnu++0x 

LFLAGS = -lSDL2 -lSDL2_image

SRC_DIR ?= src
BUILD_DIR ?= objs


SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS  := $(SRCS:$(SRC_DIRS)/%.cpp=$(BUILD_DIR)/%.o)
#INCLUDES := $(shell find $(SRC_DIR) -name *.h) #$(wildcard $(SRC_DIR)/*.h)

#CPPFLAGS ?= -I $(INCLUDES)

MAIN = Contra

$(BUILD_DIR)/$(MAIN): ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LFLAGS} -o ${MAIN}


all: ${MAIN}
	@echo   Simple compiler named Contra has been compiled

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
