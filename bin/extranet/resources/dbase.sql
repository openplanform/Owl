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

-- NOTICIA
DROP TABLE IF EXISTS `tblNoticia`;
CREATE  TABLE `tblNoticia` (
  `idNoticia` INT(11) NOT NULL AUTO_INCREMENT ,
  `vTitulo` VARCHAR(400) NOT NULL ,
  `vTexto` VARCHAR(10000) NOT NULL ,
  `dFecha` DATE NOT NULL ,
  `bActivo` TINYINT(1) NOT NULL DEFAULT 1 ,
  `vSubtitulo` VARCHAR(1000) NULL ,
  `iImagen` INT(11) NULL ,
  `iAlign` INT(1) NULL ,
  `vAutor` VARCHAR(400) NULL ,
  `mod_user` VARCHAR(45) NOT NULL ,
  `last_modified` DATE NOT NULL ,
  PRIMARY KEY (`idNoticia`) )
DEFAULT CHARACTER SET = utf8$$


-- INSERTS

-- USUARIO
INSERT INTO `tblUsuario` (idUsuario,vNombre,vPassword,vEmail) VALUES (1,'admin','563566b348459042881bc33f336211a3','info@ningen.es');

-- ROL
INSERT INTO `tblRol` (idRol,vNombre,vDescripcion) VALUES (1,'Administrador','Administrador del Sistema');
INSERT INTO `tblRol` (idRol,vNombre,vDescripcion) VALUES (2,'Usuario','Usuario de la aplicación');

-- ROL USUARIO
INSERT INTO `trelRolUsuario` (fkUsuario,fkRol) VALUES (1,1);

-- ACCESOS
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (1,0,'Usuarios',1,0,'usuario',NULL,NULL);
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (2,1,'Alta',1,0,'usuario','alta','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (3,1,'Listado',1,1,'usuario','index','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (4,1,'_Buscar',1,2,'usuario','buscar','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (5,1,'Editar',0,3,'usuario','editar','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (6,1,'Ficha',0,4,'usuario','ficha','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (7,1,'Eliminar',0,5,'usuario','eliminar','1');

INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (8,0,'Administración',1,1,'administrador',NULL,NULL);
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (9,8,'Menú',1,0,'administrador','menu','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (10,8,'Roles',1,1,'administrador','roles','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (11,8,'Configuración',1,2,'administrador','configuracion','1');
INSERT INTO `tblAcceso` (idAcceso,fkPadre,vNombre,bMenu,iOrden,vControlador,vAccion,vRoles) VALUES (12,8,'Panel',0,3,'index','panel','1,2');


SET FOREIGN_KEY_CHECKS = 1;
