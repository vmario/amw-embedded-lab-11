---
title: "Ćwiczenie 9: Pomiar czasu względnego za pomocą timera"
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
...

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

Rozdzielczość pomiarowa timera dla dzielnika $N$ dana jest zależnością:

\begin{equation}
\Delta t = \frac{N}{f_{clkI/O}}
\end{equation}

zaś zakres pomiarowy (dla timera 16-bitowego):

\begin{equation}
t_{max} = \Delta t (2^{16} - 1)
\end{equation}

Wyznacz oba parametry dla wybranego w części praktycznej dzielnika.

\vspace{3cm}

## Zadanie rozszerzone

_Timer/Counter1_ posiada wejście _Input Capture Pin_ (`ICP1`). Może ono niezależnie od pracy programu skopiować wartość licznikia `TCNT1` do specjalnego rejestru `ICR1` po wystąpieniu zbocza narastającego lub opadającego. Umożliwiłoby to natychmiastowy pomiar czasu, także w sytuacji gdy przerwanie od przycisku nie może być natychmiast obsłużone (z powodu obsługiwania w tym momencie innego przerwania). Do czego jest podłączony pin `ICP1` na płytce _WPSH209_? Czy można go użyć w celu ulepszenia miernika refleksu?

\awesomebox[violet]{2pt}{\faBook}{violet}{Wykorzystanie pinu \lstinline{ICP1} omówione jest w rozdziale \textit{16-bit Timer/Counter1 with PWM} w~sekcji \textit{Input Capture Unit} dokumentacji mikrokontrolera, jednak do odpowiedzi na pytanie wystarczy odczytanie połączeń ze schematów płytek \textit{Arduino Uno} i \textit{WPSH209}.}

\vspace{3cm}
