<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Controlador genérico, todos los controladores deben heredar de esta clase
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
require_once 'dbase/NingenConnection.inc';
require_once 'helper/NingenControllerHelper.inc';


class NingenController{
	
	/**
	 * Layout asignado al controlador
	 * @var NingenLayout
	 */
	protected $layout = null;
	
	/**
	 * Vista asignada al controlador
	 * @var NingenView
	 */
	protected $view = null;
	
	/**
	 * Pila de modulos
	 * @var array
	 */
	protected $moduleStack = array();
	
	/**
	 * Slot donde se renderizará la acción
	 * @var string
	 */
	protected $defaultSlot = 'contenido_principal';
	
	/**
	 * Nombre del controlador actual 
	 * @var string
	 */
	protected $controllerName;
	
	/**
	 * Nombre de la acción actual
	 * @var string
	 */
	protected $actionName;
	
	/**
	 * Objeto de referencia a la conexion
	 * de base de datos
	 * @var NingenConnection
	 */
	protected $db;
	
	/**
	 * Nombre de layout alternativo
	 * @var string
	 */
	protected $alternateLayout = null;
	
	/**
	 * Helper para controladores
	 * @var NingenControllerHelper
	 */
	protected $helper;
	
	/**
	 * Constructor, instancia algunos objetos necesarios 
	 */
	public function __construct(){
	    
	    // Se inicia la conexión a la base de datos
        $this->_initDatabase();
	    
	    // Helper para controladores
	    $this->helper = new NingenControllerHelper();
	    
	}
	
	/**
	 * Metodo llamado excusivamente por el dispatcher, no debe ser sobrecargado
	 * @param $layout
	 * @param $view
	 * @return bool
	 */
	final public function preDispatch($layout = null, $view = null){
		
		// Si hay se establece el layout (opcional)
		if (!is_null($layout)){
			$this->layout = $layout;
		}
		
		// Se establece la vista (obligatoria)
		if (!is_null($view)){
			$this->view = $view;
		}
		
	}
	
	/**
	 * Inicia el controlador
	 * @return void
	 */
	public function initController(){
		
		
		
	}
	
	/**
	 * Verifica si existe una configuración de conexión
	 * a base de datos, si es así, conecta y propaga al
	 * objecto de abstracción en la clase
	 */
	private function _initDatabase(){
	    
	    // Se intentará obtener la configuración de la aplicación
        if (array_key_exists('app_config', $GLOBALS['NINGEN_CMS']) && $GLOBALS['NINGEN_CMS']['app_config'] instanceof NingenApplicationConfig){

            // Verificaremos si hay configurada una conexión a base de datos
            $appConfig = $GLOBALS['NINGEN_CMS']['app_config'];
            $dbaseConfig = $appConfig->getDatabaseConfiguration();
            
            if (is_null($dbaseConfig)){
                return;
            }
            
            // Finalmente se realiza la conexión
            $this->db = new NingenConnection($dbaseConfig);
            
        }
        
	} 
	
	/**
	 * Agrega un modulo a la pila, este método siempre debe llamarse antes del dispatch
	 * de lo contrario arrojará la correspondiente excepcion
	 * @param NingenModule $modulo
	 * @return void
	 */
	final protected function addModule($modulo){
		
		if ($modulo instanceof NingenModule){
			array_push($this->moduleStack, $modulo);
			return true;
		}
		
		return false;
		
	}
	
	/**
	 * Acción inicial el controller
	 * @return void
	 */
	public function indexAction(){
		
		throw new  NingenException('La acción index debe ser sobreescrita');
		
	}
	
	
	/**
	 * Establece el slot por defecto para mostrar la salida de la acción actual
	 * @param string $slotName
	 * @return void
	 */
	public function setDefaultSlot($slotName){
		
		$this->defaultSlot = $slotName;
		
	}
	
