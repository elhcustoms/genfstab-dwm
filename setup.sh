!#/bin/bash
if [ `whoami` != root ]; then
    echo "Please run this script using sudo"
    exit
else
make clean install || rm config.h && make clean install
mkdir -p /usr/share/xsessions/ || echo "xsessions folder already exist. Skipping...."
cp dwm.desktop /usr/share/xsessions/ || echo "dwm.desktop already exist. Skipping...."
echo "Done."
fi
