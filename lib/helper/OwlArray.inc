<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase estática con métodos de utilidad para el tratamiento de arrays
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class OwlArray{
    
    /**
     * Castea un array a objeto, si se trata de un array
     * multidimensional es conveniente utilizar createObjectFromArray,
     * lo contrario las propiedades de más de un nivel segirán siendo arrays
     * @param unknown_type $vector
     */
    static public function castArrayToObject($vector){
        
        return (object) $vector;
        
    }
    
    /**
     * Genera un objeto recursivamente a partir del array $vector, 
     * @param array $vector
     * @return object
     */
    static public function createObjectFromArray($vector){
        
        if(!is_array($vector)) {
            return $vector;
        }
        $object = new stdClass();
        if (is_array($vector) && count($vector) > 0) {
          foreach ($vector as $name=>$value) {
             $name = strtolower(trim($name));
             if (!empty($name)) {
                $object->$name = self::createObjectFromArray($value);
             }
          }
          return $object;
        }
        else {
          return false;
        }
    }
    
}

?>