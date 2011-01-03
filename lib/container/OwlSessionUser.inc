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
 * Clase contenedora que encapsula los datos de un usuario
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

class OwlSessionUser{
	
	/**
     * Nombre de usuario
     * @var string
     */
    private $_nombre;
    
    /**
     * Id de usuario
     * @var integer
     */
    private $_id;
    
    /**
     * Array con las claves de los roles asignados
     * @var array
     */
    private $_arrRoles;
    
    /**
     * Guarda el email del usuario
     * @var string
     */
    private $_email;
   
    /**
     * Carga los datos en el objeto
     * @param integer $id
     * @param string $nombre
     * @param array $roles
     */
    public function __construct( $id, $nombre, $roles, $email ){
        
        $this->_id = $id;
        
        $this->_nombre = $nombre;
        
        $this->_arrRoles = $roles;
        
        $this->_email = $email;
        
    }
    
    /**
     * Devuelve el nombre del usuario
     * @return string
     */
    public function getNombre(){
        
        return $this->_nombre;
        
    }
    
    /**
     * Devuelve el ID del usuario
     * @return integer 
     */
    public function getId(){
        
        return $this->_id;
        
    }
    
    /**
     * Devuelve los roles del usuario
     * @return array
     */
    public function getRoles(){

        return $this->_arrRoles;
        
    }
    
    /**
     * Devuelve el email del usaurio
     * @return string
     */
    public function getEmail(){
        
        return $this->_email;
        
    }	
	
}

?>