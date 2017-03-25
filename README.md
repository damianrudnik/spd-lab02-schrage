# Wymagania do zadania

Format pliku z danymi : Pierwsza linia zawiera liczbę calkowitą n oznaczającą liczbę zadań. Każda z następnych n linii zawiera 3 liczby (r, p i q) oznaczajace kolejno r - termin dostępności, p - czas obsługi q - czas dostarczenia zadania.

Format plikow z wynikami : Dokładnie 1 liczba okreslajaca wartość funkcji Cmax dla rozwiazania wygenerowanego danym algorytmem.

Plik z danymi
6
1 5 9 	
4 5 4 	
1 4 6 	
7 3 3 	
3 6 8 	
4 7 1

Plik z wynikami
32

# O Algorytmie Schrage
Algorytm polega na uszeregowaniu zadań najpierw wg. czasu dostarczenia r.
W chwili t, gdy mamy dostępne zadania i czas na maszynie, wtedy ściągamy wszystkie dostępne zadania z kolejki priorytetowej sortującej po r, a wstawiamy je do kolejki sortującej po czasie stygnięcia q i wykonujemy zadanie o najdłuższym czasie stynięcia z tej kolejki.

