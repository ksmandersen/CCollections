\NeedsTeXFormat{LaTeX2e}[1994/06/01]
\ProvidesClass{ituthesis}[2012/09/06 A document class for IT University of Copenhagen theses and reports]

%% This document class is based on memoir
\LoadClass[a4paper, 12pt, twoside, openright, onecolumn, final]{memoir}

\RequirePackage[danish,english]{babel}
\RequirePackage{csquotes}
\RequirePackage{ifthen}


%% Graphics
\RequirePackage{tikz}
\usetikzlibrary{positioning}

%% Listings
\RequirePackage{listings}
\lstset{frame=tb,
%  aboveskip=3mm,
%  belowskip=3mm,
  showstringspaces=false,
  basicstyle={\small\ttfamily},
  numbers=none,
  keywordstyle=\bfseries,
  commentstyle=\itshape,
  numberbychapter=true,
  captionpos=b
}

\lstnewenvironment{code}[1][]%
{
   \lstset{#1}
}{
}
\definecolor{shadecolor}{gray}{0.9}
\newenvironment{aside}{
  \noindent\begin{shaded}
  \begin{minipage}[t]{0.05\textwidth}{\sffamily \bfseries Aside:}\end{minipage}
  \hspace{0.1\textwidth}
  \begin{minipage}[t]{0.75\textwidth}
}{
  \end{minipage}\end{shaded}
}

%% Get \maketitle to produce something nice for ITU
\setlength{\droptitle}{5cm}

%% More comprehensive math
\usepackage{amsmath}
\usepackage{amsfonts}

%% Better fonts
\usepackage[T1]{fontenc}
\usepackage{textcomp}

\usepackage{palatino}
\linespread{1.05} % palatino needs a bit more space
\usepackage[sc]{mathpazo} % math font that matches palatino
% TODO: Consider osf in mathpazo

% Use Optima for sans-serif
\renewcommand*\sfdefault{uop}

% Luxi Mono is an attractive typewriter font with bold and italic
\usepackage[scaled]{luximono}

%% Abstract sans serif
\renewcommand{\abstractnamefont}{\Large\sffamily}

%% TOC sans serif

\renewcommand{\cftpartfont}{\normalfont\sffamily\bfseries}
\renewcommand{\cftchapterfont}{\normalfont\sffamily}
\renewcommand{\cftsectionfont}{\normalfont\sffamily}
\renewcommand{\cftchapterpagefont}{\normalfont\sffamily}
\renewcommand{\cftsectionpagefont}{\normalfont\sffamily}
\setsecnumdepth{chapter}

%% Parts sans serif
\renewcommand{\parttitlefont}{\Huge\sffamily}
\renewcommand{\partnamefont}{\Huge\sffamily}
\renewcommand{\partnumfont}{\Huge\sffamily}

%% Chapter headers sans serif
\chapterstyle{default} % try also: default , section , hangnum , companion , article, demo

\renewcommand{\chaptitlefont}{\normalfont\Huge\sffamily\raggedright} % set sans serif chapter title font
\renewcommand{\chapnamefont}{\normalfont\Huge\sffamily\raggedright}
\renewcommand{\chapnumfont}{\normalfont\Huge\sffamily\raggedright} % set sans serif chapter number font

%% Section headers sans serif
%\hangsecnum % hang the section numbers into the margin to match \chapterstyle{hangnum}
\maxsecnumdepth{subsection} % number subsections

\setsecheadstyle{\Large\sffamily\raggedright} % set sans serif section font
\setsubsecheadstyle{\large\sffamily\raggedright} % set sans serif subsection font

%% Captions sans serif
\captionnamefont{\small\sffamily}
\captiontitlefont{\small\sffamily}
\subcaptionfont{\footnotesize\sffamily}
\subcaptionlabelfont{\footnotesize\sffamily}

%% Page headings
\nouppercaseheads
\copypagestyle{ituheadings}{headings}
\makeevenhead{ituheadings}{\sffamily\thepage}{}{\normalfont\sffamily\leftmark}
\makeoddhead{ituheadings}{\normalfont\sffamily\rightmark}{}{\sffamily\thepage}
\pagestyle{ituheadings}

\makeevenfoot{plain}{}{\sffamily\thepage}{}
\makeoddfoot{plain}{}{\sffamily\thepage}{}

%% Mark term definitions
\newcommand{\termfont}{\itshape}
%\newcommand{\term}[1]{\marginpar{\termfont #1} {\termfont #1}} % Uncomment for margin terms
\newcommand{\term}[1]{{\termfont #1}}

\newlength{\linespace}
\setlength{\linespace}{\baselineskip}

%%%% for the title page and approval page.
\newlength{\toptafiddle}
\setlength{\toptafiddle}{2\linespace}
\newlength{\bottafiddle}
\setlength{\bottafiddle}{0pt}
\newlength{\topfiddle}
\setlength{\topfiddle}{\toptafiddle}
\newlength{\botfiddle}
\setlength{\botfiddle}{\onelineskip}

% your title
\newcommand{\settitle}[1]{\def\itutitle{#1}}
% you
\newcommand{\setauthor}[1]{\def\ituauthor{#1}}
% your supervisor
\provideboolean{itumultisup}
\setboolean{itumultisup}{false}
\newcommand{\setsupervisor}[1]{\def\itusupervisor{#1}}
\newcommand{\setextrasupervisor}[1]{
  \def\itusupervisorextra{#1}
  \setboolean{itumultisup}{true}}
% submission date
\newcommand{\setdate}[1]{\def\itudate{#1}}


%%% typesets the TITLE page
\newcommand{\thetitlepage}{
  \thispagestyle{empty}
  \begin{tikzpicture}[remember picture,overlay,line width=0mm,shift=(current page.center)]
    \node[align=center,font=\sffamily\Huge] (title) at (0, 3cm){
      \itutitle
    };
    \node[align=center,font=\sffamily\Large] (author) at (0, 1cm){
      \ituauthor
    };
  \end{tikzpicture}
  \begin{tikzpicture}[remember picture,overlay,line width=0mm,shift=(current page.south west), align=left, font=\sffamily\large]
    \node[anchor=south west] (meta) at (2.5cm, 2.5cm) {
      \begingroup
        \begin{tabular}{l@{ }l}
          \iflanguage{danish}{
            Vejleder\ifthenelse{\boolean{itumultisup}}{e}{}:
          }{
            Supervisor\ifthenelse{\boolean{itumultisup}}{s}{}:
          } & \itusupervisor\\
          \ifthenelse{\boolean{itumultisup}}{& \itusupervisorextra \\}{}
          \iflanguage{danish}{Afleveret}{Submitted}: & \itudate
        \end{tabular}
      \endgroup
    };
  \end{tikzpicture}

  \begin{tikzpicture}[remember picture,overlay,line width=0mm,shift=(current page.south east)]
    \node[anchor=south east] (logo) at (-2.5cm,2.5cm) {
      \iflanguage{danish}{
        \includegraphics[width=7cm]{dansk}
      }{
        \includegraphics[width=7cm]{english}
      }
    };
  \end{tikzpicture}
}