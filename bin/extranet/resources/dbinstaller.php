<?php

#####################################################
#													#
# Ningen CMS - Script de instalación de extranet	#
# Version: 0.5.3 Fecha: NOV/2010					#
#													#
#####################################################

die("DUMMY SCRIPT - NO UTILIZAR");

# Modificaremos el include path
set_include_path("/var/www/ningenCMS/lib/");

# Clases requeridas
require_once "NingenConsole.inc";
require_once "dbase/NingenConnection.inc";

$dbname = $argv[1];
$out = new NingenConsole();
$db = new NingenConnection(array("host"=>"localhost", "password"=>"hastalavistababy", "username"=>"terminator", "dbname"=>$dbname));

# Se comprueban los parámetros
if ($argc < 2){
	$out->println("\nExtranet Installer - Modo de uso:\n\t php dbinstaller.php <nombre base de datos>\n");
	print_r($db->getLog());
	exit(1);
}

# Se ejecuta el SQL
$sql = file_get_contents("./dbase.sql");
$db->begin();

if (!$db->executeQuery($sql)){
	
	$db->rollback();
	$out->println("ERROR: al ejecutar el sql.");
	print_r($db->getLog());
	exit(2);
	
}

$db->commit();

exit(0);

?>
