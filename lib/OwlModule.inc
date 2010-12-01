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
 * Clase que deberá implementar cualquier módulo compatible con OwlApplication
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