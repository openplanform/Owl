<?php 

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase de datos para imágenes estátitas generadas por NOWL
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 **/


require_once 'NingenException.inc';
 
class NingenImage {

    /**
     * Nombre de la imagen ES
     * @var string
     */
    private $_nombre_es = null;
    
    /**
     * Nombre de la imagen CT
     * @var string
     */
    private $_nombre_ct = null;
    
    /**
     * Nombre de la imagen EN
     * @var string
     */
    private $_nombre_en = null;
    
    /**
     * Nombre de la imagen DE
     * @var string
     */
    private $_nombre_de = null;
    
    /**
     * Nombre de la imagen FR
     * @var string
     */
    private $_nombre_fr = null;
    
    /**
     * Código iso del idioma actual
     * @var string
     */
    private $_idioma = null;
    
    /**
     * Url del archivo
     * @var string
     */
    private $_url;
    
    /**
     * Ancho de la imagen
     * @var integer
     */
    private $_ancho;
    
    /**
     * Alto de la imagen
     * @var integer
     */
    private $_alto;
    
    /**
     * Flag de error
     * @var boolean
     */
    private $_isImage = false;
    
    /**
     * Atributo alt
     * @var string
     */
    private $_alt;
    
    /**
     * Atributo style
     * @var string
     */
    private $_style;
    
    /**
     * Returns $_alto.
     * @see statixImgX::$_alto
     */
    public function get_alto() {
        return $this->_alto;
    }
    
    /**
     * Sets $_alto.
     * @param object $_alto
     * @see statixImgX::$_alto
     */
    public function set_alto($_alto) {
        $this->_alto = $_alto;
    }
    
    /**
     * Returns $_ancho.
     * @see statixImgX::$_ancho
     */
    public function get_ancho() {
        return $this->_ancho;
    }
    
    /**
     * Sets $_ancho.
     * @param object $_ancho
     * @see statixImgX::$_ancho
     */
    public function set_ancho($_ancho) {
        $this->_ancho = $_ancho;
    }
    
    /**
     * Returns $_idioma.
     * @see statixImgX::$_idioma
     */
    public function get_idioma() {
        return $this->_idioma;
    }
    
    /**
     * Sets $_idioma.
     * @param object $_idioma
     * @see statixImgX::$_idioma
     */
    public function set_idioma($_idioma) {
        $this->_idioma = $_idioma;
    }
    
    /**
     * Returns $_nombre_ct.
     * @see statixImgX::$_nombre_ct
     */
    public function get_nombre_ct() {
        return $this->_nombre_ct;
    }
    
    /**
     * Sets $_nombre_ct.
     * @param object $_nombre_ct
     * @see statixImgX::$_nombre_ct
     */
    public function set_nombre_ct($_nombre_ct) {
        $this->_nombre_ct = $_nombre_ct;
    }
    
    /**
     * Returns $_nombre_de.
     * @see statixImgX::$_nombre_de
     */
    public function get_nombre_de() {
        return $this->_nombre_de;
    }
    
    /**
     * Sets $_nombre_de.
     * @param object $_nombre_de
     * @see statixImgX::$_nombre_de
     */
    public function set_nombre_de($_nombre_de) {
        $this->_nombre_de = $_nombre_de;
    }
    
    /**
     * Returns $_nombre_en.
     * @see statixImgX::$_nombre_en
     */
    public function get_nombre_en() {
        return $this->_nombre_en;
    }
    
    /**
     * Sets $_nombre_en.
     * @param object $_nombre_en
     * @see statixImgX::$_nombre_en
     */
    public function set_nombre_en($_nombre_en) {
        $this->_nombre_en = $_nombre_en;
    }
    
    /**
     * Returns $_nombre_es.
     * @see statixImgX::$_nombre_es
     */
    public function get_nombre_es() {
        return $this->_nombre_es;
    }
    
    /**
     * Sets $_nombre_es.
     * @param object $_nombre_es
     * @see statixImgX::$_nombre_es
     */
    public function set_nombre_es($_nombre_es) {
        $this->_nombre_es = $_nombre_es;
    }
    
    /**
     * Returns $_nombre_fr.
     * @see statixImgX::$_nombre_fr
     */
    public function get_nombre_fr() {
        return $this->_nombre_fr;
    }
    
    /**
     * Sets $_nombre_fr.
     * @param object $_nombre_fr
     * @see statixImgX::$_nombre_fr
     */
    public function set_nombre_fr($_nombre_fr) {
        $this->_nombre_fr = $_nombre_fr;
    }
    
    /**
     * Returns $_url.
     * @see statixImgX::$_url
     */
    public function get_url() {
        return $this->_url;
    }
    
    /**
     * Sets $_url.
     * @param object $_url
     * @see statixImgX::$_url
     */
    public function set_url($_url) {
        $this->_url = $_url;
    }

    
    /**
     * Returns $_alt.
     * @see staticImgX::$_alt
     */
    public function get_alt() {
        return $this->_alt;
    }
    
    /**
     * Sets $_alt.
     * @param object $_alt
     * @see staticImgX::$_alt
     */
    public function set_alt($_alt) {
        $this->_alt = $_alt;
    }
    
    /**
     * Returns $_style.
     * @see staticImgX::$_style
     */
    public function get_style() {
        return $this->_style;
    }
    
    /**
     * Sets $_style.
     * @param object $_style
     * @see staticImgX::$_style
     */
    public function set_style($_style) {
        $this->_style = $_style;
    }
    
    /**
     * Devuelve el campo multilang nombre
     * @return string
     */
    public function getNombre() {
    
        if (is_null($this->_idioma)) {
            //Si no se ha especificado el idioma se utiliza el por defecto
            $this->_idioma = DEFAULT_LANG;
        }
        
        return call_user_func('get_nombre_'.$this->_idioma);
        
    }
    
	/**
	 * Contructora, crea el objeto a partir de los parametros
	 * @param string $url [optional]
	 * @param integer $ancho [optional]
	 * @param integer $alto [optional]
	 * @return boolean
	 */
    public function NingenImage($url = null, $ancho = null, $alto = null) {
    
        $this->_url = $url;
        $this->_ancho = $ancho;
        $this->_alto = $alto;
        
        //Comprobamos los parámetros
        if (is_null($url) || is_null($ancho) || is_null($alto)) {
            throw new NingenException('El objeto staticImg no está recibiendo todos los parámetros necesarios.');
			return false;
        }
        
		$this->_isImage = true;
		
		return true;
    }
	
	/**
	 * Devuelve el valor de _isImage
	 * @return boolean
	 */
	public function isImage(){
		return $this->_isImage;
	}
	
    /**
     * Imprime el tag img
     * @return boolean
     */
    public function echoImg() {
    	
		if ($this->_isImage){
	    	$styleText = $altText = '';
		
			if ($this->_alt != ''){
				$altText = 'alt="' . $this->_alt . '" ';
			}
			
			if ($this->_style != ''){
				$styleText = 'style="' . $this->_style . '" ';
			}
		
			echo '<img src="' . $this->_url . '" width="' . $this->_ancho . '" height="' . $this->_alto . '" ' . $styleText . $altText . '/>' . "\n";
		} else {
			return false;
		}
	
    }

    
}

?>
