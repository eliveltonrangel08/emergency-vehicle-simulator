#! /usr/bin/env sh

# Exit in case of error
set -e

sourceEdge="165666070#0"
targetEdge="99185911#2"


python3 /root/sumo/tools/findAllRoutes.py -n "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.net.xml" -o "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.rou.xml" -s "${sourceEdge}" -t "${targetEdge}"
