-- mysqldump -u terminator -phastalavistababy planespime tblPais tblProvincia tblPersona tblRol tblUsuario trelRolUsuario tblAcceso tblTipoIdentificacion tblNivelEstudios tblEstadoCivil tblEstadoLaboral > /var/www/dump.sql

delimiter $$

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ROL
DROP TABLE IF EXISTS `tblRol`;
CREATE TABLE `tblRol` (
  `idRol` int(11) NOT NULL auto_increment,
  `vNombre` varchar(45) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idRol`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$

-- ACCESO
DROP TABLE IF EXISTS `tblAcceso`;
CREATE TABLE `tblAcceso` (
  `idAcceso` int(11) NOT NULL auto_increment,
  `fkPadre` int(11) NOT NULL default '0',
  `vNombre` varchar(45) NOT NULL,
  `bMenu` tinyint(1) NOT NULL default '1',
  `iOrden` int(3) NOT NULL,
  `vControlador` varchar(45) default NULL,
  `vAccion` varchar(45) default NULL,
  `vRoles` varchar(255) default NULL,
  PRIMARY KEY  (`idAcceso`,`fkPadre`),
  KEY `fk_tblAcceso_tblAcceso1` (`fkPadre`),
  CONSTRAINT `fk_tblAcceso_tblAcceso1` FOREIGN KEY (`fkPadre`) REFERENCES `tblAcceso` (`idAcceso`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$

-- TIPO IDENTIFICACION
DROP TABLE IF EXISTS `tblTipoIdentificacion`;
CREATE TABLE `tblTipoIdentificacion` (
  `idTipoIdentificacion` int(11) NOT NULL auto_increment,
  `vNombre` varchar(100) NOT NULL,
  PRIMARY KEY  (`idTipoIdentificacion`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$

-- NIVEL ESTUDIOS
DROP TABLE IF EXISTS `tblNivelEstudios`;
CREATE TABLE `tblNivelEstudios` (
  `idNivelEstudios` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  `vDescripcion` varchar(1000) default NULL,
  PRIMARY KEY  (`idNivelEstudios`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$

-- ESTADO LABORAL
DROP TABLE IF EXISTS `tblEstadoLaboral`;
CREATE TABLE `tblEstadoLaboral` (
  `idEstadoLaboral` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) NOT NULL,
  PRIMARY KEY  (`idEstadoLaboral`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COMMENT='Empleado, autónomo, parado, etc.'$$

-- ESTADO CIVIL
DROP TABLE IF EXISTS `tblEstadoCivil`;
CREATE TABLE `tblEstadoCivil` (
  `idEstadoCivil` int(11) NOT NULL auto_increment,
  `vNombre` varchar(255) default NULL,
  PRIMARY KEY  (`idEstadoCivil`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$

-- PAIS
DROP TABLE IF EXISTS `tblPais`;
CREATE TABLE `tblPais` (
  `vIso` varchar(2) NOT NULL,
  `vNombre_es` varchar(100) NOT NULL,
  `vNombre_ca` varchar(100) default NULL,
  `vNombre_en` varchar(100) default NULL,
  `vNombre_de` varchar(100) default NULL,
  PRIMARY KEY  (`vIso`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8$$

-- PROVINCIA
DROP TABLE IF EXISTS `tblProvincia`;
CREATE TABLE `tblProvincia` (
  `idProvincia` int(11) NOT NULL auto_increment,
  `vNombre_es` varchar(100) NOT NULL,
  `vNombre_ca` varchar(100) default NULL,
  `vNombre_en` varchar(100) default NULL,
  `vNombre_de` varchar(100) default NULL,
  PRIMARY KEY  (`idProvincia`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$

-- USUARIO
DROP TABLE IF EXISTS `tblUsuario`;
CREATE TABLE `tblUsuario` (
  `idUsuario` int(11) NOT NULL auto_increment,
  `vNombre` varchar(50) NOT NULL,
  `vPassword` varchar(32) NOT NULL,
  `vEmail` varchar(45) NOT NULL,
  PRIMARY KEY  (`idUsuario`),
  KEY `idUsuario` (`idUsuario`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$

-- ROL USUARIO
DROP TABLE IF EXISTS `trelRolUsuario`;
CREATE TABLE `trelRolUsuario` (
  `fkUsuario` int(11) NOT NULL,
  `fkRol` int(11) NOT NULL,
  PRIMARY KEY  (`fkUsuario`,`fkRol`),
  KEY `fk_trelRolUsuario_tblUsuario1` (`fkUsuario`),
  KEY `fk_trelRolUsuario_tblRol1` (`fkRol`),
  CONSTRAINT `fk_trelRolUsuario_tblRol1` FOREIGN KEY (`fkRol`) REFERENCES `tblRol` (`idRol`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_trelRolUsuario_tblUsuario1` FOREIGN KEY (`fkUsuario`) REFERENCES `tblUsuario` (`idUsuario`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8$$

-- ENTIDAD(Persona o empresa)
DROP TABLE IF EXISTS `tblEntidad`;
CREATE TABLE `tblEntidad` (
  `idEntidad` int(11) NOT NULL auto_increment,
  `fkUsuario` int(11) NOT NULL,
  `fkPais` varchar(2) NOT NULL,
  `fkProvincia` int(11) default NULL,
  `fkTipoIdentificacion` int(11) NULL,
  `fkEstadoCivil` int(11) NULL,
  `fkEstadoLaboral` int(11) NULL,
  `fkNivelEstudios` int(11) NULL,
  `vNombre` varchar(45) NOT NULL,
  `vPrimerApellido` varchar(45) NOT NULL,
  `vSegundoApellido` varchar(45) default NULL,
  `vNumeroIdentificacion` varchar(20) NOT NULL,
  `dNacimiento` date NOT NULL,
  `vPoblacion` varchar(100) default NULL,
  `vCp` varchar(45) default NULL,
  `vDireccion` varchar(255) default NULL,
  `vTelefono` varchar(45) default NULL,
  `vMovil` varchar(45) default NULL,
  `vFax` varchar(45) default NULL,
  `bActiva` tinyint(1) default '0',
  `dAlta` date NOT NULL,
  `dBaja` date default NULL,
  `mod_user` varchar(45) default NULL,
  `last_modified` date default NULL,
  PRIMARY KEY  (`idEntidad`),
  KEY `fk_tblPersona_tblPais1` (`fkPais`),
  KEY `fk_tblPersona_tblUsuario1` (`fkUsuario`),
  KEY `fk_tblPersona_tblTipoDocumento1` (`fkTipoIdentificacion`),
  KEY `fk_tblPersona_tblEstadoCivil1` (`fkEstadoCivil`),
  KEY `fk_tblPersona_tblEstadoLaboral1` (`fkEstadoLaboral`),
  KEY `fk_tblPersona_tblNivelEstudios1` (`fkNivelEstudios`),
  KEY `fk_tblPersona_tblProvincia1` (`fkProvincia`),
  CONSTRAINT `fk_tblPersona_tblEstadoCivil1` FOREIGN KEY (`fkEstadoCivil`) REFERENCES `tblEstadoCivil` (`idEstadoCivil`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblEstadoLaboral1` FOREIGN KEY (`fkEstadoLaboral`) REFERENCES `tblEstadoLaboral` (`idEstadoLaboral`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblNivelEstudios1` FOREIGN KEY (`fkNivelEstudios`) REFERENCES `tblNivelEstudios` (`idNivelEstudios`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblPais1` FOREIGN KEY (`fkPais`) REFERENCES `tblPais` (`vIso`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblProvincia1` FOREIGN KEY (`fkProvincia`) REFERENCES `tblProvincia` (`idProvincia`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblTipoDocumento1` FOREIGN KEY (`fkTipoIdentificacion`) REFERENCES `tblTipoIdentificacion` (`idTipoIdentificacion`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_tblPersona_tblUsuario1` FOREIGN KEY (`fkUsuario`) REFERENCES `tblUsuario` (`idUsuario`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8$$


-- INSERTS

-- USUARIO
INSERT INTO `tblUsuario` (idUsuario,vNombre,vPassword,vEmail) VALUES (1,'admin','563566b348459042881bc33f336211a3','info@ningen.es');

-- ROL
INSERT INTO `tblRol` (idRol,vNombre,vDescripcion) VALUES (1,'Administrador','Administrador del Sistema');
INSERT INTO `tblRol` (idRol,vNombre,vDescripcion) VALUES (2,'Usuario','Usuario de la aplicación');

-- ROL USUARIO
INSERT INTO `trelRolUsuario` (fkUsuario,fkRol) VALUES (1,1);

-- ACCESO
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (1,0,'Administración',1,11,'administrador',NULL,NULL);
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (2,1,'Roles',1,19,'administrador','roles',1);
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (3,1,'Configuración',1,18,'administrador','configuracion',1);
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (4,1,'Menú',1,17,'administrador','menu',1);

-- TIPO IDENTIFICACION
INSERT INTO `tblTipoIdentificacion` (idTipoIdentificacion,vNombre) VALUES (1,'DNI');
INSERT INTO `tblTipoIdentificacion` (idTipoIdentificacion,vNombre) VALUES (2,'NIE');
INSERT INTO `tblTipoIdentificacion` (idTipoIdentificacion,vNombre) VALUES (3,'Pasaporte');
INSERT INTO `tblTipoIdentificacion` (idTipoIdentificacion,vNombre) VALUES (4,'CIF');

-- NIVEL ESTUDIOS
INSERT INTO `tblNivelEstudios` (idNivelEstudios,vNombre,vDescripcion) VALUES (1,'EGB',NULL);
INSERT INTO `tblNivelEstudios` (idNivelEstudios,vNombre,vDescripcion) VALUES (2,'ESO',NULL);
INSERT INTO `tblNivelEstudios` (idNivelEstudios,vNombre,vDescripcion) VALUES (3,'Universidad',NULL);

-- ESTADO LABORAL
INSERT INTO `tblEstadoLaboral` (idEstadoLaboral,vNombre) VALUES (1,'Ocupado');
INSERT INTO `tblEstadoLaboral` (idEstadoLaboral,vNombre) VALUES (2,'Desocupado');
INSERT INTO `tblEstadoLaboral` (idEstadoLaboral,vNombre) VALUES (3,'Parado');

-- ESTADO CIVIL
INSERT INTO `tblEstadoCivil` (idEstadoCivil,vNombre) VALUES (1,'Casado/a');
INSERT INTO `tblEstadoCivil` (idEstadoCivil,vNombre) VALUES (2,'Soltero/a');
INSERT INTO `tblEstadoCivil` (idEstadoCivil,vNombre) VALUES (3,'Divorciado/a');

-- PAISES
INSERT INTO `tblPais` VALUES ('ad','Andorra',NULL,NULL,NULL),('ae','Emiratos Árabes Unidos',NULL,NULL,NULL),('af','Afganistán',NULL,NULL,NULL),('ag','Antigua y Barbuda',NULL,NULL,NULL),('ai','Anguila',NULL,NULL,NULL),('al','Albania',NULL,NULL,NULL),('am','Armenia',NULL,NULL,NULL),('an','Antillas Holandesas',NULL,NULL,NULL),('ao','Angola',NULL,NULL,NULL),('aq','Antártica',NULL,NULL,NULL),('ar','Argentina','Argentina','Argentina',NULL),('as','Samoa Americana',NULL,NULL,NULL),('at','Austria',NULL,NULL,NULL),('au','Australia',NULL,NULL,NULL),('aw','Aruba',NULL,NULL,NULL),('az','Azerbaidjan',NULL,NULL,NULL),('ba','Bosnia-Herzegovina',NULL,NULL,NULL),('bb','Barbados',NULL,NULL,NULL),('bd','Bangladesh',NULL,NULL,NULL),('be','Bélgica',NULL,NULL,NULL),('bf','Burkina Faso',NULL,NULL,NULL),('bg','Bulgaria',NULL,NULL,NULL),('bh','Bahrain',NULL,NULL,NULL),('bi','Burundi',NULL,NULL,NULL),('bj','Benin',NULL,NULL,NULL),('bm','Bermuda',NULL,NULL,NULL),('bn','Brunei Darussalam',NULL,NULL,NULL),('bo','Bolivia',NULL,NULL,NULL),('br','Brasil',NULL,NULL,NULL),('bs','Bahamas',NULL,NULL,NULL),('bt','Bhutan',NULL,NULL,NULL),('bv','Isla Bouvet',NULL,NULL,NULL),('bw','Botswana',NULL,NULL,NULL),('by','Bielorusia',NULL,NULL,NULL),('bz','Belice',NULL,NULL,NULL),('ca','Canadá',NULL,NULL,NULL),('cc','Isla Cocos (Keeling Islands)',NULL,NULL,NULL),('cd','República Democratica del Congo',NULL,NULL,NULL),('cf','República Central Africana',NULL,NULL,NULL),('cg','Congo',NULL,NULL,NULL),('ch','Suiza',NULL,NULL,NULL),('ci','Costa Marfil',NULL,NULL,NULL),('ck','Islas Cook',NULL,NULL,NULL),('cl','Chile',NULL,NULL,NULL),('cm','Camerún',NULL,NULL,NULL),('cn','China',NULL,NULL,NULL),('co','Colombia',NULL,NULL,NULL),('cr','Costa Rica',NULL,NULL,NULL),('cs','República Checa y Eslovakia',NULL,NULL,NULL),('cu','Cuba',NULL,NULL,NULL),('cv','Cabe Verde',NULL,NULL,NULL),('cx','Islas Christmas',NULL,NULL,NULL),('cy','Chipre',NULL,NULL,NULL),('cz','República Checa',NULL,NULL,NULL),('de','Alemania',NULL,NULL,NULL),('dj','Djibouti',NULL,NULL,NULL),('dk','Dinamarca',NULL,NULL,NULL),('dm','Dominica',NULL,NULL,NULL),('do','República Dominicana',NULL,NULL,NULL),('dz','Argelia',NULL,NULL,NULL),('ec','Ecuador',NULL,NULL,NULL),('ee','Estonia',NULL,NULL,NULL),('eg','Egypto',NULL,NULL,NULL),('eh','Sáhara Occidental',NULL,NULL,NULL),('er','Eritrea',NULL,NULL,NULL),('es','España','Espanya','Spain',NULL),('et','Etiopía',NULL,NULL,NULL),('fi','Finlandia',NULL,NULL,NULL),('fj','Fiji',NULL,NULL,NULL),('fk','Falkland Islands (Islas Malvinas)',NULL,NULL,NULL),('fm','Micronesia',NULL,NULL,NULL),('fo','Islas Faroe',NULL,NULL,NULL),('fr','Francia',NULL,NULL,NULL),('ga','Gabón',NULL,NULL,NULL),('gd','Granada',NULL,NULL,NULL),('ge','Georgia',NULL,NULL,NULL),('gf','Guyana Francesa',NULL,NULL,NULL),('gg','Guernsey',NULL,NULL,NULL),('gh','Ghana',NULL,NULL,NULL),('gl','Groenlandia',NULL,NULL,NULL),('gm','Gambia',NULL,NULL,NULL),('gn','Guinea',NULL,NULL,NULL),('gp','Guadelupe (Francesa)',NULL,NULL,NULL),('gq','Guinea Ecuatorial',NULL,NULL,NULL),('gr','Grecia',NULL,NULL,NULL),('gs','Islas S. Georgia y S. Sandwich',NULL,NULL,NULL),('gt','Guatemala',NULL,NULL,NULL),('gu','Guam (USA)',NULL,NULL,NULL),('gw','Guinea Bissau',NULL,NULL,NULL),('gy','Guyana',NULL,NULL,NULL),('hk','Hong Kong',NULL,NULL,NULL),('hm','Islas Heard y McDonald',NULL,NULL,NULL),('hn','Honduras',NULL,NULL,NULL),('hr','Croacia',NULL,NULL,NULL),('ht','Haití',NULL,NULL,NULL),('hu','Hungría',NULL,NULL,NULL),('id','Indonesia',NULL,NULL,NULL),('ie','Irlanda',NULL,NULL,NULL),('il','Israel',NULL,NULL,NULL),('im','Isla de Man',NULL,NULL,NULL),('in','India',NULL,NULL,NULL),('io','Territorio Británico del Oceano Índico',NULL,NULL,NULL),('iq','Iraq',NULL,NULL,NULL),('ir','Irán',NULL,NULL,NULL),('is','Islandia',NULL,NULL,NULL),('it','Italia',NULL,NULL,NULL),('je','Jersey',NULL,NULL,NULL),('jm','Jamaica',NULL,NULL,NULL),('jo','Jordania',NULL,NULL,NULL),('jp','Japón',NULL,NULL,NULL),('ke','Kenya',NULL,NULL,NULL),('kg','Kyrgyzstan',NULL,NULL,NULL),('kh','Camboya',NULL,NULL,NULL),('ki','Kiribati',NULL,NULL,NULL),('km','Comoras',NULL,NULL,NULL),('kn','San Cristóbal y Nieves',NULL,NULL,NULL),('kp','Corea del norte',NULL,NULL,NULL),('kr','Corea del sur',NULL,NULL,NULL),('kw','Kuwait',NULL,NULL,NULL),('ky','Cayman Islands',NULL,NULL,NULL),('kz','Kazakhstan',NULL,NULL,NULL),('la','Laos',NULL,NULL,NULL),('lb','Líbano',NULL,NULL,NULL),('lc','Santa Lucía',NULL,NULL,NULL),('li','Liechtenstein',NULL,NULL,NULL),('lk','Sri Lanka',NULL,NULL,NULL),('lr','Liberia',NULL,NULL,NULL),('ls','Lesotho',NULL,NULL,NULL),('lt','Lituania',NULL,NULL,NULL),('lu','Luxemburgo',NULL,NULL,NULL),('lv','Letonia',NULL,NULL,NULL),('ly','Libia',NULL,NULL,NULL),('ma','Marruecos',NULL,NULL,NULL),('mc','Mónaco',NULL,NULL,NULL),('md','Moldavia',NULL,NULL,NULL),('me','Montenegro',NULL,NULL,NULL),('mg','Madagascar',NULL,NULL,NULL),('mh','Islas Marshall',NULL,NULL,NULL),('mk','Macedonia',NULL,NULL,NULL),('ml','Mali',NULL,NULL,NULL),('mm','Myanmar',NULL,NULL,NULL),('mn','Mongolia',NULL,NULL,NULL),('mo','Macao',NULL,NULL,NULL),('mp','Northern Mariana Islands',NULL,NULL,NULL),('mq','Martinica (Francesa)',NULL,NULL,NULL),('mr','Mauritania',NULL,NULL,NULL),('ms','Montserrat',NULL,NULL,NULL),('mt','Malta',NULL,NULL,NULL),('mu','Mauricia',NULL,NULL,NULL),('mv','Maldivas',NULL,NULL,NULL),('mw','Malawi',NULL,NULL,NULL),('mx','México',NULL,NULL,NULL),('my','Malasia',NULL,NULL,NULL),('mz','Mozambique',NULL,NULL,NULL),('na','Namibia',NULL,NULL,NULL),('nc','Nueva Caledonia (Francesa)',NULL,NULL,NULL),('ne','Niger',NULL,NULL,NULL),('nf','Norfolk Island',NULL,NULL,NULL),('ng','Nigeria',NULL,NULL,NULL),('ni','Nicaragua',NULL,NULL,NULL),('nl','Holanda',NULL,NULL,NULL),('no','Noruega',NULL,NULL,NULL),('np','Nepal',NULL,NULL,NULL),('nr','Nauru',NULL,NULL,NULL),('nu','Niue',NULL,NULL,NULL),('nz','Nueva Zelanda',NULL,NULL,NULL),('om','Omán',NULL,NULL,NULL),('pa','Panamá',NULL,NULL,NULL),('pe','Perú',NULL,NULL,NULL),('pf','Polinesia (Francesa)',NULL,NULL,NULL),('pg','Papua Nueva Guinea',NULL,NULL,NULL),('ph','Filipinas',NULL,NULL,NULL),('pk','Pakistán',NULL,NULL,NULL),('pl','Polonia',NULL,NULL,NULL),('pm','Saint Pierre y Miquelon',NULL,NULL,NULL),('pn','Islas Pitcairn',NULL,NULL,NULL),('pr','Puerto Rico',NULL,NULL,NULL),('pt','Portugal',NULL,NULL,NULL),('pw','Palau',NULL,NULL,NULL),('py','Paraguay',NULL,NULL,NULL),('qa','Qatar',NULL,NULL,NULL),('re','Reunión (Francesa)',NULL,NULL,NULL),('ro','Rumanía',NULL,NULL,NULL),('rs','Serbia',NULL,NULL,NULL),('ru','Rusia',NULL,NULL,NULL),('rw','Rwanda',NULL,NULL,NULL),('sa','Arabia Saudita',NULL,NULL,NULL),('sb','Islas Salomón',NULL,NULL,NULL),('sc','Seychelles',NULL,NULL,NULL),('sd','Sudán',NULL,NULL,NULL),('se','Suecia',NULL,NULL,NULL),('sg','Singapore',NULL,NULL,NULL),('sh','Santa Helena',NULL,NULL,NULL),('si','Eslovenia',NULL,NULL,NULL),('sj','Islas Svalbard y Jan Mayen',NULL,NULL,NULL),('sk','República Eslovaca',NULL,NULL,NULL),('sl','Sierra Leona',NULL,NULL,NULL),('sm','San Marino',NULL,NULL,NULL),('sn','Senegal',NULL,NULL,NULL),('so','Somalia',NULL,NULL,NULL),('sr','Suriname',NULL,NULL,NULL),('st','Sao Tomé y Príncipe',NULL,NULL,NULL),('sv','El Salvador',NULL,NULL,NULL),('sy','Siria',NULL,NULL,NULL),('sz','Swaziland',NULL,NULL,NULL),('tc','Islas Turcos y Caicos',NULL,NULL,NULL),('td','Chad',NULL,NULL,NULL),('tf','Territorios Franceses de Sur',NULL,NULL,NULL),('tg','Togo',NULL,NULL,NULL),('th','Tailandia',NULL,NULL,NULL),('tj','Tadjikistán',NULL,NULL,NULL),('tk','Tokelau',NULL,NULL,NULL),('tm','Turkmenia',NULL,NULL,NULL),('tn','Túnez',NULL,NULL,NULL),('to','Tonga',NULL,NULL,NULL),('tp','Timor del Este',NULL,NULL,NULL),('tr','Turquía',NULL,NULL,NULL),('tt','Trinidad y Tobago',NULL,NULL,NULL),('tv','Tuvalu',NULL,NULL,NULL),('tw','Taiwán',NULL,NULL,NULL),('tz','Tanzania',NULL,NULL,NULL),('ua','Ucrania',NULL,NULL,NULL),('ug','Uganda',NULL,NULL,NULL),('uk','Reino Unido',NULL,NULL,NULL),('um','USA Isla Menores',NULL,NULL,NULL),('us','Estados Unidos',NULL,NULL,NULL),('uy','Uruguay',NULL,NULL,NULL),('uz','Uzbekistán',NULL,NULL,NULL),('va','Vaticano',NULL,NULL,NULL),('vc','San Vicente y Granadinas',NULL,NULL,NULL),('ve','Venezuela',NULL,NULL,NULL),('vg','Islas Vírgenes (Reino Unido)',NULL,NULL,NULL),('vi','Islas Vírgenes (USA)',NULL,NULL,NULL),('vn','Vietnam',NULL,NULL,NULL),('vu','Vanuatu',NULL,NULL,NULL),('wf','Islas Wallis y Futuna',NULL,NULL,NULL),('ws','Samoa',NULL,NULL,NULL),('ye','Yemen',NULL,NULL,NULL),('yt','Mayotte',NULL,NULL,NULL),('za','África del Sur',NULL,NULL,NULL),('zm','Zambia',NULL,NULL,NULL),('zr','Zaire',NULL,NULL,NULL),('zw','Zimbabwe',NULL,NULL,NULL);

-- PROVINCIAS
INSERT INTO `tblProvincia` VALUES (1,'Araba','Araba','Araba',NULL),(2,'Albacete','Albacete','Albacete',NULL),(3,'Alacant',NULL,NULL,NULL),(4,'Almería',NULL,NULL,NULL),(5,'Ávila',NULL,NULL,NULL),(6,'Badajoz',NULL,NULL,NULL),(7,'Balears',NULL,NULL,NULL),(8,'Barcelona',NULL,NULL,NULL),(9,'Burgos',NULL,NULL,NULL),(10,'Cáceres',NULL,NULL,NULL),(11,'Cádiz',NULL,NULL,NULL),(12,'Castellón de la Plana',NULL,NULL,NULL),(13,'Ciudad Real',NULL,NULL,NULL),(14,'Córdoba',NULL,NULL,NULL),(15,'A Coruña',NULL,NULL,NULL),(16,'Cuenca',NULL,NULL,NULL),(17,'Girona',NULL,NULL,NULL),(18,'Granada',NULL,NULL,NULL),(19,'Guadalajara',NULL,NULL,NULL),(20,'Gipuzkoa',NULL,NULL,NULL),(21,'Huelva',NULL,NULL,NULL),(22,'Huesca',NULL,NULL,NULL),(23,'Jaén',NULL,NULL,NULL),(24,'León',NULL,NULL,NULL),(25,'Lleida',NULL,NULL,NULL),(26,'La Rioja',NULL,NULL,NULL),(27,'Lugo',NULL,NULL,NULL),(28,'Madrid',NULL,NULL,NULL),(29,'Málaga',NULL,NULL,NULL),(30,'Murcia',NULL,NULL,NULL),(31,'Navarra',NULL,NULL,NULL),(32,'Ourense',NULL,NULL,NULL),(33,'Asturies',NULL,NULL,NULL),(34,'Palencia',NULL,NULL,NULL),(35,'Las Palmas',NULL,NULL,NULL),(36,'Pontevedra',NULL,NULL,NULL),(37,'Salamanca',NULL,NULL,NULL),(38,'S.C.Tenerife',NULL,NULL,NULL),(39,'Cantabria',NULL,NULL,NULL),(40,'Segovia',NULL,NULL,NULL),(41,'Sevilla',NULL,NULL,NULL),(42,'Soria',NULL,NULL,NULL),(43,'Tarragona',NULL,NULL,NULL),(44,'Teruel',NULL,NULL,NULL),(45,'Toledo',NULL,NULL,NULL),(46,'Valencia',NULL,NULL,NULL),(47,'Valladolid',NULL,NULL,NULL),(48,'Bizkaia',NULL,NULL,NULL),(49,'Zamora',NULL,NULL,NULL),(50,'Zaragoza',NULL,NULL,NULL),(51,'Ceuta',NULL,NULL,NULL),(52,'Melilla',NULL,NULL,NULL);

-- ENTIDAD
INSERT INTO `tblEntidad` (idEntidad,fkUsuario,fkPais,fkProvincia,fkTipoIdentificacion,fkEstadoCivil,fkEstadoLaboral,fkNivelEstudios,vNombre,vPrimerApellido,vSegundoApellido,vNumeroIdentificacion,dNacimiento,vPoblacion,vCp,vDireccion,vTelefono,vMovil,vFax,bActiva,dAlta,dBaja,mod_user,last_modified) VALUES (1,1,1,1,1,1,1,1,'admin','apellido','apellido','43335521M','2010-10-27','Palma','07004','Gremi Fusters 7',971776655,687987765,971223344,1,now(),NULL,NULL,now());

SET FOREIGN_KEY_CHECKS = 1;
