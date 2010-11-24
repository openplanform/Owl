<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase estática con funciones de utilidad para el manejo de fechas  
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Aaron Amengual Arranz <aaron@ningen.es>, Nicolás Daniel Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class OwlDate{
    
    /**
     * @see OwlDate::getDiaMesAno()
     * @param $fecha
     * @return string
     */
    public static function getDMA($fecha){
        
        return self::getDiaMesAno($fecha);
        
    }
    
    /**
     * Devuelve la fecha en formato DD/MM/AAAA, 
     * si la fecha pasada no es reconocible devuelve null
     * @param $fecha
     * @return string
     */
    public static function getDiaMesAno($fecha){
        
        $timestamp = strtotime($fecha);
        
        return date('d/m/Y', $timestamp);
        
    }
    
    /**
     * Convierte una fecha del formato europeo al formato americano (MySql)
     * @param string $fecha
     * @param string $sepOriginal
     * @param string $sepNuevo
     */
    public static function europeoAmericano($fecha, $sepOriginal = '/', $sepNuevo = '-'){
        
        list($anio, $mes, $dia) = explode($sepOriginal, $fecha);
    	$returnDate = $dia . $sepNuevo . $mes . $sepNuevo . $anio; 
        
        return $returnDate;
        
    }    
    
}

?>