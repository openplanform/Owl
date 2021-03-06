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
 * Clase que implementa el manejador de listas de acceso.
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

require_once 'OwlSession.inc';
require_once 'extranet/OwlUsuarioSesion.inc';

require_once MODELDIR . 'TblAcceso.inc';
require_once MODELDIR . 'TblUsuario.inc';
require_once MODELDIR . 'TblRol.inc';

class OwlAclManager{
    
    /**
     * Referencia a la base de datos
     * @var OwlConnection
     */
    protected $db;
    
    /**
     * Cadena añadida para codificar contraseñas
     * @var string
     */
    private $_secret = 'N1NG3N';
    
    /**
     * Clave de rol administrador
     * @var integer
     */
    const ROL_ADMINISTRADOR = 1;
    
    /**
     * Clave de rol usuario
     * @var integer
     */
    const ROL_USUARIO       = 2;
    
    /**
     * Lista de acceso
     * @var array
     */
    private $_acl;
    
    /**
     * Flag que indica que la lista ha sido cargada en el objeto
     * @var boolean
     */
    private $_acl_fetched = false;
    
    /**
     * Todos los nombres de roles indexados por su clave
     * @var array
     */
    private $_rolesIDX;
    
    /**
     * Flag que indica que los roles han sido cargados en el objeto
     * @var unknown_type
     */
    private $_roles_idx_fetched = false; 
    
    /**
     * Guarda toda la lista de acceso en un array
     * @var array
     */
    private $_aclARR = array();
    
    /**
     * Obtiene la base de datos
     */
    public function __construct( $db ){
        
        // Se propaga la referencia a la base de datos
        $this->db = $db;
        
    }
    
    /**
     * Realiza un login en el sistema, si es correcto
     * devuelve true y propaga los datos del acceso por la sesion
     * 
     * @param string $username
     * @param string $password
     * @return boolean
     */
    public function login( $username, $password){
        
        $password = $this->codificaPassword(strtolower($password));
        $username = strtolower($username);

        $sql = "SELECT * FROM tblUsuario WHERE LOWER(vNombre) = '$username' AND vPassword = '$password'";
        $this->db->executeQuery($sql);
        
        $row = $this->db->fetchRow();
        
        if ($row === false){
            return false;
        }
        
        // Implementamos objeto de sesion y propagar datos
        $rolesARR = $this->getRolesUsuario($row['idUsuario']);
        $usuarioSesion = new OwlUsuarioSesion($row['idUsuario'], $row['vNombre'], $rolesARR, $row['vEmail']);
        
        OwlSession::setValue('usuario', $usuarioSesion);
        
        return true;
        
    }
    
    /**
     * Crea el objeto de sesión de usuario a partir de su clave
     * y lo devuelve, en caso de no existir devuelve null
     * 
     * @param integer $claveUsuario
     * @return OwlUsuarioSesion
     */
    public function createSessionObject($claveUsuario){
        
        if (!$usuarioDO = TblUsuario::findByPrimaryKey($this->db, $claveUsuario)){
            return null;
        }
        
        $rolesARR = $this->getRolesUsuario($claveUsuario);
        $returnBO = new OwlUsuarioSesion($usuarioDO->getIdUsuario(), $usuarioDO->getVNombre(), $rolesARR, $usuarioDO->getVEmail());
        
        return $returnBO;
        
    }
    
    /**
     * Codifica una contraseña
     * 
     * @param string $cadena
     * @return string
     */
    public function codificaPassword( $cadena ){
        
        return md5( $this->_secret . $cadena . $this->_secret );
        
    }
    
    /**
     * Obtiene los roles asignados a un usuario a partir de su clave
     * @param integer $claveUsuario
     */
    public function getRolesUsuario( $claveUsuario ){
        
        $sql = "SELECT * FROM trelRolUsuario WHERE fkUsuario='$claveUsuario'";
        $this->db->executeQuery($sql);
        
        $arrRoles = array();
        while ( $row = $this->db->fetchRow() ){
            $arrRoles[] = $row['fkRol'];
        }
        
        return $arrRoles;
        
    }
    
    /**
     * Verifica que el usuario actual tiene permiso para el controlador y acción indicados
     * 
     * @param string $controllerName
     * @param string $actionName
     * @return boolean
     */
    public function hasPerms( $controllerName, $actionName){
        
        $usuario = OwlSession::getValue('usuario');
        $rolesUsuario = $usuario->getRoles();
        
        // Se busca el controlador
        if (array_key_exists($controllerName, $this->_aclARR)){
            
            // Se busca la acción
            if (array_key_exists($actionName, $this->_aclARR[$controllerName])){
                
                // Se verifican los roles
                $rolesZona = $this->_aclARR[$controllerName][$actionName];
                foreach ($rolesUsuario as $rolUsuario){

                     if (array_search($rolUsuario, $rolesZona) === false){
                         return false;
                     } else {
                         return true;
                     }
                    
                }
                
            }
            
        }
        
        // Por defecto ahí te quedas
        return false;
        
    }
    
