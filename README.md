## 📓Source_to_HTML


📜**Description**

Source to HTML is a C-based lexical analyzer that reads a C source file, identifies different types of tokens, and generates an HTML file with syntax highlighting. The project classifies tokens such as keywords, identifiers, operators, numbers, strings, characters, comments, special characters, and preprocessor directives.

🔷 **Features**

* Read C source code from a file
* Identify and classify different tokens
* Highlight keywords
* Highlight identifiers
* Highlight operators
* Highlight numbers
* Highlight character constants
* Highlight strings
* Highlight comments
* Highlight special characters
* Highlight preprocessor directives
* Generate syntax-highlighted HTML output
* Escape HTML special characters

⚙️**Technologies Used**

* C Programming
* File Handling
* Lexical Analysis
* String Handling
* HTML
* CSS

📍**Token Classification**

* Keywords – `int`, `char`, `return`, `if`, `else`, etc.
* Identifiers – Variable names and function names
* Operators – `+`, `-`, `*`, `/`, `==`, `++`, etc.
* Numbers – Integer and numeric constants
* Characters – Character constants
* Strings – String literals
* Comments – Single-line comments
* Special Characters – `{`, `}`, `;`, `(`, `)`, etc.
* Preprocessor – `#include`, `#define`, etc.

▶️**How to Run**

```text
    Compile :- gcc *.c

    Run :- ./a.out
```

**svg**

🔶**Sample Input**

```c
#include <stdio.h>

int main()
{
    int num = 10;

    // Check the number

    if(num > 0)
    {
        printf("Positive\n");
    }

    return 0;
}
```



🔶**Sample Output**

The generated `output.html` displays the source code with different colors for different token types.

```text
    Keywords       → Blue
    Identifiers    → Black
    Operators      → Red
    Numbers        → Green
    Characters     → Dark Green
    Comments       → Gray
    Strings        → Brown
    Special        → Purple
    Preprocessor   → Orange
```



👩‍💻**Author**

```text
    Praveena
```
# source-to-html
