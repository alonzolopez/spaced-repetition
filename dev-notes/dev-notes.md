# Dev Notes
- [Dev Notes](#dev-notes)
    - [Docker](#docker)
    - [Compile the Docs](#compile-the-docs)
        - [Install Doxygen](#install-doxygen)
    - [Test Cases](#test-cases)
        - [Compile the Test Executable](#compile-the-test-executable)
        - [Resources](#resources)
    - [Dependencies](#dependencies)

## Docker
1. Pull the docker image
    ```bash
    docker pull danger89/cmake:latest
    ```
2. Start the container
    Windows:
    ```bash
    # Windows generic command
    docker run -v C:\Users\<username>\projects\spaced-repetition:/spaced-repetition --name spaced  -d -t --rm danger89/cmake:latest

    # specific path
    docker run -v C:\Users\AL30832\projects\spaced-repetition:/spaced-repetition --name spaced  -d -t --rm danger89/cmake:latest
    ```
    Mac:
    ```bash
    # template
    docker run -v <path-to-repo-on-host>:/spaced-repetition --name spaced -d -t --rm danger89/cmake:latest

    # specific path
    docker run -v /Users/alonzolopez/projects/spaced-repetition:/spaced-repetition --name spaced -d -t --rm danger89/cmake:latest
    ```

## Compile the Docs
### Install Doxygen
```bash
# linux
sudo apt install doxygen doxygen-latex doxygen-doc doxygen-gui

# mac
brew install doxygen
```
Note: doxygen is included in the Docker container.

## Test Cases
### Compile the Test Executable
0. Set the proxy if necessary
    ```bash
    export HTTP_PROXY=http://30832:tue@proxy-west.aero.org:8080
    export HTTPS_PROXY=http://30832:tue@proxy-west.aero.org:8080
    export http_proxy=http://30832:tue@proxy-west.aero.org:8080
    export https_proxy=http://30832:tue@proxy-west.aero.org:8080
    ```
1. Build the executable
    ```bash
    cd spaced-repetition
    mkdir build && cd build
    cmake ..
    make
    ```
2. Run the executable:
    ```bash
    ./spaced_repetition_test
    ```
### Resources
- [GoogleTest User's Guide](https://google.github.io/googletest/)
    - [GoogleTest Primer](https://google.github.io/googletest/primer.html)
    - [GoogleTest Samples](https://google.github.io/googletest/samples.html)
    - [Assertions](https://google.github.io/googletest/reference/assertions.html)
- [GoogleTest Generic Build Instructions](https://github.com/google/googletest/blob/main/googletest/README.md)
- [C++ Ordered Set](https://cppbyexample.com/set.html)
- time:
    - [date and time functions in c++ with examples](https://www.softwaretestinghelp.com/date-and-time-in-cpp/) - a good overview
    - [ctime](https://cplusplus.com/reference/ctime/ctime/)
    - [gmtime](https://cplusplus.com/reference/ctime/gmtime/)
    - [localtime](https://cplusplus.com/reference/ctime/localtime/)
    - [strptime](https://linux.die.net/man/3/strptime) - convert a string representation of time to a time tm structure
    - [strftime](https://cplusplus.com/reference/ctime/strftime/) - Copies into ptr the content of format, expanding its format specifiers into the corresponding values that represent the time described in timeptr, with a limit of maxsize characters.

## Dependencies
- [json](https://json.nlohmann.me/)