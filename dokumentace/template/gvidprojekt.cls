% -----------------------------------------------------------
% Šablona pro ročníkový projekt na Gymnáziu Vídeňská
% Tato šablona je vytvořena pro XeLaTeX a vyžaduje novější distribuci LaTeXu.
% Autor: David Martinek, 2017--2023
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{gvidprojekt}[2023/05/02 Sablona pro RP na GVID]
\def\@version{2.5}
% -----------------------------------------------------------

% Výchozí je třída memoir
\LoadClass[a4paper, twoside, openany, 12pt]{memoir}

% Parametry třídy
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{memoir}}
\ProcessOptions\relax

% -----------------------------------------------------------
% Texty pro případný překlad do jiného jazyka
% Zatím se jiný jazyk než čeština nepoužívá
\def\@tgvid@CZ{Gymnázium Brno, Vídeňská, příspěvková organizace}
\def\@tgvid@EN{Grammar school Brno, Videnska, funded organization}
\def\@tauthor@CZ{Autor práce}
\def\@tauthor@EN{Author}
\def\@tabstract@CZ{Abstrakt}
\def\@tabstract@EN{Abstract}
\def\@tkeywords@CZ{Klíčová slova}
\def\@tkeywords@EN{Keywords}
\def\@tcopyright@CZ{Tato práce vznikla jako školní dílo na škole Gymnázium Brno, Vídeňská, příspěvková organizace. Práce je chráněna autorským zákonem a~její užití bez udělení oprávnění autorem je nezákonné, s~výjimkou zákonem definovaných případů. Autor souhlasí s~archivací této práce a~s~jejím použitím pro studijní účely na výše zmíněné škole a~jejích případných právních nástupcích.}
\def\@tcopyright@EN{This work was created as school work at the Grammar school Brno, Videnska, funded organization. This work is copyrighted and its use without the author's permission is illegal, except in cases defined in law. The author agrees with archiving and using of this work for educational purposes at the aforementioned school and its possible legal successors.}
\def\@tdeclaration@CZ{Prohlášení}
\def\@tdeclaration@EN{Declaration}
\def\@tacknowledgement@CZ{Poděkování}
\def\@tacknowledgement@EN{Acknowledgment}
\def\@cite@CZ{Citace}
\def\@cite@EN{Citation}
\def\@forcourse@CZ{pro}
\def\@forcourse@EN{for}

% -----------------------------------------------------------
% Balíčky
\RequirePackage{polyglossia}
\setdefaultlanguage{czech}

% české uvozovky
\newcommand{\uv}[1]{„#1“}

% Národní uvozovky. Umí české i jiné uvozovky podle zapnutého jazyka. Základní příkaz je \enquote{text}. Tento balík je tu zejména kvůli biblatexu.
\RequirePackage{csquotes}


% Sázení loga \XeLaTeX
\RequirePackage{metalogo}


% Nastavení fontů pro XeLaTeX je velmi přirozené – k dispozici 
% jsou všechny fonty dostupné uživateli standardní cestou 
% v operačním systému. Používají se i jejich obvyklá jména.
% \defaultfontfeatures{Scale=MatchLowercase, Mapping=tex-text, WordSpace = 1.2} 
\defaultfontfeatures{Scale=MatchLowercase, Mapping=tex-text}
% \setromanfont{DejaVuSerifCondensed} % Výběr patkového (základního) fontu.
\setromanfont{DejaVuSerif} % Výběr patkového (základního) fontu.
\setsansfont{DejaVuSans} % Výběr bezpatkového fontu.
\setmonofont{DejaVuSansMono} % Výběr neproporcionálního fontu.
% \setmathfont{Asana Math} % Výběr matematického fontu. Jen, když funguje balík unicode-math.


\RequirePackage[top=3cm, head=15pt, left=2cm, right=2cm, bottom=2cm, marginpar=1.5cm]{geometry}

% Matematické balíčky
\RequirePackage{amsmath}
\RequirePackage{amssymb}
\RequirePackage{amsfonts}
\RequirePackage{eucal}

% umí zmenšit mezery mezi položkami výčtů
\RequirePackage{enumitem}
\setlist[itemize]{itemsep=0pt, topsep=1mm, partopsep=0pt, leftmargin=1.2em}
\setlist[enumerate]{itemsep=0pt, topsep=1mm, partopsep=0pt, leftmargin=1.2em}

% proti vdovám a sirotkům
\RequirePackage[all]{nowidow}


\RequirePackage{url}
\DeclareUrlCommand\url{\def\UrlLeft{<}\def\UrlRight{>} \urlstyle{tt}}

\RequirePackage[xetex]{pstricks}

\RequirePackage{xcolor}
\definecolor{darkblue}{HTML}{000080}
\definecolor{darkred}{HTML}{800000}
\definecolor{darkgreen}{HTML}{008000}
\definecolor{darkbrown}{HTML}{804000}
% Nová modrá je světlejší
\definecolor{gvidblue}{RGB}{39,68,160}

%-----------------------------------------------------------------------------
% Projectinfo - parametrizace sablony
%-----------------------------------------------------------------------------
%Parametry
\define@key{projinfo}{title}{\global\def\@title{#1}}
\define@key{projinfo}{subtitle}{\global\def\@subtitle{#1}}
\define@key{projinfo}{type}{\def\@type{#1}}
\define@key{projinfo}{course}{\def\@course{#1}}
\define@key{projinfo}{school}{\def\@school{#1}}
\define@key{projinfo}{logo}{\def\@logo{#1}}
\define@key{projinfo}{icon}{\def\@icon{#1}}
\define@key{projinfo}{date}{\def\@date{#1}}
\define@key{projinfo}{author}{\def\@author{#1}}
\define@key{projinfo}{authorsclass}{\def\@authorsclass{#1}}
\define@key{projinfo}{keywords}{\def\@keywords{#1}}
\define@key{projinfo}{abstract}{\def\@abstract{#1}}
\define@key{projinfo}{declaration}{\def\@declaration{#1}}
\define@key{projinfo}{acknowledgment}{\def\@acknowledgment{#1}}

%Výchozí hodnoty
\setkeys{projinfo}{title={Šablona školní práce v. \@version},
  type={Ročníkový projekt},
  school={\@tgvid@CZ},
  logo={img/logo-gvid-blue-40mm.pdf},
  icon={img/icon-gvid-blue-40mm.pdf},
  date=\today,
  author=Donald Kačer,
}%

\def\projectinfo{\setkeys{projinfo}}

% LaTeXová makra zpřístupňující definované hodnoty
\newcommand{\templateversion}{\@version}
\newcommand{\projtitle}{\ifx\undefined\@title\else\@title\fi}
\newcommand{\projsubtitle}{\ifx\undefined\@subtitle\else\@subtitle\fi}
\newcommand{\projtype}{\ifx\undefined\@type\else\@type\fi}
\newcommand{\projcourse}{\ifx\undefined\@course\else\@course\fi}
\newcommand{\projschool}{\ifx\undefined\@school\else\@school\fi}
\newcommand{\projlogo}{\ifx\undefined\@logo\else\@logo\fi}
\newcommand{\projicon}{\ifx\undefined\@icon\else\@icon\fi}
\newcommand{\projdate}{\ifx\undefined\@date\else\@date\fi}
\newcommand{\projauthor}{\ifx\undefined\@author\else\@author\fi}
\newcommand{\projauthorsclass}{\ifx\undefined\@authorsclass\else\@authorsclass\fi}
\newcommand{\projkeywords}{\ifx\undefined\@keywords\else\@keywords\fi}
\newcommand{\projabstract}{\ifx\undefined\@abstract\else\@abstract\fi}
\newcommand{\projdeclaration}{\ifx\undefined\@declaration\else\@declaration\fi}
\newcommand{\projacknowledgment}{\ifx\undefined\@acknowledgment\else\@acknowledgment\fi}

%Prohlaseni
\newcommand{\declaration}[1]{\def\@declaration{#1}}

%Podekovani
\newcommand{\acknowledgment}[1]{\def\@acknowledgment{#1}}

%Abstrakt
\renewcommand{\abstract}[1]{\def\@abstract{#1}}

%Klicova slova
\newcommand{\keywords}[1]{\def\@keywords{#1}}

%----------------------------------------------------------------------------------------
%       titulní strana (pro memoir je to titlingpage)
%----------------------------------------------------------------------------------------

\renewcommand{\maketitle}{%
\begin{titlingpage}
\begin{center}
\begin{Large}\@school\end{Large}


\ifx\undefined\@logo\else
\vfill
\includegraphics[height=30mm]{\@logo}\\
\fi


\vfill

\begin{LARGE}
\@type
\ifx\undefined\@course\else\\\@forcourse@CZ\ \@course\fi
\end{LARGE}

\vspace{0.5cm}

\ifx\undefined\@subtitle
\begin{Huge}\textbf{\@title}\end{Huge}
\else
\begin{Huge}\textbf{\@title}\\\medskip\@subtitle\end{Huge}
\fi
\end{center}

\vfill

\begin{flushleft}
\begin{Large}\@date \hfill \@author\ifx\undefined\@authorsclass\else, \@authorsclass\fi\end{Large}
\end{flushleft}
\end{titlingpage}
}


\newlength{\mkspc}
\setlength{\mkspc}{2pt}

\def\setfontsize#1{\renewcommand{\baselinestretch}{1.5}\fontsize{#1}{\f@baselineskip}\selectfont}
%text
\newcommand{\mktxt}[2]{\vbox{\setfontsize{#1}\noindent#2}\vspace\mkspc}
%bold
\newcommand{\mktxt@b}[2]{\vbox{\setfontsize{#1}\noindent\bfseries#2}\vspace\mkspc}
\newcommand{\mkuctxt}[2]{\vbox{\setfontsize{#1}\noindent\MakeUppercase{#2}}\vspace\mkspc}
%-----------------------------------------------------------------------------
%Abstrakt, klicovaslova \makeabstract
%-----------------------------------------------------------------------------
\usepackage{xstring}
\def\getYear#1{\StrRight{#1}{4}}

\newcommand\makeabstract{%
\thispagestyle{empty}\null%

\ifx\undefined\@abstract\else%
\mktxt@b{16}{\@tabstract@CZ}\noindent\@abstract\fi

\vfill
\ifx\undefined\@keywords\else%
\mktxt@b{16}{\@tkeywords@CZ}\noindent\@keywords\fi

\vfill

\mktxt@b{16}{\@cite@CZ}
\ifx\undefined\@subtitle
\noindent\@author: \@title, \MakeLowercase{\@type}, Brno, \@school, \getYear{\@date}.
\else
\noindent\@author: \@title{} \@subtitle, \MakeLowercase{\@type}, Brno, \@school, \getYear{\@date}.
\fi
%===================================================
\newpage
\setcounter{page}{1}
}


%-----------------------------------------------------------------------------
%Prohlaseni, podekovani \makedeclaration
%-----------------------------------------------------------------------------
\newcommand\makedeclaration{
\thispagestyle{empty}%
\ifx\undefined\@subtitle
\mktxt@b{18}{\@title{}}
\else
\mktxt@b{18}{\@title{} \@subtitle}
\fi

\vfill

\ifx\undefined\@declaration\else%
\mktxt@b{16}{\@tdeclaration@CZ}
\noindent\@declaration
\begin{flushright}
    \makebox[4cm]{\dotfill} \\
    \@author\\
    \@date
\end{flushright}\fi

\vfill

\ifx\undefined\@acknowledgment
\else
\vspace{20mm}
\mktxt@b{16}{\@tacknowledgement@CZ}
\noindent\@acknowledgment
\fi

\vfill

\noindent\copyright\ \@author, \getYear{\@date}.\newline
{\em \@tcopyright@CZ}
%===================================================
\newpage
\setcounter{page}{1}
}

% Nastavení výsledného PDF, aby podporovalo hypertextové odkazy a vlastnosti dokumentu.
\RequirePackage[xetex]{hyperref}
\hypersetup{
    unicode=true,         % non-Latin characters in Acrobat’s bookmarks
    pdffitwindow=true,    % window fit to page when opened
    pdfstartview={FitH},  % fits the width of the page to the window
    pdftitle={\projtitle},   
    pdfauthor={\projauthor}, 
    pdfsubject={\projtype, \projcourse}, 
    pdfkeywords={\projkeywords},
    colorlinks=true,      % false: boxed links; true: colored links
    linkcolor=darkred,    % color of internal links
    citecolor=darkgreen,  % color of links to bibliography
    filecolor=darkbrown,  % color of file links
    urlcolor=darkblue,    % color of external links
    pageanchor=true,
%     hyperfootnotes=false,
%     hypertexnames=false,
}
% konec nastavení hyperref



\endinput
