<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuído bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Definición de clase para el tratado de formularios pdf, ha sido escrita siguiendo 
 * las recomendaciones de la especificación PDF 1.4 de Adobe. 
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es>
 * @version 0.5.3
 * @since 0.5.3
 * 
 **/

require_once 'OwlException.inc';


class OwlPdf{
    
    /**
     * Path del pdf a tratar
     * @var string
     */
    protected $pdfPath;
    
    /**
     * Contenido del pdf en memoria
     * @var string
     */
    private $_content;
    
    /**
     * Pila de campos
     * @var array
     */
    private $_fieldStack = array();
    
    /**
     * Tipos de campos soportados
     * @var array
     */
    private $_supportedTypes;
    
    /**
     * Puntero que referencia al archivo de salida
     * @var integer
     */
    private $__file;
    
    /**
     * Sufijo de campo pdf
     * @var integer
     */
    const PDF_FIELDSUFFIX = 0xFEFF;
    
    /**
     * Salto de línea
     * @var integer
     */
    const PDF_LINEBREAK = 0x0A;
    
    /**
     * Espacio
     * @var integer
     */
    const PDF_SPACECHAR = 0x20;
    
    /**
     * Espacio especial para valores de cadena
     * @var integer
     */
    const PDF_ZERO = 0x00;
    
    /**
     * Encoding de entrada
     * @var string
     */
    private $_inputEncoding = 'UTF-8';
    
    /**
     * Encoding de salida (PDF)
     * @var string
     */
    private $_outputEncoding = 'ISO-8859-1';
    
    
    /**
     * Establece el path del archivo pdf a tratar
     * @throws OwlException
     * @param string $pdfPath
     */
    public function __construct($pdfPath){
        
        // Se verifica la existencia del archivo
        if (!file_exists($pdfPath)){
            throw new OwlException('El archivo pdf seleccionado <strong>(' . $pdfPath . ')</strong> no existe, o no tiene permisos de lectura', 500);
        }
        
        // Tipos de campos soportados
        $this->_supportedTypes = array(
            'text',
            'checkbox'
        );
        
        $this->pdfPath = $pdfPath;
        
    }
    
    
    /**
     * Destruye el recurso de archivo, si existe
     */
    public function __destruct(){
        
        // Liberamos el recurso
        if (is_resource($this->__file)){
            fclose($this->__file);
        }        
        
    }
    
    
    /**
     * Carga el pdf con permiso de escritura
     */
    public function loadForEdit(){
        
        if (!is_writable($this->pdfPath)){
            throw new OwlException('El pdf abierto para edición <strong>(' . $this->pdfPath . ')</strong> no tiene permisos de escritura.', 500);
        }
        
        if (!$this->_content = file_get_contents($this->pdfPath, false)){
            throw new OwlException('Ha ocurrido un error al abrir el archivo para edición: <strong>(' . $this->pdfPath . ')</strong>', 500);
        }
        
        if (!$this->_checkIntegrity()){
            throw new OwlException('El archivo <strong>(' . $this->pdfPath . ')</strong> no parece ser un PDF', 500);
        }
        
    }
    
    
    /**
     * Verifíca si un tipo de campo está soportado
     * @throws OwlException
     * @param string $tipo
     */
    private function _isSupportedType($tipo){
        
        return in_array($tipo, $this->_supportedTypes);
        
    }
    
    /**
     * Añade un array a la pila de reemplazos, con los valores asignados.
     * Notar que si nombre ya existe en la pila, su contenido será reemplazado.
     */
    public function addFieldValue($nombre, $valor, $tipo){

        if (!$this->_isSupportedType($tipo)){
            throw new OwlException('El tipo de campo <strong>' . $tipo . '</strong>, no está soportado.', 500);
        }
        
        $this->_fieldStack[$nombre] = array(
            'valor' => $valor,
            'tipo'  => $tipo
        );
        
    }
    
