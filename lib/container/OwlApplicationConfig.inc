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
 * Clase contenedora que encapsula la configuración de una aplicación
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


class OwlApplicationConfig{
	
	/**
	 * Objeto de configuración
	 * @var Zend_Config_Ini
	 */
	private $_configData;
	
	/**
	 * Array de configuración
	 * @var array
	 */
	private $_configDataArray;
	
	/**
	 * Controlador por defecto
	 * @var string
	 */
	private $_defaultController = 'index';
	
	/**
	 * Acción por defecto
	 * @var string
	 */
	private $_defaultAction = 'index';
	
	/**
	 * Codificación or defecto de la aplicación
	 * @var string
	 */
	private $_appEncoding = 'UTF-8';
	
	/**
	 * Idioma por defcto
	 * @var string
	 */
	private $_defaultLang = 'es';
	
	/**
	 * Nombre de host de la applicación
	 * @var string
	 */
	private $_appHostname;
	
	/**
	 * Configuración del sistema
	 * @var stdClass
	 */
	private $_systemConfig;
	
	/**
	 * Nombre del layout por defecto a utilizar
	 * @var string
	 */
	private $_defaultLayout = null;
	
	/**
	 * Nombre del tema por defecto a utilizar
	 * @var string
	 */
	private $_defaultTheme = null;
	
	/**
	 * Hash con la configuración de los distintos 
	 * menues del sitio (si hay)
	 * @var array
	 */
	private $_menuesConfigurationContainer = array();
	
	/**
	 * Flag que indica si se deben canonizar los nombres
	 * @var boolean
	 */
	private $_canonizeNames = false;
	
	/**
	 * Titulo de base de la aplicación
	 * @var string
	 */
	private $_baseTitle = null;
	
	
	/**
	 * Verifica la integridad del objeto de configuración
	 * @param Zend_Config_Ini $configData
	 * @return void
	 */
	final public function __construct($configData){
		
		// Se verifica el objeto
		if (!$configData instanceof Zend_Config_Ini){
			throw new OwlException('La información de configuración no es válida.');
		}
		
		// Se almacena
		$this->_configData = $configData;
		$this->_configDataArray = $configData->toArray();
		
		// Se verifican los requerimientos
		$this->checkConfigRequirements();
		
	}
	
	
	/**
	 * Checkea lo requerientos para validar la configuración
	 * esta funcion seguramente vaya cambiando con el tiempo
	 * @return void
	 */
	protected function checkConfigRequirements(){

		// REGLA 1 - Configuración de sistema (BBDD, dominios, etc)
		$systemConfig = $this->_configData->system;
		
		if (!$systemConfig instanceof Zend_Config){
			throw new OwlException('No ha sido podible obtener la configuración del sistema. No se puede continuar.');
		} else {
			$this->_systemConfig = $systemConfig;
		}
		
		// REGLA 2 - Se obtienen los dátos básicos de configuración
		if ($customController = $this->_configData->app->default_controller){
			$this->_defaultController = $customController;
		} 
		
		if ($customAction = $this->_configData->app->default_action){
			$this->_defaultAction = $customAction;
		}
		
		if ($customEncoding = $this->_configData->app->encoding){
			$this->_appEncoding = $customEncoding;
		}
		
		if ($customLang = $this->_configData->app->default_lang){
			$this->_defaultLang = $customLang;
		}
		
		if ($appHostname = $this->_configData->app->hostname){
			$this->_appHostname = $appHostname;
		}
		
		if ($defaultLayout = $this->_configData->app->default_layout){
			$this->_defaultLayout = $defaultLayout;
		}
		
		if ($defaultTheme = $this->_configData->app->default_theme){
			$this->_defaultTheme = $defaultTheme;
		}
		
		if ($menuesConfig = $this->_configData->app->menu){
			$this->_menuesConfigurationContainer = $menuesConfig;
		}
		
		if ($canonizeNames = $this->_configData->app->canonize){
			$this->_canonizeNames = $canonizeNames;
		}
		
	}
	
	
	/**
	 * Devuelve el controlador por defecto
	 * @return string
	 */
	public function getDefaultController(){
		return $this->_defaultController;
	}
	
	/**
	 * Devuelve la acción por defecto
	 * @return string
	 */
	public function getDefaultAction(){
		return $this->_defaultAction;
	}
	
	/**
	 * Devuelve el idioma por defecto
	 * @return string
	 */
	public function getDefaultLang(){
		return $this->_defaultLang;
	}

	/**
	 * Dvuelve la codificación de la aplicación
	 * @return string
	 */
	public function getAppEncoding(){
		return $this->_appEncoding;
	}

	/**
	 * Devuelve el hostname de la applicación
	 * @return string
	 */
	public function getAppHostname(){
		return $this->_appHostname;
	}
	
	/**
	 * Devuelve un valor de configuración, si no lo encuentra
	 * devuelve null
	 * @param string $keyName
	 * @return string
	 */
	public function get($keyName){
		return $this->_configData->get($keyName, null);
	}
	
	/**
	 * Devuelve la configuración del sistema
	 * @return array
	 */
	public function getSystemConfig(){
		return $this->_systemConfig;
	}
	
	/**
	 * Devuelve el nombre del layout por defecto
	 * @return string
	 */
	public function getDefaultLayout(){
		return $this->_defaultLayout;
	}
	
	/**
	 * Devuelve el nombre del tema por defecto
	 * @return string
	 */
	public function getDefaultTheme(){
		return $this->_defaultTheme;
	}
	
	/**
	 * Devuelve la cantidad de menúes configurados
	 * para la aplicación
	 * @return integer
	 */
	public function hasNavigationMenu(){
		return count($this->_menuesConfigurationContainer);
	}
	
