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
    
    /**
     * Devuelve el valor de clave desde el request escapado, o un string vacío
     * en caso de no existir
     * 
     * @param $clave
     * @return string
     */
    public function getAndEscape( $clave ){
        
        return $this->escapeInjection($this->get($clave));
        
    }
    
    /**
     * Devuelve los parámetros del query como un string, los parámetros
     * enviados a $rewrites en forma de clave=>valor sobreescribirán a 
     * las claves que existan, de lo contrario se agregarán.
     * 
     * @param $rewrites
     * @return string
     */
    public function getQueryString($rewrites = null){
        
        $url = $_SERVER['REQUEST_URI'];
        
        $query = explode("&", $_SERVER['QUERY_STRING']);
        $params = false;
        
        if ( !empty($query[0]) ){
            $params = true;
        }
        
        // modify/delete data
        foreach($query as $q) {
            if (!empty($q)){
                list($key, $value) = explode("=", $q);
                if(array_key_exists($key, $rewrites)) {
                    if($rewrites[$key]) {
                        $url = preg_replace('-'.$key.'='.$value.'-', $key.'='.$rewrites[$key], $url);
                    } else {
                        $url = preg_replace('-&?'.$key.'='.$value.'-', '', $url);
                    }
                }
            }
            
        }
        
        // add new data
        foreach($rewrites as $key => $value) {
            if($value && !preg_match('-'.$key.'=-', $url)) {
                if ( $params ) {
                    $url .= '&'.$key.'='.$value;
                } else {
                    $url .= '?'.$key.'='.$value;
                    $params = true;
                }
            }
        }
        
        return $url;
        
    }
    
}


?>