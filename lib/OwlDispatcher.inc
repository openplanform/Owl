<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Dispatcher general de módulos, controladores y acciones
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 **/

require_once 'OwlLayout.inc';
require_once 'OwlView.inc';


class OwlDispatcher{
	
	/**
	 * Pila de módulos
	 * @var unknown_type
	 */
	//protected $moduleStack = null;
	
	/**
	 * Controlador actual
	 * @var OwlController
	 */
	protected $controller = null;
	
	/**
	 * Layout actual
	 * @var OwlLayout
	 */
	protected $layout = null;
	
	/**
	 * Vista actual
	 * @var OwlView
	 */
	protected $view = null;
	
	/**
	 * Nombre del controlador
	 * @var string
	 */
	protected $controllerName = null;
	
	/**
	 * Nombre de la acción
	 * @var string
	 */
	protected $actionName = null;
	
	/**
	 * Parámetros de la url
	 * @var array
	 */
	protected $urlParams = null;
	
	/**
	 * Contructora, establece los valores iniciales 
	 */
	public function __construct($controllerName, $actionName){
	
		$this->controllerName = $this->canonizeName($controllerName);
		$this->actionName = $this->canonizeName($actionName);
		
	}
	
	/**
	 * Método que canoniza los nombres de controladores y acciones
	 * TODOLIST #1
	 * @param string $name
	 * @return string
	 */
	protected function canonizeName($name){
	
		if (preg_match('/(.+)(\.html$|\.htm$)/', $name, $parts)) {
			return $parts[1];
		} else {
			return $name;
		}
		
	}
	
	
	/**
	 * Verificar la existencia de controlador y accion
	 * y los cargará de ser necesario
	 * @return boolean
	 */
	public function verifyRoute(){
		
		$controllerFetched = false;
		$actionFetched = false;
		
		// Se carga el controlador, aqui siempre llegará al menos "index"
		if (!is_null($this->controllerName)){
			$controllerFetched = $this->_loadController($this->controllerName);
		}
		
		// Igual que controller al menos será index
		if (!is_null($this->actionName)){
			$actionFetched = $this->_actionExists($this->actionName);
		}
		
		return $controllerFetched && $actionFetched;
		
	}
	
	
	/**
	 * Verifica si existe un controlador, si asi lo carga
	 * @param string $controllerName
	 * @return boolean
	 */
	private function _loadController($controllerName){
		
		// Se contruye el path hacia el controller (ejemploController.php)
		$fullControllerPath = CONTROLLERDIR . $controllerName . 'Controller.php';
		
		// Se verifica la existencia del script
		if (file_exists($fullControllerPath)){
			
			require_once $fullControllerPath;
			$controllerClassName = $controllerName . 'Controller';
			$this->controller = new $controllerClassName;
			
			return true;
			
		}
		
		return false;
		
	}
	
	/**
	 * Verifica si una acción determinada existe
	 * @param string $actionName
	 * @return boolean
	 */
	private function _actionExists($actionName){
		
		if ($this->controller instanceof OwlController){
			
			return method_exists($this->controller, $actionName . 'Action');
			
		}
		
		return false;
		
	}
	
	/**
	 * Establece los parámetros de la url
	 * @param array $params
	 */
	public function setParams( $params ){
	    
	    if (!is_null($params)){
    	    $this->urlParams = $params;
	    }
	    
	}
	
	/**
	 * Realiza el dispatch del controlador actual
	 * y la accion actual
	 * @param string $layoutName
	 * @return void
	 */
	public function dispatch($layoutName = null){
		
		// 1 - Se inicia el layout por defecto si ha sido pasado
		if (!is_null($layoutName)){
			
			$this->layout = new OwlLayout($layoutName);
			
		}
		
		// 2 - Se inicia la vista asociada a la acción actual
		$this->view = new OwlView($this->controllerName, $this->actionName);
		
		// Datos necesarios para el controlador
		$this->controller->setControllerName($this->controllerName);
		$this->controller->setActionName($this->actionName);
		
		// 3 - Se efectúa el predispatch
		$this->controller->preDispatch($this->layout, $this->view);
		
		// 4 - Se pasan los parámetros de la url al controlador
		$this->controller->setParams($this->urlParams);
		
		// 5 - Inicio del controlador
		$this->controller->initController();
		
		// 6 - Se renderiza la salida
		$this->controller->render($this->actionName);
		
	}
	
	
	
	
}