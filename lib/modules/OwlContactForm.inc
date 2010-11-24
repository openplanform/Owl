<?php

/**
 * OWL (Open Web Library)
 * 
 * Software distribuido bajo la "New BSD License", mas información en /doc/LICENSE
 * 
 * Clase que implementa un formulario de contacto compatible con Owl
 * 
 * @category Owl
 * @package Owl
 * @license New BSD License (http://www.opensource.org/licenses/bsd-license.php)
 * @author Nicolás Palumbo <nico@ningen.es> 
 * @version 0.5
 * @since 0.5
 * 
 */

require_once 'OwlModule.inc';
require_once 'OwlException.inc';
require_once 'OwlCaptcha.inc';
require_once 'OwlSession.inc';
require_once 'OwlMailer.inc';

require_once 'helper/OwlLanguage.inc';
require_once 'helper/OwlString.inc';

class OwlContactForm extends OwlModule{
	
	/**
	 * Array que contendrá los campos del formulario
	 * @var array
	 */
	protected $fields;
	
	/**
	 * Texto del email a enviar
	 * @var string
	 */
	protected $message;
	
	/**
	 * Mailer 
	 * @var OwlMailer
	 */
	protected $mailer;
	
	/**
	 * Herramienta de idioma
	 * @var OwlLanguage
	 */
	protected $lang;
	
	/**
	 * Devuelve el contenido del mail
	 * @param array $fields
	 * @param array $POST
	 * @param boolean $html
	 */
	protected function createContactMail($fields, $POST, $mode = 'html'){
		
		if ($mode == 'html'){
			return $this->createHtmlContactMail($fields, $POST);
		} elseif ($mode == 'plain') {
			return $this->createPlainContactMail($fields, $POST);
		}
		
	}
	
	/**
	 * Crea el mensaje de contacto en texto plano
	 * @param array $fields
	 * @param array $POST
	 * @return string
	 */
	protected function createPlainContactMail($fields, $POST){
		
		$this->lang = new OwlLanguage();
		
		$this->message .= "Apreciado Cliente,\n\n";
		$this->message .= "Un usuario le ha enviado un mensaje mediante la página de contactos de su sitio web, a continuación le detallamos el contenido de dicho mensaje. También le recordamos que puede contactar al usuario, respondiendo este mail.\n\n";
		
		$this->message .= 'Contenido del mensaje:';
		
		foreach($fields as $fieldname=>$field){
			
			if (array_key_exists($fieldname, $POST) && $POST[$fieldname] != ''){
				
				if ($fieldname == 'pais'){
					$this->message .= $field['label'].': '.$this->lang->getPaisEs($POST[$fieldname]) . "\n";
				} elseif( $fieldname == 'session' || $fieldname == 'captcha'){
					continue;
				} else {
					$this->message .= $field['label'].': ' . $POST[$fieldname] . "\n";
				}
				
			}
			
		}
		
		$this->message .= "\nFin del mensaje enviado.\nUn cordial saludo.";
		
		return $this->message;
		
		
	}
	
	
	/**
	 * Crea el mensaje de contacto en formato html
	 * @param array $fields
	 * @param array $POST
	 * @return string
	 */
	protected function createHtmlContactMail($fields, $POST){
		
		$this->lang = new OwlLanguage();
		
		$this->message .= '<body style="padding: 10px; font: normal 12px Arial;">';
		
		$this->message .= "<p>Apreciado Cliente,</p>";
		$this->message .= "<p>Un usuario le ha enviado un mensaje mediante la página de contactos de su sitio web, a continuación le detallamos 
		el contenido de dicho mensaje. También le recordamos que puede contactar al usuario, respondiendo este mail.</p><br />";
		
		$this->message .= '<div style="border: 1px solid #CFCFCF;background-color: #F5F5F5; padding: 10px 20px;">';
		$this->message .= '<h3 style="font-size: 14px; color: #1F1F1F; text-decoration: underline;">Contenido del mensaje:</h3>';
		
		foreach($fields as $fieldname=>$field){
			
			if (array_key_exists($fieldname, $POST) && $POST[$fieldname] != ''){
				
				if ($fieldname == 'pais'){
					$this->message .= '<p><strong>'.$field['label'].':</strong> '.$this->lang->getPaisEs($POST[$fieldname]).' </p>';
				} elseif( $fieldname == 'session' || $fieldname == 'captcha'){
					continue;
				} else {
					$this->message .= '<p><strong>'.$field['label'].':</strong> '.$POST[$fieldname].' </p>';
				}
				
			}
			
		}
		
		$this->message .= '</div>';
		
		$this->message .= '<br/><p>Fin del mensaje enviado.<br />Un cordial saludo.<br /><br />--<br /><a href="http://www.xinax.net">xinax</a> mailer v1.0</p>';
		
		$this->message .= '</body>';
		
		return $this->message;
		
	}
	
	/**
	 * Intenta obtener un valor desde el request
	 * si lo logra lo devuelve 
	 * @param string $keyname
	 * @return string
	 */
	protected function get( $keyname ){
		
		if (array_key_exists($keyname, $_REQUEST) && $_REQUEST[$keyname] != ''){
			return $_REQUEST[$keyname];
		}
		
	}

}

?>