#include <iostream>

namespace lab
{
    namespace initialization
    {

        void run()
        {
            //---------------------------------------------------------------------------
            // basic terminology and concepts about variable initialization/declaration
            //---------------------------------------------------------------------------

            // We can access memory through an object. An object is a representation of a
            // region of storage (RAM or a register).
            // An instantiated object is sometimes called an instance. Most often, this
            // term is applied to class type objects, but it can also be used for other
            // object types.

            // declaration, definition, creation, initialization, and assignment
            // int a;
            // -> a is declared, a is defined (for variables, declaration and definition
            //    are usually the same thing).
            // -> Storage is allocated for a.
            // -> a is not initialized.
            // -> Since a is a local variable, its value is indeterminate.

            // int b = 5;
            // -> b is declared.
            // -> b is defined.
            // -> Storage is allocated.
            // -> b is initialized with the value 5.
            // -> Specifically, this is copy-initialization.

            int a; // default-initialization (no initializer)

            // Traditional initialization forms:
            a = 69;
            int b = 5; // copy-initialization
            int c(6);  // direct-initialization

            // Modern initialization forms (preferred):
            int d{7};     // direct-list-initialization
            int e{};      // value-initialization, becomes 0
            int f = {89}; // copy-list-initialization

            std::cout << a << '\n';
            std::cout << b << '\n';
            std::cout << c << '\n';
            std::cout << d << '\n';
            std::cout << e << '\n';
            std::cout << f << '\n';

            // List initialization rejects narrowing conversions:
            // int ab{6.7}; // error
            int ab{6};
            std::cout << ab << '\n';

            // For now this lab is intentionally focused on initialization concepts.
        }

    } // namespace initialization
} // namespace lab
