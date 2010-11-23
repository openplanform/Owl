<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Generador de Data Objets.
 * 
 * @category dslDoGen
 * @package dslDoGen
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Daniel Sánchez López (Código descargado desde http://www.dslprog.com y adaptado a ningenCMS)
 * 
 * @version 0.6
 * @since 0.5
 * 
 **/

require_once 'dbase/NingenDatabaseMetaData.inc';
require_once 'dbase/NingenConnection.inc';


class NingenDogen{

    /**
     * Version del objeto.
     * @var string
     */
    private $_version = "v.0.6";

	/**
	 * Directorio donde se guardan los archivos generados.
	 * @var string
	 */
	private $_generatedCodeDir = "generatedCode";

	/**
	 * Conjunto de idiomas soportados.
	 * @var array
	 */
	private $_languages = array(
	
	   'es',   // Castellano
	   'ca',   // Catalán
	   'en',   // Inglés
	   'fr',   // Francés
	   'de',   // Alemán
	
	);

	/**
	 * Cadena iso con el idioma por defecto. Utilizado 
	 * para obtener el tipo de un campo multi-idioma.
	 * @var string
	 */
	private $_defaultLang = "es";

	/**
	 * Objeto de connexión con la base de datos.
	 * @var Connection
	 */
	private $_db;

	/**
	 * Prefijo de aplicación.
	 * @var string
	 */
	private $_appPrefix = "";

	/**
	 * Objeto que contiene la meta-información 
	 * de la base de datos.
	 * @var DatabaseMetaData
	 */
	private $_databaseMetaData;

	/**
	 * Copia un archivo.
	 * @param Ruta origen $from
	 * @param Ruta destino $to
	 */
	private function _copyFile( $from, $to ){
	    
	    if( !copy( $from, $to ) ){
		    echo "<p><strong>Error: No se ha podido copiar el archivo \"$from\" en \"$to\"</strong></p>";
		}
		
	}

	/**
	 * Imprime el código del método constructor del DO.
	 * @param string $tableName
	 */
	private function _echoConstructor( $tableName ){
	    
	    $className = $this->_strToClass( $tableName );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Constructor";
	    echo "\n     */";
	    echo "\n    public function __construct( \$db, \$data=null ){\n";
	    echo "\n        if( \$data ){";
	    echo "\n            \$this->_setData(\$data);";
	    echo "\n        }";
	    echo "\n        \$this->_db = \$db;\n";
	    echo "\n    }";
	    
	}

	/**
	 * Inicio del archivo del DO generado.
	 * @param string $tableName
	 */
	private function _echoDOHeader( $tableName ){
	    
	    $className = $this->_strToClass( $tableName );

	    echo "<?php";

	    echo "\n/**";
	    echo "\n * Este archivo ha sido generado con Ningen DoGen ".$this->getVersion();
	    echo "\n * el ".strftime("%d de %B de %Y a las %H:%M:%S");
	    echo "\n * @package dataAccess";
	    echo "\n */";
	    echo "\n";
	    echo "\n/**";
	    echo "\n * Archivos requeridos.";
	    echo "\n */";
	    
	    //echo "\nrequire_once( INCLUDE_DIR.'sql/ConnectionCfg.inc');";
	    
	    echo "\nrequire_once( 'dbase/NingenConnection.inc');";
	    echo "\nrequire_once( 'dbase/NingenGenericDO.inc');";
	    echo "\nrequire_once( '${className}Search.inc' );";
	    echo "\nrequire_once( '${className}PK.inc' );";
	    
	}

	/**
	 * Inicio del archivo del DOSearch generado.
	 */
	private function _echoDOSearchHeader(){
	    
	    echo "<?php";

	    echo "\n/**";
	    echo "\n * Este archivo ha sido generado con Ningen Dogen ".$this->getVersion();
	    echo "\n * el ".strftime("%d de %B de %Y a las %H:%M:%S");
	    echo "\n * @package dataAccess";
	    echo "\n */";
	    
	}

	/**
	 * Inicio del archivo del DOPK generado.
	 */
	private function _echoDOPKHeader(){
	    
	    echo "<?php";

	    echo "\n/**";
	    echo "\n * Este archivo ha sido generado con Ningen Dogen ".$this->getVersion();
	    echo "\n * el ".strftime("%d de %B de %Y a las %H:%M:%S");
	    echo "\n * @package dataAccess";
	    echo "\n */";
	    
	}

	/**
	 * Fin del archivo del DO generado.
	 */
	private function _echoDOFoot(){
	    
	    echo "\n?>";
	    
	}

	/**
	 * Inicio de la clase del DO.
	 * @param string $tableName
	 * @param string $baseClass Clase de la que deriva el DO. Por defecto GenericDO.
	 */
	private function _echoDOClassBegin( $tableName, $baseClass="NingenGenericDO" ){
	    
	    $className = $this->_appPrefix.$this->_strToClass($tableName);
	    $fields = $this->_databaseMetaData->getTableFields( $tableName );

	    echo "\n";
	    echo "\n/**";
	    echo "\n * Objeto para acceder a la tabla $tableName.";
	    echo "\n *";
	    echo "\n * @package dataAccess";
	    echo "\n */";
	    echo "\nclass $className extends $baseClass{";

	    foreach( $fields as $fieldName ){
	        echo "\n";
            echo "\n    /**";
            echo "\n     * Atributo que representa el campo \"$fieldName\"";
            //echo "\n     *";
            echo "\n     * @var ".$this->_databaseMetaData->getFieldType($tableName, $fieldName );
            echo "\n     */";
	        echo "\n    public \$".$this->_strToVariable($fieldName).';';
	    }
	    
	}

	/**
	 * Inicio de la clase del DOSearch.
	 * @param string $className
	 */
	private function _echoDOSearchClassBegin( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass($tableName);

	    echo "\n";
	    echo "\n/**";
	    echo "\n * Objeto para pasar parámetros de búsqueda al objeto $className.";
	    echo "\n *";
	    echo "\n * @package dataAccess";
	    echo "\n */";
	    echo "\nclass ${className}Search{";
	    
	}

	/**
	 * Inicio de la clase del DOPK.
	 * @param string $tableName
	 */
	private function _echoDOPKClassBegin( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass($tableName);

	    echo "\n";
	    echo "\n/**";
	    echo "\n * Objeto que representa la clave primaria de la tabla $tableName.";
	    echo "\n *";
	    echo "\n * @package dataAccess";
	    echo "\n */";
	    echo "\nclass ${className}PK{";
	    
	}

	/**
	 * Fin de la clase del DO.
	 */
	private function _echoDOClassEnd(){
	    
	    echo "\n}";
	    
	}

	/**
	 * Imprime el código de un método get???.
	 * @param string $tableName Nombre de la tabla.
	 * @param string $fieldName Nombre del campo.
	 */
	private function _echoGetMethod( $tableName, $fieldName ){
	    
	    $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $fieldName );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n      * Obtiene el valor del atributo '$fieldName'.";
	    echo "\n      *";
	    echo "\n      * @return $fieldType";
	    echo "\n      */";

        // Para los campos de tipo "boolean", escribimos el metodo isX.
        if( $fieldType == "boolean" ){

    	    echo "\n    public function ".$this->_strToIsMethod($fieldName)."(){";
            echo "\n        return (\$this->".$this->_strToVariable($fieldName)." ? true : false);";
            echo "\n    }";

        }else{

            echo "\n    public function ".$this->_strToGetMethod($fieldName)."(){";
            echo "\n        return \$this->".$this->_strToVariable($fieldName).";";
            echo "\n    }";

        }
        
	}

	/**
	 * Imprime el código de un método "get", que obtiene los DOs relacionados con el DO actual.
	 * @param string $table
	 * @param string $relatedTable
	 */
	private function _echoGetRelatedDOsMethod( $table, $relatedTable ){
	    
	    $class = $this->_strToClass( $table );
	    $relatedClass = $this->_strToClass( $relatedTable );

	    $params = array();
	    $pks = $this->_databaseMetaData->getTablePrimaryKeys( $table );
	    foreach( $pks as $pk ){
	        $params[] = '$this->'.$this->_strToVariable($pk);
	    }
	    $params = implode( ", ", $params );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Obtiene todos los elementos relacionados de la tabla '$relatedTable'";
	    echo "\n     *";
	    echo "\n     * @param Connection \$db Conexión con la base de datos.";
	    echo "\n     * @param string \$orderBy Cadena con los campos de ordenación separados por comas.";
	    echo "\n     */";
	    echo "\n    public function get".$this->_strToClassPlural( $relatedTable )."( \$orderBy='' ){\n";
	    echo "\n        include_once('${relatedClass}.inc');";
	    echo "\n        return $relatedClass::findBy$class( \$this->_db, $params, \$orderBy );\n";
	    echo "\n    }";
	    
	}

	/**
	 * Imprime el código de un método get??? segun el idioma.
	 * @param string $tableName Nombre de la tabla.
	 * @param string $fieldName Nombre del campo.
	 */
	private function _echoGetMethodMultiLang( $tableName, $fieldName ){
	    
	    $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $fieldName.'_'.$this->_defaultLang );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n      * Obtiene el valor de la atributo '$fieldName' según el idioma activo.";
	    echo "\n      *";
	    echo "\n      * @return $fieldType";
	    echo "\n      * @see NingenGenericDO::setLang()";
	    echo "\n      */";
	    echo "\n    public function ".$this->_strToGetMethod($fieldName)."(){\n";
	    echo "\n        \$attribute = '".$this->_strToVariable($fieldName)."'.ucfirst(\$this->getLang());";
        echo "\n        return \$this->\$attribute;\n";
        echo "\n    }";
        
	}

	/**
	 * Imprime el código del método _setData
	 * @param string $tableName
	 */
	private function _echoSetDataMethod( $tableName ){
	    
	    $fields = $this->_databaseMetaData->getTableFields($tableName);

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Asigna los valores de los atributos del DO utilizando los valores de la variable \$data.";
	    echo "\n     *";
	    echo "\n     * @param array \$data";
	    echo "\n     */";
	    echo "\n    private function _setData( \$data ){\n";
	    echo "\n        \$this->_data = \$data;";

	    foreach( $fields as $fieldName ){
	        echo "\n        \$this->".$this->_strToVariable($fieldName)." = \$data['$fieldName'];";
	    }

	    echo "\n\n    }";
	    
	}

	/**
	 * Imprime el código de un método setAtributo
	 * @param string $fieldName
	 */
	private function _echoSetMethod( $tableName, $fieldName ){
	    
	    $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $fieldName );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n      * Establece el valor del atributo '$fieldName'.";
	    echo "\n      *";
	    echo "\n      * @param $fieldType Valor.";
	    echo "\n      */";
        echo "\n    public function ".$this->_strToSetMethod($fieldName)."( \$value ){\n";
        echo "\n        \$this->".$this->_strToVariable($fieldName)." = \$value;\n";
	    echo "\n    }";
	    
	}

	/**
	 * Imprime el código de un método setAtributo segun el idioma.
	 * @param string $tableName Nombre de la tabla.
	 * @param string $fieldName Nombre del campo.
	 */
	private function _echoSetMethodMultiLang( $tableName, $fieldName ){
	    
	    $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $fieldName.'_'.$this->_defaultLang );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n      * Establece el valor del atributo '$fieldName' según el idioma activo.";
	    echo "\n      *";
	    echo "\n      * @param $fieldType \$value Valor.";
	    echo "\n      * @see NingenGenericDO::setLang()";
	    echo "\n      */";
        echo "\n    public function ".$this->_strToSetMethod($fieldName)."( \$value ){\n";
        echo "\n        \$attribute = '".$this->_strToVariable($fieldName)."'.ucfirst(\$this->getLang());";
        echo "\n        \$this->\$attribute = \$value;\n";
	    echo "\n    }";
	    
	}

	/**
	 * Imprime el código de los métodos findByPrimaryKey y findByPKObject.
	 * @param string $tableName Nombre de la tabla.
	 */
	private function _echoFindByPKMethod( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass($tableName);

	    $fields = $this->_databaseMetaData->getTablePrimaryKeys( $tableName );

	    $params = array();
	    foreach( $fields as $field ){
	        $params[] = $this->_strToVariable($field);
	    }
	    $paramsStr = '$'.implode(", $", $params);

	    $where = array();
	    foreach( $fields as $field ){
	        $variableName = $this->_strToVariable($field);
            $where[] = "$field = '\$$variableName'";
	    }
	    $whereStr = implode(" AND ",$where);

	    // Método findByPrimaryKey

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Obtiene el elemento de la tabla $tableName que coincide con la clave primaria especificada.";
	    echo "\n     *";
	    echo "\n     * @param Connection \$db Conexión con la base de datos.";

	    foreach( $fields as $field ){
	        $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $field );
	        echo "\n     * @param $fieldType \$".$this->_strToVariable($field)." valor del campo '$field'.";
	    }

	    echo "\n     * @return $className";
	    echo "\n     */";
	    echo "\n    public static function findByPrimaryKey( \$db, $paramsStr ){\n";
        echo "\n       \$db->executeQuery(\"SELECT * FROM $tableName WHERE $whereStr\");";
	    echo "\n       \$data = \$db->fetchRow();";
        echo "\n       return NingenGenericDO::createDO( \$db, \$data, '$className');\n";
        echo "\n    }";

	    // Método findByPKObject

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Obtiene el elemento de la tabla $tableName que coincide con la clave primaria especificada.";
	    echo "\n     *";
	    echo "\n     * @param Connection \$db Conexión con la base de datos.";
	    echo "\n     * @param ${className}PK \$pk Objeto de la clave primaria.";
	    echo "\n     * @return $className";
	    echo "\n     */";
	    echo "\n    public static function findByPKObject( \$db, \$pk ){\n";
	    echo "\n        \$where = array();";

	    foreach( $fields as $fieldName ){
	        $variableName = $this->_strToVariable($fieldName);
	        echo "\n        \$where[]=\"$fieldName='\".\$pk->$variableName.\"'\";";
	    }

	    echo "\n        \$where = implode(' AND ',\$where);";
        echo "\n        \$db->executeQuery(\"SELECT * FROM $tableName WHERE \$where\");";
	    echo "\n        \$data = \$db->fetchRow();";
        echo "\n        return NingenGenericDO::createDO( \$db, \$data, '$className');\n";
        echo "\n    }";
        
	}

	/**
	 * Imprime un método de búsqueda
	 * @param unknown_type $tableName
	 */
	private function _echoFindMethod( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass( $tableName );
	    $fields = $this->_databaseMetaData->getTableFields( $tableName );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Realiza una búsqueda en la tabla $tableName segun los atributos asignados en \$searchItem.";
	    echo "\n     *";
	    echo "\n     * @param Connection \$db Conexión con la base de datos.";
	    echo "\n     * @param ${className}Search \$searchItem Objeto con los atributos de búsqueda.";
	    echo "\n     * @param string \$orderBy Cadena con los campos de ordenación separados por comas.";
	    echo "\n     */";
	    echo "\n    public static function find( \$db , \$searchItem, \$orderBy='' ){\n";
	    echo "\n        \$sql = 'SELECT * FROM $tableName';";
	    echo "\n        \$where = array();";

	    foreach( $fields as $fieldName ){
	       $variable = $this->_strToVariable( $fieldName );
	       echo "\n        if( \$tmp = \$searchItem->$variable ){";
	       echo "\n            \$where[] = \"$fieldName='\$tmp'\";";
	       echo "\n        }";
	    }
	    echo "\n        if( count(\$where) > 0 ){";
	    echo "\n            \$where = implode( ' and ', \$where );";
	    echo "\n            \$sql.=' WHERE '.\$where;";
	    echo "\n        }";
	    echo "\n        if( \$orderBy != '' ){";
	    echo "\n            \$sql.=\" ORDER BY \$orderBy\";";
	    echo "\n        }";
	    echo "\n        return NingenGenericDO::createCollection( \$db, \$sql, '$className' );";
	    echo "\n}";
	    
	}

	/**
	 * Imprime el código del método findAll.
	 * @param string $tableName
	 */
	private function _echoFindAllMethod( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass($tableName);

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Obtiene todas las filas de la tabla $tableName.";
	    echo "\n     *";
	    echo "\n     * @param Connection \$db Conexión con la base de datos.";
	    echo "\n     * @param string \$orderBy Cadena con los campos de ordenación separados por comas.";
	    echo "\n     * @return array";
	    echo "\n     */";
        echo "\n    public static function findAll( \$db, \$orderBy='' ){";
        echo "\n         \$sql = 'SELECT * FROM $tableName';" ;
        echo "\n         if( \$orderBy != '' ){";
        echo "\n             \$sql .= \" ORDER BY \$orderBy\";";
        echo "\n         }";
        echo "\n         return NingenGenericDO::createCollection( \$db, \$sql, '$className' );";
        echo "\n    }";
        
	}

	/**
	 * Imprime el código del método findBy{clave extranjera}
	 * @param string $tableName
	 * @param string $fields
	 * @param string $relatedTable
	 */
	private function _echoFindByFKMethod( $tableName, $fields, $relatedTable ){
	    
	    $className = $this->_appPrefix.$this->_strToClass( $tableName );
	    $relatedClass = $this->_strToClass($relatedTable);

	    $params = array();
	    $where = array();
	    foreach( $fields as $field ){
            $param = '$'.$this->_strToVariable($field);
            $where[] = $field."='$param'";
            $params[] = $param;
	    }
	    $params = implode(",", $params);
	    $where = implode(",", $where);

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Obtiene todas las filas de la tabla $tableName que coinciden con el criterio $where.";
	    echo "\n     *";
	    echo "\n     * @param Connection \$db Conexión con la base de datos.";

	    foreach( $fields as $field ){
	        $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $field );
	        echo "\n     * @param $fieldType ".$this->_strToVariable($field)." string Valor del campo $field.";
	    }

	    echo "\n     * @param string \$orderBy Cadena con los campos de ordenación separados por comas.";
	    echo "\n     * @return array";
	    echo "\n     */";
	    echo "\n     public static function findBy$relatedClass( \$db, $params, \$orderBy='' ){";
	    echo "\n         \$sql = \"SELECT * FROM $tableName WHERE $where\";";
	    echo "\n         if( \$orderBy != '' ){";
	    echo "\n             \$sql .= \" ORDER BY \$orderBy\";";
	    echo "\n         }";
	    echo "\n         return NingenGenericDO::createCollection( \$db, \$sql, '$className' );";
	    echo "\n     }";
	    
    }

	/**
	 * Imprime el código del metodo delete.
	 * @param string $tableName Nombre de la tabla de la que eliminar un registro.
	 */
	private function _echoDeleteMethod( $tableName ){

	    $primaryKeys = $this->_databaseMetaData->getTablePrimaryKeys( $tableName );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Borra una fila de la tabla $tableName.";
	    echo "\n     */";
	    echo "\n    public function delete(){";
        echo "\n        \$where = array();";
	    foreach( $primaryKeys as $fieldName ){
           echo "\n        \$where[] = \"$fieldName=\".\"'\".addslashes(\$this->".$this->_strToVariable($fieldName).").\"'\";";
	    }
	    echo "\n        \$where = implode(\" AND \", \$where);";
	    echo "\n        return \$this->_db->executeQuery(\"DELETE FROM $tableName WHERE \$where\");";
	    echo "\n    }";
	    
	}

	/**
	 * Escribe el código de de un método get que obtiene un DO de una tabla relacionada.
	 * @param array $foreignKeys
	 * @param string $relatedTable
	 */
	private function _echoGetRelatedDOMethod( $foreignKeys, $relatedTable ){
	    
	    $className = $this->_appPrefix.$this->_strToClass($relatedTable);
	    $methodName = $this->_strToGetMethod( $relatedTable );

	    $params = array();
	    foreach( $foreignKeys as $fk ){
	        $params[] = '$this->'.$this->_strToVariable($fk);
	    }
	    $params = implode(', ', $params );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Obtiene el objeto '$className' relacionado.";
	    echo "\n     *";
	    echo "\n     * @return $className";
	    echo "\n     */";
	    echo "\n    public function $methodName(){";
	    echo "\n        require_once('$className.inc');";
	    echo "\n        return $className::findByPrimaryKey( \$this->_db, $params );";
	    echo "\n    }";
	    
	}

	/**
	 * Escribe el código de de un método set que asigna un DO de una tabla relacionada.
	 * @param array $foreignKeys Array de campos que forman una clave extranjera.
	 * @param string $relatedTable
	 */
	private function _echoSetRelatedDOMethod( $foreignKey, $relatedTable ){
	    
	    $className = $this->_appPrefix.$this->_strToClass($relatedTable);
	    $methodName = $this->_strToSetMethod( $relatedTable );
	    $relatedTablePrimaryKey = $this->_databaseMetaData->getTablePrimaryKeys($relatedTable);

	    $relations = array();
	    for($i=0; $i<count($foreignKey); $i++){
	        $relations[] = array($foreignKey[$i],$relatedTablePrimaryKey[$i]);
	    }

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Asigna el objeto '$className' relacionado.";
	    echo "\n     *";
	    echo "\n     * @param $className \$dataObject";
	    echo "\n     */";
	    echo "\n    public function $methodName( \$dataObject ){";
	    echo "\n        require_once('$className.inc');";

	    foreach( $relations as $relation ){
	       list($fk,$pk) = $relation;

           $var = $this->_strToVariable($fk);
           $getX = $this->_strToGetMethod( $pk );
           $setX = $this->_strToSetMethod( $var );
	       echo "\n        \$this->$setX( \$dataObject->$getX() );";
	    }
	    echo "\n    }";
	    
	}

	/**
	 * Imprime el código del método update.
	 * @param string $tableName Nombre de la tabla que se actualizará
	 */
	private function _echoUpdateMethod( $tableName ){
	    
	    $fields = $this->_databaseMetaData->getTableFields($tableName);
	    $primaryKeys = $this->_databaseMetaData->getTablePrimaryKeys($tableName);

	    $clauses = array();
	    foreach( $primaryKeys as $fieldName ){
	        $clauses[] = "$fieldName='\".addslashes(\$this->_data['$fieldName']).\"'";
	    }
	    $whereStr = implode(" AND ", $clauses);

	    echo "\n";
	    echo "\n    /**";
	    echo "\n     * Actualiza una fila de la tabla $tableName.";
	    echo "\n     */";
	    echo "\n    public function update(){";
	    echo "\n        \$sets = array();";
	    foreach( $fields as $fieldName ){
	        if( !$this->_databaseMetaData->isFieldAutoincrement( $tableName, $fieldName ) ){
	           echo "\n        \$sets[] = '$fieldName=' . ( ( ( \$value = \$this->".$this->_strToVariable($fieldName)." ) === null || !isset(\$this->".$this->_strToVariable($fieldName).") ) ? 'null' :  \"'\".addslashes(\$value).\"'\" );";
	        }
	    }
	    echo "\n        \$setStr = implode(',', \$sets);";
        echo "\n        return \$this->_db->executeQuery(\"UPDATE $tableName SET \$setStr WHERE $whereStr\");";
	    echo "\n    }";
	    
	}

	/**
	 * Imprime el código del método insert
	 * @param array $tableName Nombre de la tabla.
	 */
	private function _echoInsertMethod( $tableName ){
	    
	    $primaryKeys = $this->_databaseMetaData->getTablePrimaryKeys( $tableName );
	    $fields = $this->_databaseMetaData->getTableFields( $tableName );

	    echo "\n";
	    echo "\n    /**";
	    echo "\n      * Inserta una nueva fila en la tabla $tableName.";
	    echo "\n      */";
	    echo "\n    public function insert(){";

	    // Atributos
	    echo "\n        \$attributes = array();";
	    foreach( $fields as $fieldName ){
	        if( !$this->_databaseMetaData->isFieldAutoincrement( $tableName, $fieldName ) ){
	           echo "\n        \$attributes[] = '$fieldName';";
	        }
	    }
	    echo "\n        \$attributes = implode(',', \$attributes);";

	    // Valores
	    echo "\n        \$values = array();";
	    foreach( $fields as $fieldName ){
	        if( !$this->_databaseMetaData->isFieldAutoincrement( $tableName, $fieldName ) ){
	           echo "\n        \$values[] = (( \$value = \$this->".$this->_strToVariable($fieldName)." ) === null || !isset(\$this->".$this->_strToVariable($fieldName).") ) ? 'null' : \"'\".addslashes(\$value).\"'\";";
	        }
	    }
	    echo "\n        \$values = implode(',', \$values);";

	    $pkValues = array();
	    foreach( $primaryKeys as $fieldName ){
	        if( $this->_databaseMetaData->isFieldAutoincrement( $tableName, $fieldName ) ){
	            $pkValues[] = "\$this->_db->getLastInsertId()";
	        }else{
	            $pkValues[] = "\$this->".$this->_strToVariable($fieldName);
	        }
	    }

	    $pkValues = ", ".implode(", ", $pkValues );
	    echo "\n        if( \$this->_db->executeQuery(\"INSERT INTO $tableName(\$attributes) VALUES(\$values)\") ){";
	    echo "\n            \$eleDO = \$this->findByPrimaryKey( \$this->_db".$pkValues." );";
	    echo "\n            \$this->_setData(\$eleDO->_data);";
	    echo "\n            return true;";
	    echo "\n        }";
	    echo "\n        return false;";
	    echo "\n    }";
	    
	}

	/**
	 * Método que genera el Data Object de la tabla especificada.
	 *
	 * @param string $tableName
	 */
	private function _generateDO( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass( $tableName );
		$fp=fopen($className.".inc","wt");

		ob_start();

    		$this->_echoDOHeader( $tableName );
    		$this->_echoDOClassBegin( $tableName );

    		  // Constructor

    		  echo "\n\n    // Constructor";

    		  $this->_echoConstructor( $tableName );

    		  // Método _setData()

    		  $this->_echoSetDataMethod( $tableName );

    		  // Métodos find

    		  echo "\n\n    // Métodos find";

    		  $this->_echoFindMethod( $tableName );

    		  $this->_echoFindAllMethod( $tableName );

    		  $this->_echoFindByPKMethod( $tableName );

    		  foreach( $this->_databaseMetaData->getTableForeignKeys($tableName) as $relation ){
    		      $this->_echoFindByFKMethod( $tableName, $relation["fields"], $relation["relatedTable"] );
    		  }

    		  // Método update
    		  $this->_echoUpdateMethod( $tableName );

    		  // Método insert
    		  $this->_echoInsertMethod( $tableName );

    		  // Método delete
    		  $this->_echoDeleteMethod( $tableName );

    		  // Métodos get y set
    		  foreach( $this->_databaseMetaData->getTableFields($tableName) as $fieldName ){

    		      $this->_echoGetMethod( $tableName, $fieldName );

    		      // Si el campo de la bd es auto generado no tendrá método set.
    		      if( !$this->_databaseMetaData->isFieldAutoincrement($tableName, $fieldName ) ){
    		          $this->_echoSetMethod( $tableName, $fieldName );
    		      }
    		  }

    		  $tables = $this->_databaseMetaData->getTables();
    		  foreach( $tables as $relatedTable ){
    		      $fks = $this->_databaseMetaData->getTableForeignKeys( $relatedTable );
    		      foreach($fks as $fk){
    		          if( $fk["relatedTable"] == $tableName ){
    		              $this->_echoGetRelatedDOsMethod( $tableName, $relatedTable );
    		          }
    		      }
    		  }


    		  // Métodos multi-idioma

    		  // Construimos la expresión regular para saber si un campo es multi-idioma.
              // Concretamente comprobamos si termina en "_es", "_en", "_ca",...
              // La expresión regular sería ((_es)|(_en)|(_ca))$
    		  $pattern = array();
    		  foreach( $this->_languages as $lang ){
    		      $pattern[] = "(_$lang)";
    		  }
    		  $pattern = '('.implode('|', $pattern ).')$';

    		  // Averiguamos que atributos son multi-idioma y los guardamos en un array indexado por nombre del campo,
    		  // colocando true en el valor.
    		  $fields = array();
    		  foreach( $this->_databaseMetaData->getTableFields($tableName) as $fieldName ){

    		      if( ereg( $pattern, $fieldName ) ){
    		          // El campo es multi-idioma

    		          // Guardamos el nombre del campo sin el sufijo del idioma.
    		          $fields[ ereg_replace( $pattern, "", $fieldName) ] = true;
    		      }
    		  }

    		  if( !empty($fields) ){
    		      echo "\n\n    // Métodos multi-idioma.";

        		  // Creamos el método get y set
        		  foreach( array_keys($fields) as $fieldName ){
                      $this->_echoGetMethodMultiLang( $tableName, $fieldName );
                      $this->_echoSetMethodMultiLang( $tableName, $fieldName );
        		  }
    		  }

              // Relaciones

    		  $relations = $this->_databaseMetaData->getTableForeignKeys($tableName);
    		  if( !empty( $relations ) ){
        		  echo "\n\n    // Relaciones";
        		  foreach( $relations as $relation ){
        		      $this->_echoGetRelatedDOMethod( $relation["fields"], $relation["relatedTable"] );
        		      $this->_echoSetRelatedDOMethod( $relation["fields"], $relation["relatedTable"] );
        		  }
    		  }

    		$this->_echoDOClassEnd();
		    $this->_echoDOFoot();
		$content = ob_get_clean();

		fwrite($fp, $content);
		fclose($fp);
		
	}

	/**
	 * Método que genera el objeto de búsqueda para un Data Object.
	 * @param string $tableName
	 */
	private function _generateDOSearch( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass( $tableName );
		$fp=fopen($className."Search.inc","wt");

		$fields = $this->_databaseMetaData->getTableFields( $tableName );

		ob_start();

    		$this->_echoDOSearchHeader();
    		$this->_echoDOSearchClassBegin( $tableName );

    		foreach( $fields as $fieldName ){
                $variable = $this->_strToVariable( $fieldName );
                $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $fieldName );

                echo "\n";
                echo "\n    /**";
                echo "\n     * Representa el atributo $fieldName.";
                echo "\n     *";
                echo "\n     * @var $fieldType";
                echo "\n     */";
    		    echo "\n    public \$$variable;";
    		}

    		$this->_echoDOClassEnd();
		    $this->_echoDOFoot();
		$content = ob_get_clean();

		fwrite($fp, $content);
		fclose($fp);
		
	}

	/**
	 * Método que genera el objeto que representa la clave primaria de un Data Object.
	 * @param string $tableName
	 */
	private function _generateDOPK( $tableName ){
	    
	    $className = $this->_appPrefix.$this->_strToClass( $tableName );
		$fp=fopen($className."PK.inc","wt");

		$fields = $this->_databaseMetaData->getTablePrimaryKeys( $tableName );

		ob_start();

    		$this->_echoDOPKHeader();
    		$this->_echoDOPKClassBegin( $tableName );

    		foreach( $fields as $fieldName ){
                $variable = $this->_strToVariable( $fieldName );

                $fieldType = $this->_databaseMetaData->getFieldType( $tableName, $fieldName );

                echo "\n";
                echo "\n    /**";
                echo "\n     * Representa el atributo $fieldName.";
                echo "\n     *";
                echo "\n     * @var $fieldType";
                echo "\n     */";
    		    echo "\n    public \$$variable;";
    		}

    		$this->_echoDOClassEnd();
		    $this->_echoDOFoot();
		$content = ob_get_clean();

		fwrite($fp, $content);
		fclose($fp);
		
	}

	/**
	 * Método principal de generación de código.
	 * @param Connection $connection
	 * @return boolean
	 */
	function generateCode( $connection ){
	    
		$this->_db = $connection;
		$this->_databaseMetaData = $connection->getDatabaseMetadata();

		$tables = $this->_databaseMetaData->getTables();

		if( count($tables) == 0 ){
			echo "<p>No hay tablas en la base de datos.</p>";
			return false;
		}

		$rootDir = getcwd();

		// Creamos el directorio de destino de los archivos generados y lo ponemos como directorio actual.
		if( !file_exists($this->_generatedCodeDir ) ){
			mkdir( $this->_generatedCodeDir );
		}
		chdir( $this->_generatedCodeDir );

		// Generamos los DOs para cada tabla.
		echo "<p>Generando codigo...</p>";
		for( $i=0; $i<count($tables); $i++ ){

		    $this->_generateDO( $tables[$i] );
	        $this->_generateDOSearch( $tables[$i] );
	        $this->_generateDOPK( $tables[$i] );
		}

		chdir($rootDir);

		// Copiamos los archivos necesarios.
		/*$files = array(
		    "config.inc",
		);
		foreach( $files as $file ){

		    $this->_copyFile( $file, $this->_generatedCodeDir."/".$file );

		}*/
		
		echo "<p>Completado.</p>";
		echo '<p>Archivos creados en el directorio "<strong>'.$this->_generatedCodeDir.'</strong></strong>"</p>';
		return true;
		
	}

	/**
	 * Obtiene la versión.
	 * @return string
	 */
	function getVersion(){
	    return $this->_version;
	}

	/**
	 * Establece el prefijo de aplicación.
	 * @param string $appPrefix
	 */
	function setApplicationPrefix( $appPrefix ){
	    $this->_appPrefix = $appPrefix;
	}

	/**
	 * Establece el directorio de destino para los archivos generados.
	 * @param string $path
	 */
	function setGeneratedCodeDir( $path ){
	    $this->_generatedCodeDir = $path;
	}

	/**
	 * Convierte una cadena al nombre de una clase, utilizando la convención de Java.
	 * @param string $str
	 * @return string
	 */
	private function _strToClass( $str ){
	    return ucfirst( $this->_strToVariable($str) );
	}

	/**
	 * Convierte una cadena al nombre de una clase en plural, utilizando la convención de Java.
	 * @param string $str
	 * @return string
	 */
	private function _strToClassPlural( $str ){
	    return ucfirst( $this->_strToVariable($str) ).'s';
	}

	/**
	 * Convierte una cadena al nombre de su método get.
	 * @param string $str
	 * @return string
	 */
	private function _strToGetMethod( $str ){
	    return ("get".ucfirst($this->_strToVariable($str)));
	}

	/**
	 * Convierte una cadena al nombre de su método isX.
	 * Por ejemplo, para la cadena "used" devolverá "isUsed".
	 * @param string $str
	 * @return string
	 */
	private function _strToIsMethod( $str ){
	    return ("is".ucfirst($this->_strToVariable($str)));
	}

	/**
	 * Convierte una cadena al nombre de su método set.
	 * @param string $str
	 * @return string
	 */
	private function _strToSetMethod( $str ){
	    return "set".ucfirst($this->_strToVariable($str));
	}

	/**
	 * Convierte una cadena a un nombre de una variable, utilizando la convención de Java.
	 * @param string $str
	 * @return string
	 */
	private function _strToVariable( $str ){
	    
	    $parts = explode("_", $str);
	    for($i=1; $i<count($parts); $i++){
	        $parts[$i] = ucfirst($parts[$i]);
	    }
	    return implode(null,$parts);
	    
	}
}
?>