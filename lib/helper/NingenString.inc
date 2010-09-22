<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase estática con funciones de utilidad para el manejo de cadenas  
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class NingenString{
	
    /**
     * Método que limita la longitud de un texto
     * al llegar a límite corta por el espacio entre palabras
     * @param string $cadena
     * @param integer $longitud
     * @return string
     */
    public static function limitaTexto($cadena,$longitud){
        
    	$cadenaARR = explode(' ', $cadena);
        $caracteres = strlen($cadena);
        if ($caracteres >= $longitud){
            $cadenaResult = '';
            foreach($cadenaARR as $palabra){
                if (strlen($cadenaResult) + strlen($palabra) >= $longitud){
                    return trim($cadenaResult) . '...';
                } else {
                    $cadenaResult .= $palabra . ' ';                    
                }
            }
        } else {
            return $cadena;
        }
        
    }
    
	/**
	 * Valida una dirección de mail
	 * @param string $pMail
	 * @return boolean
	 */
	public static function validaMail($pMail) {
		
		if (preg_match('/^[_a-zA-Z0-9-]+(\.[_a-zA-Z0-9-]+)*@{1}([_a-zA-Z0-9-]+\.)*[a-zA-Z0-9-]{2,200}\.[a-zA-Z]{2,6}$/', $pMail)) {
	       return true;
	    } else {
	       return false;
	    }
	    
	}     

    
	
}

?>
