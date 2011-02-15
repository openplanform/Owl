<?php

require_once 'extranet/OwlExtranetController.inc';
require_once 'helper/OwlString.inc';
require_once 'helper/OwlExtranetHelper.inc';
require_once 'OwlMailerTemplate.inc';
require_once 'OwlMailer.inc';

class indexController extends OwlExtranetController{
	
	
	/**
	 * Init
	 * @see OwlController::initController()
	 */
	public function initController(){
		
        // Necesitaremos los módulos para el panel principal
        if ($this->actionName == 'panel'){
            $this->rewriteControllerLabel('administrador');
            parent::initController();            
        }		
		
        // La página principal siempre será el login
        if ($this->actionName == 'index'){
            
            $this->redirectTo('index', 'login');
            
        }		
		
	}

	
	/**
	 * Index
	 * @see OwlController::indexAction()
	 */
	public function indexAction(){
		
		
		
	}	
	
	
	/**
	 * Identifica a un usuario en el sistema
	 */
	public function loginAction(){
	    
	    // Se verifica si el usuario se encuentra ya logueado
        $this->usuario = OwlSession::getValue('usuario');
        
        // De ser así lo redireccionamos a la página principal
        if ($this->usuario instanceof OwlUsuarioSesion){
            
            // Si el usuario no tiene una entidad asignada, obligamos a que complete sus datos.
            $claveUsuario = $this->usuario->getId();
            $this->redirectTo('index', 'panel');
            
            return;
        }
	    
	    // El login implementa el layout alternativo
	    $this->setAlternateLayout('libre');
	    
	    // Recibe los datos del formulario de login
	    if (count($_POST) != 0){
	     
	        // Se verifican y escapan los datos
    	    $usuario = $this->helper->getAndEscape('username');
    	    $password = $this->helper->getAndEscape('password');
    	    
            if (empty($usuario)){
    	        $this->view->mensaje = 'El nombre de usuario no puede estar vacío.';
    	        return;
    	    }
    	    
    	    if (empty($password)){
    	        $this->view->mensaje = 'La constraseña no puede estar vacía.';
    	        return;
    	    }
    	    
    	    // Se realiza el login
    	    if (!$this->aclManager->login($usuario, $password)){
    	        
    	        $this->view->mensaje = 'Datos Incorrectos.';
    	        return;
    	        
    	    } else {
    	        
                $this->usuario = OwlSession::getValue('usuario');
                $claveUsuario = $this->usuario->getId();
                $this->redirectTo('index', 'panel');
                
                return;
    	        
    	    }
    	    
	    }
    	    
	}
	
	
	/**
	 * Recordatorio de contraseña
	 */
	public function recordatorioAction(){
		
		$this->setAlternateLayout('libre');
	    
	    if (count($_POST) != 0){
	    	
	        // Se verifican y escapan los datos
    	    $usuario = $this->helper->escapeInjection($this->helper->get('username'));
    	    $email = $this->helper->escapeInjection($this->helper->get('email'));
    	    
            if (empty($usuario)){
    	        $this->view->mensaje = 'El nombre de usuario no puede estar vacío.';
    	        return;
    	    }
    	    
    	    if (empty($email)){
    	        $this->view->mensaje = 'El email no puede estar vacío.';
    	        return;
    	    }
    	    
    	    // Se comprueba si existe el usuario
    	    $usuarioSearch = new TblUsuarioSearch();
    	    $usuarioSearch->vNombre = $usuario;
    	    $usuarioSearch->vEmail = $email;
    	    $usuarioDO = array_shift(TblUsuario::find($this->db, $usuarioSearch));
    	    
	        if ( !empty($usuarioDO) ){
		        
	        	$password = OwlString::generaPassword(10, false);
	        	
		        // Se obtiene la configuración del mailer
	            $appConfig = $GLOBALS['OWL']['app_config'];
	            if (!$appConfig instanceof OwlApplicationConfig){
	                throw new OwlException('No se ha obtenido la configuración del mailer. Error crítico.', 500);
	            }
	            
	            // Template del mail
	            $mt = new OwlMailerTemplate();
	            $mt->setTemplate(LAYOUTDIR . 'recordatorioContrasena.txt');
	            $mt->addField('USUARIO', $usuario);
	            $mt->addField('CONTRASENA', $password);
	            
	            // Mailer
	            $mailerConfig = $appConfig->getMailerConfiguration();
	            $mailer = new OwlMailer($mailerConfig);
	            $mailer->addTo($email, $usuario);
	            $mailer->setSubject('OWL - Cambio de contraseña');
	            $mailer->setFrom('<noreply@nobody.com>', 'OWL');
	            $mailer->setBody($mt->getContent());
	            
	            // Se envía el correo
	            if(!$mailer->send()){
	                $this->view->error = 'Error al enviar el mensaje, por favor intente nuevamente en un momento.';
	                return;
	            } else {
	            	$usuarioDO->setVPassword($this->aclManager->codificaPassword($password));
	            	$usuarioDO->update();
	            }
	        	
	        }
	        
	        $this->view->mensaje = 'Si sus datos son correctos, se le ha enviado un correo';
	        
	    }		
		
		
	}
		
	/**
	 * Panel Principal
	 */
    public function panelAction(){
        
        // USUARIOS ----------------------------------------------
        
        $sql = "SELECT COUNT(*) AS total FROM tblUsuario;";
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->view->totalUsuarios = $row['total'];
        
        $sql = "SELECT idUsuario, vNombre FROM tblUsuario ORDER BY idUsuario DESC LIMIT 1;";
        $this->db->executeQuery($sql);
        $this->view->ultimoUsuario = $this->db->fetchRow();

    }
    
    
    /**
     * Logout - Elimina al usuario actual de la sesión
     */
    public function logoutAction(){
    	
		// Logout tampoco necesita layout
	    $this->setAlternateLayout('libre');
	    
	    // Tararí tararí...
	    OwlSession::setValue('usuario', null);
	    session_destroy();
	    
	    // Redirigimos al login nuevamente
	    $this->redirectTo('index', 'login');    	
    	
    }
	
}

?>