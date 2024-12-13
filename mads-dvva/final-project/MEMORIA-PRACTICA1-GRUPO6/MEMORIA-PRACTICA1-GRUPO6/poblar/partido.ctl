load data
 infile './csv/partido.csv'
 into table Partido
 fields terminated by ";"
 ( nombre_corto_local, nombre_corto_visitante, goles_locales, goles_visitantes, id_jornada)