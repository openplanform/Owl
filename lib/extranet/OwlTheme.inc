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
	const CLAVE_TEMA = 'owl_c5f3de31f3a2c4018f39966fa6563659';
	
	/**
	 * Tiempo de expiración de la cookie. 2 años
	 * @var string
	 */
	const TIEMPO_EXPIRACION = 63072000;
	
	/**
	 * Ruta al css del tema
	 * @var string
	 */
	private $_cssPath;
	
	/**
	 * Constructor
	 * @param string $tema Nombre del tema
	 * @throws OwlException
	 */
	public function __construct($tema){

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
	
}


?>