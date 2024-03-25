---
title: "Ćwiczenie 11: Obsługa sterownika wyświetlacza alfanumerycznego HD44780"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
  \usepackage{tikz}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
  \usepackage{lcd}
  \LCDcolors[MidnightBlue]{MidnightBlue!10}{MidnightBlue!80}
...

\lstset{language=[11]C++}

> Programming is the art of telling another human being what one wants the computer to do.
>
> — _Donald E. Knuth_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* wymaganiami czasowymi w komunikacji z urządzeniami zewnętrznymi,
* wyświetlaniem tekstu na wyświetlaczach alfanumerycznych,
* prostymi operacjami na łańcuchach znaków.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _LCD Keypad Shield_ do _Arduino Uno_.
1. Wyświetlacz nie wyświetla żadnych znaków lub wyświetla przypadkowe symbole.

Używany wyświetlacz oparty jest na sterowniku Hitachi HD44780. Jest to sterownik wyświetlacza alfanumerycznego, czyli takiego, który jest w stanie wyświetlać tylko określony zestaw predefiniowanych znaków, np. liter, cyfr czy innych znaków z zakresu ASCII[^1]. Uniemożliwia to lub co najmniej mocno ogranicza wyświetlanie dowolnych kształtów, ale odciąża mikrokontroler od renderowania fontu i&nbsp;znacząco upraszcza sterowanie.

[^1]: _American Standard Code for Information Interchange_.

\awesomebox[gray]{2pt}{\faMonument}{gray}{Sterownik HD44780 został opracowany przez firmę Hitachi w latach 80. XX wieku i~jest używany do dziś. Oprócz znaków ASCII niektóre wersje są w stanie wyświetlać również inne symbole, np.japońskie pismo sylabiczne kana. Dostępne są wyświetlacze LCD, OLED i VFD zgodne z interfejsem HD44780.}

W tym przykładzie komunikacja ze sterownikiem została uproszczona do minimum. Szyna komunikacyjna została zredukowana z 8 bitów do 4 bitów, a linię $R/\overline{W}$ zwarto na stałe do masy, skutkiem czego niemożliwy jest odczyt odpowiedzi wyświetlacza na wysyłane komendy.

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{W systemach wbudowanych często wykorzystujemy uproszczone magistrale, nawet jeżeli spowalnia to komunikację lub ogranicza funkcjonalność. Pozwala to bowiem zastosować mikrokontroler o mniejszej liczbie wyprowadzeń, co obniża koszt i~wymiary urządzenia.}

# Zadanie podstawowe

Celem zadania podstawowego jest uzupełnienia sterownika wyświetlacza, tak by dokonywał poprawnej konfiguracji i umożliwiał wyświetlanie łańcuchów znaków.

## Wymagania funkcjonalne

1. Wyświetlacz wyświetla tekst \textLCD[0]{13}+Hello, world!+ począwszy od trzeciej kolumny drugiego wiersza.
1. Kursor jest niewidoczny.

\begin{center}
\LCD{2}{16}
    ||
    |  Hello, world!|
\captionof{figure}{Oczekiwany stan wyświetlacza}
\end{center}

## Modyfikacja programu

### Konfiguracja wyświetlacza

Uzupełnij metodę `LcdDisplay::init()`. Inicjalizuje ona szynę danych `bus`, a następnie wysyła z&nbsp;jej pomocą 5 instrukcji do kontrolera HD44780, zgodnie z zalecaną procedurą inicjalizacji i konfiguracji. Ponieważ linia $R/\overline{W}$ nie jest podłączona, nie ma możliwości, by uzyskać z wyświetlacza informację o&nbsp;zakończeniu przerwarzania instrukcji. Maksymalny czas obsługi każdej z instrukcji jest zadeklarowany przez producenta sterownika, więc wystarczy po każdej z 5 komend `bus.instructionWrite()` odmierzyć odpowiedni interwał.

\awesomebox[violet]{2pt}{\faBook}{violet}{Skorzystaj z tabeli \textit{Instructions} dokumentacji kontrolera HD44780.}

\awesomebox[teal]{2pt}{\faCode}{teal}{Ponieważ odmierzamy krótkie odcinki czasu i to tylko w momencie aktualizowania wyświetlacza, nieopłacalne jest implementowanie ich odmierzania za pomocą timera. Użyj funkcji \lstinline{_delay_us()} i \lstinline{_delay_ms()}.}

### Przesuwanie kursora

Uzupełnij metodę `LcdDisplay::goTo(uint8_t line, uint8_t column)`, by przesunąć kursor na wyznaczoną pozycję za pomocą instrukcji _Set DDRAM address_, która ustawia adres pozycji w&nbsp;pamięci _Display Data_.

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Niezależnie od fizycznej szerokości wyświetlacza pojedyncza linia ma długość 64 (\texttt{0x40}) znaków.}

\awesomebox[teal]{2pt}{\faCode}{teal}{Kod instrukcji \textit{Set DDRAM addres} został zdefiniowany w pliku \texttt{lcdDisplayInstruction.hpp} jako \lstinline{SET_DDRAM_ADDRESS}.}

