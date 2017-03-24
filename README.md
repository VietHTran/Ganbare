# Ganbare
(Fun Project) Linux desktop application that keeps the user focus by playing loud music whenever it detects the user is sleeping.

## Required Software & Package
1. Debian package development tools
2. Embedded GNU C Library 
3. GNU C++ compiler
4. Make
5. OpenCV 3.2
6. Python 2 (console version only)
7. QMake (UI version only)
8. Qt 5.8 (UI version only)
9. Flask Socket-IO (console version only)

## Installation
### Console version
- Open the terminal and locate it to the 'console' folder.
- Run command `./Install.sh` or `bash Install.sh` to start the installation process.
- After a sucessful installation the program `./ganbare` can then be run at the console folder.

### UI version
- Open the terminal and locate it to the 'GanbareUI' folder.
- Run command `./install.sh` or `bash install.sh` to start the installation process.
- After a sucessful installation the program 'ganbare' can then be initialized by running the script 'runUI.sh' in the outermost folder or runnining the 'GanbareUI' program inside the 'UIBuild' folder.

## How to use
After a successful installation process, the program can then be run on the terminal.
### Console version
- Open 2 terminals and locate them to the 'console' folder.
- Run command `./ganbare` on one terminal and `python client.py` on the other.
- Open the file 'video.html' in the directory 'console/web' with a browser to start the program.

### UI version
- Open a terminal and locate it to the outermost folder ('Ganbare').
- Run command `./runUI.sh` or `bash runUI.sh` to start the program.
- A new window will popup displaying a youtube video.
- To begin the facial detection, press the 'Start' button in lower part of the program.
- To end the detection, press the 'Stop' button.
- To load a new video, enter a youtube video key in the text box and press 'Load' to load the video.
