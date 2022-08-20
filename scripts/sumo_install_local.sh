#!/bin/bash

# Sets script to fail if any command fails.
set -e


#sudo	echo "deb http://hu.archive.ubuntu.com/ubuntu/ trusty main restricted universe multiverse" | tee -a  /etc/apt/sources.list && \
#sudo    echo "deb-src http://hu.archive.ubuntu.com/ubuntu/ trusty main restricted universe multiverse" | tee -a  /etc/apt/sources.list && \
#sudo    echo "deb http://hu.archive.ubuntu.com/ubuntu/ xenial main restricted universe multiverse" | tee -a  /etc/apt/sources.list && \
#sudo    echo "deb-src http://hu.archive.ubuntu.com/ubuntu/ xenial main restricted universe multiverse" | tee -a  /etc/apt/sources.list && \
#sudo    echo "deb http://hu.archive.ubuntu.com/ubuntu/ bionic main restricted universe multiverse" | tee -a  /etc/apt/sources.list && \
#sudo    echo "deb-src http://hu.archive.ubuntu.com/ubuntu/ bionic main restricted universe multiverse" | tee -a  /etc/apt/sources.list

#sudo apt-get update && sudo apt-get upgrade -y

#sudo apt-get install -y build-essential gcc g++ bison flex perl \
#    python python3 qt5-default libqt5opengl5-dev tcl-dev tk-dev \
#    libxml2-dev zlib1g-dev default-jre doxygen graphviz \
#    software-properties-common libnvidia-gl-460 openjdk-8-jdk

#sudo add-apt-repository ppa:ubuntugis/ubuntugis-unstable && sudo apt-get update

#sudo apt-get install -y openscenegraph-plugin-osgearth libosgearth-dev libwebkitgtk-1.0-0

#sudo apt-get install -y libpcap-dev

#sudo apt-get install -y cmake python python3 g++ libxerces-c-dev \
#    libfox-1.6-dev libgdal-dev libproj-dev libgl2ps-dev swig

#sudo apt-get install -y python3-setuptools python-setuptools python3-pip

JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/
export JAVA_HOME

mkdir /home/ubuntu/src
cd /home/ubuntu/src

wget https://github.com/omnetpp/omnetpp/releases/download/omnetpp-5.6.2/omnetpp-5.6.2-src-linux.tgz
tar zxvf omnetpp-5.6.2-src-linux.tgz && \
	cd /home/ubuntu/src/omnetpp-5.6.2 && \
	export PATH=$PATH:/home/ubuntu/src/omnetpp-5.6.2/bin && \
	./configure && \
	make

cd /home/ubuntu/src
wget https://sumo.dlr.de/releases/1.8.0/sumo-src-1.8.0.tar.gz
tar zxf ./sumo-src-1.8.0.tar.gz && \
    rm sumo-src-1.8.0.tar.gz && \
    mkdir /home/ubuntu/src/sumo-1.8.0/build/cmake-build && \
    cd /home/ubuntu/src/sumo-1.8.0/build/cmake-build && \
    cmake ../.. && \
    make -j$(nproc)


cd /home/ubuntu/src
wget https://veins.car2x.org/download/veins-5.1.zip
unzip veins-5.1.zip

cd /home/ubuntu/src
wget https://github.com/inet-framework/inet/releases/download/v4.1.2/inet-4.1.2-src.tgz
tar zxvf inet-4.1.2-src.tgz

ln -s /home/ubuntu/src/sumo-1.8.0/ /root/sumo
ln -s /home/ubuntu/src/omnetpp-5.6.2 /root/omnetpp
ln -s /home/ubuntu/src/veins-veins-5.1 /root/veins
echo export PATH=$PATH:/home/ubuntu/src/omnetpp/bin | tee -a ~/.bashrc
echo export PATH=$PATH:/home/ubuntu/src/sumo/bin | tee -a ~/.bashrc

LD_LIBRARY_PATH=/usr/local/lib:/root/omnetpp/lib

