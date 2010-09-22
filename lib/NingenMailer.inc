<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 *
 * Clase con funciones de abstracción para envio de mails
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once ZEND_FRAMEWORK . 'Mail.php';
require_once ZEND_FRAMEWORK . 'Mail/Transport/Smtp.php';

require_once 'NingenException.inc';

class NingenMailer{
	
	/**
	 * Servidor SMTP
	 * @var string
	 */
	private $_server = 'localhost';
	
	/**
	 * Usuario
	 * @var string
	 */
	private $_username;
	
	/**
	 * Contraseña
	 * @var string
	 */
	private $_password;
	
	/**
	 * Asunto
	 * @var string
	 */
	private $_subject;
	
	/**
	 * Cuerpo del mensaje
	 * @var string
	 */
	private $_body;
	
	/**
	 * Zend Mailer
	 * @var Zend_Mail
	 */
	private $_ZendMailer;
	
	/**
	 * Zend Transporter
	 * @var unknown_type
	 */
	private $_ZendTransporter;
	
	/**
	 * Modo de envío (html | plain)
	 * @var string
	 */
	private $_mode = 'html';
	
	/**
	 * Tipo de servidor 
	 * Por ahora:
	 * 		mail ( funcion mail del API de php )
	 * 		smtp ( conexión a servidor smtp autentificado )
	 * @var string
	 */
	private $_serverType = 'mail';
	
	/**
	 * Nombre del mail de destino
	 * @var string
	 */
	private $_toName = null;
	
	/**
	 * Dirección del mail de destino
	 * @var string
	 */
	private $_toMail = null;
	
	/**
	 * Nombre del mail del remitente
	 * @var string
	 */
	private $_fromName = null;
	
	/**
	 * Dirección del mail del remitente
	 * @var string
	 */
	private $_fromMail = null;	
	
	/**
	 * Flag que indica si se debe convertir 
	 * el body del mail a UTF8
	 * @var boolean
	 */
	private $_forceUtf = false;
	
	/**
	 * Contructor instancia el Zend mailer
	 * @return void
	 */
	public function __construct( $mailerConfiguration ){
			
		// Se procesa la configuración del mailer
		$this->_processConfiguration($mailerConfiguration);
		
	}
	
	/**
	 * Verifica la configuración del mailer y la popula
	 * de acuerdo al modo del objeto
	 * @param array $mailerConfiguration
	 * @throws NingenException
	 */
	private function _processConfiguration( $mailerConfiguration ){
		
		if (is_null($mailerConfiguration)){
			throw new NingenException('No hay ningún mailer configurado', 500);
		}

		// Antes que nada se verificará el tipo de servidor y el modo de funcionamiento del mailer
		$this->_setServerType($mailerConfiguration['server-type']);
		$this->_setMode($mailerConfiguration['mode']);
		
		// La configuración requerida varía de acuerdo al tipo de servidor 
		if ($this->_serverType == 'smtp'){
			
			// SMTP con autentificación
			$requiredKeys = array('target', 'server', 'username', 'password', 'subject');
			
			foreach ($requiredKeys as $key){
				if (!array_key_exists($key, $mailerConfiguration)){
					throw new NingenException('NingenMailer: la clave ' . $key . ' debe ser configurada', 500);
				}
			}

			//Mailer
			$this->_ZendMailer = new Zend_Mail(NINGENCMS_APPENCODING);
			
			//Generator
			$this->_ZendMailer->addHeader('X-MailGenerator', 'Ningen Mailer 1.0');
			
			//Header encoding
			$this->_ZendMailer->setHeaderEncoding(Zend_Mime::ENCODING_BASE64);
			
			// Se popula la configuración
			$this->_server = $mailerConfiguration['server'];
			$this->_username = $mailerConfiguration['username'];
			$this->_password = $mailerConfiguration['password'];
			
			
		} elseif( $this->_serverType == 'mail') {
			
			// Función mail del api de php
			$requiredKeys = array('target', 'subject');

			foreach ($requiredKeys as $key){
				if (!array_key_exists($key, $mailerConfiguration)){
					throw new NingenException('NingenMailer: la clave ' . $key . ' debe ser configurada', 500);
				}
			}
			
		}
		
		// Claves de configuración opcionales
		if (array_key_exists('force-utf', $mailerConfiguration) && $mailerConfiguration['force-utf'] != ''){
			$this->_forceUtf = $mailerConfiguration['force-utf'];			
		}
		
		// Datos comunes entre los dos modos de funcionamiento
		$this->_addTo($mailerConfiguration['target']['mail'], $mailerConfiguration['target']['name']);
		$this->_subject = $mailerConfiguration['subject'];
		
		
	}
	
