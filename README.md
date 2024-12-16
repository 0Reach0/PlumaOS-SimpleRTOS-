# PlumaOS


## Inctruction

### 1. Move files into your project

### 2. In the `CPUDriver.h` file, you'll find a `comment` with `code` and `include file` name that needs to be inserted into the timer IRQ handler (this will serve as the task scheduler)




## Project Structure

This project consists of several key components organized into the following directories:

### 1. `kernel`
- The core of the system that handles low-level operations and system initialization.
- Contains the essential functions and services for the overall functionality of the system.
- Responsible for managing resources, scheduling, interrupt handling, and more.

### 2. `modules`
- Contains different modules that extend the functionality of the kernel.
- Includes various subsystems that interact with the kernel to provide additional features like file systems, networking, and device drivers.
- Each module can be loaded or unloaded dynamically based on system requirements.

### 3. `MCDrivers`
- This folder contains drivers for microcontroller peripherals, ensuring communication between hardware components and the kernel.
- Includes drivers for timers

### 4. `CPUDrivers`
- Contains drivers for the CPU and architecture-specific functions.
- Manages CPU states, context switching
### 5. `Templates`
- A collection of template projects with an imported RTOS.
- Provides ready-to-use project templates for faster development, ensuring consistency and easy integration with the runtime system.
  


### `kernel`
- Contains the core components of the system, including:
  - **Inc**: General include files and configuration file	
  - **TaskManagement**: Manages tasks and their states.
  - **TaskScheduler**: Schedules tasks based on their priority and timing.
  - **TaskDelay**: Handles task delays, allowing tasks to wait for specific periods or events.
  - **Initialisation**: Initializes the system, setting up all necessary resources.

### `Modules`
--Once you include any module in your project, make sure to uncomment the corresponding macros in the PlumaConfig.h file. 


### `PlumaConfig`
- The configuration file allows you to enable or disable specific modules and configure various settings within the project. 
By modifying the macros within this file, you can easily include or exclude modules and adjust other project settings according to your needs
