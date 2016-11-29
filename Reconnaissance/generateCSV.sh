#! /bin/bash
## usage : generateCSV ImagesDir
rm ../../Reconnaissance/learning.csv
python3 ../../Reconnaissance/ScriptCSV.py $1 >> ../../Reconnaissance/learning.csv


