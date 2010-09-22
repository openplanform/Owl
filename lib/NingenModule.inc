<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase que deberá implementar cualquier módulo compatible con NingenApplication
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class NingenModule{
	
	/**
	 * Nombre del slot donde debe 
	 * ser deplegado el módulo
	 * @var string
	 */
	protected $slot;
	
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
	 * @return NingenApplicationConfig
	 */
	protected function getApplicationConfig(){
		
		$applicationConfig = $GLOBALS['NINGEN_CMS']['app_config'];
		
		if ($applicationConfig instanceof NingenApplicationConfig){
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
	
}

?>