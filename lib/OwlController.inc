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
 * Controlador genérico, todos los controladores deben heredar de esta clase
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
require_once 'dbase/OwlConnection.inc';
require_once 'helper/OwlControllerHelper.inc';


class OwlController{
	
	/**
	 * Layout asignado al controlador
	 * @var OwlLayout
	 */
	protected $layout = null;
	
	/**
	 * Vista asignada al controlador
	 * @var OwlView
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
	 * @var OwlConnection
	 */
	protected $db;
	
	/**
	 * Nombre de layout alternativo
	 * @var string
	 */
	protected $alternateLayout = null;
	
	/**
	 * Helper para controladores
	 * @var OwlControllerHelper
	 */
	protected $helper;

	/**
	 * Parámetros de la url
	 * @var array
	 */
	protected $urlParams = null;
	
	/**
	 * Si vale true, no se implementará el layout asignado
	 * @var boolean
	 */
	private $_bypassLayoutValue = false;
	
    /**
     * Reescritura de la etiqueta de controlador
     * @var string
     */
    protected $controllerRewrite = null;	
    
    /**
     * Objeto de sesión de usuario
     * @var OwlUsuarioSesion
     */
    protected $usuario;
    
    /**
     * Flag de parada, indica que la aplicación debe dejar de ejecutarse
     * generalmente empleado para mostrar páginas de error
     * @var boolean
     */
    private $_stop = false;
    
	
	/**
	 * Constructor, instancia algunos objetos necesarios 
	 */
	public function __construct(){
	    
	    // Se inicia la conexión a la base de datos
        $this->_initDatabase();
	    
	    // Helper para controladores
	    $this->helper = new OwlControllerHelper();
	    
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
        if (array_key_exists('app_config', $GLOBALS['OWL']) && $GLOBALS['OWL']['app_config'] instanceof OwlApplicationConfig){

            // Verificaremos si hay configurada una conexión a base de datos
            $appConfig = $GLOBALS['OWL']['app_config'];
            $dbaseConfig = $appConfig->getDatabaseConfiguration();
            
            if (is_null($dbaseConfig)){
                return;
            }
            
            // Finalmente se realiza la conexión
            $this->db = new OwlConnection($dbaseConfig);
            
        }
        
	} 
	
