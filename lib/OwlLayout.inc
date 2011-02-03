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
 * Helper que implementa cualquier layout de una aplicacion OWL-MVC
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
 

require_once 'OwlException.inc';
require_once 'OwlSession.inc';

class OwlLayout{
	
	/**
	 * Modo de maquetación
	 * @var string
	 */
	protected $mode = 'XHTML1STRICT';
	
	/**
	 * Modos disponibles de maquetaciíon
	 * @var array
	 */
	protected $modes = array();
	
	/**
	 * Nombre del archivo de layout
	 * @var string
	 */
	protected $layoutFile = null;
	
	/**
	 * Path al layout a utilizar
	 * @var string
	 */
	protected $layoutPath;
	
	/**
	 * Path al estilo del tema
	 * @var string
	 */
	protected $themeCssPath = null;
	
	/**
	 * Pila de slots
	 * @var array
	 */
	private $_slotStack = array();
	
	/**
	 * Array con los paths de los css a incluir
	 * @var array
	 */
	private $_resourcesStack = array();
	
	/**
	 * Título de página
	 * @var string
	 */
	private $_pageTitle = null;
	
	
	/**
	 * Establece los modos válidos de maquetacíon
	 * @return unknown_type
	 */
	protected function setModes(){
		
		$modos = array(
		
			// xhtml 1.1 a estricto
			'XHTML1STRICT',
		
			// html 5 (experimental)
			'HTML5',
		
		);
		
		$this->modes = $modos;
		
	}
	
	/**
	 * Establece los valores iniciales
	 * @return void
	 */
	public function __construct($layoutName = null){

		if(is_null($layoutName)){
			throw new OwlException('No se ha indicado un nombre de layout');
		}
		
		// Nombre del layout a utilizar
		$this->layoutFile = trim($layoutName);
		
		if (!$this->layoutFileExists()){
			throw new OwlException('El layout por defecto indicado no existe');
		} 
		
		// Se establecen los modos de maqetación
		$this->setModes();
		
		// Se inicializan los slots
		$this->initializeSlots();
		
	}
	
	/**
	 * Se inicializa el array con los slots por defecto
	 * @return void
	 */
	private function initializeSlots(){
		
		$this->_slotStack['contenido_principal'] = '';
		
	}
	
	/**
	 * Añade un slot a la pila
	 * @param string $slotName
	 * @return void
	 */
	private function addSlot( $slotName ){
		
		$this->_slotStack[$slotName] = '';
		
	}
	
	/**
	 * Procesa los módulos
	 * @param array $moduleStack
	 * @return void
	 */
	final public function processModules( $moduleStack ){
		
		foreach ($moduleStack as $module){

			$module->requestModule();
			
			ob_start();
			$module->runModule();
			
			$moduleContent = ob_get_clean();
			$moduleSlot = $module->getModuleSlot();
			
			if ($moduleSlot != ''){
				$this->addSlot($moduleSlot);
				$this->prepareContentForSlot($module->getModuleSlot(), $moduleContent);
			} else {
				throw new OwlException('Se ha procesado un módulo que no contiene slot designado.');
			}
			
			
				
		}
		
	}
	
	/**
	 * Guarda el contenido para un slot determinado
	 * @param string $slotName
	 * @param string $content
	 * @return void
	 */
	public function prepareContentForSlot($slotName, $content = ''){
		
		if (!array_key_exists($slotName, $this->_slotStack)){
			throw new OwlException('El slot indicado: <strong>' . $slotName . '</strong> no exíste.');
		}
		
		$this->_slotStack[$slotName] = $content;
		
	}
	
	/**
	 * Establece el modo de maquetación
	 * @param string $modo
	 * @return void
	 */
	public function setModoMaquetacion($modo){
		
		if (!in_array($modo, $this->modes)){
			throw new OwlException('El modo ' . $modo . ' no es un modo de maquetación válido. Modos válidos: ' . implode(',', $this->modes) . '.');
		}
		
		$this->mode = $modo;
		
	}
	
	/**
	 * Imprime el doctype seleccionado
	 * @return void
	 */
	public function echoDoctype(){
		
		switch ($this->mode){
			
			case 'XHTML1STRICT':
				echo '<?xml version="1.0" encoding="UTF-8" ?>' . "\n";
				echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">' . "\n";
				break;
				
			case 'HTML5':
				echo '<! DOCTYPE html>' . "\n";
				break;
			
		}
		
	}
	
	/**
	 * Verificará si existe el layout, de ser así establecerá el path hacia el
	 * @return boolean
	 */
	protected function layoutFileExists(){
		
		// Se contruye el path
		$layoutPath = LAYOUTDIR . $this->layoutFile . '.phtml';
		
		if (file_exists($layoutPath)){
			$this->layoutPath = $layoutPath;
			return true;
		}
		
		return false;
		
	}
	
	/**
	 * Incluye el archivo de layout y lo imprime
	 * @return void
	 */
	public function renderlayout(){
		
	    /** @TODO Implementar tidy **/ 
	    
	    /*ob_start();
		include $this->layoutPath;
		$codigo = ob_get_clean();
		
        $config = array(
            'indent' => true,
            'output-xhtml' => true,
            'wrap' => 200,
            'clean' => true,
            'doctype' => 'strict',
            'show-body-only' => false,
            'markup' => true,
            'tab-size' => 4,
            'vertical-space' => true,
            'new-inline-tags' => 'script',
        );
        
        $tidy = tidy_parse_string($codigo, $config, 'UTF8');
        $tidy->cleanRepair();
        echo $tidy;*/
	    
	    include $this->layoutPath;
		
	}
	
