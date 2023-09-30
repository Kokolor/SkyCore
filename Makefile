CXX = g++
INCLUDE_DIR = /usr/local/systemc-2.3.3/include
LIB_DIR = /usr/local/systemc-2.3.3/lib-linux64
SRC = testbench.cpp
OUT = testbench
LIBS = -lsystemc

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o $(OUT) $(SRC) $(LIBS)
	make -C program
	cp program/program.bin .

run: $(OUT)
	./$(OUT)

clean:
	make -C program clean
	rm program.bin
	rm -f $(OUT)
