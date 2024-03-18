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
...

> Programming is the art of telling another human being what one wants the computer to do.
>
> — _Donald E. Knuth_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* wymaganiami czasowymi w komunikacji z urządzeniami zewnętrznymi,
* wyświetlaniem tekstu na wyświetlaczach alfanumerycznych,
* prostymi operacjami na łańcuchach znaków.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _WPSH209_ do _Arduino Uno_.
1. Wyświetlacz wskazuje wartość `8.888`.

# Zadanie podstawowe

Celem zadania podstawowego jest zaprogramowanie miernika refleksu. Urządzenie ma co około 10 sekund rozpoczynać odliczanie sygnalizowane sygnałem świetlnym lub dźwiękowym, które użytkownik ma jak najszybciej zatrzymać wciśnięciem przycisku _S1_. Czas między sygnałem a wciśnięciem przycisku ma być mierzony z rozdzielczością 1&nbsp;ms.

## Wymagania funkcjonalne

1. Po kilku–kilkunastu sekundach od uruchomienia zaświecana jest dioda _D1_ i/lub uruchamiany jest buzzer _LS1_. Rozpoczyna się odmierzanie czasu na wyświetlaczu.
1. Po chwili (np. 20&nbsp;ms) dioda i/lub buzzer są wyłączane.
1. Po wciśnięciu przycisku _S1_ odliczanie czasu zostaje zatrzymane i można go odczytać z&nbsp;wyświetlacza.
1. Po kilku–kilkunastu sekundach cykl pracy rozpoczyna się od nowa.

## Modyfikacja programu

Implementację programu najlepiej podzielić na kroki, pozwalające stopniowo realizować żądaną funkcjonalność.

Do odmierzania czasu można użyć timera _Timer/Counter1_, który dzięki 16-bitowej rozdzielczości pozwoli zachować odpowiednią rozdzielczość pomiaru.

### Wyświetlanie stanu timera

W funkcji `currentTime()` zwróć wartość licznika `TCNT1`.

Na wyświetlaczu będzie widoczna domyślna wartość tego rejestru, tj. 0.

### Uruchomienie timera

W celu uruchomienia timera należy za pomocą bitów `CS10`…`CS12` podać sygnał zegarowy o&nbsp;częstotliwości, która umożliwi odliczenie czasu rzędu kilku sekund. Możesz zrobić to w pętli głónwej `mainLoop()`, dzięki czemu odliczanie będzie mogło być cyklicznie wznawiane.

Na wyświetlaczu będzie widoczne odliczanie licznika `TCNT1`.

### Przeskalowanie czasu

Przelicz wartość zwracaną przez `currentTime()`, tak by była wyrażona w milisekundach.

### Opóźnienie startu

Opóźnij start odliczania dodając wywołanie funkcji `_delay_ms()` w pętli głównej.

\awesomebox[teal]{2pt}{\faCode}{teal}{Ponieważ pomiar czasu następuje za pomocą timera, a przycisk obsługiwany jest w~przerwaniu, umieszczanie w pętli głównej odliczania czasu za pomocą \lstinline{_delay_ms()} (co blokuje program na czas odliczania interwału) nie stanowi problemu.}

### Zatrzymanie odliczania

Aby po wciśnięciu przycisku jak najszybciej zatrzymać odliczanie, należy użyć przerwania.

Aby włączyć przerwanie od przycisku `S1` należy w funkcji `interruptsInitialize()` włączyć przerwanie `PCINT1` dla wejścia `PCINT9`[^1]:

[^1]: Tak, w tym mikrokontrolerze `PCINT` raz oznacza przerwanie od GPIO, a raz pin wywołujący to przerwanie…

```cpp
PCMSK1 |= _BV(PCINT9);
PCICR |= _BV(PCIE1);
```

W obsłudze tego przerwania (`ISR(PCINT1_vect)`) zatrzymaj pracę timera przez wyłączenie sygnału zegarowego.

### Resetowanie timera

Na początku każdego cyklu (po odmierzeniu opóźnienia za pomocą `_delay_ms()`) wyzeruj licznik timera, tak by pomiar czasu zaczynał się zawsze od zera.

### Sygnalizacja rozpoczęcia odliczania

Bezpośrednio po lub bezpośrednio przed włączeniem timera[^2] w pętli głównej włącz buzzer i/lub LED. Wyłącz je po krótkiej chwili, do odmierzenia której też możesz użyć `_delay_ms()`.

[^2]: Nie da się tego zrobić jednocześnie, gdyż nie da się w jednej instrukcji zapisać danych do kilku rejestrów.

# Zadanie rozszerzone

Celem zadania rozszerzonego jest usunięcie możliwości oszukiwania urządzenia przez użytkownika.

## Wymagania funkcjonalne

1. Po przepełneniu timera odliczanie jest zatrzymywane.
1. Ciągłe wciskanie i puszczanie przycisku opóźnia start odliczania, żeby nie było możliwe w ten sposób uzyskanie niskiego wyniku (falstart).

## Modyfikacja programu

Przepełnienie timera można obsłużyć w przerwaniu `TIMER1_OVF_vect`. Włącza się je za pomocą flagi `TOIE1`.

Obsłużenie falstartu można zrealizować przez ustawianie dodatkowej zmiennej w przerwaniu od przycisku i sprawdzaniu jej w pętli głównej.
