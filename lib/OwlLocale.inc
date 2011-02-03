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
 * Clase que implementa el sistema de locale
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


class OwlLocale{

    /**
     * Iso del idioma actual
     * @var String
     */
    private $_langActual;
    
    /**
     * Isos de los idiomas disponibles
     * @var array
     */
    private $_idiomasARR;
    
    /**
     * Idioma por defecto de la aplicación
     * @var string
     */
    private $_defaultLang;
    
    /**
     * Array con el locale
     * @var array
     */
    private $_localeARR = null;
    
    /**
     * Identificador de la cookie de idioma
     * MD5 de la cadena "lang"
     * @var string
     */
    const COOKIE_LANG_ID = 'owl_7572559ca86e781ba8fe8073a0b725c6';
    
    /**
     * Tiempo de expiración de la cookie, 2 años
     * @var integer
     */
    const COOKIE_LANG_TIME = 63072000;
    

    /**
     * Constructora, inicializa el objeto 
     * y las opciones básicas.
     * @param OwlApplicationConfig $appConfig
     */
    public function __construct(OwlApplicationConfig $appConfig){

    	// Se obtienen los idiomas configurados para la aplicación
  		$this->_idiomasARR = $appConfig->getLangs();

  		// 1 - Idioma por defecto
  		$this->_langActual = $this->_defaultLang = $appConfig->getDefaultLang();
  		
  		// 2 - Si autolang se encuentra activo, se intentará obtener el idioma preferido del navegador
  		if ($appConfig->isAutolang() && $browserLang = $this->_detectBrowserLang()){
  			$this->_langActual = $browserLang;
  		}
  		
  		// 3 - Idioma elegido por el usuario
  		if ($userLang = $this->_detectUserLang()){
  			$this->_langActual = $userLang;
  		}
  		
  		// 4 - Cambio de idioma
  		if ($newLang = OwlSession::getValue('new_lang')){
  			
  			$this->_langActual = $newLang;
  			
  			// Se almacena en un cookie
  			$this->setUserLang($newLang);
  			
  			// Se borra de la sesión
  			OwlSession::destroyValue('new_lang');
  			
  		}
  		
  		// 5 - Se carga el locale (Sólo si se han definido idiomas para la aplicación)
  		if (!is_null($this->_idiomasARR)){
  			$this->_loadLocale();
  		}
  		
    }
    
   
    /**
     * Detecta y devuelve el idioma del navegador del usuario,
     * si no lo logra devuelve n ull
     * 
     * @return string
     */
    private function _detectBrowserLang(){
        
        if ($tmp = $_SERVER['HTTP_ACCEPT_LANGUAGE']){
            $detectedLang = substr($tmp, 0, 2);
            if ($this->_isLangAllowed($detectedLang)){
                return $detectedLang;
            }    
        } 

        return null;
        
    }
    
    
    /**
     * Detecta el idioma del usuario, si ha elegido alguno.
     * 
     * @return string
     */
    private function _detectUserLang(){
    	
    	if (array_key_exists(self::COOKIE_LANG_ID, $_COOKIE)){
    		
    		if ($this->_isLangAllowed($_COOKIE[self::COOKIE_LANG_ID])){
    			return $_COOKIE[self::COOKIE_LANG_ID];
    		}
    		
    	}
    	
    	return null;
    	
    }
    
    
    /**
     * Establece el nuevo idioma y lo almacena en una cookie
     * 
     * @param string $lang
     * @return boolean
     */
    public function setUserLang($lang){
    	
    	if (!$this->_isLangAllowed($lang)){
    		return false;
    	}
    	
    	$this->_langActual = $lang;
    	
    	return setcookie(self::COOKIE_LANG_ID, $lang, time() + self::COOKIE_LANG_TIME, '/');
    	
    }
    
    
    /**
     * Devuelve un booleano indicando si el idioma
     * está activo en el sitio
     * 
     * @param string $lang
     */
    private function _isLangAllowed($lang){
    	
    	if (is_null($this->_idiomasARR)){
    		return false;
    	}
    	
    	return in_array($lang, $this->_idiomasARR);
    	
    }
    
    /**
     * Devuelve el idioma actual
     * @return string
     */
    public function getLangActual(){
    	
    	return $this->_langActual;
    	
    }
    
    
    /**
     * Carga los archivos de locale necesarios
     * @throws OwlException
     */
    private function _loadLocale(){
    	
    	// Se carga $default_locale
    	include LIBDIR . 'locale/' . $this->_langActual . '.inc';
    	
    	if (!file_exists(LOCALEDIR . $this->_langActual . '.inc')){
    		throw new OwlException('No existe el archivo de locale para la aplicación en el idioma actual: <strong>' . $this->_langActual . '</strong>', 500);
    	}
    	
    	// Se carga el locale de aplicación ($locale)
    	include LOCALEDIR . $this->_langActual . '.inc';
    	
    	// Se mezclan los dos locales obtenidos
    	$this->_localeARR = array_merge($default_locale, $locale);
    	
    }
    
    
    /**
     * Devuelve el array completo de locale o si $clave es especificado
     * la sección correspondiente a dicha clave, si no la encuentra 
     * devuelve null
     * 
     * @param string $clave
     * @return array
     */
    public function getLocale($clave = null){
    	
    	// Se intentará retornar una sección
    	if (!is_null($clave)){

    		if (array_key_exists($clave, $this->_localeARR)){
	    		return $this->_localeARR[$clave];
    		} else {
    			return null;
    		}
    		
    	}
    	
    	// Se retorna el locale completo
    	return $this->_localeARR;
    }
    
   
    
    
}

?>