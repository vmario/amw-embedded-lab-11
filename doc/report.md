---
title: "Ćwiczenie 11: Obsługa sterownika wyświetlacza alfanumerycznego HD44780"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: no
colorlinks: yes
header-right: "\\faEdit"
footer-left: "Sprawozdanie z laboratorium"
header-includes: |
  \usepackage{awesomebox}
  \usepackage{tikz}
  \usetikzlibrary{positioning}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
...

\lstset{language=[11]C++}

_W trosce o Państwa wyniki proszę o czytelne wpisywanie nazwisk._

**Data**: \dotfill

**Autorzy**: \dotfill

# Część praktyczna

## Zadanie podstawowe

**Ocena prowadzącego**: \dotfill

## Zadanie rozszerzone

**Ocena prowadzącego**: \dotfill

# Część teoretyczna

## Zadanie podstawowe

Ile maksymalnie znaków wyświetlacza może obsłużyć sterownik HD44780?

\vspace{1.5cm}

Oszacuj czas potrzebny na zapisanie całej zawartości wyświetlacza.

\vspace{1.5cm}

## Zadanie rozszerzone

Ile bajtów w pamięci symboli zajmuje jeden symbol?

\vspace{1.5cm}

Ile własnych symboli można zdefiniować w sterowniku HD44780?

\vspace{1.5cm}

\begin{minipage}{0.2\linewidth}
\tcbset{size=small, colback=white, halign=center, valign=bottom, sharp corners}
\begin{tcbitemize}[raster row skip=-.5mm, raster column skip=-.5mm, raster equal height=rows,
        left=0mm, right=0mm,
        raster columns=8, colframe=white, coltext=gray, fontupper=\footnotesize]
    \tcbitem 7 \tcbitem 6 \tcbitem 5 \tcbitem 4 \tcbitem 3 \tcbitem 2 \tcbitem 1 \tcbitem 0
\end{tcbitemize}
\begin{tcbitemize}[raster row skip=.5mm, raster column skip=.5mm, raster equal height=rows,
        left=0mm, right=0mm,
        raster columns=8, colframe=black!10, colback=black!10]
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
\end{tcbitemize}
\end{minipage}
\captionof{figure}{Szablon pierwszego znaku}

\vspace{5cm}

\begin{minipage}{0.2\linewidth}
\tcbset{size=small, colback=white, halign=center, valign=bottom, sharp corners}
\begin{tcbitemize}[raster row skip=-.5mm, raster column skip=-.5mm, raster equal height=rows,
        left=0mm, right=0mm,
        raster columns=8, colframe=white, coltext=gray, fontupper=\footnotesize]
    \tcbitem 7 \tcbitem 6 \tcbitem 5 \tcbitem 4 \tcbitem 3 \tcbitem 2 \tcbitem 1 \tcbitem 0
\end{tcbitemize}
\begin{tcbitemize}[raster row skip=.5mm, raster column skip=.5mm, raster equal height=rows,
        left=0mm, right=0mm,
        raster columns=8, colframe=black!10, colback=black!10]
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
\end{tcbitemize}
\end{minipage}
\captionof{figure}{Szablon drugiego znaku}

