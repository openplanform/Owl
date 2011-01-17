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
require_once 'OwlLog.inc';


class OwlException extends Exception{
	
	/**
	 * Manejador de logs 
	 * @var OwlLog
	 */
	protected $log;
	
	
	/**
	 * Prepara el mensaje de debug
	 * @return unknown_type
	 */
	public function getDebugMessage(){
		
		return OwlHtmlHelper::getHtmlExceptionDebug($this->getFormatedMessage($this->getMessage()), $this->getTrace(), $this->getLine(), $this->getFile());
		
	}
	
	
	/**
	 * Errores comprometidos con el servidor se mostraran en la 
	 * correspondiente página de error, si el servidor se encuentra
	 * en producción, el error será logeado y no se mostrará  
	 * ningún tipo de debug.
	 */
	public function echoCmsMessage(){
		
		if (DEVELOPMENT){
		
			// Se muestra la página de error con información de debug
			$response = new OwlServerResponses(500, $this->getDebugMessage());
			$response->sendResponse();
			
		} else {
			
			// Se almacena el error en el archivo de log
			$this->logMessage('[' . $_SERVER['REMOTE_ADDR'] . '] - ' . $this->getMessage() . ' - ' . $this->getFile() . ':' . $this->getLine());
			
			// Se muestra una página de error sin información de depurado
			$response = new OwlServerResponses(500, $this->getFormatedMessage('Ha ocurrido un error, el administrador ya ha sido notificado, intente nuevamente mas tarde. Disculpe las molestias.'));
			$response->sendResponse();
			
		}
		
	}
	
	
	/**
	 * Devuelve el mensaje en un párrafo, si no hay mensaje devuelve null
	 * @return string
	 */
	protected function getFormatedMessage($msg){
		
		return '<p>' . $msg . '</p>';
		
	}
	
	
	/**
	 * Imprime el mensaje de la excepción en el log de errores
	 * @param string $msg
	 */
	protected function logMessage($msg){
		
		$this->log = new OwlLog('errors');
		$this->log->addLine($msg, true);
		
	}
	

 	
	
}

?>