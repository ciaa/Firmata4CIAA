# Guia de instalación#

***
## Prerequisito ##

Para poder hacer uso de los programas que se presentan debe tener instalado el software del proyecto CIAA. De no contar con él diríjase a la [web oficial del proyecto](http://www.proyecto-ciaa.com.ar/devwiki/doku.php?id=docu:fw:bm:ide:install) para descargarlo.


## Firmata4CIAA ##

__Paso 1:__ Descargar el firmware del [repositorio oficial del proyecto Firmata4CIAA](https://github.com/OlivieriIan/Firmata4CIAA)

__Paso 2:__ Copiar la carpeta _Firmata4CIAA_ dentro de la carpeta Firmware del proyecto.  
- Ruta de Firmware en Windows: C:\CIAA\Firmware   
- Ruta de Firmware en Linux: /home/$USER/ciaa-ide/Firmware

_Por ejemplo_: pegar la carpeta Firmata4CIAA descargada dentro de C:\CIAA\Firmware

__FIXME: Fijate porque cuando lo subis seguro tenes q descomprimirlo para obtener la carpeta deseada. Agrega eso aca para evitar q peguen lo q descomprimen directamente__

__Paso 3:__ Cambiar la ruta del proyecto actual en el _Makefile.mine_ para poder compilarlo.

Si la carpeta Firmata4CIAA fue pegado en Firmware, la ruta del Makefile será:   _PROJECT_PATH ?= Firmata4CIAA_, ya que los path en el makefile son relativos a la carpeta Firmware.

__Paso 4:__ Subir el programa a la placa

__En Windows__:   
1 - Abrir el _CIAA cygwin_  
2 - Navegar a la carpeta firmware introduciendo: _cd C:/CIAA/Firmware_  
3 - Introducir el comando _make clean_  
4 - Introducir el comando _make_ (puede tardar unos minutos)  
5 - Introducir el comando _make download_

__En Linux__  
1 - Abrir la terminal de linux  
2 - Introducir " _export PATH=$PATH:$HOME/ciaa-ide/gcc-arm-none-eabi-4_9-2015q1/bin:$HOME/ciaa-ide/openocd-0.9.0/src_ " (sin espacios ni comillas)  
3 - Navegar a la carpeta firmware introduciendo: _/home/$USER/ciaa-ide/Firmware_  
4 - Introducir el comando _make clean_  
5 - Introducir el comando _make_  
6 - Introducir el comando _make download_

Si en el último paso (make download) obtiene el siguiente mensaje de error:

![make download error](\Resources\1-Guia_de_instalacion\1-1-makeDownload_ERROR.png)

reintente el último paso (make clean).

__Paso 5:__ La placa ya está lista para comunicarse via Firmata. Puede probar si todo funciona correctamente mediante el programa _Firmata Test_ 


## Snap ##
### Instalación del Snap ###

Ir a la [web de Snap](http://s4a.cat/snap/) y descargar la versión acorde a su sistema operativo.

![Snap download](\Resources\1-Guia_de_instalacion\1-2-snap_download.png)

__En Windows__  
Ejecutar el archivo descargado y seguir los pasos de instalación.

__En Linux__  
Abrir la terminal, navegar a la carpeta donde fue descargado el archivo (por ejemplo: cd /home/$USER/Downloads/Snap4Arduino) y luego introducir ./Snap4Arduino


### Conecxión a la placa desde Snap ###

Una vez abierto el programa, ir a la solapa Arduino y luego seleccionar conectar Arduino. Si, dice arduino, pero puede ser utilizado con la EDU-CIAA gracias al firmware que cargaron antes. 

![Conectar placa](\Resources\1-Guia_de_instalacion\1-3-Connecting_Board.png)

Si la placa no se conecta automáticamente es porque hay varios dispositivos USB conectados y preguntará en cual de ellos está conectada la placa. Para poder establecer la conexión es necesario elegir el puerto que corresponda. 
 

En este caso (windows) el puerto es el COM4, por lo que al intentar conectarse se obtendrá el mensaje de la izquierda, seguido del de la derecha si la conexión fue exitosa.

 
![Snap conexión exitosa](\Resources\1-Guia_de_instalacion\1-4-Happy_Prototyping.png)

En caso de que la conexión falle reintentarlo, y en caso de que Snap no lo permita cierrelo y vuelvalo a abrir.

### Cambio de idioma ###

![Snap conexión exitosa](\Resources\1-Guia_de_instalacion\1-5-Idioma.png)


### Alternativa a Snap ###

Otra opción es el _Firmata Test_. Esta aplicación no permite crear programas, pero si controlar la placa más rápidamente.   
Para descargarla, ir a la [web del proyecto Firmata](http://firmata.org/wiki/Main_Page), a la sección de "Firmata Test Program".

## Mapeo de pines ##

Para poder operar la placa a través del protocolo Firmata es necesario saber cuál es el mapeo de pines, ya que nos indica la relación entre los "pines" que Snap y Firmata Test utilizan, y los pines físicos de la placa.

El mapeo de pines actualizado puede ser encontrado en [el repositorio oficial del proyecto Firmata4CIAA]()

__Agregá un link al docs de tu github para q vean el pinmap__  

## Ejemplo ##
El siguiente programa permite que, al presionar las teclas 1, 2 o 3 se enciendan los leds 1,2 o 3, respectivamente.

Para ello conecte la placa como se vió en los pasos anteriores y arme el siguiente programa.

![Ejemplo TecsLeds](\Resources\1-Guia_de_instalacion\1-6-TecsLeds.png)

Los bloques amarillos pueden ser obtenidos de la etiqueta _Control_, los azules de la etiqueta _Arduino_, y los verdes de la etiqueta _Operaciones_.  
Todas estas etiquetas pueden ser encontradas en la esquina superior izquierda, como se ve en la siguiente figura:

![Etiquetas](\Resources\1-Guia_de_instalacion\1-6-Snap_Labels.png)

En cuanto a valores de los pines digitales, 40, 41 y 42 corresponden al LED1, 2 y 3, mientras que 36, 37 y 38 a las TEC1, 2 y 3, respectivamente, de la placa. Esta información puede ser obtenida del mapeo de pines.

Es __importante__ tener un pequeño retardo en los programas hechos en Snap, ya que de no utilizar uno es muy proable que la aplicación se tilde y deba ser cerrada.
