<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase que implementa un menu de navegación compatible con Owl
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once 'OwlModule.inc';
require_once 'OwlException.inc';

class OwlNavigation extends OwlModule{
	
	/**
	 * Configuración de la applicacion
	 * @var OwlApplicationConfig
	 */
	protected $applicationConfig;
	
	/**
	 * Configuración del menu
	 * @var stdClass
	 */
	protected $menuConfig;
	
	/**
	 * Nombre del controlador actual
	 * @var string
	 */
	protected $controllerName;
	
	/**
	 * Nombre de la acción actual
	 * @var unknown_type
	 */
	protected $actionName;
	
	/**
	 * Flag que indica si se deben canonizar los nombres
	 * @var boolean
	 */
	private $_canonizeNames = false;
	
	/**
	 * Controlador por defecto
	 * @var string
	 */
	private $_defaultController = null;
	
	/**
	 * Acción por defecto
	 * @var string
	 */
	private $_defaultAction = null;
	
	/**
	 * Flag que indica si se ha encontrado la opción activa
	 * @var boolean
	 */
	private $_activeFound = false;
	
	
	/**
	 * Obtiene la configuración del menu
	 * @return void
	 */
	public function initNavigation($nombreMenu){
		
		try {
			
			// Configuración general
			$this->applicationConfig = $GLOBALS['OWL']['app_config'];
			if (!$this->applicationConfig instanceof OwlApplicationConfig){
				throw new OwlException('No ha sido posible obtener la configuración de la aplicación para generar el menú.');
			}
			
			// Configuración de menu
			if (!$this->applicationConfig->hasNavigationMenu()){
				throw new OwlException('No se ha configurado un menu para la aplicación actual.');
			} 

			// Se obtiene la configuracion
			$this->menuConfig = $this->applicationConfig->getMenuConfig($nombreMenu);
			if (is_null($this->menuConfig)){
				throw new OwlException('El menu ' . $nombreMenu . ' no existe.');
			}
			
			// Se canonizarán los nombres?
			$this->_canonizeNames = $this->applicationConfig->isCanonizeNames();
			
			// Existe un root path?
			if (array_key_exists('root', $this->menuConfig)){
				
				$rootPath = explode('.', $this->menuConfig['root']);
				
				// Controlador->accion
				if (is_array($rootPath)){

					$this->_defaultController = $rootPath[0];
					$this->_defaultAction = $rootPath[1];
				
				} 
				
			}
			
			
		} catch (OwlException $e) {
			
			$e->echoCmsMessage();
			
		}
		
		
	}
	
	/**
	 * Verifica si el controlador y la acción actual 
	 * son los definidos por defecto, de ser así
	 * los marcará como actuales
	 * @return booelan
	 */
	private function verifyRootPath(){
		
		if (!is_null($this->_defaultController) && !is_null($this->_defaultAction)){
			
			$this->controllerName = $this->_defaultController;
			$this->actionName = $this->_defaultAction;
			
			return true;
			
		}
		
		return false;
		
	
	}
	