	/**
	 * Agrega un destinatario
	 * @param string $email Direccion de email
	 * @param string $nombre Nombre del destinatario
	 * @return void
	 */
	private function _addTo($email, $nombre = null){
		
		$this->_toMail = $email;
		$this->_toName = $nombre;
		
	}
	
	/**
	 * Establece el modo del mail
	 * @param string (text|html)
	 * @return void
	 */
	private function _setMode($mode){

		$allowedModes = array('plain', 'html');
		
		if (!in_array($mode, $allowedModes)){
			throw new NingenException('NingenMailer: ' . $mode . ' no es modo válido', 500);
		} else {
			$this->_mode = $mode;
		}
		
	}
	
	/**
	 * Establece el tipo de servidor
	 * @param string $type
	 */
	private function _setServerType($type){
		
		$allowedTypes = array('mail', 'smtp');
		
		if (!in_array($type, $allowedTypes)){
			throw new NingenException('NingenMailer: ' . $type . ' no es un tipo de servidor válido', 500);
		} else {
			$this->_serverType = $type;
		}
		
	}
	
	/**
	 * Establece el cuerpo del mensaje
	 * @TODO pasar encoding
	 * @return void
	 */
	public function setBody($body){

		if ($this->_forceUtf){
			$this->_body = utf8_encode($body);
			return;
		}
		
		$this->_body = $body;
		
	}
	
	/**
	 * Inicia el mailer y transporte de Zend
	 * No es necesario llamarlo cuando se utiliza la funcion mail de php
	 * @return boolean
	 */
	private function _initMailer(){
		
		//Configuracion
		$configParams = array(
			'auth' => 'login',
			'username' => $this->_username,
			'password' => $this->_password,
		);
		
		//Transporter
		return ($this->_ZendTransporter = new Zend_Mail_Transport_Smtp($this->_server, $configParams));
		
	}
	
	/**
	 * Establece la dirección de respuesta (Opcional)
	 * @param string $from (email)
	 * @param string $nombre
	 * @return void
	 */
	public function setFrom($from, $nombre = null){
		
		$this->_fromMail = $from;
		$this->_fromName = $nombre;
		
	}
	
	/**
	 * Envía el mail
	 * @return boolean
	 */
	public function send(){

		if (is_null($this->_body)){
			throw new Exception('NingenMailer: nada para enviar');
		}		
		
		switch ($this->_serverType){
			
			case 'smtp':

				// Se inicia el transporte de Zend
				$this->_initMailer();
				$this->_ZendMailer->addTo($this->_toMail, $this->_toName);
				$this->_ZendMailer->setFrom($this->_fromMail, $this->_fromName);
				$this->_ZendMailer->setReplyTo($this->_toMail, $this->_toName);	
				$this->_ZendMailer->setSubject($this->_subject);
				
				if ($this->_mode == 'html'){
					$this->_ZendMailer->setBodyHtml($this->_body);
				}else{
					$this->_ZendMailer->setBodyText($this->_body);
				}
				
				return $this->_ZendMailer->send($this->_ZendTransporter);
						
			break;
				
			case 'mail':
				
				// Se preparan las cabeceras
				$cabeceras = 'From: ' . $this->_fromMail . "\n";
				$cabeceras .= 'Reply-To: ' . $this->_fromMail . "\n";
				$cabeceras .= 'MIME-Version: 1.0' . "\r\n";
		        $cabeceras .= 'To: ' . $this->_toMail . "\n";
		        $cabeceras .= 'Content-type: text/html; charset=UTF-8' . "\n";
				$cabeceras .= 'X-Mailer: PHP/' . phpversion();
				
				return mail($this->_toMail, $this->_subject , $this->_body, $cabeceras);
				
			break;
				
			default:
				return false;
			break;
			
		}
		
		
	}
	
	
}

?>