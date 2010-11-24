<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase encargada de mostrar los mensajes del servidor en el cliente
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


class OwlServerResponses{
	
	/**
	 * Código de error
	 * @var integer
	 */
	private $_errorCode;
	
	/**
	 * Mensajes de error
	 * @var array
	 */
	private $_errorMessages;
	
	/**
	 * Descripcion del error
	 * @var string
	 */
	private $_errorDescription;
	
	/**
	 * Constructora, inicializa el codigo de error HTTP y los valores necesarios
	 * @param integer $code
	 * @param stirng $description
	 * @return void
	 */
	public function __construct($code, $description = ''){
		
		// Se inicializan los códigos de error manejables
		$this->initializeErrorMessages();
		
		if (array_key_exists(intval($code), $this->_errorMessages)){

			$this->_errorCode = $code;
			$this->_errorDescription = $description ? $description : null;
			return;
			
		}
		
		// No debería suceder, pero por las moscas
		die('Error no manejado por el servidor');
		
	}
	
	/**
	 * Inicia el array de mensajes de servidor
	 * @return void
	 */
	private function initializeErrorMessages(){
		
		$status = array(
			
			// The request had bad syntax or was inherently impossible to be satisfied. 
			400 => 'Bad request',
			
			// The parameter to this message gives a specification of authorization schemes which are acceptable. 
			// The client should retry the request with a suitable Authorization  header. 
			401 => 'Unauthorized',
			
			// The parameter to this message gives a specification of charging schemes acceptable. 
			// The client may retry the request with a suitable ChargeTo header. 
			402 => 'PaymentRequired',
			
			// The request is for something forbidden. Authorization will not help. 
			403 => 'Forbidden',
			
			// The server has not found anything matching the URI given 
			404 => 'Not found',
			
			// The server encountered an unexpected condition which prevented it from fulfilling the request.
			500 => 'Internal Error',
			
			// The server does not support the facility required. 
			501 => 'Not implemented',
		
		);
		
		$this->_errorMessages = $status;
		
	}
	
	/**
	 * Envía la página de error al buffer
	 * @return void
	 */
	public function sendResponse(){
		
		$this->sendHeaders();
		$this->sendErrorPage();
		
	}

	/**
	 * Envia los headers solo si ya no han sido enviados
	 * @return void
	 */
	private function sendHeaders(){
		
		if (!headers_sent()){
			$headerString = $_SERVER["SERVER_PROTOCOL"] . " " . $this->_errorCode . " " . $this->_errorMessages[$this->_errorCode];
			header($headerString);
		}
				
	}
	
	/**
	 * Crea el código html para mostrar la página de error
	 * @return void
	 */
	private function sendErrorPage(){
		
		$titulo = $this->_errorCode . ' - ' . $this->_errorMessages[$this->_errorCode];
		echo OwlHtmlHelper::getHtmlErrorPage($titulo, $this->_errorCode, $this->_errorMessages[$this->_errorCode], $this->_errorDescription);
		die();
		
	}
	
}

?>