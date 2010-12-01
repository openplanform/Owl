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
require_once 'dbase/OwlGenericDO.inc';


class OwlSqlCollection{

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