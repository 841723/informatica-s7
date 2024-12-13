CREATE TABLE Estadio(
    nombre VARCHAR(50) PRIMARY KEY,
    aforo NUMBER(9) CHECK (aforo > 0),
    fecha_inag NUMBER(4)
);
CREATE TABLE Equipo(
  nombre_oficial VARCHAR(64) PRIMARY KEY,
  nombre_historico VARCHAR(64),  
  otro_nombre VARCHAR(64),
  ciudad VARCHAR (64),
  fundacion NUMBER(4),
  fund_legal NUMBER(4),
  nombre_corto VARCHAR(32) UNIQUE,
  estadio VARCHAR(64),
  FOREIGN KEY (estadio) REFERENCES Estadio(nombre)
);
CREATE TABLE Division(
    nombre VARCHAR(32) PRIMARY KEY 
);
CREATE TABLE Temporada(
    -- agno en el que empieza la temporada
    agno NUMBER(4),
    nom_div VARCHAR(32),
    PRIMARY KEY (agno, nom_div),
    FOREIGN KEY (nom_div) REFERENCES Division(nombre)
);
CREATE TABLE Jornada(
    id NUMBER GENERATED ALWAYS as IDENTITY(START with 1 INCREMENT by 1),
    numero NUMBER(3),
    agno NUMBER(4),
    nom_div VARCHAR(32),
    PRIMARY KEY (id),
    FOREIGN KEY (agno, nom_div) REFERENCES Temporada
);
CREATE TABLE Partido(
    id_jornada NUMBER(5),
    nombre_corto_local VARCHAR(32),
    nombre_corto_visitante VARCHAR(32),
    goles_locales NUMBER(2),
    goles_visitantes NUMBER(2),
    PRIMARY KEY (nombre_corto_local, id_jornada),
    FOREIGN KEY (nombre_corto_local) REFERENCES Equipo(nombre_corto),
    FOREIGN KEY (nombre_corto_visitante) REFERENCES Equipo(nombre_corto),
    CHECK (nombre_corto_local != nombre_corto_visitante),
    FOREIGN KEY (id_jornada) REFERENCES Jornada(id)
);
CREATE TABLE Clasifican(
    nombre_corto_equipo VARCHAR(64),
    id_jornada NUMBER (5),
    puntos NUMBER (3),
    goles_favor NUMBER (3), 
    goles_contra NUMBER (3),
    victorias NUMBER (3),
    derrotas NUMBER (3),
    empates NUMBER (3),
    PRIMARY KEY (nombre_corto_equipo, id_jornada),
    FOREIGN KEY (nombre_corto_equipo) REFERENCES Equipo(nombre_corto),
    FOREIGN KEY (id_jornada) REFERENCES Jornada(id)
);