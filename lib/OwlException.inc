<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase extendida de exception que puede ser utilizada por xinax-debug
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once 'helper/OwlHtmlHelper.inc';
require_once 'OwlServerResponses.inc';


class OwlException extends Exception{
	
	/**
	 * Prepara el mensaje de debug
	 * @return unknown_type
	 */
	public function getDebugMessage(){
		
		return OwlCmsHtmlHelper::getHtmlExceptionDebug($this->getFormatedMessage($this->getMessage()), $this->getTrace(), $this->getLine(), $this->getFile());
		
	}
	
	/**
	 * Errores comprometidos con el servidor se mostraran en la 
	 * correspondiente página de error
	 */
	public function echoCmsMessage(){
		
		$response = new OwlServerResponses(500, $this->getDebugMessage());
		$response->sendResponse();
		
	}
	
	/**
	 * Devuelve el mensaje en un párrafo, si no hay mensaje devuelve null
	 * @return string
	 */
	protected function getFormatedMessage($msg){
		
		return '<p>' . $msg . '</p>';
		
	}
	
	

 	
	
}

?>