<?php
/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Data Object genérico.
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

require_once 'dbase/NingenConnection.inc';
require_once 'dbase/NingenGenericDO.inc';


class NingenSqlCollection{

    /**
     * Conexión con la base de datos.
     * @var Connection
     */
    private $_db;

    /**
     * Select
     * @var string
     */
    private $_select = "*";

    /**
     * From
     * @var string
     */
    private $_from = "";

    /**
     * Clauses
     * @var array
     */
    private $_clauses = array();

    /**
     * Joins
     * @var array
     */
    private $_joins = array();

    /**
     * Order by
     * @var string
     */
    private $_orderBy = "";

    /**
     * Constructor
     * @param Connection $db
     * @return SQLCollection
     */
    public function __construct( $db ){
        $this->_db = $db;
    }

    public function addWhereClause( $clause ){
        $this->_clauses[] = $clause;
    }

    public function addJoin( $join ){
        $this->_joins[] = $join;
    }

    public function setSelect( $sql ){
        $this->_select = $sql;
    }

    public function setFrom( $from ){
        $this->_from = "FROM $from";
    }

    public function setOrderBy( $orderBy ){
        $this->_orderBy = "ORDER BY $orderBy";
    }

    /**
     * Search
     * @param $page
     * @param $itemsPerPage
     * @param $className
     */
    public function search( $page, $itemsPerPage, $className ){
        
        $joins = "";
        $clauses = "";
        $totalRows = 0;
        $items = array();

        $first = ($page-1) * $itemsPerPage;

        if( !empty( $this->_joins ) ){
            $joins .= implode( " ", $this->_joins );
        }
        if( !empty( $this->_clauses ) ){
            $clauses .= "WHERE ".implode( " AND ", $this->_clauses );
        }

        $sql = array( "SELECT count(*) as totalRows", $this->_from, $joins, $clauses );
        $this->_db->executeQuery( implode(" ",$sql) );
        $row = $this->_db->fetchRow();
        if( $row ){
            $totalRows = $row["totalRows"];

            $sql = array( "SELECT ".$this->_select, $this->_from, $joins, $clauses, $this->_orderBy, "LIMIT $first,$itemsPerPage" );
            $items = GenericDO::createCollection( $this->_db, implode( " ", $sql ), $className );
        }

        return array("total"=>$totalRows, "items"=>$items );
        
    }
}
?>