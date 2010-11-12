<?php

require_once 'NingenController.inc';

require_once 'extranet/NingenExtranetController.inc';
require_once 'extranet/NingenAclManager.inc';

require_once 'extranet/modulos/menuPrincipalModule.php';
require_once 'extranet/modulos/logoutModule.php';
require_once 'extranet/modulos/popupModule.php';
require_once 'extranet/modulos/barraHerramientasModule.php';
require_once 'extranet/modulos/breadcrumbsModule.php';


class NingenExtranetController extends NingenController{
	
	/**
     * Manejador de listas de acceso
     * @var NingenAclManager
     */
    protected $aclManager;
	
	/**
     * Añado el soporte de AclManager
     */
    public function __construct(){
        
        parent::__construct();
        
        // Se instancia el AclManager
        $this->aclManager = new NingenAclManager($this->db);
        
    }
    
	/**
     * Se instancian los módulos mas significativos de la aplicacion
     * @see extranet.planespime.es/ningencms/lib/NingenController::initController()
     */
    public function initController(){
        
        /**
         * El usuario deberá tener una cuenta para poder ejecutar 
         * cualquier acción del controlador
         */
        if ($this->controllerName != 'index' || ($this->controllerName == 'index' && $this->actionName == 'panel' )){
            
        	$usuarioBO = NingenCmsSession::getValue('usuario');
        	
            if (!$usuarioBO instanceof NingenUsuarioSesion){
                $this->redirectTo('index', 'login');
                return;
            }
            
        }  
        
        // Se globaliza el usuario actual
	    $this->usuario = $usuarioBO;   
        
        
        // ------------ MÓDULO - MENÚ PRINCIPAL -----------
        $menuPrincipalModule = new menuPrincipalModule('contenedor_menu');
            
            $menuPrincipalModule->setDb($this->db);

            // Se configuran los permisos del menu
            $acl = $this->aclManager->getAclData($this->usuario);
            $menuPrincipalModule->setMenuArray($acl);
            
            $this->addModule($menuPrincipalModule);

        // ------------ MÓDULO - LOGOUT -------------------
        $logoutModule = new logoutModule('contenedor_logout');
            
            $logoutModule->setAcl($this->aclManager);
            $logoutModule->setUsuario($this->usuario);
            $this->addModule($logoutModule);
        
        // ------------ MÓDULO - BARRA DE HERRAMIENTAS ----
        $barraHerramientasModule = new barraHerramientasModule('contenedor_toolbar');
            
            $barraHerramientasModule->setAction($this->actionName);
            $barraHerramientasModule->setController($this->controllerName);
            $barraHerramientasModule->setParam($this->getParam(0));
            $this->addModule($barraHerramientasModule);
        
        
        // ------------ MÓDULO - POPUP ----------------------
        $popupModule = new popupModule('contenedor_popup');

            $this->addModule($popupModule);
            
            
        // ------------ MÓDULO - BREADCRUMBS -------------------
        $pathModule = new breadcrumbsModule('contenedor_path');
        
            $pathModule->setControllerAction($this->controllerName, $this->actionName, $this->controllerRewrite);
            $pathModule->setDb($this->db);
            $this->addModule($pathModule);
            
            
        // Casos especiales en los que no es necesario un layout
    	if ( $this->actionName == "eliminar" || $this->actionName == "duplicar" ){
    		$this->bypassLayout();
    	}
    	
    }
}

?>