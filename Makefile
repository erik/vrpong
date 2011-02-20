CC := g++

IFLAGS  := -Iinclude/
CFLAGS  := -Wall -Wextra -Wno-unused-parameter `pkg-config opencv --cflags`
DFLAGS  := -g -DDEBUG
LNFLAGS := `pkg-config opencv --libs`

EXE     := vrpong

SRC := $(shell find 'src' -name '*.cpp')
OBJ := $(SRC:.cpp=.o)

.SUFFIXES = .cpp

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(IFLAGS) $(LNFLAGS) -o$(EXE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

debug:
	@$(MAKE) $(MFLAGS) CFLAGS="$(CFLAGS) $(DFLAGS)"
