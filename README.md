# Laboratorio 2. Sistemas Operativos 2017-1

## Compilación

En este trabajo se agrega una nueva syscall al kernel de linux 4.4.64
La syscall que recibe un stado de proceso, entrega la informacion de todos los procesos que se encuentren en ese estado, agregando la informacion de su hijos

Para compilar:

* Determinar la cantidad de CPUs disponibles
	* `lscpu`
* Preparacion
* en /linux-4.4.64 
	* `menuconfig`
	* append custom name
	* save
	* exit
* Compilar
	- `make -j<numero cpus> deb-pkg`
	- esperar de 1 a 4 horas
* Instalar
	* `cd ..`
	* `sudo dpkg -i linux*.deb`
	* `sudo update-grub`


En caso de error instalar ncurses y openssl
* `sudo apt-get install libncurses-dev python-pip python-dev libffi-dev libssl-dev libxml2-dev libxslt1-dev libjpeg8-dev zlib1g-dev`


## Uso

Para usar los syscalls nuevos compilar main.c con `make` o `gcc -o lab main.c`

Para ejecutar el programa de test
* Listar todos los procesos y sus estados
	* `lab -l [-a <32|64>]`
	* `lab -l` para listar usando la syscall de 64 bits 
* Listar todos los procesos con un estado en especifico
	* `lab -s <state> [-a <32|64>]`
	* `lab -s <state>` syscall de 64 bits por defecto


	

