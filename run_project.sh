gcc -c data_loader.c -o data_loader
gcc -c spam_classifier_impl.c -o spam_classifier_impl

ar rcs lib.a data_loader spam_classifier_impl

gcc -o test_output main.c -L. lib.a

if [ $? -eq 0 ]; then
    ./test_output
else 
    echo "Compilation failed"
fi