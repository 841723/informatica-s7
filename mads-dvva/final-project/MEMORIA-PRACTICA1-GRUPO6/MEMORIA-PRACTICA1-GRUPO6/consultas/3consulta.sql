CREATE OR REPLACE VIEW rivales_perdieron_romareda AS(
SELECT p.nombre_corto_visitante, j.agno, j.numero
FROM partido p 
JOIN jornada j ON p.id_jornada = j.id AND p.nombre_corto_local = 'Zaragoza' AND (j.nom_div='1' OR j.nom_div='2')
WHERE p.goles_locales > p.goles_visitantes);

CREATE OR REPLACE VIEW rivales_perdieron_su_casa AS(
SELECT j.agno, p.nombre_corto_local, j.numero
FROM partido p 
JOIN jornada j ON p.id_jornada = j.id AND (p.nombre_corto_visitante = 'Zaragoza')
WHERE p.goles_locales < p.goles_visitantes);

CREATE OR REPLACE VIEW cantidad_casos_agno AS(
SELECT COUNT(*) AS cuentas, j.agno
FROM rivales_perdieron_romareda t
JOIN rivales_perdieron_su_casa j
ON (j.nombre_corto_local = t.nombre_corto_visitante) AND j.agno=t.agno
GROUP BY j.agno
HAVING COUNT(*) >=4); 

CREATE OR REPLACE VIEW id_max_2 AS (
SELECT MAX(id) AS max_id, agno 
FROM jornada 
WHERE nom_div='2'
GROUP BY agno);

CREATE OR REPLACE VIEW  id_max_1 AS (
SELECT MAX(id) AS max_id, agno
FROM jornada 
WHERE nom_div='1'
GROUP BY agno); 

CREATE OR REPLACE VIEW goles_favor_zgz AS(
SELECT goles_favor, id_jornada
FROM clasifican
WHERE nombre_corto_equipo='Zaragoza');


SELECT a.agno, c.goles_favor, a.cuentas AS ocurrencias
FROM id_max_1 i1
JOIN id_max_2 i2
ON i1.agno = i2.agno
JOIN cantidad_casos_agno a
ON (a.agno = i1.agno) OR (a.agno = i2.agno)
JOIN goles_favor_zgz c
ON (c.id_jornada = i1.max_id) OR (c.id_jornada = i2.max_id)
ORDER BY agno;
