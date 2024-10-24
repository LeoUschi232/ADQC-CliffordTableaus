#!/bin/bash

# Move to the directory of the script
cd "$(dirname "$0")" || exit

# Enter the Docs directory
cd Documentation || exit

# Start the compilation stages
echo "Documentation Compilation stage 1..."
pdflatex -interaction=nonstopmode CliffordTableausDocumentation.tex > compilation_log.txt

echo "Documentation Compilation stage 2..."
biber CliffordTableausDocumentation >> compilation_log.txt

echo "Documentation Compilation stage 3..."
pdflatex -interaction=nonstopmode CliffordTableausDocumentation.tex >> compilation_log.txt

echo "Presentation Compilation stage 1..."
cd ../Presentation || exit
pdflatex -interaction=nonstopmode CliffordTableausPresentation.tex > compilation_log.txt

echo "Presentation Compilation stage 2..."
biber CliffordTableausPresentation >> compilation_log.txt

echo "Presentation Compilation stage 3..."
pdflatex -interaction=nonstopmode CliffordTableausPresentation.tex >> compilation_log.txt

# Move back to the original directory
echo " Compilation finished"
cd ..
