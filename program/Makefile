ASM = skyasm
SRC = program.asm
OUT = program.bin

all: $(OUT)

$(OUT): $(SRC)
	$(ASM) -src $(SRC) -out $(OUT)

clean:
	rm -f $(OUT)
