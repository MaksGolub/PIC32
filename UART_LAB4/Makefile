TARGET := main
DEPS:= UART init
MCU := 32MZ2048ECG100

MDB := mdb -l OFF
MDBSCRIPT := mdbscript.txt
CC = xc32-gcc -mprocessor=$(MCU)
CFLAGS = -O2 -std=gnu11
# not c11 
.PHONY: all size flash clean compile hex

compile: $(TARGET).c
	$(CC) $(CFLAGS) $(addsuffix .c,$(DEPS)) $< -o $(subst .c,.elf,$<)
	
	
hex: $(TARGET:=.elf)	
## create .hex file
	xc32-bin2hex $< 

# objcopy --change-address 0xE0000 -O ihex $(TARGET).elf $(TARGET).hex

all: | clean compile size hex flash 

size: $(TARGET).elf
	@echo -en "\n\e[38;5;82m"
	@echo -e "** Size of the resulting sections:"
	xc32-size -Bd $<
	@echo -en "\n\e[39m"



# Be ready to give an answer on what happens here and below
.ONESHELL:
flash: 
	@cat <<- EOF > $(MDBSCRIPT)
	device PIC$(MCU)
	set programoptions.eraseb4program true
	set poweroptions.powerenable false
	hwtool PICkit3 -p
	program $(TARGET).hex
	reset MCLR
	quit
	EOF
	$(MDB) $(MDBSCRIPT)
clean:
	@echo Cleaning up...
	rm -f $(MDBSCRIPT) $(TARGET).hex $(TARGET).elf $(TARGET) ...add more here...