	/**
	 * Imprime el menú de navegación
	 * @return void
	 */
	protected function renderNavigation(){
		
		// Se vuelve a verificar la configuración
		if (!$this->applicationConfig instanceof OwlApplicationConfig){
			throw new OwlException('El menu no ha sido iniciado aún');
		}
		
		// Se obtienen los items de menu
		if (array_key_exists('add', $this->menuConfig)){
			$menuItems = $this->menuConfig['add'];
		} else {
			throw new OwlException('El menu dispone de entradas en la configuración');
		}
		
		// Cantidad de items
		$numMenuItems = count($menuItems);
		
		// Se obtiene las reescrituras 
		if (array_key_exists('rewrite', $this->menuConfig)){
			$menuRewrites = $this->menuConfig['rewrite'];
		}
		
		
		// Se inicia el menú
		$this->startMenu();
		
		// Contador de items iterados
		$i = 0;
		
		foreach ($menuItems as $controllerName => $itemLabel){
			
			// Clases para posiciones especiales
			if($i == 0){
				
				$addClass = 'first';
				
			} elseif($i == ($numMenuItems -1 )){
				
				$addClass = 'last';
				
			} else {
				
				$addClass = '';
				
			}
			
			// Se trata de una entrada compuesta (menu => accion)
			if (is_array($itemLabel)) {

				// Se iteran las opciones del subemnu
				foreach ($itemLabel as $actionName => $menuLabel){

					// Se imprime la opción de menu
					if ($controllerName == $this->controllerName && $actionName == $this->actionName ){
						
						$this->echoActiveItem($menuLabel, $this->prepareUri($controllerName, $actionName), $addClass, $i);
						$this->_activeFound = true;
						
					} else {
						
						$this->echoItem($menuLabel, $this->prepareUri($controllerName, $actionName), $addClass, $i);
						
					}
					
				}
				
			// Es una entrada simple solo controlador	
			} else {
				
				// Se imprime la opción de menu
				if ($controllerName == $this->controllerName){
				
					$this->echoActiveItem($itemLabel, $this->prepareUri($controllerName), $addClass, $i);
					$this->_activeFound = true;
					
				} else {
					
					$this->echoItem($itemLabel, $this->prepareUri($controllerName), $addClass, $i);
					
				}
				
			}
			
			$i++;			
			
		}
		
		// Se cierra el menú
		$this->endMenu();
		
	}
	
	/**
	 * Devuelve el codigo html obtenido al llamar a
	 * renderNavigation, util para cuando el módulo se ejecuta 
	 * desde el controlador
	 * @return unknown_type
	 */
	public function getNavigationHtml(){
	
		ob_start();
		$this->renderNavigation();
		
		if (!$this->_activeFound && $this->verifyRootPath()){
			ob_clean();
			$this->renderNavigation();
		}
		
		$retHtml = ob_get_clean();
		
		return $retHtml;
		
	}
	
	/**
	 * Establece el nombre del controlador actual
	 * @param string $controllerName
	 * @return void
	 */
	public function setControllerName($controllerName){
		
		$this->controllerName = $controllerName == '' ? 'index' : $controllerName;
		
	}
	
	/**
	 * Establece el nombre de la acción actual
	 * @param string $actionName
	 * @return void
	 */
	public function setActionName($actionName){
		
		$this->actionName = $actionName == '' ? 'index' : $actionName;
		
	}
	
	/**
	 * Código html que se imprimirá al iniciar el menu
	 * @return void
	 */
	protected function startMenu(){
		
		?><ul class="menu">
			<?
		
	}
	
	/**
	 * Código html que se imprimirá al finalizar el menu
	 * @return void
	 */
	protected function endMenu(){

		?></ul>
		<?
		
	}
	
	/**
	 * Imprime una opción de menu
	 * @param string $class
	 * @param string $label
	 * @param string $url
	 */
	protected function echoItem($label, $url, $class = '', $numItem){

		$classStr = $class == '' ? '' : ' class="' . $class .'" ';
		
		echo '<li' . $classStr . '><a href="' . $url . '">' . $label . '</a></li>' . "\n";
		
	}
	
	/**
	 * Imprime una opción de menu activa
	 * @param string $class
	 * @param string $label
	 * @param string $url
	 */
	protected function echoActiveItem($label, $url, $class = '', $numItem){

		echo '<li class="activo ' . $class . '"><a href="' . $url . '">' . $label . '</a></li>' . "\n";
		
	}
	
	/**
	 * Función que prepara la url a partir de un controlador
	 * y opcionalmente una accion
	 * @param string $controller
	 * @param string $action
	 * @return string
	 */
	protected function prepareUri($controller, $action = null){
		
		// Se verifica la canonización de nombres
		$fileExt = $this->_canonizeNames ? '' : '.html';
			
		// La acción por defecto siempre es index
		if (is_null($action)){
			
			$retStr = '/' . $controller . '/index' . $fileExt;
			
		} else {
			
			$retStr = '/' . $controller . '/' . $action . $fileExt; 
		
		}

		// Evitaremos /index/index.html
		if ($controller == 'index' && ($action == 'index' || $action == null)){
			
			$retStr = '/';
			
		}
		
		return $retStr;
		
	}
	
	public function runModule(){
       
	    echo $this->getNavigationHtml();
	    
	}
}

?>