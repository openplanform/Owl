<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 *
 * Clase que implementa el sistema de locale
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

class NingenLocaleManager{

    /**
     * Iso del idioma actual
     * @var String
     */
    private $_langActual;
    
    /**
     * Isos de los idiomas disponibles
     * @var array
     */
    private $_idiomas;
    
    /**
     * Path hacia el directorio de locales
     * @var string
     */
    private $_localePath = 'locale/';
    
    /**
     * Iso del idioma por defecto
     * @var string
     */
    private $_langDefecto = 'es';
    
    /**
     * Hash con el locale 
     * @var array
     */
    private $_localeArray = null;
    
    /**
     * Hash con la metadata del locale actual
     * @var array
     */
    private $_metadataArray = null;
    
    /**
     * Constructora, inicializa el objeto 
     * y las opciones básicas.
     */
    public function __construct( $lang = '' ){
        
        $this->_setIdiomasDisponibles();
        
        $this->_setLang($lang);
        
        $this->_loadLocale();
        
    }
    
    /**
     * Establece los idiomas en los que estará disponible 
     * el gestor de locale.
     */
    private function _setIdiomasDisponibles(){
        
        $this->_idiomas = array( 'es', 'ca', 'en', 'de');
        
    }
    
    /**
     * Establece el idioma actual
     * @param unknown_type $lang
     */
    private function _setLang($lang){
        
        if ($lang != ''){
            if (in_array($lang, $this->_idiomas)){
                $this->_langActual = $lang;
            } else {
                throw new Exception('El idioma sugerido no se encuentra disponible');
            }
        } else {
            $this->_langActual = $this->_langDefecto;
        }        
        
    }
    
    /**
     * Carga el hash de locale
     * y la metadata del mismo
     */
    private function _loadLocale(){
        
        $fileTarget = $this->_localePath . $this->_langActual . '.inc';
        
        if (file_exists($fileTarget)){
            include $fileTarget;
        } else {
            throw new Exception('No se ha encontrado el archivo de locale: ' . $fileTarget);
        }
        
        $this->_metadataArray = $metadata;
        $this->_localeArray = $locale;
        
    }
    
    /**
     * Extrae un valor del locale, ya sea una clave, un subgrupo o 
     * una sub clave o false en caso de error
     * @param string $key
     * @return string
     */
    private function _extractFromLocale($key){
        
        //Se busca la clave en el primer nivel
        if (array_key_exists($key, $this->_localeArray)){
            return $this->_localeArray[$key];
        }
        
        //Se busca en los subgrupos, segundo nivel
        //no se buscara en niveles de mas profundidad
        foreach($this->_localeArray as $clave => $valor){
            if (is_array($valor)){
                foreach($valor as $subclave => $subvalor){
                    if ($subclave == $key){
                        return $subvalor;
                    }
                }
            }
        }
        
        //no se ha encontrado la clave
        return null;
        
    }
    
    /**
     * Detecta el idioma del navegador del usuario,
     * si todo va bien lo establece como el idioma actual
     * de lo contrario devuelve false
     * @return boolean
     */
    public function detectLang(){
        
        if ($tmp = $_SERVER['HTTP_ACCEPT_LANGUAGE']){
            $detectedLang = substr($tmp, 0, 2);
            if (in_array($detectedLang, $this->_idiomas)){
                
                $this->_langActual = $detectedLang;
                $this->_loadLocale();
                
                return true;
            }    
        } 

        return false;
        
    }
    
    
    /**
     * Devuelve el locale si $key no es enviado, de lo contrario se buscará
     * $key en el locale y se devolverá su valor.
     * @param string $key
     * @return mixed
     */
    public function get($key = ''){

        //Se obtiene todo el locale
        if ($key == '' && !is_null($this->_localeArray)){
            return $this->_localeArray;
        } else {
        //Se busca la clave indicada
            return $this->_extractFromLocale($key); 
        }
        
        return null;
        
    }
    
    /**
     * Establece un nuevo idioma y vuelve a cargar el locale
     * @param string $lang
     */
    public function setLangAndReloadLocale($lang){
        
        $this->_setLang($lang);
        $this->_loadLocale();
        
    }
    
    
    /**
     * Devuelve el hash de metadatos del actual locale
     * @param $key
     * @return mixed
     */
    public function getMetadata($key = ''){

        //No hay metadata
        if (is_null($this->_metadataArray)){
            return null;
        }
        
        //Una clave en particular
        if ($key != '' && array_key_exists($key, $this->_metadataArray)){
            return $this->_metadataArray[$key];
        } 
        
        //Todo el hash de metadatos
        return $this->_metadataArray; 
        
    }
    
    /**
     * Devuelve el locale como un objeto, null en caso que
     * no consiga lograrlo
     * @experimental 
     * @return object
     */
    public function getLocaleObject(){
        
        //Sin datos se devuelve null
        if (is_null($this->_localeArray)){
            return null;
        }
        
        require_once 'helper/NingenArray.inc';
        return NingenArrayHelper::createObjectFromArray($this->_localeArray);
        
    }
    
    
}

?>