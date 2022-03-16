# objcopy --only-keep-debug kernel.o kernel.sym
cp ./kernel/kernel/kernel.o ./gdb/
cp ./kernel/arch/i386/*.o ./gdb
cp ./sysroot/boot/myos.kernel ./gdb
cd ./gdb/
for file in ./*.o; do
    if [ -e "$file" ] ; then
        export newfile=$(basename -- $file .o) 
        export newfile=$newfile".sym"
        echo "Generating debug sym file for $file, saving as $newfile"
        objcopy --only-keep-debug "$file" "$newfile"
        rm $file
    fi
done
objcopy --only-keep-debug myos.kernel myos.sym
rm myos.kernel
cd ../
