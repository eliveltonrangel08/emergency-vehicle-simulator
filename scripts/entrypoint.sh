#!/bin/bash

# Sets script to fail if any command fails.
set -e

set_xauth() {
	echo xauth add $DISPLAY . $XAUTH
	touch ~/.Xauthority
	xauth add $DISPLAY . $XAUTH
}


print_usage() {
echo "

Usage:	$0 COMMAND

XAPPS Container

Options:
  help		Print this help
  omnet	Run OMNeT++ IDE
  set_xautch	To fix GUI applications running (default by all)
  sumo_veins	Run veins lunchpad to listen sumo application
  run_sumo_gui	Run SUMO GUI
  xeyes	If `set_xauth` doesn't solve gui problem, run this command
"
}

case "$1" in
    help)
      print_usage
      ;;
    sumo_veins)
      set_xauth
      /root/veins/bin/veins_launchd -vv -c /root/sumo/bin/sumo-gui > log_sumo_veins 2>&1&
      ;;
    run_sumo_gui)
      set_xauth
      /root/sumo/bin/sumo-gui &
      ;;
    omnet)
      set_xauth
      /root/omnetpp/bin/omnetpp
      ;;
    xeyes)
      set_xauth
      xeyes
      ;;
    *)
      exec "$@"
esac