Na tym etapie na wyświetlaczu będzie widoczna litera _a_ wypisana przez polecenie w funkcji `main()`:

```
lcdDisplay.write('a');
```

\begin{center}
\LCD{2}{16}
    |a{fcur} |
    ||
\captionof{figure}{Stan wyświetlacza}
\end{center}

Przesuń kursor na odpowiednią pozycję, dopisując w funkcji `main()`:

```
lcdDisplay.goTo(1, 2);
```

### Wyświetlanie łańcucha znaków

Uzupełnij metodę `LcdDisplay::write(const char* text)`, by wyświetlić łańcuch znaków w funkcji `main()` za pomocą:

```
lcdDisplay.write("Hello, world!");
```

Zwróć uwagę, że łańcuch znaków w językach C i C++[^2] to tablica znaków zakończonych wartością `0`, zatem literał łańcuchowy zapisany za pomocą cudzysłowów:

[^2]: W języku C++ istnieje jeszcze klasa `std::string`, która ma znacznie większe możliwości przetwarzania tekstu, ale nie jest zaimplementowana w kompilatorze AVR-GCC.

```
const char* foo = "Hello!";
```

może być traktowany jako tablica znaków[^3]:

```
const char foo[] = {'H', 'e', 'l', 'l', 'o', '!', 0};
```

[^3]: Zwróć uwagę, że zapisanie łańcucha znaków o długości $N$ wymaga $N + 1$ bajtów.

### Usunięcie kursora

Zmodyfikuj opcje instrukcji _Display on/off control_ (`DISPLAY_CONTROL`) w metodzie `LcdDisplay::init()`, by wyłączyć wyświetlanie kursora.

# Zadanie rozszerzone

Zdefiniuj dwa własne symbole i wyświetl je na początku wyświetlacza.

## Wymagania funkcjonalne

1. Oprócz napisu \textLCD[0]{13}+Hello, world!+ na początku wyświetlacza wyświetlane są zdefiniowane przez Ciebie symbole.

\DefineLCDchar{user0}{10000110001110011110111001100010000}
\DefineLCDchar{user1}{00001000110011101111001110001100001}
\begin{center}
\LCD{2}{16}
    |{user0}{user1} |
    |  Hello, world!|
\captionof{figure}{Przykładowy stan wyświetlacza}
\end{center}

## Modyfikacja programu

### Projektowanie symboli

Zaprojektuj dwa symbole, według poniższego schematu. Skorzystaj z szablonu zamieszczonego w&nbsp;sprawozdaniu.

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
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem[colback=black,colframe=black] \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem[colback=black,colframe=black] \tcbitem[colback=black,colframe=black] \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem[colback=black,colframe=black] \tcbitem \tcbitem \tcbitem \tcbitem
    \tcbitem[colback=white] \vphantom{-} \tcbitem[colback=white] \tcbitem[colback=white] \tcbitem \tcbitem \tcbitem \tcbitem \tcbitem
\end{tcbitemize}
\end{minipage}
\captionof{figure}{Przykład własnego symbolu}

```
constexpr uint8_t RIGHT_TRIANGLE[] = {
    0b00010000,
    0b00011000,
    0b00011100,
    0b00011110,
    0b00011100,
    0b00011000,
    0b00010000,
    0b00000000,
};
```

### Dodawanie symboli do sterownika

Dodaj zaprojektowane symbole do pamięci CGRAM, przekazując je do metody `LcdDisplay::addSymbol()` jako symbole o numerach \texttt{0} i \texttt{1}, np.:

```
lcdDisplay.addSymbol(RIGHT_TRIANGLE, 0);
lcdDisplay.addSymbol(LEFT_TRIANGLE, 1);
```

Uzupełnij metodę `LcdDisplay::addSymbol()`, tak by zapisywała tablicę, otrzymaną w&nbsp;argumencie `symbol`, w pamięci CGRAM (_Character Generator RAM_) pod adresem zależnym od argumentu `position`. Użyj instrukcji _Set CGRAM address_, by ustawić adres, i metody `bus.dataWrite()`[^4], by zapisać dane.

[^4]: Tak, tej samej, której używa się do zapisywania tekstu w pamięci DDRAM.

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Bajty symboli są ułożone w pamięci CGRAM jeden po drugim. Kolejne bajty pierwszego symbolu należy zatem zapisywać pod adresami \texttt{0}…\texttt{7}, a drugiego — \texttt{8}…\texttt{15}.}

\awesomebox[teal]{2pt}{\faCode}{teal}{Użyj pętli \lstinline{for()}, by powtórzyć operacje adresowania i zapisu dla każdego bajtu symbolu.}

\awesomebox[teal]{2pt}{\faCode}{teal}{Kod instrukcji \textit{Set CGRAM addres} został zdefiniowany w pliku \texttt{lcdDisplayInstruction.hpp} jako \lstinline{SET_CGRAM_ADDRESS}.}

### Wyświetlanie symboli

Wyświetl zdefiniowane symbole w funkcji `main()`. Numer znaku możesz wskazać w postaci liczbowej za pomocą sekwencji `\x`:

```
lcdDisplay.write('\x00');
lcdDisplay.write('\x01');
```