	/**
	 * Devuelve la configuración del menu especificado, si no lo encuentra devuelve null
	 * @param stirng $menuName
	 * @return stdClass
	 */
	public function getMenuConfig($menuName = ''){
		
		if (!array_key_exists('menu', $this->_configDataArray['app'])){
			return null;
		}
		
		if (array_key_exists($menuName, $this->_configDataArray['app']['menu'])){
			return $this->_configDataArray['app']['menu'][$menuName];
		}
		
		return null;
		
	}
	
	/**
	 * Devuelve el fag de canonize 
	 * @return boolean
	 */
	public function isCanonizeNames(){
		return intval($this->_canonizeNames);
	}
	
	/**
	 * Devuelve el flag de mantenimiento
	 * @return boolean
	 */
	public function isMantenimiento(){
		return intval($this->_systemConfig->mantenimiento);
	}
	
	/**
	 * Se determinará si el usuario actual tiene acceso al sitio 
	 * @return boolean
	 */
	public function isUserAllowed(){

		// Datos iniciales
		$userIp = $_SERVER['REMOTE_ADDR'];
		$allowString = $this->_systemConfig->allow;

		// Verificaremos los permitidos
		if (!is_null($allowString)){
			
			$allowParts = explode(',', $allowString);
			
			foreach ($allowParts as $allowed){
				if ($userIp == trim($allowed)){
					// El usuario es uno de los elegidos
					return true;
				}
			}
			
			return false;
			
		}
		
		return true;
		
		
	}
	
	/**
	 * Devuelve la descripción de la aplicación, si ha sido configurada
	 * @return string
	 */
	public function getApplicationDescription(){
		
		if (array_key_exists('description', $this->_configDataArray['app'])){
			return $this->_configDataArray['app']['description'];
		}
		
		return null;
		
	}
	
	/**
	 * Devuelve el nombre de la aplicación
	 * @return string
	 */
	public function getApplicationName(){
		
		if (array_key_exists('name', $this->_configDataArray['app'])){
			return $this->_configDataArray['app']['name'];
		}
		
		return null;		
		
	}
	
	/**
	 * Devuelve las palabras clave de la aplicación, si han sido configuradas
	 * @return string
	 */
	public function getApplicationKeywords(){
		
		if (array_key_exists('keywords', $this->_configDataArray['app'])){
			return $this->_configDataArray['app']['keywords'];
		}
		
		return null;
		
	}
	
	/**
	 * Obtiene la configuración del mailer si fue especificada, 
	 * si no es así devuelve null
	 * @return array
	 */
	public function getMailerConfiguration(){
		
		if (array_key_exists('mailer', $this->_configDataArray['system']) && is_array($this->_configDataArray['system']['mailer'])){
			return $this->_configDataArray['system']['mailer'];
		}
		
		return null;
		
	}
	
	/**
	 * Optiene la configuración del captcha si fue especificada, 
	 * si no es así devuelve null
	 * @return array
	 */
	public function getCaptchaConfiguration(){
		
		if (array_key_exists('captcha', $this->_configDataArray['system']) && is_array($this->_configDataArray['system']['captcha'])){
			return $this->_configDataArray['system']['captcha'];
		}
		
		return null;		
		
	}
	
	/**
	 * Optiene la configuración de la base de datos si fue especificada, 
	 * si no es así devuelve null
	 * @return array
	 */
	public function getDatabaseConfiguration(){
		
		if (array_key_exists('db', $this->_configDataArray['system']) && is_array($this->_configDataArray['system']['db'])){
			return $this->_configDataArray['system']['db'];
		}
		
		/**
		 * @TODO procesar la config, y verificar que todos los campos estan completos
		 */
		
		return null;		
		
	}
	
	
	/**
	 * Devuelve el flag que indica si se debe activar el debug del sistema
	 * @return boolean
	 */
	public function getDebugFlag(){

		// Se evalua el flag de debug (resto de clientes)
	    $systemConfig = $this->getSystemConfig();
	    if (intval($systemConfig->owl_debug)){
	    	
			return true;
	    	
	    } else {
		
			// Si el cliente pertenece al grupo de desarrollo
			// Mostraremos el debug
			$ipsDesarrollo = $this->getIpDesarrollo();
			
			if (!is_null($ipsDesarrollo)){
				if (is_array($ipsDesarrollo)){
					if (in_array($_SERVER['REMOTE_ADDR'], $ipsDesarrollo)){
						return true;
					}
				} else {
					if ($ipsDesarrollo == $_SERVER['REMOTE_ADDR']){
						return true;
					}
				}
			}
			
	    }
		
	}
	
	
	/**
	 * Devuelve el título base de la aplicación, si no fué configurado, devuelve null
	 * @return string
	 */
	public function getBaseTitle(){

	    if (array_key_exists('app', $this->_configDataArray) && array_key_exists('basetitle', $this->_configDataArray['app'])){
	        return $this->_configDataArray['app']['basetitle'];
	    }
	    
	    return null;
	    
	}

	
	/**
	 * Devuelve las ips que han sido indicadas bajo la clave ip_desarrollo, si no hay ninguna configurada, devuelve null
	 * @return string | array
	 */
	public function getIpDesarrollo(){
		
		if (array_key_exists('ip_desarrollo', $this->_configDataArray['system']) && !is_null($this->_configDataArray['system']['ip_desarrollo'])){
			
			$ips = $this->_configDataArray['system']['ip_desarrollo'];
			$ipsARR = explode(',', $ips);
			
			return $ipsARR;
			
		} else {
			
			return null;
			
		}		
		
	}
	
	
	
	
	
	
}

?>