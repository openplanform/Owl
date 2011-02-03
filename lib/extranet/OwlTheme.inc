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
 * Controller de la extranet.
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

require_once 'OwlException.inc';


class OwlTheme{
	
	/**
	 * Clave para almacenar el tema en el array de cookies
	 * La clave es owl_md5('tema')
	 */
	const COOKIE_THEME_ID = 'owl_c5f3de31f3a2c4018f39966fa6563659';
	
	/**
	 * Tiempo de expiración de la cookie. 2 años
	 * @var string
	 */
	const COOKIE_THEME_TIME = 63072000;
	
	/**
	 * Ruta al css del tema
	 * @var string
	 */
	private $_cssPath;
	
	/**
	 * Constructor
	 * @param OwlApplicationConfig $appConfig
	 * @throws OwlException
	 */
	public function __construct(OwlApplicationConfig $appConfig){

		// Comprobamos si existe la cookie del tema
		if ( array_key_exists( self::COOKIE_THEME_ID, $_COOKIE ) ){
			$tema = ($_COOKIE[self::COOKIE_THEME_ID]);
		} else {
    		$tema = new OwlTheme($appConfig->getDefaultTheme());
		}
		
		// Si no existe el tema, por defecto toma el general
		if ( !is_dir( THEMEDIR . $tema ) || !is_file( THEMEDIR . $tema . '/css/' . $tema . '.css' ) ){
			$this->_cssPath = '/css/general.css';
		} else {
			$this->_cssPath = '/themes/' . $tema . '/css/' . $tema . '.css';
		}
		
	}
	
	/**
	 * Devuelve el path al css
	 * @return string
	 */
	public function getCssPath(){
		return $this->_cssPath;	
	}

	
	/**
	 * Establece el tema actual, y lo almacena en una coockie
	 * 
	 * @param string $tema
	 * @return boolean
	 */
	public function setTheme($tema){
	
		if (!empty($tema)){
			return setcookie(self::COOKIE_THEME_ID, $tema, time() + self::COOKIE_THEME_TIME, '/');
		}		
		return false;
		
	}
	
}


?>