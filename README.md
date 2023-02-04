# Grundlagen der Programmierung – WS22/23 

## Aufgabe 18 Labyrinth

Es soll ein Programm implementiert werden, in dem sich ein Spieler durch ein Labyrinth bewegen
kann.
Sie erhalten ein Labyrinth in folgender Form in einer Datei:

```text
5 7
2 0
2 6
*******
* * * *
*
* ***
*******
```

Wobei die erste Zahl die Höhe, die zweite Zahl die Breite, die dritte Zahl die Zeile des Startpunktes,
die vierte Zahl die Spalte des Startpunktes, die fünfte Zahl die Zeile des Zielpunktes, die
sechste Zahl die Spalte des Zielpunktes angibt. Das Labyrinth selbst lässt sich also in einem
zweidimensionalen Feld speichern.
- Schreiben Sie ein Programm, das das Spielfeld einliest und auf dem Bildschirm ausgeben
kann.
- Zeichnen Sie in das Spielfeld den Standort des Spielers und, soweit der Spieler nicht dort
steht, die Startposition und die Zielposition ein.
- Erlauben Sie einem Spieler uber Eingabe von `O`, `U`, `L`, `R` sowie den Zahlen `8`, `2`, `4`, `6`
sich im Spielfeld zu bewegen. Nach einem Zug soll das neue Spielfeld ausgegeben werden.
- Wenn der Spieler die Zielposition erreicht hat, soll sich das Programm die Anzahl der Züge ausgeben und dann automatisch beenden. 
- Beim Ablaufen des Spielfeldes soll jedes besuchte Feld mit einem `.` markiert werden.
- Zählen Sie die Anzahl der Zuge und geben diese mit aus.
- während des Spieles soll es möglich sein, den aktuellen Spielstand in eine Datei zu speichern
und später wieder zu laden.

>Achten Sie darauf, dass das Programm nicht nur das vorgegebene Labyrinth verwendet, sondern
berucksichtigen Sie auch andere Fälle.
