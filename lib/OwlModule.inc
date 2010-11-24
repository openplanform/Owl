<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase que deberá implementar cualquier módulo compatible con OwlApplication
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class OwlModule{
	
	/**
	 * Nombre del slot donde debe 
	 * ser deplegado el módulo
	 * @var string
	 */
	protected $slot;
	
	/**
	 * Nombre de la acción actual
	 * @var string
	 */
	protected $actionName;
	
	/**
	 * Nombre del controlador actual
	 * @var string
	 */
	protected $controllerName;
	
	
	/**
	 * Constructora, establece el nombre slot donde será deplegado el modulo
	 * @param string $nombreSlot
	 * @return void
	 */
	public function __construct( $nombreSlot ){
		
		$this->slot = $nombreSlot;
		
	}
	
	public function requestModule(){
		
	}
	
	public function runModule(){
		
	}
	
	/**
	 * Devuelve la configuración de la aplicación
	 * @return OwlApplicationConfig
	 */
	protected function getApplicationConfig(){
		
		$applicationConfig = $GLOBALS['OWL']['app_config'];
		
		if ($applicationConfig instanceof OwlApplicationConfig){
			return $applicationConfig;
		}
		
		return null;
		
	}
	
	/**
	 * Devuelve el nombre del slot donde sera desplegado el modulo
	 * @return unknown_type
	 */
	public function getModuleSlot(){
		
		return $this->slot;
		
	}
	
	/**
	 * Establece el nombre del controlador actual
	 * @param string $controllerName
	 */
	public function setController($controllerName){
		
		$this->controllerName = $controllerName;
		
	}
	
	/**
	 * Establece el nombre de la acción actual
	 * @param string $actionName
	 */
	public function setAction($actionName){
		
		$this->actionName = $actionName;
		
	}
	
}

?>