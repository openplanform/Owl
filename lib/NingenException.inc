<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase extendida de exception que puede ser utilizada por xinax-debug
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once 'helper/NingenCmsHtmlHelper.inc';
require_once 'NingenServerResponses.inc';


class NingenException extends Exception{
	
	/**
	 * Prepara el mensaje de debug
	 * @return unknown_type
	 */
	public function getDebugMessage(){
		
		return NingenCmsHtmlHelper::getHtmlExceptionDebug($this->getFormatedMessage($this->getMessage()), $this->getTrace(), $this->getLine(), $this->getFile());
		
	}
	
	/**
	 * Errores comprometidos con el servidor se mostraran en la 
	 * correspondiente página de error
	 */
	public function echoCmsMessage(){
		
		$response = new NingenServerResponses(500, $this->getDebugMessage());
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