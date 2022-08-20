export $(cat ../.env | sed 's/#.*//g' | xargs)


sh ./download-map.sh

sh ./netconvert.sh

sh ./polyconvert.sh