    /**
     * Verifica la integridad del documento pdf.
     * @return boolean
     */
    private function _checkIntegrity(){
        
        // Se espera "%PDF-1.X"
        if (preg_match('/^%PDF-.+/', $this->_content)) {
            return true;
        }
        
        return false;

    }
    
    
    /**
     * Rellena el formulario pdf, con los campos almacenados en la pila
     * 
     * @throws OwlException
     * @return boolean
     */
    public function fillPdfForm(){
        
        // Flag de error
        $correcto = true;
        
        foreach ($this->_fieldStack as $key => $data){
            
            switch ($data['tipo']){
                
                case 'text':
                    $correcto = $this->_fillTextField($key, $data['valor']);
                    break;
                    
                case 'checkbox':
                    $correcto = $this->_fillCheckboxField($key, $data['valor']);
                    break;
                
            }
            
            if (!$correcto){
                throw new OwlException('Ha ocurrido un error al efectuar reemplazos.', 500);
                return false;
            }
            
        }
        
        
        return true;
            
        
    }
    
    
    /**
     * Rellena un campo del tipo text, devuelve la cantidad de cambios efectuados.
     * @param string $name
     * @param string $value
     * @return boolean
     */
    private function _fillTextField($name, $value){
        
        // Se convierten los datos a un encoding en común
        $value = mb_convert_encoding($value, $this->_outputEncoding, $this->_inputEncoding); 

        // Cadena que propaga el grupo #1 de la expresión regular 
        $reemplazo = '/T(' . $name . ')' . chr(self::PDF_LINEBREAK) . '/TU<FEFF>' . chr(self::PDF_LINEBREAK) . '${1}' . chr(self::PDF_LINEBREAK) . '/V' . chr(self::PDF_SPACECHAR) . '<' . $this->_encodeFormValue($value) . '>' . chr(self::PDF_LINEBREAK) . '/DV' . chr(self::PDF_SPACECHAR) .'<' . $this->_encodeFormValue($value) . '>';
        
        // Se efectúa el reemplazo
        if (!$resultado = preg_replace('%/T\('.$name.'\)\n/TU<[A-F0-9]+>\n(.*)\n*/V\s<[A-F0-9]+>\n/DV\s<[A-F0-9]+>%', $reemplazo, $this->_content, -1, $cuenta)){
            return false;
        }
        
        // Se actualiza el buffer
        $this->_content = $resultado;
        
        // Se devuelve la cantidad de reemplazos
        return $cuenta;
        
    }
    
    
    /**
     * Rellena un campo del tipo checkbox
     * @param string $name
     * @param string $value
     * @return boolean
     */
    private function _fillCheckboxField($name, $value){
        
        // Valor
        $value = $value ? 'Yes' : 'Off';
        
        // Cadena de reemplazo, no hace falta propagar ningún gruo para el checkbox
        $reemplazo = '/T(' . $name . ')' . chr(self::PDF_LINEBREAK) . '/TU<FEFF>' . chr(self::PDF_LINEBREAK) . '/V /' . $value . chr(self::PDF_LINEBREAK) . '/DV /' . $value;
        
        // Se reemplaza el patrón
        if (!$resultado = preg_replace('%/T\(' . $name . '\)\n/TU<FEFF>\n/V\s/.+\n/DV\s/.+%', $reemplazo, $this->_content, -1, $cuenta)){
            return false;
        }
        
        // Se actualiza el buffer
        $this->_content = $resultado;
        
        // Se devuelve la cantidad de reemplazos
        return $cuenta;
        
    }
    
    
    /**
     * Escribe el archivo de salida en el disco
     * @param string $outputFullPath
     * @return integer
     */
    public function writeFile($outputFullPath){
        
        if (!$this->__file = fopen($outputFullPath, 'w+')){
            throw new OwlException('No se puede abrir/crear para escritura el archivo: <strong>' . $outputFullPath . '</strong>', 500);
        }
        
        // fwrite me devolvera los bytes escritos o false en caso de error
        if (!$bytesEscritos = fwrite($this->__file, $this->_content)){
            throw new OwlException('Ha ocurrido un error al escribir el archivo: <strong>' . $outputFullPath . '</strong>', 500);
        }
        
        return $bytesEscritos;
        
    }
    
    
    /**
     * Codifica una cadena para el formato de valores de PDF
     * Básicamente devuelve el valor hexadecimal de cada 
     * caracter que la conforma separado por el espacio de valores PDF (0x00)
     *  
     * @param string $value
     * @return string
     */
    private function _encodeFormValue($value){
        
        // Tamaño de la cadena
        $tam = strlen($value);
        
        // Ademas del sufijo de campo (0xFEFF) se añade un valor ZERO
        $ret = 'FEFF00';
        $valueChars = array();
        
        for($x=0; $x<$tam; $x++){
            
            // Ord me devuelve el valor ascii del caracter, lo convierto
            // a hexa y normalizo los valores alfa a mayusculas
            $valueChars[] = strtoupper(dechex(ord($value[$x])));
            
        }
        
        // Adobe ha decidido que todos los valores que sean strings en formularios
        // deberán estar separados por el caracter zero.
        $ret .= implode('00', $valueChars);
        
        return $ret;
        
    }
    
    
    /**
     * Establece la codificación de entrada, por defecto UTF-8
     * @param string $encoding
     */
    public function setInputEncoding($encoding){
        
        $this->_inputEncoding = $encoding;
        
    }
    
    
    /**
     * Establece la codificación de salida, por defecto ISO-8859-1
     * @param string $encoding
     */
    public function setOutputEncoding($encoding){
        
        $this->_outputEncoding = $encoding;
        
    }
    
      
    
    
}

?>