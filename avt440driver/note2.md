po próbie kontunuowania projektu na starej płycie głównej abit ic7 bez dysku,
z 256MB RAM, okazało się, że w DSM są znacze braki w sterownikach i oprogramowaniu,
mimo, że działa szybko, płynnie, wyamga mało pamięci i jest ladny to nie było
sterowników ani do żadnej z dwuch sprawdzanych kart sieciowych ethernet, ani karty
wifi na usb. nie było też gcc i całego zestawu narzędzi gnu. To wykluczyło tą
dystrybucję.
W puppy linux nie ma wbu8dowanego gcc, ani odpowiedniego pakietu do zainstalowania.
Instalacja gcc jest w nim dość skomplikowana i wymaga znacznych ingerencji w system.
Knopix okazał się dobrze działać, odrazu był internet i gcc. Jedyną wadą jest wymaganie
duzej przestrzeni dyskowej, przez co potrzebny był 8 gigowy pendrajw.

niestety gdy podłączyłem płytkę i odpaliłem testowanie, okazało się, że nie działa
SELECT (pin jest zawsze na 0), oraz rejestr wyjściowy/wejściowy.
Podejżewam, że szkodliwe dla portu może być podłączanie płytki do włączonego systemu.
tylko czemu miało by się psuć select, na który płytka nic nie podaje