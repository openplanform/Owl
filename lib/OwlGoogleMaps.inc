<?php

/**																			 
 *  ,_,  
 * (o,o) 
 * {`"'}   OWL (Open Web Library)
 * -"-"-
 * 
 * Software distribuido bajo la "GNU GENERAL PUBLIC LICENSE v3", 
 * mas información en /doc/LICENSE
 * 
 * Clase que implementa el sistema de captcha compatible con OWL
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

require_once 'container/OwlMarcadorGmap.inc';

class OwlGoogleMaps{
	
	/**
	 * 
	 * Latitud
	 * @var integer
	 */
	private $_latitud = '39.57420604477404';
	
	/**
	 * Longitud
	 * @var integer
	 */
	private $_longitud = '2.655208557844162';
	
	/**
	 * Almacena el id del contenedor del mapa
	 * @var string
	 */
	private $_contenedor = 'mapa';
	
	/**
	 * Zoom del mapa
	 * @var intenger
	 */
	private $_zoom = '16';
	
	/**
	 * Array contenedor de los marcadores del mapa
	 * @var array
	 */
	private $_marcadoresARR = array();
	
	/**
	 * Imprime la cabecera con los recursos para mostrar el mapa
	 */
	static public function echoCabeceraMapa(){
		
		$cabecera = '<meta name="viewport" content="initial-scale=1.0, user-scalable=no" />
					<script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"></script>';
		
		return $cabecera;
	}
	
	/**
	 * Devuelve el código javascript del mapa
	 * @param string $funcion
	 * <p>El nombre de la función es necesario ya que si se
	 * crea más de un mapa, se sobreescribirían
	 * unos a otros</p>
	 * @return string $googleMap
	 */
	public function echoMapa($funcion){
		
		$googleMap = 
		'<script type="text/javascript">
			//<![CDATA[
			function ' . $funcion . '() {
				
				var latlng = new google.maps.LatLng(' . $this->_latitud . ', ' . $this->_longitud . ');
				var myOptions = {
					zoom: ' . $this->_zoom . ',
					center: latlng,
					mapTypeId: google.maps.MapTypeId.ROADMAP
				};
				var map = new google.maps.Map(document.getElementById("' . $this->_contenedor . '"), myOptions);
				
				//google.maps.event.addListener(map, "click", function(evento) {
				//	alert(evento.latLng.lat() + ", " + evento.latLng.lng())
				//});
							
				'. $this->_echoMarcadores() . '
					    	
			}
			jQuery(document).ready(function(){

				//mapa
				' . $funcion . '();
							
			});
			//]]>
		</script>';
		
		return $googleMap;
	}
	
	/**
	 * Imprime los marcadores en el mapa
	 */
	private function _echoMarcadores(){
		
		$marcadores = '';
		foreach ( $this->_marcadoresARR as $marcadorDO ){
			
			$marcadores .=
			'   
				// ' . $marcadorDO->getNombre() . '
				var latlngMarcador = new google.maps.LatLng(' . $marcadorDO->getLatitud() . ', ' . $marcadorDO->getLongitud() . ');
				var ' . $marcadorDO->getNombre() . ' = new google.maps.Marker({
					position: latlngMarcador,
					map		: map
				});
				' . $marcadorDO->getInfoWindow();
			
		}
		
		return $marcadores;
	}
	
	/**
	 * Añade un marcador al mapa
	 * @param string $nombre
	 * @param integer $latitud
	 * <p>Toma por defecto la del mapa</p>
	 * @param integer $longitud
	 * <p>Toma por defecto la del mapa</p>
	 */
	public function addMarcador($nombre, $latitud = null, $longitud = null){
		
		if ( is_null($latitud) ){
			$latitud = $this->_latitud;
		}

		if ( is_null($longitud) ){
			$longitud = $this->_longitud;
		}
		
		$marcador = new OwlMarcadorGmap($nombre, $latitud, $longitud);
		$this->_marcadoresARR[$nombre] = $marcador;
		
	}
	
	/**
	 * Añade una infoWindow a un marcador
	 * @param string $html
	 * <p>Código html del infoWindow</p>
	 * @param string $nombreMarcador
	 * <p>El nombre del marcador donde irá la infoWindow</p>
	 */
	public function addInfoWindow($html, $nombreMarcador){
		
		if ( array_key_exists($nombreMarcador, $this->_marcadoresARR) ){
			
			$marcadorDO = $this->_marcadoresARR[$nombreMarcador];
			$marcadorDO->setInfoWindow($html);
		}
		
	}
	
	/**
	 * Setea la latitud
	 * @param integer $latitud
	 */
	public function setLatitud( $latitud ){
		$this->_latitud = $latitud;
	}
	
	/**
	 * Setea la longitud
	 * @param integer $longitud
	 */
	public function setLongitud( $longitud ){
		$this->_longitud = $longitud;
	}
	
	/**
	 * Setea el zoom del mapa
	 * @param integer $zoom
	 */
	public function setZoom($zoom){
		$this->_zoom = $zoom;
	}
	
	/**
	 * Setea el contenedor del mapa
	 * @param string $contenedor
	 */
	public function setContenedor($contenedor){
		$this->_contenedor = $contenedor;
	}
	
}

?>