	/**
	 * Imprime el contenido de un slot
	 * @param string $slotName
	 * @return void
	 */
	public function hereSlot($slotName){
	    
		if(array_key_exists($slotName, $this->_slotStack)){
			echo $this->_slotStack[$slotName];
		}
		
	}
	
	/**
	 * Imprime los includes del css
	 * @return void
	 */
	public function echoCssIncludes(){

		if(array_key_exists('css', $this->_resourcesStack)){
			
			$cssResources = $this->_resourcesStack['css'];
			
			foreach ($cssResources as $cssPath) {
				
				echo '<link rel="stylesheet" type="text/css" href="' . $cssPath . '" />' . "\n";
				
			}
			
		}
		
		if ( !is_null($this->themeCssPath) ){
			echo '<link rel="stylesheet" type="text/css" href="' . $this->themeCssPath . '" />' . "\n";
		}
		
	}
	
	/**
	 * Imprime los includes del css
	 * @return void
	 */
	public function echoJavascriptIncludes(){
		
		if(array_key_exists('js', $this->_resourcesStack)){
			
			$jsResources = $this->_resourcesStack['js'];
			
			foreach ($jsResources as $jsPath) {
				
				echo '<script type="text/javascript" src="'. $jsPath .'"></script>' . "\n"; 
				
			}
			
		}		
		
	}
	
	
	/**
	 * Imprime contenido en el head
	 * @return void
	 */
	public function echoOnHead(){
		
		if(array_key_exists('plain', $this->_resourcesStack)){
			
			$plainResources = $this->_resourcesStack['plain'];
			
			foreach ($plainResources as $plainContent) {
				
				echo "$plainContent \n"; 
				
			}
			
		}		
		
	}
	
	/**
	 * Establece el array de recursos
	 * @param array $resources
	 * @return void
	 */
	public function setResources($resources){
		
		$this->_resourcesStack = $resources;
		
		// Se verificará el titulo de página
		if (array_key_exists('title', $this->_resourcesStack)){

			$this->_pageTitle = $this->_resourcesStack['title'];
			
		}
		
	}
	
	/**
	 * Imprime el tag title de página
	 * @return void
	 */
	public function echoPageTitle(){
	    
        $appConfig = $GLOBALS['OWL']['app_config'];
        $baseTitle = '';
        
        // Fallo grave, no se ha obtenido la configuración
        if ($appConfig instanceof OwlApplicationConfig){
		
            $baseTitle = $appConfig->getBaseTitle();
    		
        } 
        
        if (!is_null($this->_pageTitle)){
			
            $baseTitle .= ' - ' . $this->_pageTitle;
			
		}
		
		if (strlen($baseTitle) > 0){
            echo '<title>' . $baseTitle . '</title>' . "\n";
		}
		
	}
	
	/**
	 * 
	 * Imprime la descripcion de la applicación y
	 * las palabras claves de búsqueda
	 */
	public function echoDescriptionAndKeywords(){
		
		$appConfig = $GLOBALS['OWL']['app_config'];
		
		// Fallo grave, no se ha obtenido la configuración
		if ($appConfig instanceof OwlApplicationConfig){
			
			$description = $appConfig->getApplicationDescription();
			$keywords = $appConfig->getApplicationKeywords();
			
			// description
			if (!is_null($description)){
				$this->_echoMetaTag('description', $description);
			}
			
			// keywords
			if (!is_null($keywords)){
				$this->_echoMetaTag('keywords', $keywords);
			}
			
		}
		
	}
	
	/**
	 * Imprime un tag meta
	 * @param string $name
	 * @param string $content
	 */
	private function _echoMetaTag($name, $content){

		echo '<meta name="' . $name . '" content="' . $content . '" />' . "\n";
		
	}
	
	/**
	 * Intenta obtener la configuración de la aplicación
	 * desde globals, si lo logra la devuevle en un array, de lo contrario
	 * devuelve null.
	 * 
	 * @return array
	 */
	private function _getApplicationConfig(){
	    
	    if (array_key_exists('OWL', $GLOBALS) && array_key_exists('app_config', $GLOBALS['OWL']) && $GLOBALS['OWL']['app_config'] instanceof OwlApplicationConfig){
	        
	        return $GLOBALS['OWL']['app_config'];
	         
	    }
	    
	    return null;
	    
	}
	
	/**
	 * Imprime el log de base de datos si está diponible
	 */
	public function echoDatabaseLog(){
		    
	    // Obtendremos el log sql
	    if (array_key_exists('OWL', $GLOBALS) && array_key_exists('app_dblog', $GLOBALS['OWL']) && $appConfig = $this->_getApplicationConfig()){
	    	
	        // Comprobaremos que el debug está activado
	        if ($appConfig->getDebugFlag()){
	        
    	        echo '<div id="logSql">' . "\n";
                echo $GLOBALS['OWL']['app_dblog'];
                echo '</div>' . "\n";
                
	        }
            
	    } 
	    
	}
	
	/**
	 * Establece el archivo css del tema actual
	 * @param OwlTheme $tema
	 */
	public function setThemeCss( OwlTheme $tema ){
		
		$this->themeCssPath = $tema->getCssPath();
		
	}
	
	
}

?>