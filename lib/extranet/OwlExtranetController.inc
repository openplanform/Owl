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
 * Controller de la extranet.
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

require_once 'OwlController.inc';

require_once 'extranet/OwlExtranetController.inc';
require_once 'extranet/OwlAclManager.inc';

require_once 'extranet/modulos/menuPrincipalModule.php';
require_once 'extranet/modulos/logoutModule.php';
require_once 'extranet/modulos/popupModule.php';
require_once 'extranet/modulos/barraHerramientasModule.php';
require_once 'extranet/modulos/breadcrumbsModule.php';


class OwlExtranetController extends OwlController{
	
	/**
     * Manejador de listas de acceso
     * @var OwlAclManager
     */
    protected $aclManager;
	
	/**
     * Añado el soporte de AclManager
     */
    public function __construct(){
        
        parent::__construct();
        
        // Se instancia el AclManager
        $this->aclManager = new OwlAclManager($this->db);
        
    }
    
	/**
     * Se instancian los módulos mas significativos de la aplicacion
     * @see extranet.planespime.es/owl/lib/OwlController::initController()
     */
    public function initController(){
        
        /**
         * El usuario deberá tener una cuenta para poder ejecutar 
         * cualquier acción del controlador
         */
        if ($this->controllerName != 'index' || ($this->controllerName == 'index' && $this->actionName == 'panel' )){
            
        	$usuarioBO = OwlSession::getValue('usuario');
        	
            if (!$usuarioBO instanceof OwlUsuarioSesion){
                $this->redirectTo('index', 'login');
                return;
            }
            
        }  
        
        // Se globaliza el usuario actual
	    $this->usuario = $usuarioBO;   

	    // Control de errores
        $this->aclManager->getAclData($this->usuario, true);
        
    	// ROLES
        if ($this->actionName != 'login'){
        
		    if (!$this->aclManager->hasPerms($this->controllerName, $this->actionName)){
		    	
		    	$this->stopExecution();
		    	echo OwlHtmlHelper::getHtmlErrorPage('Forbidden', 403, 'Acceso no autorizado', '<p>No dispone de los privilegios necesarios para acceder a este área.</p>');
		    	
		    	return;
		    }        
		    
        }
        
        
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
    	if ( $this->actionName == "duplicar" ){
    		$this->bypassLayout();
    	}
    	
    }
}

?>