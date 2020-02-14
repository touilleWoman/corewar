TEST_EXE=./asm
ORIGINAL_EXE=./asm_zaz

find . -name "*.cor" -exec rm {} \;
rm error_file
touch error_file
if [ "$1" == "--leaks" -o "$1" == "-l" ]
then
	find . -name "*.s" -exec valgrind $TEST_EXE {}  \; 2>> error_file
else
	find . -name "*.s" -exec $TEST_EXE {}  \;
fi
# touch my_res
# find . -name "*.cor" -exec hexdump {} \; >> my_res
# find . -name "*.cor" -exec rm {} \;
# find . -name "*.s" -exec $ORIGINAL_EXE {} \;
# touch og_res
# find . -name "*.cor" -exec hexdump {} \; >> og_res
# if [ "$1" == "--leaks" -o "$1" == "-l" ]
# then
# 	cat error_file | grep "blocks" | grep "e" | grep "d" | grep "y" | grep -v "supp"
# else
# 	rm error_file
# fi
# echo "Result from diff:"
# diff -u og_res my_res
# echo "End of diff"
