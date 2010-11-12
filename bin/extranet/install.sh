#!/bin/sh

# Valores variables
NINGENCMSVERSION="0.5.2"

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

TARGETDIR=$1;
DBNAME=$2;

# Se instala el framework

if [ -d "$TARGETDIR" ]; then

	# Aqui se definirán los targets tanto de desarrollo como producción
	
	if [ "$HOSTNAME" = "ldes" ]; then
		NINGENCMSDIR="/var/www/ningenCMS/"
	else 
		NINGENCMSDIR="/var/www/ningenCMS/"
	fi
	
	
	# Se cambia al directorio destino
	
	cd $TARGETDIR
	echo ""
	
	
	# Estructura de directorios y copia de archivos iniciales
	
	cp $NINGENCMSDIR"bin/framework/resources/base.htaccess" .htaccess
		
	cp -R $NINGENCMSDIR"bin/extranet/resources/public/" .
	
	cp $NINGENCMSDIR"bin/framework/resources/index.php" public/
	
	cp $NINGENCMSDIR"bin/framework/resources/public.htaccess" public/.htaccess		
	
	mkdir app
	
	mkdir app/configs		
	
	cp $NINGENCMSDIR"bin/extranet/resources/configs/application.ini" app/configs/
	
	cp $NINGENCMSDIR"bin/framework/resources/NingenGlobals.php" app/configs/

	cp $NINGENCMSDIR"bin/extranet/resources/configs/SessionObjects.php" app/configs/
	
	cp -R $NINGENCMSDIR"bin/extranet/resources/controllers/" app/controllers/
	
	cp -R $NINGENCMSDIR"bin/extranet/resources/models/" app/models/
	
	cp -R $NINGENCMSDIR"bin/extranet/resources/layouts/" app/layouts/
	
    mkdir app/classes
	
	mkdir app/modules
		
	cp -R $NINGENCMSDIR"bin/extranet/resources/views/" app/views/
	
	echo -e "[" "\033[32mOK\033[0m" "] Archivos copiados"
	
	
	# Enlaces simbólicos necesarios
	
	ln -s $NINGENCMSDIR ningencms
	
	ln -s $NINGENCMSDIR"share/captcha/images/" public/img/captcha
	
	echo -e "[" "\033[32mOK\033[0m" "] Enlaces creados"
		
	
	# Se establecen los permisos y propietarios
	
	chmod -R 775 $TARGETDIR
	
	if [ "$HOSTNAME" = "ldes" ]; then
		chown -R smbuser:desarrollo $TARGETDIR
	fi
	
	chmod 777 app/models	
	
	echo -e "[" "\033[32mOK\033[0m" "] Permisos establecidos"
	
		
	# Se instala la base de datos
	
	mysql -u terminator -phastalavistababy "-D"$DBNAME < $NINGENCMSDIR"bin/extranet/resources/dbase.sql"
	
	if [ $? -ne 0 ]; then
		echo -e "[" "\033[31mERROR\033[0m" "] Error al crear la base de datos"
	else 
		echo -e "[" "\033[32mOK\033[0m" "] Base de datos instalada"
	fi
	
	
	# Todo ha ido bien

	echo ""		
	echo -e "[" "\033[32mOK\033[0m" "] Felicitaciones!, ningenCMS ($NINGENCMSVERSION) ha sido instalado correctamente en $TARGETDIR"
	echo ""
	
else 

	# Directorio de instalación no existe

	echo ""
	echo -e "[" "\033[31mERROR\033[0m" "] El directorio de destino no existe"
	echo ""
	exit;	
			
fi
