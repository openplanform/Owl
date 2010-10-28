<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase estática con funciones de utilidad para el manejo de fechas  
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Aaron Amengual Arranz <aaron@ningen.es>, Nicolás Daniel Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class NingenDate{
    
    /**
     * @see NingenDate::getDiaMesAno()
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
    public function getDiaMesAno($fecha){
        
        $timestamp = strtotime($fecha);
        
        return date('d/m/Y', $timestamp);
        
    }
    
    /**
     * Convierte una fecha del formato europeo al formato americano (MySql)
     * @param string $fecha
     * @param string $sepOriginal
     * @param string $sepNuevo
     */
    public function europeoAmericano($fecha, $sepOriginal = '/', $sepNuevo = '-'){
        
        preg_match('([0-9]{1,2})' . $sepOriginal . '([0-9]{1,2})' . $sepOriginal . '([0-9]{2,4})', $fecha, $partes);
        $returnDate = $partes[3] . $sepNuevo . $partes[2] . $sepNuevo . $partes[1];
        
        return $returnDate;
        
    }    
    
}

?>