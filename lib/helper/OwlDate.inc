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
 * Clase estática con funciones de utilidad para el manejo de fechas.
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @version 0.5.4
 * @since 0.3
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
     * Convierte una fecha del formato europeo al formato americano (MySql). 
     * Si se produce algún error durante la conversión, devuelve null. 
     * @param string $fecha
     * @param string $sepOriginal
     * @param string $sepNuevo
     */
    public static function europeoAmericano($fecha, $sepOriginal = '/', $sepNuevo = '-'){

    	$fechaARR = explode($sepOriginal, $fecha);
    	
    	// Si la fecha está mal formada (o no es una fecha), se devolverá null, evitando el error resultante
    	if (is_array($fechaARR) && count($fechaARR) == 3){
    	
	        list($anio, $mes, $dia) = $fechaARR;
	    	$returnDate = $dia . $sepNuevo . $mes . $sepNuevo . $anio; 
	        
	        return $returnDate;
	        
    	}
    	
    	return null;
        
    }    
    

    /**
     * Devuelve un array con un item por cada día comprendido desde
     * y hasta. Indexado por clave autoincrementada.
     * Este método no comprueba la validez del formato de fecha,
     * que deberá ser YYYY-m-d.
     * 
     * @param date $strDateFrom
     * @param date $strDateTo
     */
	public static function createDateRangeArray($desde, $hasta) {
		
		$aryRange=array();
		
		$iDateFrom=mktime(1,0,0,substr($strDateFrom,5,2),     substr($strDateFrom,8,2),substr($strDateFrom,0,4));
		$iDateTo=mktime(1,0,0,substr($strDateTo,5,2),     substr($strDateTo,8,2),substr($strDateTo,0,4));
		
		if ($iDateTo>=$iDateFrom) {
			array_push($aryRange,date('Y-m-d',$iDateFrom)); // first entry
		
			while ($iDateFrom<$iDateTo) {
				$iDateFrom+=86400; // add 24 hours
				array_push($aryRange,date('Y-m-d',$iDateFrom));
			}
		}
		  
		return $aryRange;
	  
	}       
	
    
}

?>