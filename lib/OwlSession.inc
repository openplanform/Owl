<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase para el manejo de sessiones Owl
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once CONFIGDIR . 'SessionObjects.php';

class OwlSession{
	
	
	/**
	 * Devuelve una clave si existe en la sessión, 
	 * si no existe, devuelve null
	 * @param string $valueName
	 * @return string
	 */
	public static function getValue( $valueName ){
		
		if (array_key_exists($valueName, $_SESSION['OWL'])){
			
			return $_SESSION['OWL'][$valueName];
			
		}
		
		return null;
		
	}
	
	/**
	 * Establece una clave y su valor en la sessión
	 * @param string $valueName
	 * @param mixed $valueData
	 * @return void
	 */
	public static function setValue( $valueName, $valueData){
		
		$_SESSION['OWL'][$valueName] = $valueData;
		
	}
	
	/**
	 * Destruye la sessión actual
	 * @return boolean
	 */
	public static function destroy(){
		
		return session_destroy();
		
	}

	/**
	 * Crea la sessión
	 */
	public static function create(){
	    
    	session_start();
    	
        if (!array_key_exists('OWL', $_SESSION)){
            $_SESSION['OWL'] = array();
        }	    
	    
	}
	
	/**
	 * Elimina un valor y su clave del array de sesión
	 * @param string $clave
	 */
	public static function destroyValue($clave){
	    
	   if (array_key_exists('OWL', $_SESSION) && array_key_exists($clave, $_SESSION['OWL'])){
            unset($_SESSION['OWL'][$clave]);
        }
	    
	}
	
}

?>