<?php

require_once 'extranet/OwlExtranetController.inc';

/**
 * Controlador encargado de responder las peticiones asíncronas
 * de la a aplicacióm
 */
class ajaxController extends OwlExtranetController{

    
    public function initController(){
        
        parent::initController();
        
        $this->bypassLayout();
        
    }
    
    public function indexAction(){
        
    }
    
    /**
     * Comprueba si ya existe un usuario
     */
    public function comprobarUsuarioAction(){
    	
    	if ( array_key_exists('usuario', $_POST) ){
	    	
    		$sql = "SELECT COUNT(*) AS total FROM tblUsuario WHERE vNombre = '" . $_POST['usuario'] . "'";
            $this->db->executeQuery($sql);
            $row = $this->db->fetchRow();
            if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
            	$arrRespuesta['resultado'] = 'ko';
                $arrRespuesta['mensaje'] = 'El nombre de usuario ya existe';
            } else {
            	$arrRespuesta['resultado'] = 'ok';
            }
	    	
			$jsonArrRespuesta = json_encode($arrRespuesta);
			echo $jsonArrRespuesta;
			
    	}
    	
    }
    
    /**
     * Comprueba si ya existe el cif/dni
     */
 	public function comprobarDniAction(){
    	
    	if ( array_key_exists('dni', $_POST) && !empty($_POST['dni']) ) {
	    	
    		if ( array_key_exists('empresa', $_POST) && $_POST['empresa'] == 'false' ){
    			$sql = "SELECT COUNT(*) AS total FROM tblPersona WHERE vNumeroIdentificacion = '" . $_POST['dni'] . "'";
    		} else {
    			$sql = "SELECT COUNT(*) AS total FROM tblEmpresa WHERE vCif = '" . $_POST['dni'] . "'";
    		}
            $this->db->executeQuery($sql);
            $row = $this->db->fetchRow();
            if (is_array($row) && array_key_exists('total', $row) && $row['total'] != 0){
            	$arrRespuesta['resultado'] = 'ko';
                $arrRespuesta['mensaje'] = 'El número ya está registrado';
            } else {
            	$arrRespuesta['resultado'] = 'ok';
            }
	    	
			$jsonArrRespuesta = json_encode($arrRespuesta);
			echo $jsonArrRespuesta;
			
    	}
    	
    }    
    
}

?>
