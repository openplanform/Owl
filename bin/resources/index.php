<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Guión de bootstrap, inicia la ejecución de la aplicación
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

// Se incluyen las definiciones del sistema de archivos
include_once '../app/configs/NingenGlobals.php';

// Se inicia la sessión
session_start();
if (!array_key_exists('NINGEN_CMS', $_SESSION)){
	$_SESSION['NINGEN_CMS'] = array();
}

// Se agregan las librerías al include_path
set_include_path(get_include_path() . 
	PATH_SEPARATOR . NINGENCMS_LIBDIR . 
	PATH_SEPARATOR . NINGENCMS_EXTLIBDIR);
	
// Control de errores
if (NINGENCMS_DEV){
	error_reporting(E_ALL);
} else {
	error_reporting(!E_ALL);
}

// Se instancia la aplicación
require_once 'NingenApplication.inc';
$application = new NingenApplication();

?>