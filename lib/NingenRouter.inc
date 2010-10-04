<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Enrutador de urls, clase diseñada para ejecutar y gestionar controladores
 * de acuerdo a la URL actual.  
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once 'NingenServerResponses.inc';
require_once 'NingenDispatcher.inc';


class NingenRouter{
	
	/**
	 * Controlador actual
	 * @var string
	 */
	private $_controller = null;
	
	/**
	 * Acción actual
	 * @var string
	 */
	private $_action = null;
	
	/**
	 * Parámetros actuales
	 * @var string
	 */
	private $_params = null;
	
	/**
	 * Identificador de idioma actual
	 * deducido desde la URI
	 * @var string
	 */
	private $_deducedLang = null;
	
	/**
	 * Extensión de archivo actual
	 * deducida desde la URI
	 * @var string
	 */
	private $_deducedExtension = null;
	
	/**
	 * Cadena con la petición del cliente
	 * @var string
	 */
	private $_queryString = null;
	
	/**
	 * Configuración de la aplicacion
	 * @var NingenApplicationConfig
	 */
	private $_applicationConfig;
	
	/**
	 * Dispatcher general
	 * @var NingenDispatcher
	 */
	private $_dispatcher;

	
	/**
	 * Verifica request uri y prepara los deatos de la uri
	 * @param string $request_uri
	 * @return void
	 */
	public function __construct( $request_uri ){
		
		// Como mínimo PHP siempre almacena "/" en request_uri, ante la duda
		// y/o cualquier fallo devolvemos un 404
		if (empty($request_uri)){
			
			$response = new NingenServerResponses(404, '<p>La página solicitada no existe o ha sido movida.</p>');
			$response->sendResponse();
			
		}
		
		// Una vez comprobado se hace global
		$this->_queryString = $request_uri;
		
	}
	
	/**
	 * Método principal del router, si todo es correcto inicia
	 * el bootstrap	
	 * @return void
	 */
	public function deployAndBootstrap(){
		
		// Se parte el query string
		$queryParts = $this->_parseUri($this->_queryString);
		$queryNumParts = count($queryParts);
		
		// Se eliminan espacios
		foreach ($queryParts as $key=>$qPart){
			$queryParts[$key] = trim($qPart);
		}
		
		switch ($queryNumParts){
			
			case 0:
				// Q: /
				$this->_loadDefaultConfig();
				break;
			
			case 1:
				// Q: /acercade
				$this->_loadController($queryParts[0]);
				break;
				
			case 2:
				//Q: /acercade/index
				$this->_loadControllerAction($queryParts[0], $queryParts[1]);
				break;
				
			default:
				//Q: /acercade/index/key/value
				$this->_collectParams($queryParts);
				$this->_loadControllerAction($queryParts[0], $queryParts[1]);
				break;
			
		}
		
	}
	
	/**
	 * Parsea una cadena del query y devuelve sus partes
	 * @param string $request_uri
	 * @return array
	 */
	private function _parseUri($request_uri){
	    
	    $queryParams = explode('?', $request_uri);
	    $cleanUri = $queryParams[0];
	    
		$queryParts = explode('/', $cleanUri);
		$parts = array();
		
		foreach ($queryParts as $part){
			
			$part = trim($part);
			
			if($part != ''){
				array_push($parts, $part);
			}
		}
		
		
		return $parts;
		
	}
	
	/**
	 * Obtiene los parámetros (si hay) del uri
	 * @return void
	 */
	private function _collectParams(){
		
//	    $url = "http://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
//        $query = explode("&", $_SERVER['QUERY_STRING']);
//        
//    	// modify/delete data
//        foreach($query as $param) {
//            list($key, $value) = explode("=", $param);
//            if(array_key_exists($key, $mod)) {
//                if($mod[$key]) {
//                    $url = preg_replace('-'.$key.'='.$value.'-', $key.'='.$mod[$key], $url);
//                } else {
//                    $url = preg_replace('-&?'.$key.'='.$value.'-', '', $url);
//                }
//            }
//        }
        
	}
	
	/**
	 * No se ha recibido nada por el uri, por lo que se cargará 
	 * el controlador por defecto y se llamará a la acción por defecto
	 * @return void
	 */
	private function _loadDefaultConfig(){
		
		$defaultController = 'index';
		$defaultAction = 'index';
		
		// Se verifica la configuración, de estar establecida se obtienen los datos necesarios
		if ($this->_applicationConfig instanceof NingenApplicationConfig){
			$defaultController = $this->_applicationConfig->getDefaultController();
			$defaultAction = $this->_applicationConfig->getDefaultAction();			
		}
		
		$this->_controller = $defaultController;
		$this->_action = $defaultAction;
		
		// Se designará el controller y la acción
		$this->_virtualizeAndDispatch();
		
	}
	
	
	/**
	 * Se ha recibido el controlador por el uri
	 * @param string $controllerName
	 * @return void
	 */
	private function _loadController($controllerName){

		// Se establece el controlador actual
		$this->_controller = $controllerName;
		
		// La acción para un controlador especificado será index
		$this->_action = 'index';
		
		// Se designará el controller y la acción
		$this->_virtualizeAndDispatch();		
		
	}
	
	/**
	 * Se ha recibido el controller y el action por el uri
	 * @param string $controllerName
	 * @param string $actionName
	 * @return void
	 */
	private function _loadControllerAction($controllerName, $actionName){
		
		// Se establece el controlador actual
		$this->_controller = $controllerName;
		
		// Se establece la acción actual
		$this->_action = $actionName;

		// Se designará el controller y la acción
		$this->_virtualizeAndDispatch();		
		
	}
	

	/**
	 * Establece la configuración personalizada para la aplicacion
	 * @param NingenApplicationConfig $appConfig
	 * @return void
	 */
	public function setApplicationConfig(NingenApplicationConfig $appConfig){

		$this->_applicationConfig = $appConfig;
		
	}
	
	/**
	 * Consulta la virtualización de controladores y realiza el dispatch de los mismos
	 * @return void
	 */
	private function _virtualizeAndDispatch(){
		
		// Se buscarán alternativas
		$this->virtualizeController();
			
		// Se instancia el dispatcher
		$this->_dispatcher = new NingenDispatcher($this->_controller, $this->_action);
		
		// Se carga el controlador y la acción
		if (!$this->_dispatcher->verifyRoute()){
			
			// El controlador o la acción son incorrectos
			$response = new NingenServerResponses(404, '<p>La página solicitada no existe o ha sido movida.</p>');
			$response->sendResponse();			
			
		} else {
			
			// Se verificará si se ha configurado un layout por defecto, si es así se le pasa su nombre al dispatch
			// el se encargará de instanciarlo y de negociar con el controller su comportamiento
			$defaultLayout = $this->_applicationConfig->getDefaultLayout();
			
			// Todo OK, Se realiza el dispatch
			$this->_dispatcher->dispatch($defaultLayout);			
			
		}
		

	}

	
	/**
	 * Método que buscara alternativas para el nombre de un 
	 * controlador. Si se ha encontrado alguna alternativa
	 * devuelve true, de lo contrario false.
	 * @return boolean
	 */
	protected function virtualizeController(){
		
		/** @TODO WRITE IT **/
		
	}
	
	
	
}

?>