# TCPBank

TCPBank is a simple client-server banking application implemented using TCP sockets in C. It demonstrates basic networking concepts and simulates banking operations such as account creation, balance inquiry, deposit, and withdrawal.

## Features

- Account creation and management
- Balance inquiry
- Deposit and withdrawal operations
- Concurrent client handling using threads
- Simple command-line interface

## Requirements

- GCC compiler
- Linux environment (recommended)
- Basic knowledge of C and networking

## Usage

1. **Compile the server and client:**
    ```bash
    gcc server.c -o server -lpthread
    gcc client.c -o client
    ```

2. **Run the server:**
    ```bash
    ./server
    ```

3. **Run the client (in a new terminal):**
    ```bash
    ./client
    ```

4. **Follow the on-screen instructions to perform banking operations.**

## File Structure

- `server.c` - TCP server implementation
- `client.c` - TCP client implementation
- `README.md` - Project documentation

## License

This project is for educational purposes.
