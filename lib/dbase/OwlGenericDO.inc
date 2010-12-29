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
 * Data Object genérico.
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


class OwlGenericDO{

    /**
     * Conexión con la base de datos.
     * @var Connection
     */
    protected $_db;

    /**
     * ISO del idioma actual, por defecto español.
     * @var string
     */
    private $_lang = "es";

    /**
     * Contiene los datos extraidos de la base de datos.
     * @var array
     */
    private $_data = array();

    /**
     * Genera una colección de elementos de clase $className a partir de una sentencia sql.
     * @param Connection $db
     * @param string $sql
     * @param string $className
     */
    public static function createCollection( $db, $sql, $className ){
        
        $elemsCOL = array();
        $db->executeQuery($sql);
        while( $row = $db->fetchRow() ){
            $elemsCOL[] = OwlGenericDO::createDO( $db, $row, $className );
        }
        return $elemsCOL;
        
    }

    /**
     * Genera un Data Object de la clase $className utilizando un array indexado con los datos.
     * @param Connection $db
     * @param array $data
     * @param string $className
     * @return OwlGenericDO
     */
    public static function createDO( $db, $data, $className){
        
        if( !empty($data) ){
            return new $className( $db, $data );
        }
        return false;
        
    }

    /**
     * Genera un Data Object de la clase $className utilizando los datos obtenidos de una sentencia sql.
     * @param Connection $db
     * @param string $sql
     * @param string $className
     * @return OwlGenericDO
     */
    public static function createFromQuery( $db, $sql, $className ){
        
        $db->executeQuery($sql);
        if( $row = $db->fetchRow() ){
            return new $className( $db, $row );
        }else{
            return null;
        }
        
    }

    /**
     * Devuelve la conexión con la base de datos.
     * @return Connection
     */
    public function getDb(){
        return $this->_db;
    }

    /**
     * Devuelve la ISO del idioma actual.
     * @return string
     */
    public function getLang(){
        return $this->_lang;
    }

    /**
     * Establece el idioma para una colección de data objects.
     * @param array $col Array de data objects.
     * @param string $lang Iso del idioma.
     */
    public static function setCollectionLang( $col, $lang ){
        
        $length = count($col);
        for($i=0; $i<$length; $i++){
            $do = $col[$i];
            $do->setLang( $lang );
        }
        
    }

    /**
     * Asigna una conexión de bbdd con el objeto.
     * @param Connection $db Conexión con la base de datos.
     */
    public function setDb( $db ){
        $this->_db = $db;
    }

    /**
     * Establece el idioma actual.
     * @param string $lang Cadena con el ISO del idioma actual, "es", "en", "de", "ca", ...
     */
    public function setLang( $lang ){
        $this->_lang = $lang;
    }
}
?>