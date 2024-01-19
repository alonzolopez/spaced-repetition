# Dev Notes
- [Dev Notes](#dev-notes)
  - [Compile the Docs](#compile-the-docs)
    - [Install Doxygen](#install-doxygen)
  - [Test Cases](#test-cases)
    - [Compile the Test Executable](#compile-the-test-executable)
    - [Resources](#resources)



## Compile the Docs
### Install Doxygen
```bash
sudo apt install doxygen doxygen-latex doxygen-doc doxygen-gui
```

## Test Cases
### Compile the Test Executable
```bash
cd spaced-repetition
g++ -I include src/* -o spaced-repetition
```

Run the executable:
```bash
./spaced-repetition
```
### Resources
- [GoogleTest User's Guide](https://google.github.io/googletest/)
    - [GoogleTest Primer](https://google.github.io/googletest/primer.html)