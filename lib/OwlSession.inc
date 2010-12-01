<?php

/* vim: set syn=php expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**																			 
 *  ,_,  
 * (o,o) 
 * {`"'}   OWL (Open Web Library)
 * -"-"-
 * 
 * Software distribuido bajo la "GNU GENERAL PUBLIC LICENSE v3", 
 * mas información en /doc/LICENSE
 * 
 * Clase para el manejo de sessiones Owl
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @author Aaron Amengual Arranz <aaron.amengual@gmail.com> 
 * @version 0.5.4
 * @since 0.3
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