#!/bin/bash

# Valores variables
OWL_VERSION="0.5.4"

# Se toman los argumentos
if [ -z "$1" ]; then
	echo ""
	echo "Instalador de OWL ($OWL_VERSION) - Open Web Library" 
	echo "Modo de uso: install.sh /ruta/completa/destino/"
	echo ""
else
	
	# Se comprueba si existe el directorio destino

	if [ -d "$1"  ]; then
		
		OWL_TARGETDIR="$1"
	
		# Aqui se definirán los targets tanto de desarrollo como producción
		
		if [ "$HOSTNAME" = "ldes" ]; then
		    OWL_DIR="/var/www/owl/"
		else 
		    OWL_DIR="/var/www/owl/"
		fi
		
		
		# Se cambia al directorio destino
		
		cd $OWL_TARGETDIR
		
		
		# Estructura de directorios y copia de archivos iniciales
		
		cp $OWL_DIR"bin/framework/resources/base.htaccess" .htaccess
		
		mkdir public
		
		cp $OWL_DIR"bin/framework/resources/index.php" public/
		
		cp $OWL_DIR"bin/framework/resources/public.htaccess" public/.htaccess

		mkdir public/css
		
		mkdir public/js
		
		mkdir public/img				
		
		mkdir app
		
		mkdir app/configs		
		
		cp $OWL_DIR"bin/framework/resources/application.ini" app/configs/
		
		cp $OWL_DIR"bin/framework/resources/OwlGlobals.php" app/configs/

		cp $OWL_DIR"bin/framework/resources/SessionObjects.php" app/configs/
		
		mkdir app/controllers
		
		cp $OWL_DIR"bin/framework/resources/indexController.php" app/controllers/ 
		
		mkdir app/models

		chmod 777 app/models

        # Directorio de log

        mkdir app/log

        chown -R www-data:www-data app/log

        chmod -R 755 app/log
		
		mkdir app/layouts
		
		mkdir app/classes
		
		mkdir app/modules
		
		mkdir app/views
		
		mkdir app/views/index
		
		touch app/views/index/index.phtml
		
		
		# Enlaces simbólicos necesarios
		
		ln -s $OWL_DIR owl
		
		ln -s $OWL_DIR"share/captcha/images/" public/img/captcha
		
		
		# Se establecen los permisos
		
		chmod -R 775 $OWL_TARGETDIR
		
		
		# Todo ha ido bien

		echo ""		
		echo -e "[" "\033[32mOK\033[0m" "] Felicitaciones!, OWL - Open Web Library ($OWL_VERSION) ha sido instalado correctamente en $OWL_TARGETDIR"
		echo ""
		
	else
	
		echo ""
		echo -e "[" "\033[31mERROR\033[0m" "] El directorio de destino no existe"
		echo ""
		exit;	
		
	fi
	
fi

