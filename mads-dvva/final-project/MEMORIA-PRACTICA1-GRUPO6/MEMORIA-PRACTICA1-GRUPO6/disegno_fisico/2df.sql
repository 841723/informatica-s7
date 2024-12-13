CREATE INDEX idx_estadio_nombre ON estadio(nombre);
CREATE INDEX idx_equipo_estadio ON equipo(estadio);
CREATE INDEX idx_partido_local ON partido(nombre_corto_local);
CREATE INDEX idx_partido_goles_local ON partido(goles_locales, goles_visitantes);

CREATE OR REPLACE VIEW ganados_local AS(
SELECT COUNT(*) as partidos_ganados, s1.nombre AS nombre_estadio
FROM estadio s1
JOIN equipo e1 ON s1.nombre = e1.estadio
JOIN partido p1 ON e1.nombre_corto = p1.nombre_corto_local
WHERE p1.goles_locales >= p1.goles_visitantes 
GROUP BY s1.nombre);

CREATE OR REPLACE VIEW jugados_local AS(
SELECT COUNT(*) as partidos_jugados, s2.nombre AS nombre_estadio
FROM estadio s2
JOIN equipo e2 ON s2.nombre = e2.estadio
JOIN partido p2 ON e2.nombre_corto = p2.nombre_corto_local
GROUP BY s2.nombre);

SELECT s1.nombre_estadio AS estadio , partidos_ganados/partidos_jugados AS ratio
FROM ganados_local s1
JOIN jugados_local s2
ON s1.nombre_estadio = s2.nombre_estadio
WHERE partidos_ganados/partidos_jugados > (85/100);
