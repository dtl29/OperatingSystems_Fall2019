dd if=/dev/zero of=floppya.img bs=512 count=2880
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
bcc -ansi -c -o kernel.o kernel.c
ld86 -o kernel -d kernel.o kasm.o
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc

dd if=fib of=floppya.img bs=512 count=1 seek=30 conv=notrunc

echo "c" | bochs -f bdos.txt
