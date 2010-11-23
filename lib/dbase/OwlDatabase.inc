<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase estática con funciones de base de datos
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Aaron Amengual Arranz <aaron@ningen.es>, Nicolás Daniel Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class NingenDatabase{
    
    /**
     * Indexa un array de dataobjects por la columna pasada en campo.
     * $campo es el nombre de la columna tal y como aparece en la base de datos
     * @param mixed $campo
     * @param array $coleccionCOL
     * @return array
     */
    public static function indexFor($campo, $coleccionCOL){
        
        $returnARR = array();
        foreach ($coleccionCOL as $objetoDO){
            
            $nombreMetodo = 'get' . ucfirst($campo);
            $returnARR[$objetoDO->$nombreMetodo()] = $objetoDO;
            
        }
        
        return $returnARR;
        
    }
    
    /**
     * Agrupa dataobjects que
     * @param unknown_type $campo
     * @param unknown_type $coleccionCOL
     */
    public static function groupBy($campo, $coleccionCOL){

        $returnARR = array();
        foreach ($coleccionCOL as $objetoDO){
            
            $nombreMetodo = 'get' . ucfirst($campo);
            $returnARR[$objetoDO->$nombreMetodo()][] = $objetoDO;
            
        }
        
        return $returnARR;
        
    }
    
}

?>