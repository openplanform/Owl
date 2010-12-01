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
 * Clase que implementa el sistema de captcha compatible con OWL
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net>
 * @version 0.5.4
 * @since 0.3
 * 
 */


require_once 'container/OwlImage.inc';


class OwlCaptcha{

    /**
     * Palabra a generar
     * @var string
     */
    private $_palabra;
	
	/**
	 * Hash de la palabra en md5
	 * @var string
	 */
	private $_palabraHash;
	
	/**
	 * Objeto de imagen  
	 * @var XinaxImage
	 */
	private $_captchaSIMG;
	
	/**
	 * Ancho del captcha
	 * @var integer
	 */
	private $_ancho = 100;

	/**
	 * Alto del captcha
	 * @var integer
	 */
	private $_alto = 30;
	
	/**
	 * Cadena para añadir al hash
	 * @var string
	 */
	private $_codeString = 'never.knows.this';
		
    
    /**
     * Extrae una palabra del diccionario
     * si no logra hacerlo retorna false
     * @return string
     */
    private function _getPalabra() {
    
        //Se intenta abrir el archivo de diccionario
        if (!$filePointer = file(SHAREDIR . 'captcha/dict.es.txt', FILE_SKIP_EMPTY_LINES)) {
        	
            return false;
            
        } else {
        	
            $filelines = count($filePointer);
            
            //Aparentemente rand solo trabaja con integers
            if ($filelines > 32000) {
                $filelines = 32000;
            }
            
            $line = rand(1, $filelines);
            
            //Se crea la palabra
            if (array_key_exists($line, $filePointer)) {
            	
                $this->_palabra = trim(substr($filePointer[$line],0,8));
				$this->_palabraHash = md5($this->_palabra);
				
            } else {
            	
                return false;
                
            }
            
        }
        
    }
    
    
    /**
     * Devuelve la palabra en texto plano
     * @return string
     */
    public function getPalabraPlain(){
    	
    	return $this->_palabra;
    	
    }
    

	/**
	 * Contruye el objeto, si todo es correcto devuelve true
	 * @return boolean 
	 */
    public function init() {

		if (!$this->_getPalabra()){
			if ($this->_generaImagen()){
				return true;
			}
		}
		return false; 
    
    }
    
    
	/**
	 * Genera la imagen del captcha
	 * @return boolean 
	 */
    private function _generaImagen() {
    	
		$nombreArchivo = md5('NOIMG-' . $this->_palabra . '-NOIMG' );
    
		//Si el archivo ya existe no hacemos nada
		if (file_exists(PUBDIR . 'img/captcha/' . $nombreArchivo . '.png')){

			$this->_captchaSIMG = new OwlImage('/img/captcha/' . $nombreArchivo . '.png',  100, 30);	
			
			return true;
			
		} else {
			
	        //Se obtiene el fondo
	        $img = imagecreatefromgif(SHAREDIR . 'captcha/backs/'. rand(1, 5) .'.gif');
	        
	        //Algunos colorines
			$color = imagecolorallocate($img, 0, 0, 0);
			
	        //Algunas fuentes
	        $fuente = SHAREDIR .'captcha/fonts/'. rand(1, 3) .'.ttf';
	        
			//Texto
			$tamaño = 13;
			$angulo = rand(-3, 3);
			$left = 17;
			$bottom = 22;
			
			imagettftext($img, $tamaño, $angulo, $left, $bottom, $color, $fuente, $this->_palabra); 
			
	        //Se crea la imagen
			if (imagepng($img, SHAREDIR . 'captcha/images/' . $nombreArchivo . '.png')){
				
				$this->_captchaSIMG = new OwlImage('/img/captcha/' . $nombreArchivo . '.png',  100, 30);
				$this->_captchaSIMG->set_alt('Imagen de seguridad');
				
				return true;
					
			} else {
				
				return false;
				
			}
		}
        
    }
	
    
	/**
	 * Devuelve la cadena de hash
	 * Solo comprarar utilizando compare_palabra
	 * @return string
	 */
	public function get_hash_value(){
		
		return md5($this->_codeString . $this->_palabra . $this->_codeString);
		
	}	
	
	
	/**
	 * Compara la palabra introducida por el usuario con el hash generado
	 * @param string $palabra_usuario
	 * @return boolean
	 */
	public function compare_palabra($palabra_usuario, $hashValue){
		
		return md5($this->_codeString . trim($palabra_usuario) . $this->_codeString) == trim($hashValue);
		
	}
		
	
	/**
	 * Devuelve la imagen
	 * @return OwlImage
	 */
	public function getImg(){
		
		return $this->_captchaSIMG;
		
	}
	
	
	/**
	 * Establece el alto del capcha
	 * @param integer $alto
	 */
	public function setAlto($alto){
		$this->_alto = intval($alto);
	}
	
	
	/**
	 * Establece el ancho del capcha
	 * @param integer $ancho
	 */
	public function setAncho($ancho){
		$this->_ancho = intval($ancho);
	}
	
	
	/**
	 * Establece el valor de la cadena de seguridad
	 * @param string $codeString
	 */
	public function setCodeString($codeString){
		$this->_codeString = $codeString;		
	}
	
    
}

?>
