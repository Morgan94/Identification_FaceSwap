#! /bin/bash
## usage : generateCSV ImagesDir
rm learning.csv
python3 ScriptCSV.py $1 >> learning.csv


