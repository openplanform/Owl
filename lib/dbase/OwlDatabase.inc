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
 * Clase estática con funciones de base de datos.
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

class OwlDatabase{
    
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
     * @param string $campo
     * @param array $coleccionCOL
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