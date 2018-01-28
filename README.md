# yoga920
Linux tools for lenovo yoga 920. This tool allowes enabling and disabling of battery conservation mode (charging up to 59%), which has to be done in Windows instead. Other feature are todo. One can set the value in Windows, but sometimes after power-off the setting is getting lost and going back to Windows is kind of annoing.

This tool took it's inspiration in https://gitlab.com/mikoff/Y2P-PM/tree/master/

Build:
This tool is using boost/program_options be sure it's installed (apt install libboost-dev)

git clone git@github.com:yeckel/yoga920.git
cd yoga920
mkdir build
cd build
cmake ..
make 

The port which needs to be changed and its values was observed by dumping the EC port with sudo ./yoga920 --dump and comparing outputs after changing the value in Windows10 Lenovo Companion tool.

ToDo:
Changing the F1..F12 keys
USB Charging
