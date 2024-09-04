Philosophers Project
Overview
The "Philosophers" project is a simulation of the classical "Dining Philosophers Problem," a well-known problem in computer science that illustrates synchronization issues and the challenge of avoiding deadlock and starvation in concurrent systems. In this simulation, multiple philosophers sit around a table with forks between each pair of them. Each philosopher alternates between thinking and eating, but they must pick up two forks to eat. The goal is to implement this simulation while ensuring that no philosopher starves or gets into a deadlock.

Features
This project features a concurrent simulation where multiple philosophers (threads) run concurrently, simulating real-world parallelism. The project ensures proper management of shared resources (forks) to avoid deadlock and starvation. It also allows configurable parameters, including the number of philosophers, time to eat, think, and sleep.

Prerequisites
Before building the project, ensure that you have a C/C++ compiler, such as GCC, or any other C/C++ compiler installed on your machine, along with Make. The project uses a Makefile to simplify the build process.

Installing GCC and Make
On Ubuntu/Debian, you can install GCC and Make by running:

bash
Copy code
sudo apt update
sudo apt install build-essential
On macOS (with Homebrew), you can install them by running:

bash
Copy code
brew install gcc
brew install make
On Windows, you can install GCC and Make using MinGW or through WSL (Windows Subsystem for Linux).

Installation and Building the Project
To install and build the project, first, clone the repository to your local machine using the following command:

bash
Copy code
git clone https://github.com/your-username/philosophers.git
cd philosophers
Next, use the make command to compile the project. The Makefile provided in the project directory will handle the compilation of source files and the creation of the executable:

bash
Copy code
make
This will generate an executable named philosophers in the project directory. After building, you can run the program using the following command:

bash
Copy code
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
Here, number_of_philosophers specifies the number of philosophers and forks (default is 5). time_to_die is the maximum time (in milliseconds) a philosopher can go without eating before dying. time_to_eat specifies the time (in milliseconds) a philosopher spends eating, while time_to_sleep defines the time a philosopher spends sleeping. The number_of_times_each_philosopher_must_eat parameter is optional; if provided, the simulation stops when each philosopher has eaten at least this many times.

Project Structure
The project is structured as follows: The src/ directory contains the source code files, and the include/ directory contains the header files for the project. The Makefile is used to build the project, and the README.md file provides project documentation.

Implementation Details
The project uses mutexes to control access to the shared resources (forks). Each fork is represented by a mutex, and a philosopher must lock the mutexes for the left and right forks before they can eat. After eating, they unlock the mutexes. Deadlock is avoided by ensuring that philosophers pick up forks in a specific order and by implementing a mechanism to detect and handle potential deadlocks.

Testing
The project includes several test cases to ensure that philosophers can eat, think, and sleep as expected. It also verifies that deadlock and starvation are avoided and that the simulation runs correctly with different numbers of philosophers and varying timing parameters.

Contributing
Contributions are welcome! If you find a bug or have a suggestion for an improvement, please open an issue or submit a pull request.

License
This project is licensed under the MIT License - see the LICENSE file for details.

Contact
If you have any questions or need further assistance, feel free to contact the project maintainer at [your-email@example.com].
