gcc -c data_loader.c -o data_loader
gcc -c spam_classifier_impl.c -o spam_classifier_impl
gcc -c model_io.c -o model_io

ar rcs lib.a data_loader spam_classifier_impl model_io

gcc -o test_output main.c -L. lib.a

if [ $? -eq 0 ]; then
    echo "Compilation successful"
    echo "./test_output to run the program"
    echo "./test_output --predict to run the program in predict mode"
else 
    echo "Compilation failed"
fi