	/**
	 * Ejecuta una acción determinada y su resultado es encapsulado en la vista
	 * @param string $actionName
	 * @return string
	 */
	final protected function executeAction($actionName){
		
		// Se ejecuta la acción, si por alguna razón (debug, etc), la acción devuelve código html, será capturado
		// y enviado junto con el buffer de la vista y mostrado en el slot correspondiente
		ob_start();
		
		$this->$actionName();
		$actionCode = ob_get_clean();
		
		// Se devuelve el buffer indicado
		return $actionCode . $this->view->getBuffer();
		
	}
	
	/**
	 * Ejecuta la acción actual, y de acuerdo a la configuración dada llama a la vista asignada y al layout
	 * @param string $actionName
	 * @return void
	 */
	final public function render($actionName){
		
		// Si no hay layout se llamara directamente a la acción
		if (is_null($this->layout)){
		    
			$actionMethodName = $this->_normalizeActionName($actionName);
			$this->$actionMethodName();
			
			return;
		}

		// Se inicia el doctype
		$this->layout->echoDoctype();
		
		// Se obtiene el código de la acción ejecutada y el "merge" resultante con la vista
		$actionCode = $this->executeAction($this->_normalizeActionName($actionName));
		
	    /**
         * #0022 - Múltiples layouts
         */
        if (!is_null($this->alternateLayout)){
            
            $this->layout = new NingenLayout($this->alternateLayout);
            
        }		
		
		// Se carga el contenido
		$this->layout->prepareContentForSlot($this->defaultSlot, $actionCode);
		
		
		// Se procesan los modulos
		$this->layout->processModules($this->moduleStack);
		
		// El controlador le pasara al layout todos los recursos necesarios para la vista actual
		$this->layout->setResources($this->view->getResources());
		
		// Se renderiza el layout
		$this->layout->renderlayout();
	
		
	}
	
	
	/**
	 * Normaliza el nombre de una acción
	 * @param stirng $actionName
	 * @return string
	 */
	private function _normalizeActionName($actionName){
		
		return $actionName . 'Action';
		
	}
	
	/**
	 * Devuelve el array de módulos
	 * @return array
	 */
	public function getModules(){
		
		return $this->moduleStack;
		
	}
	
	
	/**
	 * Establece el nombre del controlador
	 * @param string $controllerName
	 * @return void
	 */
	public function setControllerName($controllerName){
		
		$this->controllerName = $controllerName;
		
	}
	
	/**
	 * Establece el nombre de la acción actual
	 * @param string $actionName
	 * @return void
	 */
	public function setActionName($actionName){
		
		$this->actionName = $actionName;
		
	}
	
	/**
	 * Devuelve el nombre de la acción actual
	 * @return string
	 */
	protected function getActionName(){
		
		return $this->actionName;
		
	}
	
	/**
	 * Devuelve el nombre del controlador actual
	 * @return string
	 */
	protected function getControllerName(){
		
		return $this->controllerName;
		
	}
	
	/**
	 * Devuelve el nombre del layout actual
	 * @return string
	 */
	public function getAlternateLayout(){
	    
	    return $this->alternateLayout;
	    
	}
	
	/**
	 * Establece el nombre del layout alternativo
	 */
	public function setAlternateLayout( $layoutName ){
	    
	    $this->alternateLayout = $layoutName;
	    
	}
	
	/**
	 * Redirecciona a un controlador y a una accion, siempre y
	 * cuando no se hayan enviado las cabeceras
	 * 
	 * @param string $controllerName
	 * @param string $actionName
	 */
	protected function redirectTo( $controllerName, $actionName = null){
	    
	    // La acción por defecto es index
	    if (is_null($actionName)){
	        $actionName = 'index';
	    }
	    
	    $headerString = '/' . $controllerName . '/' . $actionName;
	    
	    
	    if (!headers_sent()){
	        
	        header('Location: ' . $headerString);
	        return true;
	        
	    }

	    return false;
	    
	}
	 
	
}

?>