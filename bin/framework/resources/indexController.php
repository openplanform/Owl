<?php

require_once 'OwlController.inc';
require_once 'helper/OwlHtmlHelper.inc';

class indexController extends OwlController{
	
	public function indexAction(){
		
		// Eliminar esta linea, presentación del CMS
		echo OwlHtmlHelper::getHtmlInstallPage();
		
	}	
	
	
}

?>
