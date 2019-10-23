dd if=/dev/zero of=floppya.img bs=512 count=2880
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
bcc -ansi -c -o kernel.o kernel.c
ld86 -o kernel -d kernel.o kasm.o
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259
dd if=map of=floppya.img bs=512 count=1 seek=256 conv=notrunc
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc

bcc -ansi -c -o Shell.o Shell.c
as86 blackdos.asm -o basm.o
ld86 -o Shell -d Shell.o basm.o
dd if=Shell of=floppya.img bs=512 count=10 seek=30 conv=notrunc
