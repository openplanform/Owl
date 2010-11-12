<?php

require_once 'NingenModule.inc';

class logoutModule extends NingenModule{
    
    /**
     * Referencia al objeto de usuario en la sesión
     * @var PplUsuarioSesion
     */
    protected $usuario;
    
    /**
     * ACL Manager
     * @var PplAclManager
     */
    protected $acl;
    
    /**
     * Indica si la ficha de usuario está completa o no
     * @var boolean
     */
    protected $fichaUsuario = true;
    
    /**
     * Establece el gestor de listas de acceso
     * @param PplAclManager $acls
     */
    public function setAcl(NingenAclManager $acl){
        $this->acl = $acl;
    }
    
    /**
     * Establece el objeto de usuario actual
     * @param PplUsuarioSesion $usuario
     */
    public function setUsuario(NingenUsuarioSesion $usuario){
        $this->usuario = $usuario;
    }
    
    /**
     * Request
     * @see extranet.planespime.es/ningencms/lib/NingenModule::requestModule()
     */
    public function requestModule(){
        
        
        
    }
    
    /**
     * Run
     * @see extranet.planespime.es/ningencms/lib/NingenModule::runModule()
     */
    public function runModule(){
        
        if (is_null($this->usuario)){
            return;
        }

        $idRol = $this->acl->getRolMasRelevanteUsuario($this->usuario->getId());
        $rolesIDX = $this->acl->getRoles();
        
        ?><div id="logoutModule"><?php 
        
        if ( $this->fichaUsuario ){
        	?><a href="/usuario/ficha/<?= $this->usuario->getId() ?>"><?= $this->usuario->getNombre() ?></a><?
        } else {
        	echo $this->usuario->getNombre();
        }
        
       ?> <strong>(<?= $rolesIDX[$idRol] ?>)</strong> 
            <a href="/index/logout.html" class="cerrarSesion" title="cerrar sesión">
                <span>cerrar sesión</span>
            </a>
        </div><?
        
    }
    
}

?>
