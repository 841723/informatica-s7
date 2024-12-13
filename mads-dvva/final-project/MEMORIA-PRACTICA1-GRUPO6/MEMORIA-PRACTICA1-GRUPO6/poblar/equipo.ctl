load data
 infile './csv/equipo.csv'
 into table Equipo
 fields terminated by ";"
 ( nombre_corto, nombre_oficial, ciudad, fundacion,fund_legal, nombre_historico, estadio, otro_nombre )