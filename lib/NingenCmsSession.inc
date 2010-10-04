<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase para el manejo de sessiones NingenCMS
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once NINGENCMS_CONFIGDIR . 'SessionObjects.php';

class NingenCmsSession{
	
	
	/**
	 * Devuelve una clave si existe en la sessión, 
	 * si no existe, devuelve null
	 * @param string $valueName
	 * @return string
	 */
	public static function getValue( $valueName ){
		
		if (array_key_exists($valueName, $_SESSION['NINGEN_CMS'])){
			
			return $_SESSION['NINGEN_CMS'][$valueName];
			
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
		
		$_SESSION['NINGEN_CMS'][$valueName] = $valueData;
		
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
    	
        if (!array_key_exists('NINGEN_CMS', $_SESSION)){
            $_SESSION['NINGEN_CMS'] = array();
        }	    
	    
	}
	
}

?>