## update source

#/etc/apt/sources.list
#https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/

## env

#basic
sudo apt install git vim python
#kernel
sudo apt install gcc-aarch64-linux-gnu gcc flex make bison libncurses-dev libssl-dev

#vscode

sudo apt install  universal-ctags

## linux git
git clone https://mirrors.tuna.tsinghua.edu.cn/help/linux.git/

## tools git
git clone https://github.com/TinyWindzz/tools

## install chrome

wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt install ./google-chrome-stable_current_amd64.deb

## install pinyin

#->Settings -> Region and Language -> Input Sources -> + -> Chinese (Intelligent Pinyin) 
sudo apt install ibus-libpinyin 
sudo apt install ibus-clutter

## install typora

wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
sudo add-apt-repository 'deb https://typora.io/linux ./'
sudo apt-get update

## install vscode

 #ubuntu software

#Extensions
#->Chinese (Simplified) Language Pack for Visual Studio Code
#C/C++
#DeviceTree
#Embedded Linux Kernel Dev

#kernel json
./scripts/gen_compile_commands.py
#在c_cpp_properties.json文件中添加
#"compileCommands": "${workspaceFolder}/compile_commands.json"