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
 * Helper con métodos de utilidad para la implementación de controladores
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlControllerHelper{
    
    /**
     * Intenta obtener un valor del request, 
     * de no conseguirlo devuelve null.
     * 
     * @param string $clave
     * @return mixed
     */
    public function get( $clave ){
        
        if (array_key_exists($clave, $_REQUEST) && $_REQUEST[$clave] != ''){

            if (!is_array($_REQUEST[$clave])){
                return trim($_REQUEST[$clave]);
            }
            
            return $_REQUEST[$clave];
            
        }
        
        return null;
        
    }
    
    /**
     * Escapa una cadena para su correcta inserción en 
     * la base de datos. También soporta arrays unidimensionales
     * 
     * @param mixed $cadena
     * @return string
     */
    public function escapeInjection( $cadena ){
        
        if (is_array($cadena)){
            
            $returnARR = array();
            
            foreach ($cadena as $strPart){
            	if (!is_array($strPart)){
                	$returnARR[] = mysql_real_escape_string(htmlspecialchars($strPart, ENT_QUOTES));
            	}
            }
            
            return $returnARR;
        }
        
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
                    $url .= '&amp;'.$key.'='.$value;
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