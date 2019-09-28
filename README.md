#Ratelimiter in C++



#### Steps to build the project:

1. Install **cmake **
   1. On Mac OS, `brew install cmake`
2. Install the **ninja** build system
   1. On Mac OS, `brew install ninja`
3. Install the **boost** libraries
   1. On Mac OS, `brew install boost`
4. From the root directory of the project, run `mkdir -p build`
5. Go to newly created directory, `cd build`
6. Run the cmake command, `cmake -GNinja ..`
7. Run `ninja` to build the project
8. Run  `./ratelimiter` from build directory to run the project
9. Run `./test/ratelimiter_test` from build directory to run the tests.
10. On changes, run `ninja` in the "build" directory.




#### Optional: Auto formating the code

For the auto formating, we use "clang-format" .

You can install it with `brew install clang-format`

Then, install the clang-format extension on "VS Code" and run "Format Document", or any other text editor.



#### Optional: Install the "Cmake Tools" extension in VSCode



