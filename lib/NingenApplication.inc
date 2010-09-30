<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase que implementan las aplicaciones webs compatibles con NOWL
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once 'Zend/Config/Ini.php';

require_once 'NingenException.inc';
require_once 'NingenRouter.inc';
require_once 'NingenCmsSession.inc';
require_once 'container/NingenApplicationConfig.inc';
require_once 'helper/NingenCmsHtmlHelper.inc';


class NingenApplication{
	
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
	 * @var NingenRouter
	 */
	private $_applicationRouter;
	
	/**
	 * Contenedor que almacena la configuración de la
	 * aplicación
	 * @var NingenApplicationConfig
	 */
	public $applicationConfig;
	
	/**
	 * Interfaz de acceso a la session
	 * @var NingenCmsSession
	 */
	protected $ningenCmsSession;
	
	/**
	 * Reune la información necesaria para decidir si es posible 
	 * iniciar la aplicación 
	 * @return void
	 */
	public function __construct(){
		
		try{
			
			//Se establece el nivel de error
			$this->_setErrorLevel();
			
			// Se inicia la configuración de la aplicación
			$this->_loadApplicationConfig();
			
			// Se inicia el enrutador
			$this->_loadApplicationRouter();
			
			// Se inicia la aplicación
			$this->_initApplication();
			
		} catch (NingenException $e) {
			
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
		if (NINGENCMS_DEV){
			error_reporting(E_ALL);
		} else {
			error_reporting(!E_ALL);
		}		
		
	}
	
	/**
	 * Carga la configuración inicial de la aplicación 
	 * @return boolean
	 */
	private function _loadApplicationConfig(){
		
		
		// Se verifica desarrollo - producción
		$configSection = NINGENCMS_DEV ? 'develop' : 'production';
		
		// Opciones del config manager
		$opcionesConfigManager = array(
		
			// Set to TRUE to allow subsequent modification of loaded configuration data in-memory. Defaults to NULL
			'allowModifications' => NULL,
		
			// Set to the character to be used as the nest separator. Defaults to "." 
			'nestSeparator' => '.'
		
		);
		

		// Se instancia el manejador de configuración		
		$this->_configAdapter = new Zend_Config_Ini(NINGENCMS_CONFIGDIR . 'application.ini', $configSection, $opcionesConfigManager);
		
		// Se crea el contenedor público que mantendrá la configuración de la aplicación
		$this->applicationConfig = new NingenApplicationConfig($this->_configAdapter);
		
		// Se hace global la configuración
		$GLOBALS['NINGEN_CMS']['app_config'] = $this->applicationConfig;
		
	}
	
	
	/**
	 * Inicializa el router
	 * @return void
	 */	
	private function _loadApplicationRouter(){
		
		// Se inicializa el router
		$this->_applicationRouter = new NingenRouter($_SERVER['REQUEST_URI']);
		
		// Se le pasa la configuración al router
		$this->_applicationRouter->setApplicationConfig($this->applicationConfig);
		
	}
	
	/**
	 * Ordena a router iniciar el proceso de bootstrap
	 * @return void
	 */
	private function _initApplication(){
		
		// Se verificará si la aplicación no se encuetra en mantenimiento
		if ($this->applicationConfig->isMantenimiento()){
			echo NingenCmsHtmlHelper::getHtmlMantenimientoPage();
			die();	
		}
		
		// Si el usuario tiene acceso se inicia el bootstrap
		if ($this->applicationConfig->isUserAllowed()){
			$this->_applicationRouter->deployAndBootstrap();
		}
		
	}

}

?>