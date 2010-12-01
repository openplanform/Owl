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
 * Clase estática con funciones de utilidad para el manejo de cadenas.
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlString{
	
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
	
	
	/**
	 * Genera un password aleatorio
	 * @param integer $longitud
	 * @param boolean $mayusculas
	 */
	public static function generaPassword($longitud, $mayusculas = true){

        $str = 'abcdefghijkmnopqrstuvwxyz234567890';
        
        if ($mayusculas){
            $str .= 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
        }
        
        $cad = str_shuffle($str);
        $cad = substr($cad, 0, $longitud);
        
        return $cad;
	    
	}

	
	/**
	 * Escapa una cadena que ha sido obtenida desde un editor rtf TinyMCE
	 * @param string $cadena
	 * @return string $texto
	 */
	public static function escapeFromMceditor($cadena){
		
		// Tags permitidos
		$allowedTags='<p><strong><em><u><h1><h2><h3><h4><h5><h6><img><a>';
 		$allowedTags.='<li><ol><ul><span><div><br><ins><del>';
		
 		$texto = strip_tags(stripslashes($cadena),$allowedTags);
 		
 		return $texto;
		
	}
    
	
}

?>
