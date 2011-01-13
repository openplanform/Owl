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
 * Definición de clase que implementa el helper para sistemas de archivos
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


class OwlFileSystem{
	
	/**
	 * 
	 * Elimina uno o varios archivos, que correspondan
	 * con el patrón especificado en $path. 
	 * Devuelve la cantidad de archivos eliminados.
	 * 
	 * @param string $path
	 * @return integer
	 */
	public function rm($path){
		
		$puntero = 0;
		foreach (glob($path) as $filename){
			if (@unlink($filename)){
				$puntero++;
			}
		}
		
		return $puntero;
		
	}

	
	/**
	 * Devuelve el listado de archivos de un path específico
	 * @param string $path
	 */
	public function ls($path){
		
		$fileARR = array();
		foreach (glob($path) as $filename){
			array_push($fileARR, $filenamel);
		}
		
		return $fileARR;
		
	}
	
}

?>