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
 * Clase estática con funciones de utilidad para el manejo de fechas.
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlDate{
    
    /**
     * @see OwlDate::getDiaMesAno()
     * @param time $fecha
     * @return string
     */
    public static function getDMA($fecha){
        
        return self::getDiaMesAno($fecha);
        
    }
    
    /**
     * Devuelve la fecha en formato DD/MM/AAAA, 
     * si la fecha pasada no es reconocible devuelve null
     * @param time $fecha
     * @return string
     */
    public static function getDiaMesAno($fecha){
        
        $timestamp = strtotime($fecha);
        
        return date('d/m/Y', $timestamp);
        
    }
    
    /**
     * Convierte una fecha del formato europeo(dd/mm/aaaa) al formato americano (MySql aaaa-mm-dd). 
     * Si se produce algún error durante la conversión, devuelve null. 
     * @param string $fecha
     * @param string $sepOriginal
     * @param string $sepNuevo
     */
    public static function europeoAmericano($fecha, $sepOriginal = '/', $sepNuevo = '-'){

    	$fechaARR = explode($sepOriginal, $fecha);
    	
    	// Si la fecha está mal formada (o no es una fecha), se devolverá null, evitando el error resultante
    	if (is_array($fechaARR) && count($fechaARR) == 3){
    	
	        list($anio, $mes, $dia) = $fechaARR;
	    	$returnDate = $dia . $sepNuevo . $mes . $sepNuevo . $anio; 
	        
	        return $returnDate;
	        
    	}
    	
    	return null;
        
    }    
    
    /**
     * <p>Devuelve una fecha en un formato determinado</p>
     * <p>El formato se adapta al idioma de la página</p>
     * <p>Si no existe el formato devuelve null</p>
     * formato 'a': "01 de febrero de 2011"
     * formato 'b': "1 de febrero de 2011"
     * 
     * @param date $fecha
     * @param string $formato ['a', 'b']
     * @param array $locale
     * @param string $lang
     */
    public static function formatDate($fecha, $formato, $locale, $lang = null){
    	
    	$date = null;
    	
    	is_null($lang) ? $lang = 'es' : '';
    	
    	switch ($formato) {
    		
    		// 01 de enero de 2000
    		case 'a':
    			
    			$datetime = strtotime($fecha);
    			if ( $lang == 'es' || $lang == 'ca' ){
    				$date = date('d', $datetime) . ' ' . $locale['de'] . ' ' . $locale['lista_meses'][date('n', $datetime)] . ' ' . $locale['de'] . ' ' . date('Y', $datetime);
    			}
    			if ( $lang == 'en' ){
    				$date = $locale['lista_meses'][date('d', $datetime)] . ', ' . date('j', $datetime) . ' '  . date('Y', $datetime);
    			}
    			
    		break;

    		// 1 de enero de 2000
    		case 'b':
    			
    			$datetime = strtotime($fecha);
    			if ( $lang == 'es' || $lang == 'ca' ){
    				$date = date('j', $datetime) . ' ' . $locale['de'] . ' ' . $locale['lista_meses'][date('n', $datetime)] . ' ' . $locale['de'] . ' ' . date('Y', $datetime);
    			}
    			if ( $lang == 'en' ){
    				$date = $locale['lista_meses'][date('n', $datetime)] . ' ' . date('j', $datetime) . ', '  . date('Y', $datetime);
    			}
    			
    		break;
    		
    		default:
    			;
    		break;
    	}
    	
    	return $date;
    	
    }
    

    /**
     * Devuelve un array con un item por cada día comprendido desde
     * y hasta. Indexado por clave autoincrementada.
     * Este método no comprueba la validez del formato de fecha,
     * que deberá ser YYYY-m-d.
     * 
     * @param date $desde
     * @param date $hasta
     */
	public static function createDateRangeArray($desde, $hasta) {
		
		$aryRange=array();
		
		$iDateFrom = mktime(1,0,0,substr($desde,5,2), substr($desde,8,2),substr($desde,0,4));
		$iDateTo = mktime(1,0,0,substr($hasta,5,2), substr($hasta,8,2),substr($hasta,0,4));
		
		if ($iDateTo >= $iDateFrom) {
			
			array_push($aryRange,date('Y-m-d',$iDateFrom)); // first entry
		
			while ($iDateFrom<$iDateTo) {
				$iDateFrom += 86400; // add 24 hours
				array_push($aryRange,date('Y-m-d',$iDateFrom));
			}
			
		}
		  
		return $aryRange;
	  
	}      


	/**
	 * Realiza una resta entre dos tiempos y devuelve el resultado de la operación
	 * @param string $horaIni
	 * @param string $horaFin
	 * @return string
	 */
	public static function restaHoras($horaIni, $horaFin){
		return (date("H:i:s", strtotime("00:00:00") + strtotime($horaFin) - strtotime($horaIni) ));
	}	
	
	
	/**
	 * Obtiene la cantidad de minutos expresados en formato time (HH:MM:SS)
	 * @param time $time
	 */
    public static function timeToMinutes($time){
    	
	    $horaSplit = explode(":", $time);
	    if( count($horaSplit) < 3 ) {
	    	$horaSplit[2] = 0;
	    }
	
	    // Pasamos los elementos a segundos
	    $horaSplit[0] = $horaSplit[0] * 60 * 60;
	    $horaSplit[1] = $horaSplit[1] * 60;
	
	    return (($horaSplit[0] + $horaSplit[1] + $horaSplit[2]) / 60);
	    
    }

    
    /**
     * Convierte una cantidad de minutos a formato time (HH:MM)
     * @param integer $mins
     */
    public static function minutesToHours($mins){
    	
	    $hours = floor($mins / 60);
	    $minutes = $mins - ($hours * 60);

	    if (!$minutes) {
	    	$minutes = "00";
	    }elseif ($minutes <= 9) {
	    	$minutes = "0" . $minutes;
	    }

    	return ("$hours:$minutes");
    	
    }	
	
    /*
     * Original de: http://www.aaamatematicas.com/subtsbhm.htm     
     */

    /**
     * Resta tiempo en formato HH:MM:SS
     * @param string $hora1
     * @param string $hora2
     * @return string "HH:MM:SS"
     */
    public static function restaTiempo($hora1,$hora2){
    
    $temp1 = explode(":",$hora1);
    $temp_h1 = (int)$temp1[0];
    $temp_m1 = (int)$temp1[1];
    $temp_s1 = (int)$temp1[2];
    $temp2 = explode(":",$hora2);
    $temp_h2 = (int)$temp2[0];
    $temp_m2 = (int)$temp2[1];
    $temp_s2 = (int)$temp2[2];
    
    // si $hora2 es mayor que la $hora1, invierto
    if( $temp_h1 < $temp_h2 ){
        $temp  = $hora1;
        $hora1 = $hora2;
        $hora2 = $temp;
    }
    /* si $hora2 es igual $hora1 y los minutos de
       $hora2 son mayor que los de $hora1, invierto*/
    elseif( $temp_h1 == $temp_h2 && $temp_m1 < $temp_m2){
        $temp  = $hora1;
        $hora1 = $hora2;
        $hora2 = $temp;
    }
    /* horas y minutos iguales, si los segundos de 
       $hora2 son mayores que los de $hora1,invierto*/
    elseif( $temp_h1 == $temp_h2 && $temp_m1 == $temp_m2 && $temp_s1 < $temp_s2){
        $temp  = $hora1;
        $hora1 = $hora2;
        $hora2 = $temp;
    }    
    
    $hora1=explode(":",$hora1);
    $hora2=explode(":",$hora2);
    $temp_horas = 0;
    $temp_minutos = 0;        
    
    //resto segundos
    $segundos;
    if( (int)$hora1[2] < (int)$hora2[2] ){
        $temp_minutos = -1;        
        $segundos = ( (int)$hora1[2] + 60 ) - (int)$hora2[2];
    }
    else    
        $segundos = (int)$hora1[2] - (int)$hora2[2];
        
    //resto minutos
    $minutos;
    if( (int)$hora1[1] < (int)$hora2[1] ){
        $temp_horas = -1;        
        $minutos = ( (int)$hora1[1] + 60 ) - (int)$hora2[1] + $temp_minutos;
    }    
    else
        $minutos =  (int)$hora1[1] - (int)$hora2[1] + $temp_minutos;
        
    //resto horas    
    $horas = (int)$hora1[0]  - (int)$hora2[0] + $temp_horas;
        
    if($horas<10)
        $horas= '0'.$horas;
    
    if($minutos<10)
        $minutos= '0'.$minutos;
    
    if($segundos<10)
        $segundos= '0'.$segundos;
        
    $rst_hrs = $horas.':'.$minutos.':'.$segundos;    

    return ($rst_hrs);    
    
    }     
    
    /**
     * Obtiene los años desde una fecha hasta hoy
     */
    static function getAnyos($fecha){
    	
    	//fecha actual
		$dia = date('j');
		$mes = date('n');
		$ano = date('Y');
		 
		//fecha de nacimiento
		list($anonac,$mesnac,$dianac) = explode("-",$fecha);
		 
		//si el mes es el mismo pero el día inferior aun no ha cumplido años, le quitaremos un año al actual
		if ( ($mesnac == $mes) && ($dianac > $dia) ){
			$ano = ($ano-1);
		}
		 
		//si el mes es superior al actual tampoco habrá cumplido años, por eso le quitamos un año al actual
		if ($mesnac > $mes){
			$ano = ($ano-1);
		}
		 
		//ya no habría mas condiciones, ahora simplemente restamos los años y mostramos el resultado como su edad
		$anyos = ($ano-$anonac);
		 
		return $anyos;
		
    }
    
}

?>