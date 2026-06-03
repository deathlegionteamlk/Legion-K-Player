CXX = g++
CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
LDFLAGS_WIN = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows

SRC = src/main.cpp src/KEngine.cpp src/UI.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = Legion-K-Player-Bin
TARGET_WIN = Legion-K-Player.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

win: $(SRC)
	$(CXX_WIN) $(CXXFLAGS) -o $(TARGET_WIN) $^ $(LDFLAGS_WIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET_WIN)
