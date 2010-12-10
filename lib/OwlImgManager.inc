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
 * Clase para el manejo de imágenes
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
require_once 'helper/OwlFile.inc';


class OwlImgManager{
	
	/**
	 * Calidad por defecto a jpg (0 - 100)
	 * @var integer
	 */
	const JPG_QUALITY = 70;

	/**
	 * Calidad por defecto a png (0 = no compression / 10)
	 * @var integer
	 */
	const PNG_QUALITY = 5;
	
	/**
	 * Directorio de salida
	 * @var string
	 */
	private $_outDir = null;
	
	/**
	 * Imágen de origen
	 * @var string
	 */
	private $_sourceImg = null;
	
	/**
	 * Helper de archivos
	 * @var OwlFile
	 */
	private $_fileHelper;
	
	/**
	 * Extensión de la imagen
	 * @var string
	 */
	private $_ext = null;
	
	/**
	 * Recurso gd de la imagen actual
	 * @var resource
	 */
	private $_gd_resource = null;
	
	/**
	 * Tipo de imagen
	 * @var integer
	 */
	private $_gd_imageType = null;
	
	/**
	 * Recurso de salida de GD, al modificar una imagen
	 * la misma sera aqui almacenada, sin alterar la original.
	 * @var resource
	 */
	private $_gd_output_resource = null;
	
	
	/**
	 * Instancia el helper de archivos
	 */
	public function __construct(){
		
		$this->_fileHelper = new OwlFile();
		
	}
	
	
	/**
	 * Establece el directorio de salida donde se 
	 * almacenarán las imágenes resultantes
	 * @param string $outDir
	 */
	public function setOutDir($outDir){
		
		$this->_outDir = $outDir;
		
	}
	
	
	/**
	 * Establece la imagen de origen, los métodos
	 * de tratamiento y manipulación afectarán a esta imágen
	 * 
	 * @param string $sourceImg
	 * @param string $mime
	 * @throws OwlException
	 */
	public function setSourceImg($sourceImg, $mime){

		if (!file_exists($sourceImg)){
			throw new OwlException('La imágen especificada <strong>' . $sourceImg . '</strong>', 500);
			return;
		}
		
		if (!$this->_ext = $this->_fileHelper->getExtension($mime)){
			throw new OwlException('Tipo de mime no soportado: <strong>' . $mime .'</strong>', 500);
		}
		
		// Se propaga la ruta de imagen
		$this->_sourceImg = $sourceImg;
		
		// Se crea el recurso GD
		$this->_createGdResource($this->_sourceImg);

	}
	
	
	/**
	 * Mueve la imagen de origen al directorio de salida,
	 * la renombra a $newName 
	 * @param string $newName
	 */
	public function moveImage($newName){
		
		if (is_null($this->_gd_output_resource)){
		
			// La imágen se mantiene intacta, se copia tal como se recibió
			return move_uploaded_file($this->_sourceImg, $this->_outDir . $newName);
			
		} else {
			
			// La imágen has sido manipulada con GD, es necesario escribir el nuevo archivo
			switch ($this->_gd_imageType){
				
				case IMAGETYPE_JPEG:
					return imagejpeg($this->_gd_output_resource, $this->_outDir . $newName, self::JPG_QUALITY);
					break;
					
				case IMAGETYPE_GIF:
					return imagegif($this->_gd_output_resource, $this->_outDir . $newName);
					break;
					
				case IMAGETYPE_PNG:
					return imagepng($this->_gd_output_resource, $this->_outDir . $newName, self::PNG_QUALITY);
					break;
				
			}
			
		}
		
	}
	
	
	/**
	 * Verifica que el array devuelto por post al subir una imagen sea correcto
	 * @param array $imgPostARR
	 * @return boolean
	 */
	public function checkUploadedImg($imgPostARR){

	    /*
	    [name] => debian.jpg
	    [type] => image/jpeg
	    [tmp_name] => /tmp/phpQUFnwn
	    [error] => 0
	    [size] => 415738
	    */
		
		$fieldsARR = array('name', 'type', 'tmp_name', 'error',  'size');
		
		foreach ($fieldsARR as $field){
			
			if (!array_key_exists($field, $imgPostARR)){
				return false;
			} elseif ($field == 'error' && $imgPostARR['error'] != '0' ){
				return false;
			}
			
		}
		
		return true;
		
	}
	
	
	/**
	 * Calcula la altura de una imagen dependiendo el ancho deseado. 
	 * Si el ancho deseado es menor al actual, se devolvera el mismo alto.
	 * @param integer $newWidth
	 * @param integer $oldWidth
	 * @param integer $oldHeight
	 */
	public static function calculaImagenProporcional($newWidth, $oldWidth, $oldHeight){
		
		if ($oldWidth > $newWidth){
			
			$newHeight = ($newWidth * $oldHeight) / $oldWidth;
			
			return $newHeight;
			
		}
		
		return $oldHeight;
		
	}
	
	
	/**
	 * Crea un recurso gd a partir de la ruta de una imagen
	 * @param string $ruta
	 * @throws OwlException
	 */
	private function _createGdResource($ruta){
		
		switch ($this->_ext){
			
			case 'jpg':
				$this->_gd_imageType = IMAGETYPE_JPEG;
				$this->_gd_resource = imagecreatefromjpeg($ruta);
			break;
				
			case 'gif':
				$this->_gd_imageType = IMAGETYPE_GIF;
				$this->_gd_resource = imagecreatefromgif($ruta);
				break;
				
			case 'png':
				$this->_gd_imageType = IMAGETYPE_PNG;
				$this->_gd_resource = imagecreatefrompng($ruta);
				break;
				
			default:
				// Tipo no soportado por gd
				throw new OwlException('Tipo de imágen no soportado <strong>' . $this->_ext . '</strong>', 500);
				break;
			
		}
		
	}
	
	
	/**
	 * Devuelve el ancho de la imagen actual
	 * @return integer
	 */
	public function getAncho(){
		
		$resource = !is_null($this->_gd_output_resource) ? $this->_gd_output_resource : $this->_gd_resource;
		
		return imagesx($resource);
		
	}
	
	
	/**
	 * Devuelve el alto de la imágen actual
	 * @return integer
	 */
	public function getAlto(){
		
		$resource = !is_null($this->_gd_output_resource) ? $this->_gd_output_resource : $this->_gd_resource;
		
		return imagesy($resource);
		
	}
	
	
	/**
	 * Redimensiona la imagen actual
	 * @param integer $anchoDeseado
	 * @throws OwlException
	 */
	public function resizeFromWidth($anchoDeseado){
		
		// Se calculan las proporciones
		$ancho = $this->getAncho();
		$alto = $this->getAlto();
		$altoDeseado = self::calculaImagenProporcional($anchoDeseado, $ancho, $alto);
		
		// Se crea el nuevo recurso
		$this->_gd_output_resource = imagecreatetruecolor($anchoDeseado, $altoDeseado);
		
		// Se redimensiona la imágen
		if (!imagecopyresampled($this->_gd_output_resource, $this->_gd_resource, 0, 0, 0, 0, $anchoDeseado, $altoDeseado, $ancho, $alto)){
			
			throw new OwlException('Ha ocurrido un error al redimensionar la imágen, por favor intente nuevamente con una imágen que respete el ancho máximo: ' . $anchoDeseado , 500);
			
		}
		
	}
	
	
	/**
	 * Crea una imagen miniatura en el directorio destino
	 * @param integer $anchoDeseado
	 * @param string $nombre
	 * 
	 * @return boolean
	 */
	public function createThumb($anchoDeseado, $nombre){
		
		// Se calculan las proporciones
		$ancho = $this->getAncho();
		$alto = $this->getAlto();
		$altoDeseado = self::calculaImagenProporcional($anchoDeseado, $ancho, $alto);
		
		// Thumb
		$_gd_output_thumb = imagecreatetruecolor($anchoDeseado, $altoDeseado);
		
		// Se redimensiona la imágen
		if (!imagecopyresampled($_gd_output_thumb, $this->_gd_output_resource, 0, 0, 0, 0, $anchoDeseado, $altoDeseado, $ancho, $alto)){
			
			throw new OwlException('Ha ocurrido un error al redimensionar la imágen, por favor intente nuevamente con una imágen que respete el ancho máximo: ' . $anchoDeseado , 500);
			
		}
		
		// La imágen has sido manipulada con GD, es necesario escribir el nuevo archivo
		switch ($this->_gd_imageType){
			
			case IMAGETYPE_JPEG:
				return imagejpeg($_gd_output_thumb, $this->_outDir . $nombre, self::JPG_QUALITY);
				break;
				
			case IMAGETYPE_GIF:
				return imagegif($_gd_output_thumb, $this->_outDir . $nombre);
				break;
				
			case IMAGETYPE_PNG:
				return imagepng($_gd_output_thumb, $this->_outDir . $nombre, self::PNG_QUALITY);
				break;
			
		}	

		return false;
		
		
	}
	
	
	/**
	 * Devuelve la extensión del archivo actual.
	 * (Si no se ha especificado el archivo actual, devuelve null)
	 * @return boolean
	 */
	public function getExtension(){
		
		return $this->_ext ? $this->_ext : null;
		
	}
	
	
}

?>