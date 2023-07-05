sudo rmmod intel_ips
####################

if [ $1 ]
then
	cd obj_plgn/
	sudo make
	cd ..
	gcc -c obj.c -o obj.ko -Wno-implicit-function-declaration -fplugin=./obj_plgn/plugin.so
	objcopy --remove-section .bss --remove-section .strtab --remove-section .shstrtab --remove-section .comment --remove-section .note.GNU-stack --remove-section .note.gnu.property --remove-section .eh_frame obj.ko
else
	gcc -c obj.c -o obj.ko -Wno-implicit-function-declaration
	objcopy --remove-section .bss --remove-section .strtab --remove-section .shstrtab --remove-section .comment --remove-section .note.GNU-stack --remove-section .note.gnu.property --remove-section .eh_frame obj.ko
fi
####################

if [ $2 ]
then
	sudo insmod obj.ko
	sudo rmmod  obj.ko
fi
