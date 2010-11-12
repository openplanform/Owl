$j = jQuery;

jQuery(document).ready(function(){
	
	var tooltipId;
	var w;
	var jQtooltip;
	
	// Tooltips
	jQuery('.campoTexto').each( function(){
		
		jQuery(this).bind({
			
			focus: function(){
			
				tooltipId = '#' + jQuery(this).attr('id') + 'Tooltip';
				jQtooltip = jQuery(tooltipId);
				w = jQuery(this).css("width");
				jQuery(tooltipId).css('left', w);
				
				if (jQuery(tooltipId).lenght != 0){
					jQuery(tooltipId).fadeIn('normal');
				}
			},
			
			focusout: function(){
				jQuery(tooltipId).fadeOut('high');
			}
		
		});
		
	});
	
});

/**
 * Devuelve el str con la primera letra en mayúsculas
 * @param str
 * @returns str
 */
function ucfirst (str) {
    var f = str.charAt(0).toUpperCase();
    return f + str.substr(1);
}

/**
 * Comprueba si un input está vacío
 * @returns boolean
 */
function comprobarVacio( idCampo, mensaje ) {
	
	idCampo = typeof(idCampo) != 'undefined' ? idCampo : false;
	mensaje = typeof(mensaje) != 'undefined' ? mensaje : '';
	
	if ( idCampo ){
		
		var idError = '#error' + ucfirst(idCampo);
		if ( $j('#' + idCampo).val() == '' ){
			$j(idError).html(mensaje);
			$j('#' + idCampo).focus();
			$j('#' + idCampo).css("borderColor","#F00");
			return false;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
			return true;
		}

	}
	
	return false;
	
}

/**
 * Comprueba si un input cumple con una expresión regular
 * @returns boolean
 */
function comprobarRegExp( idCampo, regExp, mensaje ) {
	
	idCampo = typeof(idCampo) != 'undefined' ? idCampo : false;
	mensaje = typeof(mensaje) != 'undefined' ? mensaje : '';
	regExp = typeof(regExp) != 'undefined' ? regExp : false;
	
	if ( idCampo && regExp ){
		
		var idError = '#error' + ucfirst(idCampo);
		if ( !$j('#' + idCampo).val().match(regExp) ){
			$j(idError).html(mensaje);
			$j('#' + idCampo).focus();
			$j('#' + idCampo).css("borderColor","#F00");
			return false;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
			return true;
		}

	}
	
	return false;
	
}

/**
 * Compara un valor de input con otro valor. Devuelve true si son iguales.
 * @returns boolean
 */
function compararCon( idCampo, valorComprobacion, mensaje ) {
	
	idCampo = typeof(idCampo) != 'undefined' ? idCampo : false;
	mensaje = typeof(mensaje) != 'undefined' ? mensaje : '';
	
	if ( idCampo ){
		
		var idError = '#error' + ucfirst(idCampo);
		if ( $j('#' + idCampo).val() != valorComprobacion ){
			$j(idError).html(mensaje);
			$j('#' + idCampo).focus();
			$j('#' + idCampo).css("borderColor","#F00");
			return false;
		} else {
			$j('#' + idCampo).css("borderColor","#A6A6A6");
			$j(idError).html('');
			return true;
		}

	}
	
	return false;
	
}

/**
 * Comprueba si un usuario ya existe.
 * Editar indica si estamos en la ficha de edición,
 * y realiza la comprobación sólo si el usuario
 * ha cambiado el nombre
 * @param idCampo
 * @param editar
 */
function comprobarUsuario(idCampo, editar) {
	
	editar = typeof(editar) != 'undefined' ? editar : false;
	var usuario = $j('#' + idCampo).val();
	var idError = '#error' + ucfirst(idCampo);
	var comprobar = false;
	
	if ( editar ) {
		var usuarioOculto = $j('#' + idCampo + "Oculto").val();
		if ( usuarioOculto.toLowerCase() != usuario.toLowerCase() ){
			comprobar = true;
		}
	} else if ( usuario != '' ){
		comprobar = true;
	}
	
	if ( comprobar ){
		
		$j.ajax({
	        type: 'POST',
	        url: '/ajax/comprobarUsuario.html',
	        data: 'usuario=' + usuario.toLowerCase(),
	        //Mostramos un mensaje con la respuesta
	        success: function(data) {
				arrRespuesta = $j.parseJSON(data);
	        	if ( arrRespuesta.resultado == 'ko' ) {
	        		$j(idError).html(arrRespuesta.mensaje);
	    			$j('#' + idCampo).focus();
	    			$j('#' + idCampo).css("borderColor","#F00");
	            } else {
	            	$j('#' + idCampo).css("borderColor","#A6A6A6");
	    			$j(idError).html('');
	            }
	        }
		});
		
	} else if ( editar ){
		$j('#' + idCampo).css("borderColor","#A6A6A6");
		$j(idError).html('');
	}
}
