# cell — C++ Embeddable Lispy Language

<img src="./assets/logo_1_trans.png" width="256" height="256">

**cell** is a tiny, header-only library for embedding a Lisp-like language into your C++20 (or higher) applications. It also provides a C interface to integrate seamlessly with other languages and environments. **cell** allows both compile-time and run-time evaluation of Lisp forms and makes it effortless to add your own native functions. 

## Table of Contents
- [cell — C++ Embeddable Lispy Language](#cell--c-embeddable-lispy-language)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Quick Start](#quick-start)
    - [Requirements](#requirements)
    - [Installation](#installation)
  - [Basic Usage](#basic-usage)
    - [Runtime Evaluation](#runtime-evaluation)
    - [Compile-Time Evaluation](#compile-time-evaluation)
    - [Adding Native Functions](#adding-native-functions)
    - [C Interface](#c-interface)
    - [Contributing](#contributing)
    - [License](#license)

---

## Features

- **Embeddable**: Easily integrate into any C++ project (and offers a C interface).
- **Header-only**: No extra dependencies; just include the header file.
- **C++20 Support**: Utilizes modern C++ features.
- **Compile-time and Run-time**: Evaluate Lisp-like forms at compile-time or run-time.
- **Custom Extensions**: Effortlessly add native functions that interact with your C++ code.
- **Tiny & Fast**: Minimal overhead, easy to build, and easy to understand.

---

## Quick Start

### Requirements
- A C++20-compatible compiler (e.g., GCC 10+, Clang 10+, MSVC 2019+).
- [CMake](https://cmake.org/) 3.15 or later (for building and testing).

### Installation

1. **Header-only**: Simply copy the `include/` directory into your project, or use a Git submodule to include `cell`.
2. **CMake**: 
   - If you prefer, you can add **cell** as a CMake subdirectory:

     ```cmake
     add_subdirectory(cell)
     target_link_libraries(your_project PRIVATE cell)
     ```

   - Or install it system-wide:

     ```bash
     cd cell
     mkdir build && cd build
     cmake ..
     make
     make install  # Or sudo make install
     ```

---

## Basic Usage

Below is a minimal example of using **cell** in C++ for both run-time and compile-time evaluation.

---

### Runtime Evaluation

```cpp
#include <cell/cell.hpp>
#include <iostream>

int main() {
    // Create a new environment
    cell::Environment env;

    // Evaluate an expression at run time
    auto result = env.eval("(+ 1 2)");
    std::cout << "Result: " << result.as_int() << "\n";  // Should print "3"

    return 0;
}
```

---

### Compile-Time Evaluation
**cell** also supports compile-time evaluation where possible. For example:
```cpp
#include <cell/cell.hpp>
#include <iostream>

constexpr int compileTimeValue = cell::eval("(+ 2 2)");

int main() {
    static_assert(compileTimeValue == 4, "Compile-time evaluation failed!");
    std::cout << "Compile time result: " << compileTimeValue << "\n";  // "4"
    return 0;
}
```
>
**Note:** Compile-time evaluation is limited by C++ rules for `constexpr` and `consteval`.  Avoid using IO and other non-constexpr operations in expressions you want to evaluate at compile time.
> 


---

### Adding Native Functions
One of **cell**'s strengths is how straightforward it is to register custom native functions. For Example:

```cpp
#include <cell/cell.hpp>
#include <iostream>

cell::Value printString(const std::vector<cell::Value>& args) {
    // Expect the first argument to be a string
    std::cout << args[0].as_string() << "\n";
    return cell::Value::nil();
}

int main() {
    cell::Environment env;

    // Register a custom function named "print-string"
    env.register_function("print-string", printString);

    // Now we can call (print-string "Hello from Lisp!")
    env.eval("(print-string \"Hello from Lisp!\")");

    return 0;
}
```

You can define as many native functions as you like. Simply provide a name and function (or lambda).

```cpp
/* test.cpp -> test_prog or test_prog.exe */
#include <cell/env>
#include <iostream>
#include <string>
#include <string_view>

void print_string(char* str, std::size_t n) {
    std::cout << std::string_view{str, n};
}

void print_number(std::uint64_t n) {
    const s = std::to_string(n);
    print_string(s.data(), s.size());
}

std::uint64_t double_plus_5(std::uint64_t n) {
    return (n*2) + 5;
}

int main() {
    cell::Environment env;

    env.register_function("print-string", print_string);
    env.register_function("print-number", print_number);
    env.register_function("double-plus-5", double_plus_5)

    // Now we can call (print-string "Hello from Lisp!")
    env.eval("(print-string \"Hello from Lisp!\n\")");
    env.eval("(print-number (double-plus-5 64))");

    return 0;
}
```

**Expected Behavior**
```sh
$ ./test_prog
   Hello from Lisp!
   132
```

---

### C Interface
For usage outside of C++ (e.g., embedded in C projects), cell provides a C-friendly API. Here’s a rough example of how you might use it:

```cpp
#include "cell_c_api.h"
#include <stdio.h>

int main() {
    cell_env* env = cell_create_env();

    // Evaluate a simple expression
    cell_value* result = cell_eval(env, "(+ 1 2)");
    printf("Result: %d\n", cell_as_int(result));

    // Clean up
    cell_free_value(result);
    cell_free_env(env);

    return 0;
}
```
---

### Contributing
Contributions are welcome! If you have any ideas or bug reports, feel free to:

1. Submit a GitHub issue.

2. Open a pull request with your changes or proposed improvements.

Please ensure your code follows the existing style and is well-tested before opening a PR (pull request).

---

### License
**cell** is distributed under the terms of the [MIT License](https://en.wikipedia.org/wiki/MIT_License).
See the [LICENSE](LICENSE) file for more information.