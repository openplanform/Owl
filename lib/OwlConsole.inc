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
 * Definición de clase que implementa el entorno de consola
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
 
require_once 'dbase/OwlConnection.inc';
require_once 'helper/OwlFileSystem.inc';


class OwlConsole{

	/**
	 * Referencia a la base de datos
	 * @var OwlConnection
	 */
	public $db;
	
	/**
	 * Configuración de la aplicación
	 * @var OwlApplicationConfig
	 */
	protected $appConfig;
	
	/**
	 * Helper para filesystem
	 * @var OwlFileSystem
	 */
	public $fileSystem;
	
	
	/**
	 * Instancia algunos objetos necesarios
	 */
	public function __construct(){
		
		$this->fileSystem = new OwlFileSystem();
		
	}
	
	
	/**
	 * Imprime una cadena en una línea
	 * @param string $cadena
	 */
	public function println($cadena){
		
		echo "$cadena \n";
		
	}
	
	
	/**
	 * Devuelve el argumento en la posición de clave
	 * @param string $clave
	 */
	public function getArg($clave){
		
		global $argv;
		
		if (array_key_exists($clave, $argv)){
			
			return $argv[$clave];
			
		}
		
		return null;
		
	}
	
	
	/**
	 * Devuelve el entorno de aplicación OWL
	 */
	public function getOwlEnvironment(){
		
		// Se instancia la aplicación
		require_once 'OwlApplication.inc';
		$application = new OwlApplication();
		
		// Se carga la configuración de la aplicacion
		$this->appConfig = $application->applicationConfig;
		
		// Se inica el entorno de applicacion
		$this->_loadOwlEnvironment($this->appConfig);
		
	}
	
	
	/**
	 * Carga el entorno de OWL
	 * @param OwlApplicationConfig $appConfig
	 */
	private function _loadOwlEnvironment(OwlApplicationConfig $appConfig){

		// Base de datos
		$dbConfig = $appConfig->getDatabaseConfiguration();
		$this->db = new OwlConnection($dbConfig);
		
	}
	
	
	/**
	 * Devuelve la configuración de la aplicación
	 * @return OwlApplicationConfig
	 */
	public function getApplicationConfig(){
		
		return $this->appConfig;
		
	}
	
}

?>