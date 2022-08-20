FROM ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive
MAINTAINER Elivelton Rangel eliveltonrangel@gmail.com

RUN apt-get update && apt-get upgrade -y --fix-missing

# Installing dependencies
RUN	apt-get install -y --fix-missing build-essential gcc g++ bison flex perl python python3 qt5-default \
	libqt5opengl5-dev tcl-dev tk-dev libxml2-dev zlib1g-dev default-jre doxygen graphviz \
	libwebkit2gtk-4.0-dev libopenscenegraph-dev libosgearth-dev openscenegraph-plugin-osgearth \
	libxerces-c-dev libproj-dev libgdal-dev libfox-1.6-dev libavformat-dev libavcodec-dev \
	libswscale-dev python-dev python-configparser cmake libfox-1.6-dev libgdal-dev \
    libproj-dev libgl2ps-dev swig python3-setuptools python-setuptools python3-pip r-base wget

ARG TOOLS_PATH="/root/tools"
WORKDIR $TOOLS_PATH
ENV LIBGL_ALWAYS_SOFTWARE=1


# Build and Install OMNet++ IDE
ARG OMNET_VERSION=omnetpp-5.7
ENV PATH="${PATH}:/root/omnetpp/bin"
RUN wget -P $TOOLS_PATH https://github.com/omnetpp/omnetpp/releases/download/$OMNET_VERSION/$OMNET_VERSION-linux-x86_64.tgz
RUN tar zxvf $TOOLS_PATH/$OMNET_VERSION-linux-x86_64.tgz && rm $TOOLS_PATH/$OMNET_VERSION-linux-x86_64.tgz
RUN ln -s $TOOLS_PATH/$OMNET_VERSION /root/omnetpp
RUN echo "export PATH=$PATH" >> ~/.bashrc
RUN cd $TOOLS_PATH/$OMNET_VERSION && . ./setenv && ./configure && make

# Download and Unzip Veins
ARG VEINS_VERSION=veins-5.2
RUN wget -P $TOOLS_PATH https://veins.car2x.org/download/$VEINS_VERSION.zip
RUN unzip $TOOLS_PATH/$VEINS_VERSION.zip && rm $TOOLS_PATH/$VEINS_VERSION.zip
RUN ln -s $TOOLS_PATH/veins-$VEINS_VERSION /root/veins && cd /root/veins && ./configure && make -j$(nproc)

# Download and Unzip PLEXE
ARG PLEXE_VERSION=plexe-3.0
RUN wget -P $TOOLS_PATH https://github.com/michele-segata/plexe/archive/refs/tags/$PLEXE_VERSION.zip
RUN unzip $TOOLS_PATH/$PLEXE_VERSION.zip && rm $TOOLS_PATH/$PLEXE_VERSION.zip
RUN ln -s $TOOLS_PATH/plexe-$PLEXE_VERSION /root/plexe && cd /root/plexe && ./configure --with-veins=/root/veins && make -j$(nproc)
RUN cd /root/plexe && . ./setenv

# Buil and Install SUMO
# http://sumo.dlr.de/wiki/Installing/Linux_Build
ARG SUMO_VERSION=sumo-1.12.0
ENV PATH="${PATH}:/root/sumo/bin"
RUN wget -O $TOOLS_PATH/$SUMO_VERSION-src.tar.gz https://sumo.dlr.de/releases/1.12.0/sumo-src-1.12.0.tar.gz
RUN tar zxf $TOOLS_PATH/$SUMO_VERSION-src.tar.gz && rm $TOOLS_PATH/$SUMO_VERSION-src.tar.gz
RUN ln -s $TOOLS_PATH/$SUMO_VERSION /root/sumo
RUN echo "export PATH=$PATH" >> ~/.bashrc
RUN mkdir -p /root/sumo/build/cmake-build && cd /root/sumo/build/cmake-build && cmake ../.. && make -j$(nproc)


# Installing R packages to Plexe
RUN wget -P $TOOLS_PATH http://plexe.car2x.org/download/omnetpp_0.7-1.tar.gz
RUN R -e "install.packages(c('ggplot2', 'reshape2', 'data.table'))"
RUN R -e "install.packages('$TOOLS_PATH/omnetpp_0.7-1.tar.gz', repos=NULL)"

WORKDIR /root
ENV SUMO_HOME=/root/sumo
CMD ["bash", "-c", "source /root/.bashrc"]
