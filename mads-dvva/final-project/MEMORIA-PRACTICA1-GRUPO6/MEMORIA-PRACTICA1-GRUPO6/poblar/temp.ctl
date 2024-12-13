load data
 infile './csv/temp.csv'
 into table Temporada
 fields terminated by ";"
 ( agno, nom_div )