load data
 infile './csv/clasifican.csv'
 into table Clasifican
 fields terminated by ";"
 ( nombre_corto_equipo, id_jornada, puntos, goles_favor, goles_contra, victorias, derrotas, empates)