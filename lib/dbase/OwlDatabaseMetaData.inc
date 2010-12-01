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
 * Objeto que contiene meta-información de una base de datos.
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Daniel Sánchez López (Código descargado desde http://www.dslprog.com y adaptado a Owl)
 * @version 0.5.4
 * @since 0.3
 * 
 */

require_once 'dbase/OwlConnection.inc';


class OwlDatabaseMetaData{

    /**
     * Objeto de conexión con la base de datos.
     * @var Connection
     * @access private
     */
    private $_db;

    /**
     * Array con las tablas de la base de datos.
     * @var array
     * @access private
     */
    private $_tables = array();

    /**
     * Array indexado por nombre de tabla donde se guarda la meta-información de cada tabla.
     * @var array
     * @access private
     */
    private $_tablesMetaData = array();

    /**
     * Extrae la meta-información de la base de datos.
     */
    private function _extractDatabaseMetaData(){

        // Cargar las tablas
        if( !$result = $this->_db->executeQuery("SHOW TABLES") ){
	        return false;
	    }

		while( $row = $this->_db->fetchRow() ){
			foreach( $row as $key => $value ){
				$this->_tables[] = $row[$key];
			}
		}

		// Obtenemos los meta-datos de cada tabla.
		foreach( $this->_tables as $table ){
		    $this->_extractTableMetaData( $table );
		}

		return true;
    }

    /**
     * Extrae la meta-información de una tabla.
     * @param string $tableName
     * @access private
     */
    private function _extractTableMetaData( $tableName ){
        
	    $error = false;

	    $this->_tablesMetaData[$tableName] = array(
            "fields"=>array(),
            "primaryKeys"=>array(),
            "foreignKeys"=>array(),
		);
		$tableMetaData =& $this->_tablesMetaData[$tableName];

		if( $result = $this->_db->executeQuery( "SHOW FULL COLUMNS FROM $tableName" ) ){
    		// Recorremos el conjunto de atributos de la tabla.
    		while( $row = $this->_db->fetchRow() ){
    			$ignoreField = false;

    			// Nombre del campo
    			$fieldName = $row["Field"];

    			// Clave primaria
    			$pk = $row["Key"];
    			$pk = ereg("PRI", $pk);

    			// Clave extranjera
    			$fk = $row["Key"];
    			$fk = ereg("MUL", $fk);

    			// Tipo del campo
    			$type = $row["Type"];

    			// Tipo integer, int(?)
    			if( preg_match( '/^int\([0-9]+\)/', $type) ){
    				$type = "integer";

				// Tipo booleano, tinyint(1)
    			}elseif( preg_match( '/tinyint\([0-9]+\)/', $type ) ){
				    $type = "boolean";

				// Tipo String, varchar(?), blob y timestamp
    			}elseif( preg_match( '/(varchar\([0-9]+\))|(text)/', $type) || preg_match( '/blob/', $type) || preg_match( '/timestamp/', $type ) ){
    				$type = "string";

				// Cualquier otro tipo de datos se considerará string.
    			}else{
    			    $type = "string";
    			}

    			// Nulo
    			$null = ($row["Null"] == "YES");

    			// Campo autogenerado
    			$autoincrement = ereg( "auto_increment", $row["Extra"] ) ? true : false;

    			if( !$ignoreField ){
    				$item = array();
    				$item["type"] = $type;
    				$item["primaryKey"] = $pk;
    				$item["foreignKey"] = $fk;
    				$item["null"] = $null;
    				$item["autoIncrement"] = $autoincrement;

    				$tableMetaData["fields"][$fieldName] = $item;
    			}

    			if( $pk ){
    			    $tableMetaData["primaryKeys"][] = $fieldName;
    			}
    		}
		}else{
		    $error = true;
		}

		// Extraemos las claves extranjeras.
		if( $result = $this->_db->executeQuery("SHOW CREATE TABLE $tableName") ){
		    $row = $this->_db->fetchRow();
		    $createTable = $row["Create Table"];

		    $i=0;
		    while( !(($i = strpos($createTable, "FOREIGN KEY", $i)) === false )  ){

    		    $i = strpos($createTable, "(", $i)+2;
    		    $j = strpos($createTable, ")", $i)-1;
    		    $foreignKeys = substr($createTable, $i, $j-$i );

    		    $foreignKeys = str_replace("`","",$foreignKeys);
    		    $foreignKeys = str_replace(" ","",$foreignKeys);
    		    $foreignKeys = explode(",", $foreignKeys);

    		    $i = strpos($createTable, "REFERENCES", $i);

    		    $i = strpos($createTable, "`", $i)+1;
    		    $j = strpos($createTable, "`", $i+1);
    		    $relatedTable = substr( $createTable, $i, $j-$i );

    		    $i = strpos($createTable, "(", $i)+2;
    		    $j = strpos($createTable, ")", $i)-1;
    		    $references = substr($createTable, $i, $j-$i );

    		    $references = str_replace("`","",$references);
    		    $references = str_replace(" ","",$references);
    		    $references = explode(",",$references);

    		    $item = array();
    		    $item["fields"] = $foreignKeys;
    		    $item["relatedTable"] = $relatedTable;
    		    $item["references"] = $references;

    		    $tableMetaData["foreignKeys"][] = $item;
		    }
		}else{
		    $error = true;
		}

		return !$error;
    }

    /**
     * Constructor
     * @param Connection $db
     * @return DatabaseMetaData
     */
    public function __construct( $db ){
        
        $this->_db = $db;

        $this->_extractDatabaseMetaData();
        
    }

    /**
     * Obtiene el tipo PHP de un campo.
     * @param string $tableName Nombre de la tabla a la que pertenece el campo.
     * @param string $fieldName Nombre del campo.
     * @return string
     */
    public function getFieldType( $tableName, $fieldName ){
        return $this->_tablesMetaData[$tableName]["fields"][$fieldName]["type"];
    }

    /**
     * Obtiene un array con los nombres de las tablas de la base de datos.
     * @return array
     */
    public function getTables(){
        
        $tables = array();
        foreach( $this->_tablesMetaData as $tableName => $metaData ){
            $tables[] = $tableName;
        }
        return $tables;
        
    }

    /**
     * Obtiene un array con los campos de la tabla especificada.
     * @param string $tableName
     * @return array
     */
    public function getTableFields( $tableName ){
        
        $fields = array();
        foreach( $this->_tablesMetaData[$tableName]["fields"] as $fieldName => $fieldData ){
            $fields[] = $fieldName;
        }
        return $fields;
        
    }

    /**
     * Obtiene un array con los nombres de los campos que forman la clave primaria de la tabla especificada.
     * @param string $tableName
     * @return array
     */
    public function getTablePrimaryKeys( $tableName ){
        return $this->_tablesMetaData[$tableName]["primaryKeys"];
    }

    /**
     * Obtiene array indexado con las claves extranjeras de la tabla especificada en el siguiente formato:
     * <ul>
     *  <li>"fields" => Array de campos que forman la clave extranjera.</li>
     *  <li>"relatedTable" => Tabla a la que se hace referencia.</li>
     *  <li>"references" => Array de campos de la tabla relacionada a la que hacen referencia los campos de la tabla actual.</li>
     * </ul>
     *
     * @param string $tableName
     * @return array
     */
    public function getTableForeignKeys( $tableName ){
        return $this->_tablesMetaData[$tableName]["foreignKeys"];
    }

    /**
     * Devuelve true si el campo de la tabla es autogenerado.
     *
     * @param string $tableName
     * @param string $fieldName
     * @return boolean
     */
    public function isFieldAutoincrement( $tableName, $fieldName ){
        return $this->_tablesMetaData[$tableName]["fields"][$fieldName]["autoIncrement"];
    }
}
?>