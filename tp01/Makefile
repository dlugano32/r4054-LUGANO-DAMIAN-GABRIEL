CHAIN=arm-linux-gnueabihf
CFLAGS=-std=gnu99 -Wall -mcpu=cortex-a8
VM=qemu-system-arm
BOARD=realview-pb-a8
VMFLGS=-M $(BOARD) -m 32M -no-reboot -nographic -monitor telnet:127.0.0.1:1234,server,nowait

OBJ=obj
BIN=bin
INC=inc
SRC=src
LST=lst

#nombre del archivo .c o .s y su .o
STARTFS=suma_abi
STARTFC=suma_c

#nombre del .elf y .bin para el .c y .s
BINF=mi_suma

all: $(BIN)/$(BINF).bin $(OBJ)/$(BINF).elf

$(BIN)/$(BINF).bin: $(OBJ)/$(BINF).elf
	$(CHAIN)-objcopy -O binary $< $@


$(OBJ)/$(BINF).elf: $(OBJ)/$(STARTFS).o $(OBJ)/$(STARTFC).o
	@echo "Linkeando ... "
	mkdir -p obj
	mkdir -p lst
	#$(CHAIN)-ld $(OBJ)/*.o -o $(OBJ)/$(BINF).elf -Map $(LST)/$(BINF).map
	$(CHAIN)-ld -T memmap.ld $(OBJ)/*.o -o $(OBJ)/$(BINF).elf -Map $(LST)/$(BINF).map
	@echo "Linkeo finalizado!"
	@echo ""
	@echo "Generando archivos de información: mapa de memoria y símbolos"
	readelf -a $(OBJ)/$(BINF).elf >>$(LST)/$(BINF)_elf.txt
	$(CHAIN)-objdump -D $(OBJ)/$(BINF).elf >>$(LST)/$(BINF).lst

$(OBJ)/$(STARTFS).o: $(SRC)/$(STARTFS).s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst
	@echo "Ensamblando..."
	$(CHAIN)-as $(SRC)/$(STARTFS).s -o $(OBJ)/$(STARTFS).o

$(OBJ)/$(STARTFC).o: $(SRC)/$(STARTFC).c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst
	@echo "Compilando ..."
	$(CHAIN)-gcc -O3 $(CFLAGS) -c $(SRC)/$(STARTFC).c -o $(OBJ)/$(STARTFC).o

run:
	$(VM) $(VMFLGS) -kernel $(BIN)/$(BINF).bin -S -gdb tcp::2159
	
clean:
	rm -rf $(OBJ)/*.o
	rm -rf $(OBJ)/*.elf
	rm -rf $(BIN)/*.bin
	rm -rf $(LST)/*.lst
	rm -rf $(LST)/*.txt
	rm -rf $(LST)/*.map



