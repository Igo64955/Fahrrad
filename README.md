# Fahrrad-Kettenschaltungs-Übersetzungsrechner

Ein kleines interaktives C++-Programm zur Berechnung von Übersetzungen und
Entfaltungen für Fahrräder mit Kettenschaltung.

## Funktionen

- Eingabe von Raddurchmesser (Zoll) und Reifenbreite (mm)
- Eingabe beliebig vieler Kettenblätter (vorne, 1–5)
- Eingabe beliebig vieler Ritzel / Kassettenstufen (hinten, 1–13)
- Ausgabe der vollständigen **Übersetzungstabelle** (Übersetzung *i* und
  Entfaltung in Metern pro Kurbelumdrehung)
- Berechnung der **Gangspreizung** (größte ÷ kleinste Übersetzung in %)
- Optionale **Geschwindigkeitstabelle** für typische Kadenzen (60–100 U/min)

## Formeln

| Größe | Formel |
|---|---|
| Radumfang | `π × (Felgendurchmesser + 2 × Reifenbreite)` |
| Übersetzung *i* | `Zähnezahl vorne ÷ Zähnezahl hinten` |
| Entfaltung | `i × Radumfang` (m/U) |
| Geschwindigkeit | `Entfaltung × Kadenz × 60 ÷ 1000` (km/h) |

## Voraussetzungen

- C++17-kompatibler Compiler (g++ ≥ 7, clang++ ≥ 5, MSVC 2017+)
- `make` (optional)

## Bauen

```bash
make
# oder manuell:
g++ -std=c++17 -Wall -O2 -o fahrrad_kalkulator main.cpp
```

## Ausführen

```bash
./fahrrad_kalkulator
```

### Beispielsitzung

```
=================================================
  Fahrrad-Kettenschaltungs-Übersetzungsrechner
=================================================

Raddurchmesser (in Zoll, z. B. 28 für 28", 26 für 26"):
  Raddurchmesser [Zoll]: 28
Reifenbreite (in mm, z. B. 25 oder 40; 0 = nur Felgendurchmesser):
  Reifenbreite [mm]: 25
  → Radumfang: 2.391 m

Anzahl der Kettenblätter (vorne, 1–5):
  Kettenblätter: 2
Zähnezahl der Kettenblätter:
  Kettenblatt 1 – Zähnezahl: 34
  Kettenblatt 2 – Zähnezahl: 50

Anzahl der Ritzel / Kassettenstufen (hinten, 1–13):
  Ritzel: 3
Zähnezahl der Ritzel (Kassette):
  Ritzel 1 – Zähnezahl: 11
  Ritzel 2 – Zähnezahl: 25
  Ritzel 3 – Zähnezahl: 42

=================================================
  Übersetzungstabelle  (Übersetzung / Entfaltung)
=================================================

  Ritzel        KB 34Z        KB 50Z
               (i / m)       (i / m)
------------------------------------
    11Z     3.09/7.392   4.55/10.870
    25Z     1.36/3.252    2.00/4.783
    42Z     0.81/1.936    1.19/2.847
------------------------------------

Gangspreizung (max. / min. Übersetzung):
  Größte Übersetzung : 4.55  (Entfaltung: 10.870 m)
  Kleinste Übersetzung: 0.81  (Entfaltung: 1.936 m)
  Spreizung          : 561.5 %
```
