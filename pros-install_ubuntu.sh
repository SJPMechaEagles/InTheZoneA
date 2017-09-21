#!/bin/bash

confirm(){
    echo "Press RETURN to continue or ^C to cancel."
}

ATOM_URL='https://github.com/atom/atom/releases/download/v1.10.2/atom-amd64.deb'
DOCUMENTATION_URL='pros.cs.purdue.edu/api/'

echo "PROS UBUNTU INSTALL SCRIPT"
echo "This script will install Pros and all of its core dependencies."
echo

echo "Installing environment dependencies: git, arm-none-eabi-gcc, clang, python3, python3-pip"
echo

sudo apt-get -qq update
sudo apt-get -y install \
    git clang gcc-arm-none-eabi python3 python3-pip

if [ $? -ne 0 ]
then
    echo "Something went wrong in linux dependency installation"
    exit 1
fi

echo "Installing Atom"
echo
wget $ATOM_URL
if [ $? -eq 0 ]
then
    sudo dpkg -i atom-amd64.deb
    sudo apt-get install -f
    rm -f atom-amd64.deb
else
    echo "Failed to download Atom installation from github"
    exit 1
fi

echo "Installing python PROS CLI"
sudo pip3 install pros-cli

if [ $? -ne 0 ]
then
    echo "pros-cli failed to install open an issue on github for support"
    exit 1
fi

echo "Installing PROS atom plugins"
echo
apm install file-icons linter tool-bar tool-bar-main busy build pros

if [ $? -ne 0 ]
then
    echo "Atom package installations have failed"
    exit 1
fi

# update permissions correctly for issue: https://github.com/atom/atom/issues/5506#issuecomment-77149029
USER=`whoami`
chown -R $USER:$USER ~/.atom


echo "========================================================"
echo "Install probably worked Open up Atom and start programming your cortex."
echo "Check out $DOCUMENTATION_URL for all PROS documentation"
echo "========================================================"