<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Dispatcher general de módulos, controladores y acciones
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 **/

require_once 'NingenLayout.inc';
require_once 'NingenView.inc';


class NingenDispatcher{
	
	/**
	 * Pila de módulos
	 * @var unknown_type
	 */
	//protected $moduleStack = null;
	
	/**
	 * Controlador actual
	 * @var NingenController
	 */
	protected $controller = null;
	
	/**
	 * Layout actual
	 * @var NingenLayout
	 */
	protected $layout = null;
	
	/**
	 * Vista actual
	 * @var NingenView
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
		$fullControllerPath = NINGENCMS_CONTROLLERDIR . $controllerName . 'Controller.php';
		
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
		
		if ($this->controller instanceof NingenController){
			
			return method_exists($this->controller, $actionName . 'Action');
			
		}
		
		return false;
		
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
			
			$this->layout = new NingenLayout($layoutName);
			
		}
		
		// 2 - Se inicia la vista asociada a la acción actual
		$this->view = new NingenView($this->controllerName, $this->actionName);
		
		// Datos necesarios para el controlador
		$this->controller->setControllerName($this->controllerName);
		$this->controller->setActionName($this->actionName);
		
		// 3 - Se efectúa el predispatch
		$this->controller->preDispatch($this->layout, $this->view);
		
		// 4 - Inicio del controlador
		$this->controller->initController();
		
		// 5 - Se renderiza la salida
		$this->controller->render($this->actionName);
		
	}
	
	
	
	
}