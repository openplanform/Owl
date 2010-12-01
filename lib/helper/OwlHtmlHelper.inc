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
 * Clase estática con métodos de utilidad para pequeñas presentaciones en código html.
 * Mas conocida como la "dirty class"...
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlHtmlHelper{
	
	/**
	 * Devuelve el codigo html para mostrar la información de debug de una excepcion
	 * @param $message
	 * @param $traceInfo
	 * @param $line
	 * @param $file
	 * @return string
	 */
	public static function getHtmlExceptionDebug($message = '', $traceInfo = array(), $line = '', $file = ''){
		
		ob_start();
		
		if ($message != ''){
			echo '<p><strong>Exception message: </strong>' . $message . '</p>';
		}
		
		if ($file != ''){
			echo '<p><strong>File: </strong>' . $file . '</p>';
		}
		
		if ($line != ''){
			echo '<p><strong>Line: </strong>' . $line . '</p>';
		}		
		
		if (count($traceInfo > 0)) {
		
			?><table border="1">
					<thead>
						<tr>
							<th>file</th>
							<th>line</th>
							<th>function</th>
							<th>class</th>
						</tr>
					</thead>
			<tbody><?	
			
			foreach ($traceInfo as $traceLine){
				
				?><tr>
					<td><?= $traceLine['file'] ?></td>
					<td><?= $traceLine['line'] ?></td>
					<td><?= $traceLine['function'] ?></td>
					<td><?= $traceLine['class'] ?></td>
				</tr><?
				
			}
			
			?></tbody></table><?
			
		}
		
		$html = ob_get_clean();
		return $html;		
		
	}
	
	
	/**
	 * Imprime el código de una pagina de error del servidor
	 * @param string $title
	 * @param string $errorCode
	 * @param string $errorSubtitle
	 * @param string $errorDescription
	 * @param string $adminMail
	 * @return string
	 */
	public static function getHtmlErrorPage($title, $errorCode, $errorSubtitle, $errorDescription, $adminMail = ''){

		ob_start();
		
		echo '<?xml version="1.0" encoding="UTF-8" ?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">' . "\n";
		
		?><html xmlns="http://www.w3.org/1999/xhtml">
			<head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
				<title><?= $title ?></title>
				<style type="text/css">
					*, html, body{
						margin: 0; 
						padding: 0;
						font-family: Arial, Helvetica, sans-serif;
					}
					body {
						background-color: #8F8F8F;
					}
					#t{
						background-color: #3F3F3F; 
						height: 6em; 
						padding: 1em;
					}
					#b{}
					h1{
						color: #EFEFEF; 
						font-weight: bold; 
						font-size: 6em; 
						text-shadow: 5px 5px 5px #000
					}
					h2{
						font-size: 1.2em; 
						background-color: #EFEFEF;
						padding-left: 1em; 
						line-height: 1.5em; 
						color: #4F4D4A;
					}
					p{
						font-size: .9em; 
						color: #EFEFEF; 
						margin-left: 1em; 
						margin-top: 1em; 
						text-shadow: 1px 1px 1px #2F2F2F; 
						margin-top: 2em;
					}p a{ 
						color: #FFB32F;
					}
					table{
						font-size: .9em; 
						color: #EFEFEF; 
						text-shadow: 1px 1px 1px #2F2F2F;
						text-align: left;
						margin-left: 1em;
						margin-top: 1em;
						border-collapse: collapse;
					}
					p strong,
					table th{
						color: #FFB32F; 
					}
					table th,
					table td{
						padding: 0.3em;
					}
				</style>
			</head>
		<body>
		
			<div id="t">
				<h1><?= $errorCode ?></h1>
			</div>
			
			<h2><?= $errorSubtitle ?></h2>
			
			<div id="b">
				<?= $errorDescription ?>
			</div>
			
			<div id="c">
				<p>Si el problema continúa, por favor contacte al administrador: <a href="">nobody@nobody.net</a></p>
			</div>
			
		</body>
		
	</html><?
		
		
		$html = ob_get_clean();
		return $html;
		
	}
	
	/**
	 * Devuelve el codigo de la página de mantenimiento
	 * @return string
	 */
	public static function getHtmlMantenimientoPage(){
		
		return self::getHtmlErrorPage('Sitio en mantenimiento', '200', 'El sitio se encuentra en mantenimiento.', '<p>Se están realizando tareas de mantenimiento en este momento. Por favor, sírvase de visitarnos mas tarde, disculpe las molestias.</p>');
		
	}
	
	/**
	 * Imprime el código de una pagina de error del servidor
	 * @param string $title
	 * @param string $errorCode
	 * @param string $errorSubtitle
	 * @param string $errorDescription
	 * @param string $adminMail
	 * @return string
	 */
	public static function getHtmlInstallPage(){

		ob_start();
		
		echo '<?xml version="1.0" encoding="UTF-8" ?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">' . "\n";
		
		?><html xmlns="http://www.w3.org/1999/xhtml">
			<head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
				<title>Instalación de OWL</title>
				<style type="text/css">
					*, html, body{
						margin: 0; 
						padding: 0;
						font-family: Arial, Helvetica, sans-serif;
					}
					body {
						background-color: #8F8F8F;
					}
					#t{
						background-color: #3F3F3F; 
						height: 6em; 
						padding: 1em;
					}
					#b{}
					h1{
						color: #EFEFEF; 
						font-weight: bold; 
						font-size: 6em; 
						text-shadow: 5px 5px 5px #000
					}
					h2{
						font-size: 1.2em; 
						background-color: #EFEFEF;
						padding-left: 1em; 
						line-height: 1.5em; 
						color: #4F4D4A;
					}
					p{
						font-size: .9em; 
						color: #EFEFEF; 
						margin-left: 1em; 
						margin-top: 1em; 
						text-shadow: 1px 1px 1px #2F2F2F; 
						margin-top: 2em;
					}p a{ 
						color: #FFB32F;
					}
					table{
						font-size: .9em; 
						color: #EFEFEF; 
						text-shadow: 1px 1px 1px #2F2F2F;
						text-align: left;
						margin-left: 1em;
						margin-top: 1em;
						border-collapse: collapse;
					}
					p strong,
					table th{
						color: #FFB32F; 
					}
					table th,
					table td{
						padding: 0.3em;
					}
				</style>
			</head>
		<body>
		
			<div id="t">
				<h1>Correcto</h1>
			</div>
			
			<h2>La instalación de OWL ha concluído con éxito </h2>
			
			<p>Para más información revisar el directorio <strong>doc/</strong> de la librería.</p>
			
		</body>
		
	</html><?
		
		
		$html = ob_get_clean();
		return $html;
		
	}	
		
}

?>