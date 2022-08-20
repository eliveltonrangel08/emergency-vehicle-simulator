echo xauth add $DISPLAY . $XAUTH
touch ~/.Xauthority
xauth add $DISPLAY . $XAUTH

/root/veins/bin/veins_launchd -vv -c /root/sumo/bin/sumo-gui > log_sumo_veins 2>&1&