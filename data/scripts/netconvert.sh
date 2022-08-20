#! /usr/bin/env sh

# Exit in case of error
set -e

#netconvert --osm-files roads/fsa.osm.xml -o roads/fsa.net.xml

"${SUMO_HOME?Variable not set}/bin/"netconvert --xml-type-files "${SUMO_HOME?Variable not set}"/data/typemap/osmNetconvert.typ.xml,"${SUMO_HOME?Variable not set}"/data/typemap/osmNetconvertUrbanDe.typ.xml \
 --osm-files "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.osm.xml" \
 --output-file "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.net.xml" \
 --roundabouts.guess --ramps.guess \
 --junctions.join --tls.guess-signals --tls.discard-simple --tls.join \
 --plain-output-prefix "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}"
