load data
 infile './csv/jornada.csv'
 into table Jornada
 fields terminated by ";"
 ( id, agno, nom_div, numero )