	/**
	 * Agrega un modulo a la pila, este método siempre debe llamarse antes del dispatch
	 * de lo contrario arrojará la correspondiente excepcion
	 * @param OwlModule $modulo
	 * @return void
	 */
	final protected function addModule($modulo){
		
		if ($modulo instanceof OwlModule){
			
			// Se identifica la instancia actual
			$modulo->setAction($this->actionName);
			$modulo->setController($this->controllerName);
			
			// Se inserta el módulo en la pila
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
		
		throw new  OwlException('La acción index debe ser sobreescrita');
		
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
		
		// Se evalúa el flag de parada
		if ($this->_stop){
			return;
		}
	    
	    // Si hay base de datos activa, se propaga el log sql
	    if ($this->db instanceof OwlConnection){
	        $GLOBALS['OWL']['app_dblog'] = $this->db->getLogHTML();
	    }
		
		// Si no hay layout o si se ha deshabilitado se llamara directamente a la acción
		// empleado generalmente para peticiones ajax
		if (is_null($this->layout) || $this->_bypassLayoutValue){
		    
			$actionMethodName = $this->_normalizeActionName($actionName);
			$this->$actionMethodName();
			
			// Si se encuentra una vista para la acción actual será procesada
			if ($viewBuffer = $this->view->getBuffer()){
				echo $viewBuffer;
			}
			
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
            
            $this->layout = new OwlLayout($this->alternateLayout);
            
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
	 * Establece los parámetros de la url
	 * @param array $params
	 */
	public function setParams( $params ){
	    
	    $this->urlParams = $params;
	    
	}

	/**
	 * Devuelve los parámetros de la url ( si hay )
	 * @return array
	 */
	public function getParams(){
	    
	    return $this->urlParams;
	    
	}
	
	/**
	 * Devuelve un parámetro almacenado en la clave numérica del 
	 * array de parámetros, si no existe devuelve null
	 * @param integer $clave
	 */
	public function getParam($clave){
	    
	    // Obtendremos la clave del request
        $params = $this->getParams();
        
        if ( is_array($params) && array_key_exists($clave, $params) && !empty($params[$clave]) ){
            return $params[$clave];            
        }
        
        return null;
	    
	}
	
	/**
	 * Redirecciona a un controlador y a una accion, siempre y
	 * cuando no se hayan enviado las cabeceras, de lo contrari
	 * intentará hacerlo mediante javascript
	 * 
	 * @param string $controllerName
	 * @param string $actionName
	 * @param string $params
	 */
	protected function redirectTo( $controllerName, $actionName = null, $params = null){
	    
	    // La acción por defecto es index
	    if (is_null($actionName)){
	        $actionName = 'index';
	    }
	    
	    $headerString = '/' . $controllerName . '/' . $actionName . '.html';
	    
	    // Se verifican los parámetros
	    if (!is_null($params)){
	       $headerString = $headerString . '/' . $params;    
	    }
	    
	    if (!headers_sent()){
	    	
	        header('Location: ' . $headerString);
	        
	    } else {
	    	
	        echo '<script type="text/javascript">window.location="' . $headerString . '"</script>';
	        
	    }

	}
	
	/**
	 * Evita que se implemente el layout asignado
	 */
	protected function bypassLayout(){
	    
	    $this->_bypassLayoutValue = true;
	    
	}
	
	
    /**
     * Establece un *nombre* alternativo para el controlador actual
     * utilizado por el módulo de breadcrumbs
     * @param string $label
     */
    public function rewriteControllerLabel($label){
        
        $this->controllerRewrite = $label;
        
    }	
    
    
    /**
     * Detiene la ejecución actual del controlador
     */
    protected function stopExecution(){

    	// Hace un bypass tanto de layout como de la vista
    	$this->bypassLayout();
    	$this->view->bypassView();
    	
    	// Se activa el flag de parada
    	$this->_stop = true;
    	
    }
    
    
    /**
     * Devuelve el objeto de configuración de aplicación, si no lo logra devuelve null
     * @return OwlApplicationConfig
     */
    protected final function getApplicationConfig(){
    	
    	// Objeto global del framework
    	if (array_key_exists('OWL', $GLOBALS)){
    		
    		// Configuración 
    		if (array_key_exists('app_config', $GLOBALS['OWL'])){
    			
    			$appConfig = $GLOBALS['OWL']['app_config'];
    			
    			if ($appConfig instanceof OwlApplicationConfig){
    				return $appConfig;
    			}
    			
    		}
    		
    	}
    	
    	return null;
    	
    }
    
    
    /**
     * Devuelve el objeto de locale, si no lo logra devuelve null
     * @return OwlLocale
     */
    protected final function getLocale(){
    	
    	// Objeto global del framework
    	if (array_key_exists('OWL', $GLOBALS)){
    		
    		// Locale 
    		if (array_key_exists('app_locale', $GLOBALS['OWL'])){
    			
    			$locale = $GLOBALS['OWL']['app_locale'];
    			
    			if ($locale instanceof OwlLocale){
    				return $locale;
    			}
    			
    		}
    		
    	}
    	
    	return null;
    	
    }
    
    
    /**
     * Establece el nuevo idioma y recarga la página
     * 
     * @param string $lang
     */
    protected final function changeLang($lang){
    	
    	// Se detiene la ejecución del script
    	$this->stopExecution();
    	
    	// Se guarda el valor del nuevo idioma temporalmente en la sesión
    	OwlSession::setValue('new_lang', $lang);
    	
    	// Se recarga la página
    	$this->redirectTo($this->controllerName, $this->actionName);
    }
	 
	
}

?>