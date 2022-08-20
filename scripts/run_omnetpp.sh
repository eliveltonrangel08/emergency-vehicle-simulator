echo xauth add $DISPLAY . $XAUTH
touch ~/.Xauthority
xauth add $DISPLAY . $XAUTH

/root/omnetpp/bin/omnetpp