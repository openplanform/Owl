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
 * Clase que implementan las aplicaciones webs compatibles con OWL
 *
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Palumbo <npalumbo@xinax.net>
 * @author Aaron Amengual Arranz <aaron.amengual@gmail.com>
 * @version 0.5.4
 * @since 0.3
 *
 */


require_once 'Zend/Config/Ini.php';

require_once 'OwlException.inc';
require_once 'OwlRouter.inc';
require_once 'OwlLocale.inc';
require_once 'OwlSession.inc';
require_once 'container/OwlApplicationConfig.inc';
require_once 'helper/OwlHtmlHelper.inc';


class OwlApplication{
	
	/**
	 * Instancia del manejador principal de la
	 * configuración de la aplicación, por lo tanto
	 * es privado y solo puede ser utilizado por
	 * application.
	 * @var Zend_Config_Ini
	 */
	private $_configAdapter;
	
	/**
	 * Enrutador principal de la aplicación
	 * @var OwlRouter
	 */
	private $_applicationRouter;
	
	/**
	 * Contenedor que almacena la configuración de la
	 * aplicación
	 * @var OwlApplicationConfig
	 */
	public $applicationConfig;
	
	/**
	 * Interfaz de acceso a la session
	 * @var OwlSession
	 */
	protected $owlSession;
	
	/**
	 * Flag que indica si la
	 * applicación se ejecuta en una consola
	 * @var booelan
	 */
	protected $cliMode = false;
	
	
	/**
	 * Reune la información necesaria para decidir si es posible
	 * iniciar la aplicación
	 * @return void
	 */
	public function __construct(){
		
		try{
			// Se detecta si la aplicación se encuentra en CLI
			$this->_detectCliMode();
			
			// Se establece el nivel de error
			$this->_setErrorLevel();
			
			// Se inicia la configuración de la aplicación
			$this->_loadApplicationConfig();
			
			// Se carga el objeto de locale
			$this->_loadLocale();
			
			// Se inicia el enrutador
			$this->_loadApplicationRouter();
			
			// Se inicia la aplicación
			$this->_initApplication();
			
		} catch (OwlException $e) {
			
			$e->echoCmsMessage();
			
		}
		
	}
	
	
	/**
	 * Establece el nivel de errores que se mostrarán
	 * dependiendo de si el servidor es de desarrollo
	 * @return unknown_type
	 */
	private function _setErrorLevel(){
	
		// Control de errores
		if (DEVELOPMENT){
			error_reporting(E_ALL);
		} else {
			error_reporting(!E_ALL);
		}
		
	}
	
	
	/**
	 * Detecta si la aplicación actual,
	 * se está llamando desde la consola.
	 */
	private function _detectCliMode(){
		
		$this->cliMode = !isset($_SERVER['SERVER_SOFTWARE']);
		
	}
	
	
	/**
	 * Carga la configuración inicial de la aplicación
	 * @return boolean
	 */
	private function _loadApplicationConfig(){
		
		
		// Se verifica desarrollo - producción
		$configSection = DEVELOPMENT ? 'develop' : 'production';
		
		// Opciones del config manager
		$opcionesConfigManager = array(
		
			// Set to TRUE to allow subsequent modification of loaded configuration data in-memory. Defaults to NULL
			'allowModifications' => NULL,
		
			// Set to the character to be used as the nest separator. Defaults to "."
			'nestSeparator' => '.'
		
		);
		

		// Se instancia el manejador de configuración
		$this->_configAdapter = new Zend_Config_Ini(CONFIGDIR . 'application.ini', $configSection, $opcionesConfigManager);
		
		// Se crea el contenedor público que mantendrá la configuración de la aplicación
		$this->applicationConfig = new OwlApplicationConfig($this->_configAdapter);
		
		// Se hace global la configuración
		$GLOBALS['OWL']['app_config'] = $this->applicationConfig;
		
	}
	
	
	/**
	 * Carga el locale y lo propaga en GLOBALS
	 */
	private function _loadLocale(){

		$locale = new OwlLocale($this->applicationConfig);
		$GLOBALS['OWL']['app_locale'] = $locale;
		
	}
	
	
	/**
	 * Inicializa el router
	 * @return void
	 */
	private function _loadApplicationRouter(){
		
		// Si estamos en una consola, el entorno de applicación
		// será controlado por el helper CLI
		if ($this->cliMode){
			return;
		}
		
		// Se inicializa el router
		$this->_applicationRouter = new OwlRouter($_SERVER['REQUEST_URI']);
		
		// Se le pasa la configuración al router
		$this->_applicationRouter->setApplicationConfig($this->applicationConfig);
		
	}
	
	
	/**
	 * Ordena a router iniciar el proceso de bootstrap
	 * @return void
	 */
	private function _initApplication(){
		
		// Si estamos en una consola, el entorno de applicación
		// será controlado por el helper CLI
		if ($this->cliMode){
			return;
		}
		
		// Se verificará si la aplicación no se encuetra en mantenimiento
		if ($this->applicationConfig->isMantenimiento()){
		    
		    if ($this->applicationConfig->isUserAllowed()){
		        
    			$this->_applicationRouter->deployAndBootstrap();
    			return;
    			
		    } else {
		        
    			echo OwlHtmlHelper::getHtmlMantenimientoPage();
    			die();
    			
		    }
		    
		}

        // Si el usuario tiene acceso se inicia el bootstrap
		$this->_applicationRouter->deployAndBootstrap();
		
	}

}

?>