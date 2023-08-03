# Webserver-linux-pthread


Lightweight Multi-Threaded Network Server

## Project Description

This project is a lightweight multi-threaded network server developed in C++ for the Linux environment. It utilizes a thread pool to efficiently handle a large number of client connections and respond to their requests promptly. Advanced technologies such as I/O multiplexing, simulated Proactor pattern, and finite state machine have been employed to further optimize the server's performance.

## Key Features

- Supports remote network communication based on Socket and utilizes **epoll** for **I/O multiplexing** and socket monitoring.
- Implements a **thread pool** to efficiently handle events (I/O operations, exceptions, and timers) from the event ready queue using multiple threads.
- Wraps **Linux locks**, placing lock creation and destruction functions in the class's constructor and destructor, simplifying multi-threaded programming.
- Uses a **finite state machine** to parse HTTP request messages and generate appropriate response messages.
- Implements a timer using a **doubly-linked list** to periodically check and close **inactive connections**, improving server resource utilization.

## Requirements

- Linux operating system
- C++11 compiler or above

## Installation and Running

1. Clone the project to your local machine:

```bash
git clone https://github.com/ElricPjYi/webserver-linux-pthread.git
cd webserver
```

2. Build the project:

```bash
g++ *.cpp -pthread
```

3. Run the server:

```bash
./a.out 80
```

## Usage Example

The following example demonstrates how to use the server to set up a simple HTTP service:

```cpp
#include "webserver.h"

int main() {
    // Create a server instance
    WebServer server;

    // Set the listening port
    server.SetPort(8080);

    // Start the server
    server.Start();

    return 0;
}
```

## Contribution

Feedback and suggestions for this project are welcome! If you wish to contribute, feel free to submit a Pull Request, and we'll review and merge outstanding code.


## Author

- Author: Elric PJ
- GitHub: [Your GitHub Profile](https://github.com/your_username)

## Acknowledgments

We would like to thank the following projects for their inspiration and support:

- [ThreadPool](https://github.com/progschj/ThreadPool)
- [Epoll](https://github.com/davidmoreno/onion/tree/master/src/epoll)

## Frequently Asked Questions

If you have any questions, please check our [FAQ](FAQ.md).

---
Note: The above README is a simple template, and you can modify and expand it based on your actual project details.
