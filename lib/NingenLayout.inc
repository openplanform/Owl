<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Helper que implementa cualquier layout de una aplicacion MVC
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

class NingenLayout{
	
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
			throw new NingenException('No se ha indicado un nombre de layout');
		}
		
		// Nombre del layout a utilizar
		$this->layoutFile = trim($layoutName);
		
		if (!$this->layoutFileExists()){
			throw new NingenException('El layout por defecto indicado no existe');
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
	public function processModules( $moduleStack ){
		
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
				throw new NingenException('Se ha procesado un módulo que no contiene slot designado.');
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
			throw new NingenException('El slot indicado: <strong>' . $slotName . '</strong> no exíste.');
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
			throw new NingenException('El modo ' . $modo . ' no es un modo de maquetación válido. Modos válidos: ' . implode(',', $this->modes) . '.');
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
		$layoutPath = NINGENCMS_LAYOUTDIR . $this->layoutFile . '.phtml';
		
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
		
		if (!is_null($this->_pageTitle)){
			
			echo '<title>' . $this->_resourcesStack['title'] . '</title>' . "\n";
			
		}
		
	}
	
	/**
	 * 
	 * Imprime la descripcion de la applicación y
	 * las palabras claves de búsqueda
	 */
	public function echoDescriptionAndKeywords(){
		
		$appConfig = $GLOBALS['NINGEN_CMS']['app_config'];
		
		// Fallo grave, no se ha obtenido la configuración
		if ($appConfig instanceof NingenApplicationConfig){
			
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
	
}

?>