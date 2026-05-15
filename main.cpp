// Fahrrad Kettenschaltungs-Übersetzungs-Kalkulations-Programm
// Berechnet Übersetzungen und Entfaltungen für Fahrräder mit Kettenschaltung

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>

static const double PI = 3.14159265358979323846;

// Einlesen einer ganzen Zahl mit Bereichsprüfung
int leseInt(const std::string& eingabeText, int min, int max) {
    int wert = 0;
    while (true) {
        std::cout << eingabeText;
        if (std::cin >> wert && wert >= min && wert <= max) {
            return wert;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Ungültige Eingabe. Bitte einen Wert zwischen "
                  << min << " und " << max << " eingeben.\n";
    }
}

// Einlesen einer Fließkommazahl mit Bereichsprüfung
double leseDouble(const std::string& eingabeText, double min, double max) {
    double wert = 0.0;
    while (true) {
        std::cout << eingabeText;
        if (std::cin >> wert && wert >= min && wert <= max) {
            return wert;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Ungültige Eingabe. Bitte einen Wert zwischen "
                  << min << " und " << max << " eingeben.\n";
    }
}

// Zähne eines Kettenblatt-/Ritzel-Satzes einlesen
std::vector<int> leseZaehne(const std::string& bezeichnung, int anzahl) {
    std::vector<int> zaehne;
    zaehne.reserve(anzahl);
    for (int i = 1; i <= anzahl; ++i) {
        std::string prompt = "  " + bezeichnung + " " + std::to_string(i) +
                             " – Zähnezahl: ";
        int z = leseInt(prompt, 1, 300);
        zaehne.push_back(z);
    }
    // Aufsteigend sortieren (vorne: kleinstes zuerst → größter Gang)
    std::sort(zaehne.begin(), zaehne.end());
    return zaehne;
}

// Trennlinie ausgeben
void trennlinie(int breite) {
    std::cout << std::string(breite, '-') << '\n';
}

int main() {
    std::cout << "=================================================\n";
    std::cout << "  Fahrrad-Kettenschaltungs-Übersetzungsrechner\n";
    std::cout << "=================================================\n\n";

    // --- Raddurchmesser / Reifengröße ---
    std::cout << "Raddurchmesser (in Zoll, z. B. 28 für 28\", 26 für 26\"):\n";
    double zoll = leseDouble("  Raddurchmesser [Zoll]: ", 10.0, 50.0);

    // Reifenbreite für genaueren Reifenumfang (optional)
    std::cout << "\nReifenbreite (in mm, z. B. 25 oder 40; 0 = nur Felgendurchmesser):\n";
    double reifenBreiteMm = leseDouble("  Reifenbreite [mm]: ", 0.0, 200.0);

    // Radumfang berechnen: (Felgendurchmesser + 2 * Reifenhöhe) * PI
    // Bei Clincher-Reifen: Reifenhöhe ≈ Reifenbreite
    double radDurchmesserMm = zoll * 25.4 + 2.0 * reifenBreiteMm;
    double radUmfangM = PI * radDurchmesserMm / 1000.0;

    std::cout << "\n  → Radumfang: " << std::fixed << std::setprecision(3)
              << radUmfangM << " m\n";

    // --- Kettenbläter (vorne) ---
    std::cout << "\nAnzahl der Kettenblätter (vorne, 1–5):\n";
    int anzahlVorne = leseInt("  Kettenblätter: ", 1, 5);
    std::cout << "\nZähnezahl der Kettenblätter:\n";
    std::vector<int> vorne = leseZaehne("Kettenblatt", anzahlVorne);

    // --- Ritzel / Kassette (hinten) ---
    std::cout << "\nAnzahl der Ritzel / Kassettenstufen (hinten, 1–13):\n";
    int anzahlHinten = leseInt("  Ritzel: ", 1, 13);
    std::cout << "\nZähnezahl der Ritzel (Kassette):\n";
    std::vector<int> hinten = leseZaehne("Ritzel", anzahlHinten);

    // --- Ergebnistabelle ---
    std::cout << "\n\n";
    std::cout << "=================================================\n";
    std::cout << "  Übersetzungstabelle  (Übersetzung / Entfaltung)\n";
    std::cout << "=================================================\n\n";

    // Überschrift: Kettenblatt-Zähnezahlen als Spaltenköpfe
    int spaltenBreite = 14;
    std::cout << std::setw(8) << "Ritzel";
    for (int v : vorne) {
        std::string kopf = "KB " + std::to_string(v) + "Z";
        std::cout << std::setw(spaltenBreite) << kopf;
    }
    std::cout << '\n';

    // Einheit-Zeile
    std::cout << std::setw(8) << "";
    for (size_t i = 0; i < vorne.size(); ++i) {
        std::cout << std::setw(spaltenBreite) << "(i / m)";
    }
    std::cout << '\n';

    int tabellenBreite = 8 + static_cast<int>(vorne.size()) * spaltenBreite;
    trennlinie(tabellenBreite);

    // Ritzel von klein (schnellster Gang) nach groß (langsamster Gang)
    std::vector<int> hintenDesc = hinten;
    std::sort(hintenDesc.begin(), hintenDesc.end()); // aufsteigend sortiert

    for (int h : hintenDesc) {
        std::cout << std::setw(6) << h << "Z ";
        for (int v : vorne) {
            double uebersetzung = static_cast<double>(v) / static_cast<double>(h);
            double entfaltung   = uebersetzung * radUmfangM;
            // Format: "3.50/9.420"
            std::ostringstream zelle;
            zelle << std::fixed << std::setprecision(2) << uebersetzung
                  << "/" << std::setprecision(3) << entfaltung;
            std::cout << std::setw(spaltenBreite) << zelle.str();
        }
        std::cout << '\n';
    }

    trennlinie(tabellenBreite);

    // --- Gangspreizung ---
    double maxUebersetzung = static_cast<double>(vorne.back())  /
                             static_cast<double>(hintenDesc.front());
    double minUebersetzung = static_cast<double>(vorne.front()) /
                             static_cast<double>(hintenDesc.back());
    double spreizung = maxUebersetzung / minUebersetzung;

    std::cout << "\nGangspreizung (max. / min. Übersetzung):\n";
    std::cout << "  Größte Übersetzung : " << std::fixed << std::setprecision(2)
              << maxUebersetzung
              << "  (Entfaltung: " << std::setprecision(3)
              << maxUebersetzung * radUmfangM << " m)\n";
    std::cout << "  Kleinste Übersetzung : " << std::setprecision(2)
              << minUebersetzung
              << "  (Entfaltung: " << std::setprecision(3)
              << minUebersetzung * radUmfangM << " m)\n";
    std::cout << "  Spreizung          : " << std::setprecision(1)
              << spreizung * 100.0 << " %\n";

    // --- Kadenz-Tabelle (optional) ---
    std::cout << "\nKadenz-Tabelle anzeigen? (Entfaltung × Kadenz = Geschwindigkeit)\n";
    std::cout << "  [1] Ja   [2] Nein\n";
    int showKadenz = leseInt("  Auswahl: ", 1, 2);

    if (showKadenz == 1) {
        std::vector<int> kadenzen = {60, 70, 80, 90, 100};

        std::cout << "\n\n";
        std::cout << "=================================================\n";
        std::cout << "  Geschwindigkeitstabelle [km/h]\n";
        std::cout << "  (größte und kleinste Übersetzung)\n";
        std::cout << "=================================================\n\n";

        // Kopfzeile
        std::cout << std::setw(12) << "Kadenz [U/min]";
        for (int k : kadenzen) {
            std::cout << std::setw(10) << k;
        }
        std::cout << '\n';
        trennlinie(12 + static_cast<int>(kadenzen.size()) * 10);

        auto druckeGeschwindigkeitsZeile =
            [&](const std::string& label, double uebersetzung) {
                std::cout << std::setw(12) << label;
                for (int k : kadenzen) {
                    // v [km/h] = Entfaltung [m] * Kadenz [1/min] * 60 / 1000
                    double v = uebersetzung * radUmfangM * k * 60.0 / 1000.0;
                    std::ostringstream s;
                    s << std::fixed << std::setprecision(1) << v;
                    std::cout << std::setw(10) << s.str();
                }
                std::cout << '\n';
            };

        druckeGeschwindigkeitsZeile("Groß", maxUebersetzung);
        druckeGeschwindigkeitsZeile("Klein", minUebersetzung);
        trennlinie(12 + static_cast<int>(kadenzen.size()) * 10);
    }

    std::cout << "\nBerechnung abgeschlossen.\n";
    return 0;
}
