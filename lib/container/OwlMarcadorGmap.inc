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
 * Clase contenedora de datos implementa el sistema de mapas de Google para representar puntos
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Aaron Amengual Arranz <aaron.amengual@gmail.com> 
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlMarcadorGmap{
	
	/**
	 * Latitud del marcador
	 * @var string
	 */
	private $_latitud;
	
	/**
	 * Longitud del marcador
	 * @var string
	 */
	private $_longitud;
	
	/**
	 * Nombre del marcador
	 * @var string
	 */
	private $_nombre;
	
	/**
	 * Infowindow
	 * @var string
	 */
	private $_infoWindow = '';
	
	public function __construct($nombre, $latitud, $longitud){
		
		$this->setNombre($nombre);
		$this->setLatitud($latitud);
		$this->setLongitud($longitud);
		
	}
	
	/**
	 * Crea la infowindow
	 */
	public function setInfoWindow($html){

		$nombreUc = ucfirst($this->getNombre());
		
		$this->_infoWindow = 
			'
				// Info window ' . $this->getNombre() . '
				var infoWindow' . $nombreUc . ' =  new google.maps.InfoWindow();
				infoWindow' . $nombreUc . '.setContent("' . $html . '");
				infoWindow' . $nombreUc . '.open(map,' . $this->getNombre() . ');
				
				// Función para mostrar/ocultar la info
				var open' . $nombreUc . ' = true;
				function toggleInfoWindow' . $nombreUc . '(){
			 		if (open' . $nombreUc . ') {
			 			infoWindow' . $nombreUc . '.close();
			 		} else {
			 			infoWindow' . $nombreUc . '.open(map, ' . $this->getNombre() . ');
			 		}
			 		open' . $nombreUc . ' = !open' . $nombreUc . ';
			 	}
			    
				// Evento que oculta/muestra la info
				google.maps.event.addListener(' . $this->getNombre() . ', "click", function() {
					toggleInfoWindow' . $nombreUc . '();
				});
				
				// Evento que actualiza el estado de la info
				google.maps.event.addListener(infoWindow' . $nombreUc . ', "closeclick", function() {
					open' . $nombreUc . ' = false;
				});
			';
		
	}
	
	/**
	 * Setea la latitud
	 * @param integer $latitud
	 */
	public function setLatitud($latitud){
		$this->_latitud = $latitud;
	}
	
	/**
	 * Setea la longitud
	 * @param integer $longitud
	 */
	public function setLongitud($longitud){
		$this->_longitud = $longitud;
	}
	
	/**
	 * Setea el nombre
	 * @param string $nombre
	 */
	public function setNombre($nombre){
		$this->_nombre = $nombre;
	}
	
	/**
	 * Devuelve la latitud
	 * @return integer $latitud
	 */
	public function getLatitud(){
		return $this->_latitud;
	}
	
	/**
	 * Devuelve la longitud
	 * @return integer $longitud
	 */
	public function getLongitud(){
		return $this->_longitud;
	}
	
	/**
	 * Devuelve el nombre
	 * @return string $nombre
	 */
	public function getNombre(){
		return $this->_nombre;
	}
	
	/**
	 * Devuelve la infoWindow
	 * @return string $infoWindow;
	 */
	public function getInfoWindow(){
		return $this->_infoWindow;
	}
}

?>