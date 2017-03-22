#!/bin/bash
#Use: Install GanbareUI

#function add new line to runUI.sh file
function append {
    echo "$1" >> runUI.sh
}

cd ..
mkdir UIBuild
cd UIBuild

current_dir=$(pwd)
cd ~
home_dir=$(pwd)
cd "$current_dir"

#Assume that Qt 5.8 is installed at home directory
#Otherwise need to change directory
"$home_dir/Qt/5.8/gcc_64/bin/qmake" "$current_dir"/../GanbareUI/GanbareUI.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug

make

if [ -f ./GanbareUI  ]; then
    echo "Installation successful"
    cd ..
    echo > runUI.sh
    append "#!/bin/bash"
    append "cd UIBuild"
    append "./GanbareUI"
    chmod +x runUI.sh

    read -p "Do you want do run the program immediately? [Y/N]" option
    declare -l isRun=$option
    if [[ $isRun == "y" || $isRun == "yes" || $isRun == "yolo" ]] ; then
        ./runUI.sh
    fi
else
    echo "Installtion failed"
fi
