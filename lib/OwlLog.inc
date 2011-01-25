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
 * Clase que implementa el sistema de loggin OWL
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @version 0.5.4
 * @since 0.3
 * 
 */

require_once 'OwlSession.inc';


class OwlLog{
	
	/**
	 * Nombre del log actual
	 * @var string
	 */
	protected $logName;
	
	/**
	 * Configuración de la aplicación
	 * @var OwlApplicationConfig
	 */
	protected $appConfig;
	
	/**
	 * Path hacia el archivo de log actual
	 * @var string
	 */
	protected $logPath;
	
	/**
	 * Puntero al archivo de log
	 * @var resource
	 */
	protected $file;
	
	
	/**
	 * Constructora, inicializa el objeto
	 * @throws OwlException
	 */
	public function __construct($logName){
		
		$this->logName = $logName;
		
		if (!$this->appConfig = OwlSession::getGlobalConfig()){
			throw new OwlException('No se ha podido obtener la configuración de la aplicación', 500);
		}
		
		// Se carga el archivo de log
		$this->_loadLogFile();
		
	}
	
	
	/**
	 * Destructora, libera recursos
	 */
	public function __destruct(){
		
		fclose($this->file);
		
	}
	
	
	/**
	 * Carga el archivo de log, si existe
	 * @throws OwlException
	 */
	private function _loadLogFile(){
		
		// Nombre de la aplicacion
		$appName = strtolower($this->appConfig->getApplicationName());
		
		// Se construye el nombre de archivo y se carga
		$this->logPath = LOGDIR . $this->logName . '.log';
		
		if (false == @$this->file = fopen($this->logPath, 'a')){
			throw new OwlException('No ha sido posible abrir el archivo de log para la aplicación actual: ' . $appName, 500);
		}	
		
	}
	
	
	/**
	 * Básicamente busca en las variables de entorno, el sujeto
	 * más físico realacionado con la ejecución de la aplicación actual.
	 * Si se trata de un ACL buscará el nombre del usuario involucrado, en cambio si 
	 * es un script bajo CLI, el usuario logueado en el sistema.
	 * 
	 * @return string
	 */
	private function _searchAuthor(){
		
		// Usuario de sistema
		if (array_key_exists('USER', $_ENV) && $_ENV['USER'] != ''){
			return $_ENV['USER'];
		}
		
		// Login del usuario de sistema
		if (array_key_exists('LOGNAME', $_ENV) && $_ENV['LOGNAME'] != ''){
			return $_ENV['LOGNAME'];
		}
		
		// Usuario de aplicación
		$usuarioDO = OwlSession::getValue('usuario');
		if ($usuarioDO instanceof OwlSessionUser){
			return $usuarioDO->getNombre();
		}
		
		return 'nobody';
		
	}
	
	
	/**
	 * Añade una línea de log al archivo actual
	 * @param boolean $error
	 * @param string $content
	 */
	public function addLine($content, $error = false){
		
		$timeStamp = date('M d H:i:s');
		$author = $this->_searchAuthor();
		$breakLine = "\n";
		$errorStr = $error ? ' (ERROR)' : '';
		
		$ip = '';
		if (array_key_exists('REMOTE_ADDR', $_SERVER)){
			$ip = ' - ' . $_SERVER['REMOTE_ADDR'];
		}
		
		fwrite($this->file, $timeStamp . $errorStr . ' [' . $author . $ip . '] - ' . trim($content) . $breakLine);
		
	}
	
	
}

?>