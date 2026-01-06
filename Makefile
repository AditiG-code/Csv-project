	CXX = g++
CXXFLAGS = -std=c++17 -Wall
INC = -Iinclude

SRC = src/main.cpp \
      src/storage/CSVReader.cpp \
      src/lexer/Tokenizer.cpp

TARGET = csvsql

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o $(TARGET)

clean:
	rm -f $(TARGET)


