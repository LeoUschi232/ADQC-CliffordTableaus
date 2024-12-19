#!/bin/bash

# Move to the directory of the script
cd "$(dirname "$0")" || exit
cd Presentation || exit

export TEXINPUTS=./tum//:

echo "Presentation Compilation stage 1..."
pdflatex -interaction=nonstopmode CliffordTableausPresentation.tex > compilation_log.txt

echo "Presentation Compilation stage 2..."
biber CliffordTableausPresentation >> compilation_log.txt

echo "Presentation Compilation stage 3..."
pdflatex -interaction=nonstopmode CliffordTableausPresentation.tex >> compilation_log.txt

# Move back to the original directory
echo " Compilation finished"
cd ..
