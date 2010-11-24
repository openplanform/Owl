#!/bin/sh

# Valores variables
OWL_VERSION="0.5.4"

# Directorio

if [ -z "$1" ]; then

	echo ""
	echo -e "[" "\033[31mERROR\033[0m" "] Parámetro requerido - directorio de instalación"
	echo ""
	exit;
	
fi

# Base de datos

if [ -z "$2" ]; then

	echo ""
	echo -e "[" "\033[31mERROR\033[0m" "] Parámetro requerido - nombre de base de datos"
	echo ""
	exit;
	
fi

OWL_TARGETDIR=$1;
OWL_DBNAME=$2;

# Se instala el framework

if [ -d "$OWL_TARGETDIR" ]; then

	# Aqui se definirán los targets tanto de desarrollo como producción
	
	if [ "$HOSTNAME" = "ldes" ]; then
		OWL_DIR="/var/www/owl/"
	else 
		OWL_DIR="/var/www/owl/"
	fi
	
	
	# Se cambia al directorio destino
	
	cd $OWL_TARGETDIR
	echo ""
	
	
	# Estructura de directorios y copia de archivos iniciales
	
	cp $OWL_DIR"bin/framework/resources/base.htaccess" .htaccess
		
	cp -R $OWL_DIR"bin/extranet/resources/public/" .
	
	cp $OWL_DIR"bin/framework/resources/index.php" public/
	
	cp $OWL_DIR"bin/framework/resources/public.htaccess" public/.htaccess		
	
	mkdir app
	
	mkdir app/configs		
	
	cp $OWL_DIR"bin/extranet/resources/configs/application.ini" app/configs/
	
	cp $OWL_DIR"bin/framework/resources/OwlGlobals.php" app/configs/

	cp $OWL_DIR"bin/extranet/resources/configs/SessionObjects.php" app/configs/
	
	cp -R $OWL_DIR"bin/extranet/resources/controllers/" app/controllers/
	
	cp -R $OWL_DIR"bin/extranet/resources/models/" app/models/
	
	cp -R $OWL_DIR"bin/extranet/resources/layouts/" app/layouts/
	
    mkdir app/classes
	
	mkdir app/modules
		
	cp -R $OWL_DIR"bin/extranet/resources/views/" app/views/
	
	echo -e "[" "\033[32mOK\033[0m" "] Archivos copiados"
	
	
	# Enlaces simbólicos necesarios
	
	ln -s $OWL_DIR owl
	
	ln -s $OWL_DIR"share/captcha/images/" public/img/captcha
	
	echo -e "[" "\033[32mOK\033[0m" "] Enlaces creados"
		
	
	# Se establecen los permisos y propietarios
	
	chmod -R 775 $OWL_TARGETDIR
	
	if [ "$HOSTNAME" = "ldes" ]; then
		chown -R smbuser:desarrollo $OWL_TARGETDIR
	fi
	
	chmod 777 app/models	
	
	echo -e "[" "\033[32mOK\033[0m" "] Permisos establecidos"
	
		
	# Se instala la base de datos
	
	mysql -u terminator -phastalavistababy "-D"$OWL_DBNAME < $OWL_DIR"bin/extranet/resources/dbase.sql"
	
	if [ $? -ne 0 ]; then
		echo -e "[" "\033[31mERROR\033[0m" "] Error al crear la base de datos"
	else 
		echo -e "[" "\033[32mOK\033[0m" "] Base de datos instalada"
	fi
	
	
	# Todo ha ido bien

	echo ""		
	echo -e "[" "\033[32mOK\033[0m" "] Felicitaciones!, OWL - Open Web Library ($OWL_VERSION) ha sido instalado correctamente en $OWL_TARGETDIR"
	echo ""
	
else 

	# Directorio de instalación no existe

	echo ""
	echo -e "[" "\033[31mERROR\033[0m" "] El directorio de destino no existe"
	echo ""
	exit;	
			
fi