    /**
     * Obtiene el rol mas relevante de un usuario
     * @param integer $claveUsuario
     * 
     * @return TblRol
     */
    public function getRolMasRelevanteUsuario($claveUsuario){

        $rolesUsuario = $this->getRolesUsuario($claveUsuario);
        $returnRol = array();
        
        foreach ($rolesUsuario as $rol){
            
            if ($rol < $returnRol){
                $returnRol = $rol;
            }
            
        }
        
        return $returnRol;
        
    }    
    
    /**
     * Devuelve un array de nombres de todos los roles indexados por su clave
     * @return array
     */
    public function getRoles(){
        
        if ($this->_roles_idx_fetched){
            return $this->_rolesIDX;
        }
        
        $rolesCOL = TblRol::findAll($this->db, 'idRol ASC');
        $returnARR = array();
        
        foreach ($rolesCOL as $rolDO) {
            $returnARR[$rolDO->getIdRol()] = $rolDO->getVNombre();
        }
        
        $this->_rolesIDX = $returnARR;
        $this->_roles_idx_fetched = true;
        
        return $this->_rolesIDX;
        
    }
    
    /**
     * Devuelve la lista de acceso del sistema, filtrada por los roles
     * que posee el usuario actual. A partir de esta lista se define el
     * acceso a cuaquier zona del sistema, como también el menú. Si reload vale true, 
     * se actualizará la cache
     * 
     * @param OwlUsuarioSesion $usuario
     * @param boolean $reload 
     * @return array
     */
    public function getAclData( $usuario, $reload = false ){

        // Cachearemos la lista de acceso
        if ($this->_acl_fetched && $reload === false){
            return $this->_acl;
        }
        
        // Obtengo la clave del usuario actual
        $claveUsuario = $usuario->getId();
        
        // Roles del usuario actual
        $rolesUsuario = $this->getRolesUsuario($claveUsuario);
        
        // Obtenemos la lista desde la BD
        if ($acl = TblAcceso::findAll($this->db, 'iOrden ASC')){
            
            // Propagamos los datos de la lista de acceso
            $this->_procesaArrayAcl($acl);
            
            // Guardaremos los sitios donde el usuario puede acceder 
            $sitiosPermitidos = array();
            
            foreach ($acl as $accesoDO){

                //$accesoDO = new TblAcceso($db);
                $rolesReq = $accesoDO->getVRoles();
                
                // Si es null, se trata de una  raiz de menu
                if (!is_null($rolesReq)){
                    
                    $rolesReqARR = explode(',' , $rolesReq);
                    
                    foreach ($rolesUsuario as $rolUsuario){
                        
                         // Se comprueban los roles
                         if (in_array($rolUsuario, $rolesReqARR)){
                             $sitiosPermitidos[] = $accesoDO;
                         }
                        
                    }
                    
                } else {
                    
                    // Se trata de una raíz de menu
                    $sitiosPermitidos[] = $accesoDO;
                    
                }
                 
            }

            // Se actualiza la caché
            $this->_acl = $sitiosPermitidos;
            $this->_acl_fetched = true;

            return $this->_acl;
            
        }
        
    }
    
    
    /**
     * Método similar a getAclData, sólo que no filtra por permisos
     * los ítems de acceso. Devuelve toda la lista ACL. 
     * Este método no dispone de caché.
     * 
     * @return array TblAcceso
     */
    public function getAclRawData(){
        
        // Obtenemos la lista desde la BD
        if ($acl = TblAcceso::findAll($this->db, 'idAcceso ASC')){
            
            return $acl;
            
        }        
        
        return null;
        
    }
    
    
    /**
     * Procesa los datos de la lista de acceso y los almacena en un array
     * con el cual se comprobarán los permisos mediante hasPerms()
     * 
     * @param $acl
     */
    private function _procesaArrayAcl($acl){
        
        $returnARR = array();
        
        foreach ($acl as $accesoDO) {
            
            if ($accesoDO->getVAccion() != null){
            
                $returnARR[$accesoDO->getVControlador()][$accesoDO->getVAccion()] = explode(',', $accesoDO->getVRoles());
                
            }
            
        }
        
        $this->_aclARR = $returnARR;
        
    }
    
    /**
     * Devuelve un array con las cantidades de usuarios por rol
     * indexado por clave de rol. Útil para estadísticas.
     * 
     * @return array
     */
    public function getCantidadUsuariosRoles(){
        
        $rolesIDX = $this->getRoles();
        $returnARR = array();
        
        foreach ($rolesIDX as $clave => $rol){
            
            $sql = 'SELECT COUNT(*) AS total FROM trelRolUsuario WHERE fkRol =' . $clave;
            $this->db->executeQuery($sql);
            
            $row = $this->db->fetchRow();
            if (array_key_exists('total', $row)){
                $returnARR[$clave] = intval($row['total']);
            }
            
        }
        
        return $returnARR;
        
    }
    
}

?>