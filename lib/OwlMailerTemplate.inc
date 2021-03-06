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
 * Clase que implementa el sistema de templates de mail.
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


require_once 'OwlException.inc';


class OwlMailerTemplate{

    /**
     * Path al template
     * @var string
     */
    private $_templatePath;

    /**
     * Contenido del  archivo de template
     * @var string
     */
    private $_templateFile;

    /**
     * Campos a mostrar
     * @var array
     */
    private $_fields;

    /**
     * Separador de claves
     * @var string
     */
    private $_limitToken = '%%';


    /**
     * Constructor
     */
    public function __construct(){

    }

    /**
     * Establece la ruta del template a utilizar
     * @param string $templatePath
     */
    public function setTemplate($templatePath){

        if (!file_exists($templatePath)){
            throw new OwlException('El template de mail: ' . $templatePath . ' no existe', 500);
        }

        /**
         * IMPORTANTE: Si por alguna razón se desea utilizar una url
         * para el nombre del template, parsear antes con urlencode()
         */
        $this->_templatePath = $templatePath;

    }

    /**
     * Agrega un campo de valor al template
     * @param string $clave
     * @param string $valor
     */
    public function addField($clave, $valor){

        $this->_fields[$clave] = $valor;

    }

    /**
     * Establece el separador de claves, por defecto es %%
     * @param string $token
     */
    public function setToken($token){

        $this->_limitToken = $token;

    }

    /**
     * Procesa el template y realiza el reemplazo de
     * todas las claves por su valor correspondiente
     *
     * @return void
     */
    private function _processTemplate(){

        // Leemos el archivo de template
        if (!$this->_templateFile = file_get_contents($this->_templatePath)){
            throw new OwlException('No ha sido posible leer el archivo de template mail: ' . $this->_templatePath, 500);
        }

        // Parsearemos los campos a cambiar
        foreach ($this->_fields as $clave => $content){

            $this->_templateFile = preg_replace('/(%%' . $clave . '%%)/', $content, $this->_templateFile);

        }
        
    }

    /**
     * Devuelve el contenido parseado del template
     * @return string
     */
    public function getContent(){

        $this->_processTemplate();
        
        return $this->_templateFile;

    }







}