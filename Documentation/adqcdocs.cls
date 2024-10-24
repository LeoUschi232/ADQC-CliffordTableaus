\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{adqcdocs}[2024/10/24 v1.0]
\LoadClass[notitlepage]{article}

% Packages without parameters
\RequirePackage{amsfonts}
\RequirePackage{amsmath}
\RequirePackage{amssymb}
\RequirePackage{bbold}
\RequirePackage{bbm}
\RequirePackage{braket}
\RequirePackage{caption}
\RequirePackage{svg}
\RequirePackage{eso-pic}
\RequirePackage{etoolbox}
\RequirePackage{fancyhdr}
\RequirePackage{float}
\RequirePackage{geometry}
\RequirePackage{graphicx}
\RequirePackage{hyperref}
\RequirePackage{indentfirst}
\RequirePackage{mathtools}
\RequirePackage{needspace}
\RequirePackage{parskip}
\RequirePackage{ragged2e}
\RequirePackage{relsize}
\RequirePackage{setspace}
\RequirePackage{stmaryrd}
\RequirePackage{subcaption}
\RequirePackage{tikz}
\RequirePackage{tikz-3dplot}
\RequirePackage{titling}
\RequirePackage{tocloft}
\RequirePackage{todonotes}
\RequirePackage{wasysym}

% Packages with parameters
\RequirePackage[main=english,german]{babel}
\RequirePackage[backend=biber,style=numeric-comp,sorting=none]{biblatex}
\RequirePackage[scaled]{helvet}
\RequirePackage[nobottomtitles]{titlesec}
\RequirePackage[html]{xcolor}

% Set defaults of the packages
\renewcommand*\familydefault{\sfdefault}
\geometry{a4paper,total={170mm,257mm},left=20mm,top=20mm}
\setstretch{1.25}
\setlength{\parskip}{6pt}
\usetikzlibrary{3d, calc, backgrounds,angles, quotes, shapes.geometric, decorations.markings, perspective, arrows, arrows.meta}

% Define options and commands
\DeclareMathOperator{\ele}{\mathcal{E}}
\DeclareMathOperator{\sgn}{sgn}
\DeclareMathOperator{\re}{Re}
\DeclareMathOperator{\im}{Im}
\DeclareMathOperator{\qber}{QBER}
\DeclareMathOperator{\const}{const}
\DeclareMathOperator{\miniAnd}{\quad\wedge\quad}
\DeclareMathOperator{\tacticalAnd}{\qquad\wedge\qquad}
\DeclareMathOperator{\equi}{\Longleftrightarrow\qquad}
\DeclareMathOperator{\means}{\quad\Longrightarrow\quad}
\DeclareMathOperator{\unit}{\mathbbm{1}}
\DeclareMathOperator{\natur}{\mathbbm{N}}
\DeclareMathOperator{\tqber}{\overline{\tau}}

\DeclarePairedDelimiter\ceil{\lceil}{\rceil}
\DeclarePairedDelimiter\floor{\lfloor}{\rfloor}
\DeclarePairedDelimiter\pbrack{\left(}{\right)}
\DeclarePairedDelimiter\bbrack{\left[}{\right]}
\DeclarePairedDelimiter\sbrack{\left\{}{\right\}}

\newenvironment{noidenthere}
{\setlength{\parindent}{0pt}}
{}

\newcommand{\noidentfromhere}{\setlength{\parindent}{0pt}}
\newcommand{\indentfromhere}{\setlength{\parindent}{6pt}}
\newcommand{\citeright}[1]{%
        {\raggedleft\cite{#1}\par}%
}
\newcommand{\citeleft}[1]{%
        {\raggedright\cite{#1}\par}%
}

% Define colors
\definecolor{steel}{HTML}{4683b7}
\definecolor{carolina}{HTML}{57a0d3}
\definecolor{page_number_background}{HTML}{cee1f3}
\definecolor{title_line}{HTML}{5b9bd5}
\definecolor{title_text}{HTML}{2e74b5}
\definecolor{stokes_parameter_blue}{HTML}{7094C0}
\definecolor{stokes_parameter_red}{HTML}{973550}
\definecolor{stokes_parameter_purple}{HTML}{351238}

