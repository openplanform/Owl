<?php

require_once 'NingenController.inc';
require_once 'helper/NingenCmsHtmlHelper.inc';

class indexController extends NingenController{
	
	public function indexAction(){
		
		// Eliminar esta linea, presentación del CMS
		echo NingenCmsHtmlHelper::getHtmlInstallPage();
		
	}	
	
	
}

?>