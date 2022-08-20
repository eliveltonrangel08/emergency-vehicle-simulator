#! /usr/bin/env sh

# Exit in case of error
set -e

#Coordenadas de Feira de Santana-BA
# SW e NE (direita para esquerda

#Full map
#latN="-12.2305"
#lonN="-38.9331"
#latS="-12.2852"
#lonS="-38.9931"

# Only center
#latN="-12.2500"
#lonN="-38.9443"
#latS="-12.2670"
#lonS="-38.9710"

# Campinas
latN="-22.90119"
lonN="-47.05707"
latS="-22.90591"
lonS="-47.06325"



wget "https://api.openstreetmap.org/api/0.6/map?bbox=${lonS},${latS},${lonN},${latN}" -O "${PATH_APP?Variable not set}/${PREFIX_FILE?Variable not set}.osm.xml"


