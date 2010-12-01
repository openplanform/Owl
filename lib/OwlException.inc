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
 * Clase extendida de exception que puede ser utilizada por owl-debug
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


require_once 'helper/OwlHtmlHelper.inc';
require_once 'OwlServerResponses.inc';


class OwlException extends Exception{
	
	/**
	 * Prepara el mensaje de debug
	 * @return unknown_type
	 */
	public function getDebugMessage(){
		
		return OwlHtmlHelper::getHtmlExceptionDebug($this->getFormatedMessage($this->getMessage()), $this->getTrace(), $this->getLine(), $this->getFile());
		
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