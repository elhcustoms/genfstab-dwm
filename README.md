# dwm
- Build of DWM
- Compiled on Gentoo

# Build Dependencies
- libXinerama-devel
- libXft-devel
- freetype-devel
- All dependencies that are included with the previously stated

# Optional
By default, I am using ST, dmenu, flameshot, and pcmanfm  If you do not wish to use any of these, you can edit config.def.h to replace st with a terminal of your choice, rofi with dmenu, etc.

# Patches
I have included many QoL patches in my build. You can see the following patches included in this repository.

If you choose to remove any of these patches. Install *patch* from your distro's package manager and remove them using this sytax

1. `patch -R < patch-name.diff`
2.  correct any errors that may happen
3. `sudo make clean install`

# Installing

Assuming you installed the required dependencies from your distribution. There is an install script included.
Run the script WITHIN elh-dwm folder
1. `chmod +x setup.sh`
2. `sudo ./setup.sh`
3. Skip "Starting it from a Display Manager" if using script.

# Recompiling
If you make any changes, you must delete the old config.h. Without doing this, you may run into issues.
Simply do `sudo rm config.h && sudo make clean install` to compile dwm with new configuration.

# Starting it from a Display Manager (SDDM, LightDM, etc;)
Create a .desktop file in /usr/share/xsessions/

[Desktop Entry]

Name=dwm

Comment=Dynamic Window Manager  

Exec=dwm

Type=Application

# Hotkeys

For the most part, I am using default DWM hotkeys, with some odd exceptions
1. The Mod key is Super/Windows/Command Key.
2. Mod + P opens File Manager
3. Mod + D opens dmenu/rofi
4. Printscreen opens Flameshot
5. Mod + Shift + Q closes focused application
6. Mod + Shift + R quits dwm
7. Mod + Ctrl + Shift + Q will restart DWM without logging you out. (Good for applying changes after recompiling DWM)


# Tested Distros (including Derivatives)
1. Gentoo
