<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase que implementa la vista de una aplicación MVC
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 **/

class NingenView{
	
	/**
	 * Nombre del controlador
	 * @var string
	 */
	public $controllerName;
	
	/**
	 * Nombre de la acción
	 * @var string
	 */
	public $actionName;
	
	/**
	 * Pila de variables
	 * @var array
	 */
	private $__varStack = array();
	
	/**
	 * Buffer con el contenido 
	 * @var string
	 */
	private $__buffer;
	
	/**
	 * Path hacia el archivo de vista a incluir
	 * @var string
	 */
	private $_viewPath = null;
	
	/**
	 * Array con los recursos
	 * @var array
	 */
	private $_resources = array();
	
    /**
     * Flag que indica si se debe ignorar la vista
     * @var boolean
     */
	private $_bypass = false;
	
	/**
	 * Constructora, globaliza datos de la vista 
	 * @param string $controllerName
	 * @param string $actionName
	 * @return void
	 */
	public function __construct($controllerName, $actionName){
		
		$this->controllerName = $controllerName;
		$this->actionName = $actionName;
		
		// Se genera el path
		$this->generateViewPath();
		
		/*if (!$this->viewExist()){
			throw new NingenException('No se ha encontrado la vista para la acción <strong>' . $this->actionName . '</strong> en el controlador <strong>' . $this->controllerName . '</strong>');
		}*/
		
	}
	
	/**
	 * Verifica la existencia de una vista, si es así 
	 * popula el path en el objeto
	 * @return boolean
	 */
	private function generateViewPath(){
		
		$viewPath = NINGENCMS_VIEWDIR . $this->controllerName . '/' . $this->actionName . '.phtml';
		
		if (file_exists($viewPath)){
			$this->_viewPath = $viewPath;
			return true;
		}
		
		return false;
		
	}
	
	/**
	 * Devuelve un valor de la pila
	 * @param string $varName
	 * @return mixed
	 */
	public function __get($varName){
		
		if (array_key_exists($varName, $this->__varStack)){
			return $this->__varStack[$varName];
		}
		
		return null;
		
	}
	
	/**
	 * Establece un valor en la pila
	 * @param string $varName
	 * @param mixed $value
	 * @return void
	 */
	public function __set($varName, $value){
		
		$this->__varStack[$varName] = $value;
		
	}
	
	/**
	 * Devuelve el buffer, si hay una vista cargada,
	 * de lo contrario, devuelve null
	 * @return string
	 */
	public function getBuffer(){
		
		if (!is_null($this->_viewPath)){
		
			ob_start();
			include $this->_viewPath;

			return ob_get_clean();
			
		}
		
		return null;
		
	}
	
	/**
	 * Todo lo que aqui se imprima estará en los tags head
	 * @param string $content
	 * @return void
	 */
	public function echoOnHead($content){
		
		$this->_resources['plain'][] = $content;
		
	}
	
	/**
	 * Agrega un include css
	 * @param string $cssIncludePath
	 * @return void
	 */
	public function addCssInclude($cssFilePath){
		
		$this->_resources['css'][] = $cssFilePath;
		
	}
	
	/**
	 * Agrega un include de javascript
	 * @param string $jsFilePath
	 * @return void
	 */
	public function addJavascriptInclude($jsFilePath){
		
		$this->_resources['js'][] = $jsFilePath;
		
	}
	
	/**
	 * Devuelve el array de recursos
	 * @return array
	 */
	public function getResources(){
		
		return $this->_resources;
		
	}
	
	/**
	 * Establece el titulo de la página. Si hay un basetitle
	 * definido en application.ini, el título pasado a éste método
	 * será añadido al título base.
	 * 
	 * @param string $title
	 * @return void
	 */
	public function addTitle( $title ){
		
		$this->_resources['title'] = trim($title);
		
	}
	
	/**
	 * Establece el título de la página
	 * @deprecated utilizar addTitle en su lugar
	 */
	public function setPageTitle($title){
	    
	    $this->addTitle($title);
	    
	}
	
	/**
	 * Realiza un bypass de la vista actual
	 */
	public function bypassView(){
	    
	    $this->_bypass = true;
	    
	}

}

?>