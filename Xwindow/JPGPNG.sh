#!/bin/bash
for nazwa in *JPG
do
    NEWNAME="${nazwa/%.JPG/.jpg}"
    mv  "$nazwa" "$NEWNAME"
done

for nazwa in *PNG
do
    NEWNAME="${nazwa/%.PNG/.png}"
    mv  "$nazwa" "$NEWNAME"
done
