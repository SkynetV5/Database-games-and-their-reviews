Kompilacja:
Windows - g++ -o games.exe games.cpp
Linux - g++ -o games games.cpp
Komendy i ich użycie:
add - ./games.exe add 'tytuł' 'developer' (np. ./games.exe 'Call of Duty' 'Activision');
review - ./games.exe review [id] 'tresc' (np. ./games.exe 1 'Mysle ze jest okey.');
list - ./games.exe list (lub ./games.exe list [numer_kolumny]) (np. ./games.exe list 2);
delete - ./games.exe delete [id] (np ./games.exe delete 5);
csv - ./games.exe csv;
search - ./games.exe search 'fraza' [numer_kolumny_do_posortowania] (np. ./games.exe search 'Battlefield 1' 2);