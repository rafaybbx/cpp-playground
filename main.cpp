#include <iostream>

using namespace std;

int main()
{
    int a; // default-initialization (no initializer)

    // Traditional initialization forms:
    a = 69;
    int b = 5; // copy-initialization (initial value after equals sign)
    int c(6);  // direct-initialization (initial value in parenthesis), initial value is a must

    // Modern initialization forms (preferred) (list initialization):
    int d{7};     // direct-list-initialization (initial value in braces)
    int e{};      // value-initialization (empty braces), if no value provided then it is 0
    int f = {89}; // copy-list initialization, rarely used

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;

    // list initialization -> narrowing conversions dissallowed:
    // int ab {6.7}; -> gives error
    int ab{6};
    cout << a << endl;

    return 0;
}