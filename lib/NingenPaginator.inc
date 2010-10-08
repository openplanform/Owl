<?php

/**
 * NINGEN NOWL (NINGEN Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase que implementa el paginador de resultados
 * 
 * @category NingenNowl
 * @package NingenNowl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es>, Aaron Amengual Arranz <aaron@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 **/

require_once 'NingenException.inc';
require_once 'dbase/NingenGenericDO.inc';


class NingenPaginator{
    
    /**
     * Acceso a base de datos
     * @var NingenConnection
     */
    protected $db;
    
    /**
     * Cantidad de ítems por página
     * @var integer
     */
    protected $itemsPorPagina = 2;
    
    /**
     * Número de página actual
     * @var integer
     */
    protected $paginaActual = 0;
    
    /**
     * Sentencia sql
     * @var string
     */
    protected $sqlWhere;
    
    /**
     * Nombre de la tabla a tratar
     * @var string
     */
    protected $tableName;
    
    /**
     * Colección de ítems a paginar
     * @var array
     */
    protected $itemsCOL;
    
    /**
     * Metadata necesaria para imprimir el paginador
     * @var array
     */
    protected $metadataARR;
    
    /**
     * Cantidad de items total
     * @var integer
     */
    protected $itemsCount = 0;
    
    /**
     * Cantidad de páginas generadas
     * @var integer
     */
    protected $pagesCount = 0;
    
    /**
     * Helper para controladores
     * @var NingenControllerHelper
     */
    protected $helper;
    
    
    /**
     * Constructor, establece los parámetros de funcionamiento. 
     * Si el parámetro sqlWhere no es pasado, se hará un findall del DO indicado.
     * @param NingenConnection $db
     * @param string $sql
     * @param string $tableName
     * @param NingenControllerHelper $helper
     */
    public function __construct(NingenConnection $db, $sqlWhere = null, $tableName, NingenControllerHelper $helper){
        
        // Sin DO nada se puede hacer.
        if (!$this->tableExists($tableName)){
            throw new NingenException('Se está intentando paginar una tabla de la cual no se dispone Dataobject. Error crítico.', 500);
        } else {
            $this->tableName = $tableName;
        }

        $this->db = $db;
        
        $this->sqlWhere = $sqlWhere;
        
        $this->helper = $helper;
        
    }
    
    /**
     * Establece la cantidad de ítems que se mostrarán en una página
     * @param integer $cantidad
     */
    public function setItemsPorPagina($cantidad){
        
        $this->itemsPorPagina = $cantidad;
        
    }
    
    /**
     * Establece el número de página actual
     * @param integer $numeroPagina
     */
    public function setPaginaActual($numeroPagina){
        
        $this->paginaActual = $numeroPagina;
        
    }
    
    /**
     * Verifica si se dispone del dataobject de una tabla, si es 
     * así hace el require necesario.
     * @param string $tableName
     * @return boolean 
     */
    protected function tableExists( $tableName ){
        
        if (file_exists(NINGENCMS_MODELDIR . ucfirst($tableName) . '.inc')){
            
            require_once NINGENCMS_MODELDIR . ucfirst($tableName) . '.inc';
            return true;
            
        }
        
        return false;
        
    }

    /**
     * Obtiene los ítems a listar
     */
    protected function getItems(){
        
        $genericDO = new NingenGenericDO();

        // Generamos los metadatos
        $this->generatePaginatorMetadata();
        
        // Si no hay sql obtendremos todos los items
        if (is_null($this->sqlWhere)){
            $this->sqlWhere = '';
        } 
        
        $sql = 'SELECT * FROM ' . $this->tableName . ' ' . $this->sqlWhere;
        
        // Se prepara el sql a ejecutar
        $limitSql = ' LIMIT ' . $this->itemsPorPagina;
        
        if ($this->paginaActual != 1 || $this->paginaActual == 0){
            
            // Calcularemos el offset
            $offset = $this->itemsPorPagina * ($this->paginaActual - 1);
            $limitSql .= ' OFFSET ' . $offset ;
        }
        
        $this->itemsCOL = $genericDO->createCollection($this->db, $sql . $limitSql , ucfirst($this->tableName));
        
        
        
    }
    
    /**
     * Calcula las páginas y genera la metadata necesaria para imprimir el paginador
     */
    protected function generatePaginatorMetadata(){
        
        // Contaremos los items a paginar
        $sql = 'SELECT COUNT(*) AS total FROM ' . $this->tableName . ' ' . $this->sqlWhere;
        $this->db->executeQuery($sql);
        $row = $this->db->fetchRow();
        $this->itemsCount = intval($row['total']);
        
        // Calculamos las páginas
        $this->pagesCount = round($this->itemsCount / $this->itemsPorPagina);

        // Generamos el array con los metadatos        
        $metadataARR = array();
        $metadataARR['siguiente'] = $this->paginaActual >= 1 && $this->paginaActual < $this->pagesCount; 
        $metadataARR['anterior'] = $this->paginaActual > 1; 
        $metadataARR['paginas'] = $this->pagesCount;
        $metadataARR['paginaActual'] = $this->paginaActual; 
        
        $this->metadataARR = $metadataARR;
        
    }
    
    /**
     * Devuelve la colección de items
     * @return array;
     */
    public function getItemCollection(){
        
        // Obtengo los items
        $this->getItems();
        
        return $this->itemsCOL;
        
    }
    
    /**
     * Devuelve el array de metadatos
     * @return array
     */
    public function getPaginatorMetadata(){
        
        return $this->metadataARR;
        
    }
    
    /**
     * Imprime el paginador en código html
     */
    public function getPaginatorHtml(){
        
        // Se no llegamos a la cantidad de items por página no hay nada que paginar
        if ($this->itemsCount < $this->itemsPorPagina){
            return;
        }
        
        $metadata = $this->metadataARR;
        $paginas = $metadata['paginas'];
        
        ob_start();
        
        echo '<ul id="paginador">';
        
            if ($metadata['anterior']){
                echo '<li>';
                echo '<a class="anterior" href="' . $this->helper->getQueryString(array('p'=>($this->paginaActual - 1))) .'"><span>anterior</span></a>';
                echo '</li>';        
            }
            
            for ($x=1; $x<=$paginas; $x++){
                echo '<li>';
                
                    if ($this->paginaActual == $x){
                        echo '<strong>' . $x . '</strong>';
                    } else {
                        echo '<a class="pagina" href="' . $this->helper->getQueryString(array('p'=>$x)) . '">' . $x . '</a>';
                    }
                            
                echo '</li>';
            }
    
            if ($metadata['siguiente']){
                echo '<li>';
                echo '<a class="siguiente" href="' . $this->helper->getQueryString(array('p'=>($this->paginaActual + 1))) .'"><span>siguiente</span></a>';        
                echo '</li>';
            }        
        
        echo '</ul>';
        
        return ob_get_clean();
        
        
    }
    
}



?>
