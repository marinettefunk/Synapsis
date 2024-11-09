# Synapsis
A very simple Virtual Assistant written in C++ to work in the console of your system. This program serves as a versatile virtual assistant capable of handling various commands, managing user data, and performing tasks related to user tasks and interactions, basic file management, and more.

**Skills demonstated in this project:**

️✅ C++ Looping
️✅ C++ Error Handling
️✅ Input Validation
️✅ Console Output Formatting
️✅ Various C++ Libraries
️✅ Cross-platform Compatibility
️✅ Basic NLP with Bag-Of-Words

![SYNAPSIS Info Sheet](https://github.com/user-attachments/assets/fd0cdfc8-681b-411a-8265-31a6a9e2c58e)

## Features
SYNAPSIS includes the following capabilities:

### User Data Management
Manage your user profile with registation, login and management capabilities.
- Create your profile
  - Set username
  - Set password
- Manage your profile
   - Edit name and password
   - View your profile
   - Delete profile
     
### File Management
Perform basic file operations such as:
- Rename files or directories
- Move/copy files and directories
- Delete files or directories
- Navigate directories

### ChatBot
Receive and respond to user queries interactively in the console:
- Greeting messages and commands
- Provides fun facts and jokes when promted
- Integration with User Data Management and File Management
- Perform searches:
  - Google
  - YouTube
  - Wikipedia
- Play music via searches:
  - Spotify
  - YouTube Music
- Open Social media:
  - WhatsApp
  - Instagram
  - Facebook
  - LinkedIn

## Set Up
To set up the Virtual Assistant SYNAPSIS on your system, follow the steps below based on your operating system:

### Windows Installation

#### Set Console to Display Characters Used in SYNAPSIS (UTF-8)
1. Go to the Language Settings.
2. Click Administrative Language Settings.
3. Change System Locale.
4. Tick the Beta: Use Unicode UTF-8 for worldwide language support option.
5. Restart your computer.
   
#### Install
1. Download 'SYNAPSIS-1.0-win64.exe'.
2. Follow installation steps.

#### Usage
Once installation is complete, you can run SYNAPSIS from any firectory in your terminal simply by typing:
 ```bash
 SYNAPSIS
 ```
#### Uninstall
Uninstall via Control Panel:
1. Press Win + R
2. Type appwiz.cpl
3. Hit Enter to open Programs and Features.
4. Look for SYNAPSIS in the list of installed programs.
5. Right-click on SYNAPSIS and choose Uninstall.
6. Follow the prompts to uninstall the program.

Manual Uninstallation (if no uninstaller exists or you can't find it):
If for some reason the uninstaller is not available, or you want to completely remove SYNAPSIS manually, you can follow these steps:
1. Delete the Installation Directory:
By default, SYNAPSIS would be installed in the directory ```bash C:\Program Files\SYNAPSIS``` or ```bashC:\Program Files (x86)\SYNAPSIS``` (on a 32-bit system).
2. Go to the installation directory and delete the entire SYNAPSIS folder.

Remove from the PATH:

If the installer added SYNAPSIS to your system's PATH environment variable, you may need to remove it manually.
1. Open the Environment Variables settings by searching for Environment Variables in the Start Menu.
2. Under System Variables, find and select the Path variable, then click Edit.
3. Look for any entries related to SYNAPSIS (such as the installation path) and remove them.
4. Click OK to save the changes.

### Unix
#### Install
1. Download 'SYNAPSIS_Release_Unix.zip'.
2. Extract the files in your desired directory.
```bash
   unzip SYNAPSIS_Release_Unix.zip -d /path/to/your/directory
```
3. Navigate to the directory you have extracted the files.
```bash
cd /path/to/your/directory
```
4. Install SYNAPSIS by running:
```bash
sudo make install
```
#### Usage
Once installation is complete, you can run SYNAPSIS from any firectory in your terminal simply by typing:
 ```bash
 SYNAPSIS
 ```
      
For additional help on funxtionality, run the following in the installation directory:```bash cd /path/to/your/directory```

```bash
sudo make help
```
      
The following menu wll display:
  ```bash
  Makefile Commands:
  make            Build the executable
  make clean      Remove object files and executable
  make install    Install SYNAPSIS to /usr/local/bin/
  make uninstall  Remove SYNAPSIS from /usr/local/bin/
  make help       Display this help message
  ```

#### Unistall
Should you wish to unistall SYNAPSIS, follow these steps:
- If you are in the directory where you installed SYNAPSIS:```bash cd /path/to/your/directory```
Run the following command:
 ```bash
      sudo make uninstall
 ```
- To unistall from any directory, run:
```bash
  sudo rm /usr/local/bin/SYNAPSIS
```

