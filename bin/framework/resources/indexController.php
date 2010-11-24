<?php

require_once 'OwlController.inc';
require_once 'helper/OwlCmsHtmlHelper.inc';

class indexController extends OwlController{
	
	public function indexAction(){
		
		// Eliminar esta linea, presentación del CMS
		echo OwlCmsHtmlHelper::getHtmlInstallPage();
		
	}	
	
	
}

?>