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
	 * Constante de latitud por defecto
	 * @var string
	 */
	const LATITUD = '39.575826904309494';
	
	/**
	 * Constante de longitud por defecto
	 * @var string
	 */
	const LONGITUD = '2.653813809156418';
	
	/**
	 * Latitud
	 * @var integer
	 */
	private $_latitud = '39.575826904309494';
	
	/**
	 * Longitud
	 * @var integer
	 */
	private $_longitud = '2.653813809156418';
	
	/**
	 * Almacena el id del contenedor del mapa
	 * @var string
	 */
	private $_contenedor = 'mapa';
	
	/**
	 * Zoom del mapa
	 * @var intenger
	 */
	private $_zoom = '15';
	
	/**
	 * Array contenedor de los marcadores del mapa
	 * @var array
	 */
	private $_marcadoresARR = array();
	
	/**
	 * Setea si el mapa marca el punto donde clica el usuario
	 * @var boolean
	 */
	private $_marcadorCoordenadas = false;
	
	/**
	 * Setea si el mapa marca los puntos donde clica el usuario
	 * @var boolean
	 */
	private $_multipleMarcadorCoordenadas = false;
	
	/**
	 * Contenedor de las coordenadas en el caso de que se active el 
	 * marcador múltiple de coordenadas
	 * @var string
	 */
	private $_contenedorCoordenadas = '';
	
	/**
	 * Nombre del mapa
	 * @var string
	 */
	private $_nombreMapa;
	
	/**
	 * Constructor. Se le pasa el nombre del mapa
	 * @param string $mapa
	 */
	public function __construct($nombreMapa = 'map'){
		
		$this->_nombreMapa = $nombreMapa;
		
	}
	
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
	 * crea más de un mapa, se sobreescribirían unos a otros.
	 * Por defecto es "initialize"</p>
	 * @return string $googleMap
	 */
	public function echoMapa(){
		
		$googleMap = 
		'<script type="text/javascript">
			
			//<![CDATA[
			function initialize' . $this->_nombreMapa . '() {
				
				var latlng = new google.maps.LatLng(' . $this->_latitud . ', ' . $this->_longitud . ');
				var myOptions = {
					zoom: ' . $this->_zoom . ',
					center: latlng,
					mapTypeId: google.maps.MapTypeId.ROADMAP
				};
				' . $this->_nombreMapa . ' = new google.maps.Map(document.getElementById("' . $this->_contenedor . '"), myOptions);';
				
				// Devolución de coordenadas
				if ( $this->_marcadorCoordenadas ) {
					
					$googleMap .= $this->_echoMarcadorCoordenadas();
				
				}

				// Marcadores
				$googleMap .= $this->_echoMarcadores() . '
					
			}
			
			jQuery(document).ready(function(){

				//inicializa el mapa
				initialize' . $this->_nombreMapa . '();
							
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
					map		: ' . $this->_nombreMapa . '
				});
				' . $marcadorDO->getInfoWindow();
			
			// Código para mostrar las coordenadas del marcador que aparece en el mapa
			if ( $this->_marcadorCoordenadas ){
				
				$marcadores .= '
					google.maps.event.addListener(' . $marcadorDO->getNombre() . ',"click", function(){
						
						if ( latitud != null ){
							if (latitud.nodeName == "INPUT"){
								latitud.value = "' . $marcadorDO->getLatitud() . '";
							} else {
								latitud.innerHTML = "' . $marcadorDO->getLatitud() . '";
							}
						}
						
						if ( longitud != null ){
							if (longitud.nodeName == "INPUT"){
								longitud.value = "' . $marcadorDO->getLongitud() . '";
							} else {
								longitud.innerHTML = "' . $marcadorDO->getLongitud() . '";
							}
						}
					});';
			}
			
		}
		
		return $marcadores;
	}
	
	/**
	 * Imprime el código necesario para que el mapa te devuelva
	 * las coordenadas donde has clicado
	 * @return string $marcadorCoordenadas
	 */
	private function _echoMarcadorCoordenadas(){
		
		$marcadorCoordenadas = '';
		if ( !$this->_multipleMarcadorCoordenadas ){
			
			/**
			 * Si no hay múltiple marcador de coordendas, hay que inicializar el marcador
			 * fuera del listener del evento clic
			 */ 
			$marcadorCoordenadas .= '
			
				// Inicializamos el marcador que indicará dónde se clica
				var puntoSeleccionado = new google.maps.Marker();
				google.maps.event.addListener(puntoSeleccionado,"click", function(){
						this.setVisible(false);
						
						if ( latitud != null ){
							if (latitud.nodeName == "INPUT"){
								latitud.value = "";
							} else {
								latitud.innerHTML = "";
							}
						}
						
						if ( longitud != null ){
							if (longitud.nodeName == "INPUT"){
								longitud.value = "";
							} else {
								longitud.innerHTML = "";
							}
						}
				});
				
				var latitud = document.getElementById("latitud");
				var longitud = document.getElementById("longitud");
				google.maps.event.addListener(map, "click", function(evento) {
				
					if ( latitud != null ){
						if (latitud.nodeName == "INPUT"){
							latitud.value = evento.latLng.lat();
						} else {
							latitud.innerHTML = evento.latLng.lat();
						}
					}
					
					if ( longitud != null ){
						if (longitud.nodeName == "INPUT"){
							longitud.value = evento.latLng.lng();
						} else {
							longitud.innerHTML = evento.latLng.lng();
						}
					}
					
					// Marcador en el punto en el que han clicado
					puntoSeleccionado.setOptions({
						position: evento.latLng,
						map: ' . $this->_nombreMapa . ',
						visible: true
					});
					
				});
				';
		} else {
			
			$marcadorCoordenadas .= '
				var contenedorCoordenadas = document.getElementById("' . $this->_contenedorCoordenadas . '");
				var contadorCoordenadas = 0;
				google.maps.event.addListener(' . $this->_nombreMapa . ', "click", function(evento) {
					
					if ( contenedorCoordenadas != null ){
					
						// Nueva latitud
						var inputLatitud = document.createElement("INPUT");
						inputLatitud.value = evento.latLng.lat();
						inputLatitud.class = "coordenada";
						inputLatitud.name = "latitud_"+contadorCoordenadas;
						inputLatitud.id = "latitud_"+contadorCoordenadas;
						contenedorCoordenadas.appendChild(inputLatitud);

						// Nueva longitud
						var inputLongitud = document.createElement("INPUT");
						inputLongitud.value = evento.latLng.lng();
						inputLongitud.class = "coordenada";
						inputLongitud.name = "longitud_"+contadorCoordenadas;
						inputLongitud.id = "longitud_"+contadorCoordenadas;
						contenedorCoordenadas.appendChild(inputLongitud);
					}
					
					// Inicializamos el marcador que indicará dónde se clica
					var puntoSeleccionado = new google.maps.Marker();
					var aux = contadorCoordenadas; // Variable local de la función
					google.maps.event.addListener(puntoSeleccionado,"click", function(){
						
						this.setVisible(false);
						
						// Eliminamos las coordenadas del marcador eliminado
						var latitudEliminada = document.getElementById("latitud_"+aux);
						contenedorCoordenadas.removeChild(latitudEliminada);
						var longitudEliminada = document.getElementById("longitud_"+aux);
						contenedorCoordenadas.removeChild(longitudEliminada);
						
					});
					
					// Marcador en el punto en el que han clicado
					puntoSeleccionado.setOptions({
						position: evento.latLng,
						map: ' . $this->_nombreMapa . '
					});
					
					contadorCoordenadas++;
					
				});
				';
			
		}
		
		return $marcadorCoordenadas;
	}
	
	/**
	 * Añade un marcador al mapa
	 * @param string $nombre
	 * @param integer $latitud
	 * <p>Toma por defecto la del mapa</p>
	 * @param integer $longitud
	 * <p>Toma por defecto la del mapa</p>
	 */
	public function addMarcador($nombre = 'marcador', $latitud = null, $longitud = null){
		
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
	 * Setea la latitud, por defecto es 2.653813809156418.
	 * @param integer $latitud
	 */
	public function setLatitud( $latitud ){
		$this->_latitud = $latitud;
	}
	
	/**
	 * Setea la longitud, por defecto es 39.575826904309494
	 * @param integer $longitud
	 */
	public function setLongitud( $longitud ){
		$this->_longitud = $longitud;
	}
	
	/**
	 * Setea el zoom del mapa, por defecto es 15.
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
	
	/**
	 * Setea si el mapa te devuelve o no las coordenadas donde clicas;
	 * Devuelve las coordenadas a los elementos del DOM con los ids
	 * latitud y longitud.
	 * @param boolean $marcadorCoordenadas
	 * <p>Boleano para activar el marcador de coordenadas</p>
	 * @param boolean $multiplesPuntos
	 * <p>Boleano que setea si el mapa te ha de marcar cada punto en el que cliques
	 * o bien sólo te ha de marcar uno a la vez. Si se activa, hay que pasarle
	 * el identificador del elemento del DOM en el que mostrará las coordenadas.</p>
	 * @param string $contenedorCoordenadas
	 * <p>Por defecto el id del contenedor es "coordenadas"</p>
	 */
	public function setMarcadorCoordenadas($marcadorCoordenadas, $multiplesPuntos = false, $contenedorCoordenadas = 'coordenadas'){
		$this->_marcadorCoordenadas = $marcadorCoordenadas;
		$this->_multipleMarcadorCoordenadas = $multiplesPuntos;
		$this->_contenedorCoordenadas = $contenedorCoordenadas;
	}
	
}

?>