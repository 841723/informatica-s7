load data
 infile './csv/estadio.csv'
 into table Estadio
 fields terminated by ";"
 ( nombre, fecha_inag, aforo )