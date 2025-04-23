\NeedsTeXFormat{LaTeX2e}

\LoadClass[11pt]{article}

% ===== Basic Packages =====
\RequirePackage[spanish]{babel}
\RequirePackage{fontspec}
\RequirePackage{hyperref}
\RequirePackage{listings}
\RequirePackage{xcolor}
\RequirePackage{graphicx}
\RequirePackage{amsmath}
\RequirePackage{hyperref}
\RequirePackage{titlesec}

% ===== Page Layout =====
\RequirePackage[top=2cm, bottom=2cm, left=2.5cm, right=2.5cm]{geometry}

% ===== Hyperref Setup =====
\hypersetup{
	colorlinks=true,
	linkcolor=blue,
	filecolor=magenta,
	urlcolor=cyan,
	pdftitle={Análisis de Algoritmos - Tarea 1},
}

% ===== Title Formatting =====
\renewcommand{\maketitle}{
	\begin{center}
		{\LARGE\bfseries \@title \par}
		\vspace{0.5em}
		{\large \@author \par}
		\vspace{0.5em}
		{\large \@date \par}
	\end{center}
	\vspace{1em}
	\hrule
	\vspace{1em}
}

\titleformat{\subsubsection}{\normalfont\bfseries}{\thesubsubsection}{1em}{}

% ===== Listings Setup =====
\definecolor{codegreen}{rgb}{0,0.6,0}
\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\definecolor{codepurple}{rgb}{0.58,0,0.82}
\definecolor{backcolour}{rgb}{0.95,0.95,0.92}

\lstdefinestyle{cpp}{
    language=C++,
	basicstyle=\footnotesize\ttfamily,
	keywordstyle=\color{blue},
	commentstyle=\color{gray},
	% stringstyle=\color{red},
	showstringspaces=false,
	tabsize=1,
	numberstyle=\color{gray},
	escapeinside={<|}{|>},
	frame=tb
}

\lstdefinestyle{bash}{
    language=bash,
    basicstyle=\footnotesize\ttfamily,
    showstringspaces=false,
    commentstyle=\color{black},
    frame=tb
}

% ===== Custom Commands =====
\newcommand{\code}[1]{\texttt{#1}}
\newcommand{\order}{$\sim$}
\newcommand{\delt}{\ensuremath{\delta}}

\newcommand{\bigo}[1]{\ensuremath{\mathcal{O}(#1)}}
\newcommand{\smallo}[1]{\ensuremath{o(#1)}}

\newcommand{\eq}{\ensuremath{\quad \Leftrightarrow \quad}}
\newcommand{\larrow}{\ensuremath{\quad \Leftarrow \quad}}
\newcommand{\rarrow}{\ensuremath{\quad \Rightarrow \quad}}

% ===== Section Formatting =====
\RequirePackage{titlesec}
\titleformat{\section}{\large\bfseries}{\thesection}{1em}{}
\titleformat{\subsection}{\bfseries}{\thesubsection}{1em}{}
\titleformat{\subsubsection}{\itshape}{\thesubsubsection}{1em}{}

% ===== Figure Defaults =====
\RequirePackage{float}
\floatplacement{figure}{H}

% ===== Subfiles Support =====
\RequirePackage{subfiles}

