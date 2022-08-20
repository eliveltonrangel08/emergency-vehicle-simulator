#! /usr/bin/env sh

# Exit in case of error
set -e

"${SUMO_HOME?Variable not set}/bin/"polyconvert --net-file "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.net.xml" \
--osm-files "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.osm.xml" \
--type-file "${SUMO_HOME?Variable not set}"/data/typemap/osmNetconvert.typ.xml -o "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.poly.xml"
