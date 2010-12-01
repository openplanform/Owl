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
 * Definicion de clase que implementa el helper de consola
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