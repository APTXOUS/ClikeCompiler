CC = g++
RM = rm -rf

DBG_ENABLE   = 1
SRC_PATH   := .

SRCS         += $(wildcard $(SRC_PATH)/*.cpp)
OBJS        := $(SRCS:.cpp=.o)
TARGET     := $(SRCS:.cpp= )

LIBS := pthread
INCLUDE_PATH := .
LIBRARY_PATH := /lib
ifeq (1, ${DBG_ENABLE}) 
	CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
endif

CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

all: clean build
build:
	$(CC) -c $(CFLAGS) $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	$(RM) $(OBJS)

clean:
	$(RM) $(OBJS) $(TARGET)