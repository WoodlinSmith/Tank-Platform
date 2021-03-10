```
 _________   ________   ________    ___  __       
|\___   ___\|\   __  \ |\   ___  \ |\  \|\  \     
\|___ \  \_|\ \  \|\  \\ \  \\ \  \\ \  \/  /|_   
     \ \  \  \ \   __  \\ \  \\ \  \\ \   ___  \  
      \ \  \  \ \  \ \  \\ \  \\ \  \\ \  \\ \  \ 
       \ \__\  \ \__\ \__\\ \__\\ \__\\ \__\\ \__\
        \|__|   \|__|\|__| \|__| \|__| \|__| \|__|



 _________   ________   ________   ________   ___        _______      
|\___   ___\|\   __  \ |\   __  \ |\   __  \ |\  \      |\  ___ \     
\|___ \  \_|\ \  \|\  \\ \  \|\  \\ \  \|\  \\ \  \     \ \   __/|    
     \ \  \  \ \  \\\  \\ \   ____\\ \   ____\\ \  \     \ \  \_|/__  
      \ \  \  \ \  \\\  \\ \  \___| \ \  \___| \ \  \____ \ \  \_|\ \ 
       \ \__\  \ \_______\\ \__\     \ \__\     \ \_______\\ \_______\
        \|__|   \|_______| \|__|      \|__|      \|_______| \|_______|


                                                                 
```
  
Tank Topple is an AI driver tank battle simulation platform.  
  
## Installation  
# Pre-requisite libraries  
  * freeglut3-dev
    * OpenGL - Development libraries
  * SOIL  
    * Image processing package  
  * make
    * Linux compiler script manager
  * g++
    * Linux C++ Compiler
  * gdb
    * Linux debugger
  
# Optional Software for Windows Users  
  * Xming  
    * X-server package for displaying platform on windows
  

## Using the platform  
# Build the platform  
  * ```make```  
  * (optionaly) ```make -j8```  

# Run the initial build  
  * ```./platform```  
  
# Commandline options  
  * -quiet  
    This mode silences most text displayed during run time.  
  * -demo  
    This mode increases the display size to 1080p (1920x1080)  
  * -coverage  
    This mode silences most text and sets speed options to their fastest value  
  
## Testing and Coverage  
# Testing  
  * Method 1:  
    make tests  
    This method will build both sets of test binaries in the main program directory  
  * Method 2:  
    ```cd tests/src``` or ```cd tests/functional_tests```  
    ```make```  
    This method will build a single bianry in next to the test source files.  
  
# Coverage  
  * ```./runCoverage.sh```  
    This command does a number of things:  
      It build special versions of the platform and testing binaries with coverage markers.  
      Runs a baseline test from the current configuration file.  
      Combines all of the data to show which lines of code were executed by the testing.  
      Generates an HTML report of the coverage data.  
