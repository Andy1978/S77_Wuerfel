# S77_Wuerfel
Elektronischer Würfel für den Section77 Lötkurs

## Bauteile

Umgerechnet auf einen Bausatz

Anz. | Reichelt Bestellnummer | Bezeichnung                                | Preis
-----|------------------------|--------------------------------------------|-------
1    | ATTINY 13A-PU          | Atmel AVR-RISC-Controller                  | 0,99 €
7    | SLH 56 RT              | LED, 5mm, superhell, eingefärbt, klar, rot | 0,63 €
1    | BPW 40                 | Fototransistor, Plastikgehäuse, bedrahtet  | 0,29 €
7    | METALL 220             | Metallschichtwiderstand 220 Ohm            | 0,175 €
1    | METALL 12,0K           | Metallschichtwiderstand 12,0 K-Ohm         | 0,049 €
1    | GS 8P                  | IC-Sockel, 8-polig, superflach, gedreht, vergold. | 0,18 €
1    | TASTER 9302            | Kurzhubtaster 6x6mm, Höhe: 5,0mm, 12V, vertikal | 0,10 €
1    | H25SR160               | Streifenrasterplatine, Hartpapier, 160x100mm | 1,50 €, wird noch aufgeteilt
3    | aus GP AL40 AA         | Alkaline Mignon Aus 40er Pack              | 0,79€
1    | HALTER 3XUM3-DK        | Halter für 3 Mignonzellen (AA), Druckknopf | 0,40 €
1    | CLIP HQ9V-T            | Batterieclip für 9-Volt-Block, High-Quality, T-Form | 0,30€

## Abhängigkeiten unter GNU/Linux

* avr-gcc (Compiler für AVR µController)
* avr-libc
* avrdude (zum Übertragen der firmware)
* kicad (Für den Schaltplan)

In Debian basierten Distro z.B. über
```
sudo apt-get update
sudo apt-get install gcc-avr avr-libc avrdude kicad
```
zu installieren.

## Firmware compilieren und mit avrdude über USBasp flashen
```
cd src
make
make program
```

