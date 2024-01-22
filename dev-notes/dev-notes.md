# Dev Notes
- [Docker](#docker)
- [Compile the Docs](#compile-the-docs)
    - [Install Doxygen](#install-doxygen)
- [Test Cases](#test-cases)
    - [Setup Gtest](#setup-gtest)
    - [Compile the Test Executable](#compile-the-test-executable)
    - [Resources](#resources)

## Docker
1. Pull the docker image
    ```bash
    docker pull danger89/cmake:latest
    ```
2. Start the container
    ```bash
    # Windows generic command
    # docker run -v C:\Users\<username>\projects\spaced-repetition:/spaced-repetition --name spaced  -d -t --rm gcc:latest
    docker run -v C:\Users\<username>\projects\spaced-repetition:/spaced-repetition --name spaced  -d -t --rm danger89/cmake:latest

    # specific path
    # docker run -v C:\Users\AL30832\projects\spaced-repetition:/spaced-repetition --name spaced  -d -t --rm gcc:latest
    docker run -v C:\Users\AL30832\projects\spaced-repetition:/spaced-repetition --name spaced  -d -t --rm danger89/cmake:latest
    ```

## Compile the Docs
### Install Doxygen
```bash
sudo apt install doxygen doxygen-latex doxygen-doc doxygen-gui
```
Note: doxygen is included in the Docker container.

## Test Cases
### Setup Gtest
0. If you're working in the Docker container, install cmake in the Docker container, if necessary
    ```bash
    apt-get update && apt-get -y install cmake
    ```
1. Clone the repo and create the CMakeFile
    ```bash
    git clone https://github.com/google/googletest.git -b v1.14.0
    cd googletest        # Main directory of the cloned repository.
    mkdir build          # Create a directory to hold the build output.
    cd build
    cmake ..             # Generate native build scripts for GoogleTest.
    ```
2. Build and install GoogleTest
    ```bash
    make
    sudo make install    # Install in /usr/local/ by default
    ```

### Compile the Test Executable
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