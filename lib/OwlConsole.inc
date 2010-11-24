<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Definicion de clase que implementa el helper de consola
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 **/

class OwlConsole{
	
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
		
		if (array_key_exists($clave, $argv)){
			
			return $argv[$clave];
			
		}
		
		return null;
		
	}
	
}

?>