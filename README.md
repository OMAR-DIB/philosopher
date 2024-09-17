# Philo

## Introduction

Philo is a project focused on multithreading and synchronization using mutexes. It simulates the famous dining philosophers problem, where multiple philosophers alternately eat, think, and sleep while sharing a limited number of forks. The challenge is to prevent race conditions, ensure proper synchronization, and avoid deadlocks.

## Features

The mandatory part of the project implements the following:

1. **Multithreading**: Each philosopher is represented as a separate thread.
2. **Shared Forks**: Philosophers share forks placed between them, protected by mutexes to prevent simultaneous access.
3. **Thread Synchronization**: Mutexes are used to handle fork access and ensure no data races occur.
4. **Philosopher Actions**:
    - Philosophers can **eat**, **sleep**, and **think**.
    - The simulation stops when a philosopher dies of starvation or all philosophers have eaten a specified number of times.
5. **Simulation Output**:
    - The state of each philosopher is logged with a timestamp, including actions like taking a fork, eating, sleeping, thinking, and dying.
    - Proper synchronization ensures no overlapping of logs between philosophers.
6. **No Global Variables**: All variables are managed within threads to ensure thread safety.

## Mandatory Rules

- **Arguments**:
    1. `number_of_philosophers`: The number of philosophers (and forks).
    2. `time_to_die`: Time (in milliseconds) before a philosopher dies if they haven't eaten.
    3. `time_to_eat`: Time (in milliseconds) a philosopher takes to eat.
    4. `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
    5. `number_of_times_each_philosopher_must_eat` (optional): If provided, the simulation stops when each philosopher has eaten this many times.

- **Forks and Mutexes**: Each philosopher must take the fork to their right and left to eat. Forks are protected by mutexes to prevent race conditions.

- **State Logging**: Every state change (forks taken, eating, sleeping, thinking, or death) is logged with a timestamp in milliseconds.

## Requirements

- **C Language**: The project is written in C, following the 42 Norm.
- **Makefile**: A Makefile is provided with the following rules:
  - `all`: Compiles the program.
  - `clean`: Removes object files.
  - `fclean`: Removes all generated files.
  - `re`: Rebuilds the project.

## Usage

To compile the project, run:

```bash
make
```

To run the simulation:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 1 800 200 200 - Philosopher should not eat and should die.
./philo 5 800 200 200 - No Philosopher should die.
./philo 5 800 200 200 7 - No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
./philo 4 410 200 200 - No Philosopher should die.
./philo 4 310 200 100 - One Philosopher should die.
```
