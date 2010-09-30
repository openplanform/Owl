#!/bin/bash

# Valores variables
NINGENCMSVERSION="0.5.0"

# Se toman los argumentos
if [ -z "$1" ]; then
	echo ""
	echo "Instalador ningenCMS 0.5" 
	echo "Modo de uso: install.sh /ruta/completa/destino/"
	echo ""
else
	
	# Se comprueba si existe el directorio destino

	if [ -d "$1"  ]; then
		
		TARGETDIR="$1"
	
		# Aqui se definirán los targets tanto de desarrollo como producción
		
		if [ "$HOSTNAME" = "ldes" ]; then
		    NINGENCMSDIR="/var/www/ningenCMS/"
		else 
		    NINGENCMSDIR="/var/www/ningenCMS/"
		fi
		
		
		# Se cambia al directorio destino
		
		cd $TARGETDIR
		
		
		# Estructura de directorios y copia de archivos iniciales
		
		cp $NINGENCMSDIR"bin/resources/base.htaccess" .htaccess
		
		mkdir public
		
		cp $NINGENCMSDIR"bin/resources/index.php" public/
		
		cp $NINGENCMSDIR"bin/resources/public.htaccess" public/.htaccess

		mkdir public/css
		
		mkdir public/js
		
		mkdir public/img				
		
		mkdir app
		
		mkdir app/configs		
		
		cp $NINGENCMSDIR"bin/resources/application.ini" app/configs/
		
		cp $NINGENCMSDIR"bin/resources/NingenGlobals.php" app/configs/
		
		mkdir app/controllers
		
		cp $NINGENCMSDIR"bin/resources/indexController.php" app/controllers/ 
		
		mkdir app/models

		chmod 777 app/models
		
		mkdir app/layout
		
		mkdir app/modules
		
		mkdir app/views
		
		mkdir app/views/index
		
		touch app/views/index/index.phtml
		
		
		# Enlaces simbólicos necesarios
		
		ln -s $NINGENCMSDIR ningencms
		
		ln -s $NINGENCMSDIR"share/captcha/images/" public/img/captcha
		
		
		# Todo ha ido bien

	    echo ""		
		echo "Felicitaciones!, ningenCMS ($NINGENCMSVERSION) ha sido instalado correctamente en $TARGETDIR"
		echo ""
		
	else
		echo ""
		echo "ERROR: el directorio de destino ($1) no existe"
		echo ""
	fi
	
fi

