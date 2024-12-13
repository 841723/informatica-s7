CREATE OR REPLACE VIEW jornadas_primera AS (
SELECT * 
FROM jornada
WHERE nom_div='1');

CREATE OR REPLACE VIEW max_ids AS (
SELECT MAX(id) as max_id, agno
FROM jornada 
WHERE nom_div='1'
GROUP BY agno);

CREATE OR REPLACE VIEW equipos_agno AS (
SELECT j.id, j.agno, p.nombre_corto_local, p.nombre_corto_visitante
FROM jornadas_primera j
JOIN partido p
ON j.id = p.id_jornada);

CREATE OR REPLACE VIEW partidos_ultima_jornada AS (
SELECT j.nombre_corto_local, j.agno, j.nombre_corto_visitante, i.max_id as id
FROM max_ids i
JOIN equipos_agno j
ON j.id = i.max_id);

CREATE OR REPLACE VIEW clasificacion AS (
SELECT c.puntos, c.nombre_corto_equipo, e.agno
FROM partidos_ultima_jornada e
JOIN clasifican c
ON c.id_jornada = e.id AND (e.nombre_corto_local = c.nombre_corto_equipo OR e.nombre_corto_visitante = c.nombre_corto_equipo));

CREATE OR REPLACE VIEW clasificacion_ultima_jornada AS (
SELECT t.puntos, t.nombre_corto_equipo, t.agno
FROM clasificacion t);

CREATE OR REPLACE VIEW puntos_ganadores AS (
SELECT MAX(puntos) AS puntos_max, agno AS agno_max
FROM clasificacion_ultima_jornada
GROUP BY agno);

CREATE OR REPLACE VIEW ganadores AS (
SELECT *
FROM clasificacion_ultima_jornada c
JOIN puntos_ganadores j ON c.agno = j.agno_max AND c.puntos = j.puntos_max);

CREATE OR REPLACE VIEW num_ganadores AS (
SELECT COUNT(nombre_corto_equipo) AS cantidad, nombre_corto_equipo
FROM ganadores
GROUP BY nombre_corto_equipo);

SELECT cantidad AS campeonatos, nombre_corto_equipo AS equipo
FROM num_ganadores
ORDER BY cantidad DESC
FETCH FIRST ROW ONLY;
