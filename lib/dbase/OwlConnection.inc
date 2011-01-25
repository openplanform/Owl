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
 * Objeto de conexión con bases de datos.
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

require_once 'dbase/OwlDatabaseMetaData.inc';


class OwlConnection{
    
	/**
	 * Enlace de connexion a la base de datos
	 * @var int
	 */
	private $_link;

	/**
	 * Contiene los datos de la última consulta realizada.
	 * @var array
	 */
	private $_lastResource;

	/**
	 * Array con el historial de consultas realizadas.
	 * @var array
	 */
	private $_log = array();

	/**
	 * Constructor
	 * @param $config array 
	 */
	public function __construct( $config ){
	    
		$this->_link = mysql_connect( $config['host'], $config['username'], $config['password'] );
		
		if (!$this->_link ) {
    		throw new OwlException('No se ha podido conectar con la base de datos: '.mysql_error(), 500);
		}
		if( $config['dbname'] != '' ){
            mysql_select_db( $config['dbname'], $this->_link);
		}

		// Establecemos la codificación de caracteres de la conexión.
		if( true ){
            mysql_query("SET NAMES utf8", $this->_link);
		}
		
		// Se vaciará cualquier log existente
		if (array_key_exists('dbLog', $GLOBALS)){
		    $GLOBALS['dbLog'] = null;
		}
		
	}

	/**
	 * Comienza una transacción.
	 *
	 */
	public function begin(){
	    $this->executeQuery("BEGIN");
	}

	/**
	 * Cierra la connexión con la base de datos.
	 *
	 */
	public function close(){
	    mysql_close($this->_link);
	}

	/**
	 * Finaliza una transacción.
	 *
	 */
    public function commit(){
        return $this->executeQuery("COMMIT");
    }

    /**
     * Devuelve el log de consultas en formato HTML.
     * @return string
     */
    public function getLogHTML(){
        
        $log = '<p>SQL Log: '.count($this->_log) .' consultas.</p>';
        $log .= empty($this->_log) ? '' : '<ul>' . implode( null, $this->_log ) . '</ul>';
        
        return $log;
        
    }

    /**
     * Cancela una transacción.
     */
    public function rollback(){
        $this->executeQuery("ROLLBACK");
    }
    
    /**
     * En caso de existir un valor global de almacenamiento para 
     * el log de sql, lo actualizará
     */
    private function _updateLog(){
        
        if (array_key_exists('dbLog', $GLOBALS)){
            $GLOBALS['dbLog'] = $this->getLogHTML();
        }
        
    }

	/**
	 * Ejecuta una consulta en la base de datos.
	 * Devuelve true si la consulta tuvo exito. En caso contrario devuelve false.
	 * 
	 * @param string $sql
	 * @return boolean
	 */
	public function executeQuery( $sql ){
	    
	    $result = mysql_query( $sql, $this->_link );
		if( $result ){
		    $this->_lastResource = $result;
		    $afectedRows = mysql_affected_rows();
		    $this->_log[] = '<li class="correct">'.$sql.' (OK) <strong>[' . $afectedRows . ' ' . (intval($afectedRows) == 1 ? 'row' : 'rows') .']</strong></li>';
		    $this->_updateLog();
		    return true;
		}
		
		$this->_log[] = '<li class="error"><strong>'.$sql.' (ERROR) </strong><br />' . mysql_error().'"</li>';
		$this->_updateLog();
		
		return false;
		
	}

	/**
	 * Obtiene una nueva fila del conjunto de resultados obtenidos en la última consulta.
	 * Si no hay filas, devuelve false.
	 * @return array
	 */
	public function fetchRow(){

		// Se previene un warning
		if (is_resource($this->_lastResource)){
			return mysql_fetch_assoc( $this->_lastResource );
		} 
		
		return false;
		
	}

	/**
	 * Obtiene el último valor autogenerado.
	 * @return integer
	 */
	public function getLastInsertId(){
	    
	    $result = mysql_query("SELECT LAST_INSERT_ID()");
	    $row = mysql_fetch_assoc($result);
	    
	    return $row['LAST_INSERT_ID()'];
	    
	}

	/**
	 * Obtiene un array con las bases de datos del sistema.
	 * @return array
	 */
	public function getDatabases(){
	    
	    $databases = array();
	    $this->executeQuery("SHOW DATABASES");
	    while( $row = $this->fetchRow() ){
	        $databases[] = $row["Database"];
	    }
	    
	    return $databases;
	    
	}

	/**
	 * Obtiene la meta-información de la base de datos actual.
	 * @return DatabaseMetaData
	 */
	public function getDatabaseMetaData(){
	    return new OwlDatabaseMetaData( $this );
	}

	/**
	 * Devuelve el historial de consultas.
	 *
	 * @return array
	 */
	public function getLog(){
	    return $this->_log;
	}
	
	/**
	 * Selecciona la base de datos actual
	 * @param $databaseName
	 */
	public function setDatabase($databaseName){
	    
	    return mysql_select_db( $databaseName, $this->_link);
	    
	}
	
	/**
	 * Devuelve el identificador único de conexión
	 * @return string
	 */
	public function getLinkIdentifier(){
	    
	    return $this->_link;
	    
	}
	
	
	/**
	 * Desactiva la comprobación de claves foráneas
	 * @return boolean
	 */
	public function disableForeignChecks(){
		
		return $this->executeQuery("SET FOREIGN_KEY_CHECKS = 0");
		
	}
	
	
	/** 
	 * Activa la comprobación de claves foráneas
	 * @return boolean
	 */
	public function enableForeignChecks(){
		
		return $this->executeQuery("SET FOREIGN_KEY_CHECKS = 1");		
		
	}
	
}
?>