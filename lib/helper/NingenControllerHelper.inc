<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Helper con métodos de utilidad para la implementación de controladores
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Aaron Amengual Arranz <aaron@ningen.es>, Nicolás Palumbo <nico@ningen.es>   
 * @version 0.5
 * @since 0.5
 * 
 **/


class NingenControllerHelper{
    
    /**
     * Intenta obtener un valor del request, 
     * de no conseguirlo devuelve null.
     * 
     * @param string $clave
     * @return mixed
     */
    public function get( $clave ){
        
        if (array_key_exists($clave, $_REQUEST) && $_REQUEST[$clave] != ''){
            
            return trim($_REQUEST[$clave]);
            
        }
        
        return null;
        
    }
    
    /**
     * Escapa una cadena para su correcta inserción en 
     * la base de datos.
     * 
     * @param string $cadena
     * @return string
     */
    public function escapeInjection( $cadena ){
        
        return mysql_real_escape_string(htmlspecialchars($cadena, ENT_QUOTES));        
        
    }
    
}


?>