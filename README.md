# Kaluze_na_placu

Kałuże
Dany jest plac. Plac wyłożony jest płaskimi płytami o wymiarach 1m x 1m. Plac otoczony jest trawą. Wykonawca placu nie postarał się, więc każda płyta znajduje się na nieco innej wysokości (ale każda płyta leży idealnie poziomo). Zaczyna padać deszcz. Wyznacz, gdzie utworzą się kałuże i jaka będzie całkowita objętość wody, w litrach, która zatrzyma się w kałużach. Jeżeli płyty stykają się rogami, tworzą szczelne połączenie (woda nie przepływa przez "rogi"). W dowolny obszar trawy może wsiąknąć dowolna objętość wody w dowolnie krótkim czasie.
Wejście
Na wejściu zostaną podane wymiary placu: szerokość w i wysokość h w metrach. Następnie wystąpi w*h nieujemnych liczb opisujących wysokość w milimetrach nad poziomem trawy (trawa znajduje się na poziomie 0) na której znajdują się kolejne płyty. Każde kolejne w liczb opisuje kolejny wiersz. Wysokość i szerokość placu nie przekroczą 1536 metrów.
Wyjście
Na wyjściu należy wypisać: w pierwszym wierszu objętość wody (w litrach) która zatrzymała się w kałużach (wartość ta nie przekroczy zakresu liczb typu int). W kolejnych w*h znakach (po każdych wznakach powinien pojawić się znak nowej linii) należy opisać miejsca pojawiania się kałuż: . (kropka) oznacza, że kałuża się nie utworzy, # (krzyżyk) oznacza, że płyta będzie  zalana wodą na wysokość co najmniej 1mm.

Przykład

Wejście

8 8  
0 0 0 0 0 1 0 0   
0 1 1 1 0 1 0 0  
0 1 0 2 1 2 4 5   
0 1 1 2 0 2 4 5   
0 3 3 3 3 3 3 4   
0 3 0 1 2 0 3 4   
0 3 3 3 3 3 3 0   
0 0 0 0 0 0 0 0   

Wyjście  
11  
........  
........  
..#.....  
....#...  
........  
