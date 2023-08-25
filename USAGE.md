# USAGE
To use LEO ECU as a CAN sniffer or man in the middle attack, firstly IDE is needed.
STMCubeIDE is free to use and suitable IDE for us. Download and setup STMCubeIDE link below.
[STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html "STM32CubeIDE")
Clone the repository to your workspace and follow guide below.

1.  **Install STM32CubeIDE:**

	Download and install STM32CubeIDE from the STMicroelectronics website.
	Follow the installation instructions provided by the installer.

2. **Launch STM32CubeIDE:**

	Open STM32CubeIDE by clicking on its shortcut or executable.
3. **Workspace Selection**:

	If this is your first time opening STM32CubeIDE, it will ask you to select a workspace. A workspace is a directory where your projects, settings, and other data are stored. You can choose an existing workspace or create a new one.
4. **Open Project**:

	Once you are in the STM32CubeIDE workspace, go to "File" > "Open Projects from File System..."
5. **Select Root Directory**:

	In the "Import" dialog, select the option "Directory" and click "Browse".
	Navigate to the root directory of your existing STM32CubeIDE project. This is the directory that contains the project files, including the .project file.
6. **Select Project:**

	After selecting the root directory, the project should appear in the "Projects" section of the "Import" dialog.
	Check the box next to your project name to select it.
7. **Project Import:**

	Click "Finish" to import the project into STM32CubeIDE.

8. **Compile Code:**

	Click the hammer icon (Build Project) to compile your code.

9. **Connect ST-Link:**

	Connect the ST-Link programmer/debugger to your PC using USB.
	Connect the ST-Link to your STM32 microcontroller board using its debug connector.
10. **Debug Configuration:**

	Click on "Run" > "Debug Configurations".
	Double-click on  "GDB ST-Link Debugging"  to create a new debug configuration.
	In the "Main" tab, select your project.
	In the "Debugger" tab, choose your ST-Link interface.
	Click "Apply" and then "Debug" to start debugging.
11. **Debugging:**

	You can set breakpoints, step through code, inspect variables, and debug your application using the debug perspective.
12. **Flashing the Microcontroller:**

	Once your code is tested and debugged, you can flash it to the microcontroller.
	Click the arrow icon next to the hammer icon (Debug) to flash your code.
	This will program your microcontroller's flash memory with the compiled binary.
