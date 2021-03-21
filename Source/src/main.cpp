#include <iostream>

//#include <fmt\format>
//#include <fmt\format.h>
//#include "fmt\format.h"
int main(){
    printf("aa");

    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
    std::cout << s;

    system("pause");
    return 0;
}