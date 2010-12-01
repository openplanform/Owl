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
 * Clase estática con métodos de utilidad para el tratamiento de arrays.
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @version 0.5.4
 * @since 0.3
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