#!/bin/sh

# Directorio

if [ -z "$1" ]; then
	echo ""
	echo "- Parámetro requerido[1]: directorio"
	echo ""
	exit;
fi

# Base de datos

if [ -z "$2" ]; then
	echo ""
	echo "- Parámetro requerido[2]: nombre de base de datos"
	echo ""
	exit;
fi

DIRECTORIO=$1;
DBNAME=$2; 

# Se instala el framework

cd ../framework/
bash ./install.sh $DIRECTORIO &> /dev/null
RESULT_FW=$?;

cd ../extranet/

if [ $RESULT_FW != 0 ]; then
	echo -e "[" "\033[31mERROR\033[0m" "] al instalar el framework."
	exit;
else 
	echo -e "[" "\033[32mOK\033[0m" "] NingenCMS Instalado"
fi


# Se copian los archivos


