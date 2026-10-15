CPPFLAGS = -Wall -I/usr/local/include -I/run/media/rober/T7/UI_2/include
CFLAGS = -Wall
LDFLAGS = -lglfw -lGL -ldl -lpthread

SRCDIR := source
BUILDDIR := build

SRC_FILES_PP := $(wildcard $(SRCDIR)/*.cpp)
SRC_FILES_C := $(wildcard $(SRCDIR)/*.c)

SRC := $(notdir $(SRC_FILES_PP))
SRC_C := $(notdir $(SRC_FILES_C))
BLD_PP := $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRC))
BLD_C := $(patsubst %.c, $(BUILDDIR)/%.o, $(SRC_C))
TARGET := UI_APP_LINUX


clean: 
	rm -f $(TARGET) $(BUILDDIR)/*.o
	
bear:
	bear -- make run

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(BLD_PP) $(BLD_C)
	g++ $(CPPFLAGS) $(BLD_PP) $(BLD_C) -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	g++ $(CPPFLAGS) -c $< -o $@ $(CPPFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	gcc $(CFLAGS) -c $< -o $@ $(CFLAGS)

.PHONY: run clean bear