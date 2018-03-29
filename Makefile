.PHONY: cm all mrproper clean

all: cm
	@cd build ;	make -s


cm:
	mkdir -p build
	cd build ; cmake .. -DCMAKE_TOOLCHAIN_FILE=CMakeModule/raspi_toolchain.cmake

ccm:
	@mkdir -p build
	@cd build ; ccmake .. -DCMAKE_TOOLCHAIN_FILE=CMakeModule/raspi_toolchain.cmake


mrproper:
	rm -rf build

clean: cm
	@cd build ; make -s clean

run: all
	qemu-system-arm -s -machine raspi2 -kernel build/TestRaspiOS -serial null -serial stdio -display none
dump: all
	arm-none-eabi-objdump -D build/TestRaspiOS

gdb: all
	arm-none-eabi-gdb -x scr.gdb
