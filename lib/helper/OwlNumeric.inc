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
 * Helper con métodos de utilidad para la implementación de controladores.
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

class OwlNumeric{
    
	/**
     * Controla que la cantidad introducida tenga el formato europeo
     * @param string $subject
     * @return boolean
     */
    public static function currencyEuro( $cantidad ){
        
        if ( !empty($cantidad) && preg_match('/^[0-9.]*,?[0-9]{0,2}$/', $cantidad)) {
            return true;
        } else {
            return false;
        }
        
    } 
    
    /**
     * Convierte una cantidad de formato europeo 
     * a formato decimal para la base de datos.
     * La coma de la cantidad debe separar los decimales
     * 678.433.545,00 => 678433545.00
     * 678.433.545 => 678433545.00 
     * @param string $cantidad
     * @param integer $decimales
     * @return string 
     */
    public static function formatoEuropeoDecimal( $cantidad, $decimales ){
    	
    	$arrCantidad = explode(',', $cantidad);
    	
    	// Parte entera
    	$parteEntera = str_replace('.', '', $arrCantidad[0]);
    	
    	// Parte decimal
    	if ( isset($arrCantidad[1]) ){
    		$cantidad = $parteEntera . '.' . $arrCantidad[1];
    	} else {
    		$cantidad = $parteEntera;
    	}
    	
    	$cantidad = number_format($cantidad,$decimales,'.','');
    	
    	return $cantidad;
    }
    
	/**
     * Convierte una cantidad de formato decimal
     * a formato europeo.
     * La coma de la cantidad debe separar los decimales
     * 67843354523.00 => 678.433.545,00
     * 678433545.23 => 678.433.545,23
     * @param string $cantidad
     * @param integer $decimales
     * @return string $cantidad
     */
    public static function decimalFormatoEuropeo( $cantidad, $decimales ){
    	
    	$arrCantidad = explode('.', $cantidad);
    	
    	// Parte entera
    	$parteEntera = str_replace('.', '', $arrCantidad[0]);
    	
    	// Parte decimal
    	if ( isset($arrCantidad[1]) ){
    		$cantidad = $parteEntera . '.' . $arrCantidad[1];
    	} else {
    		$cantidad = $parteEntera;
    	}
    	
    	$cantidad = number_format($cantidad,$decimales,',','.');
    	
    	return $cantidad;
    	
    }
    
}


?>