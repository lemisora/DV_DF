# Traductor de Dirección Virtual a Física
- Este programa mostrará la dirección física resultante de acuerdo a la dirección virtual proporcionada

- Se define desde un archivo el número de páginas y el número de marcos
- Los elementos de la tabla de páginas se encuentran en el mismo archivo


## Comandos para instalar (Linux)
Instalar meson como sea posible considerando que sea la ultima version**Ultima version Usada 1.5.1**
```bash
pip install meson
```
```bash
pip install meson==1.5.1
```

***La version de `apt` puede estar desactualizada***

## Compilar con Meson
```bash
meson setup out
meson compile -C out/
```

### Ejecutar en Linux
```bash
./out/traductor {archivo usado}
```

## Ejemplo básico de como funcionaría:
- Se parte sabiendo que de forma predeterminada el programa genera aleatoriamente los datos que van en cada una de las entradas de la tabla de páginas, entre los datos se encuentra el número de marco
### Tratando la dirección virtual
- Para una tabla de páginas de 512 páginas, que conste de 1024 bytes para cada página y una memoria que conste de 32 marcos para página

    - Sabiendo que la DV consiste en No.Pagina + Desplazamiento
    	- El número de bits de desplazamiento se obtiene con log2(1024) que resulta en 10, 10 bits
	    - El número de bits para el indizado de páginas se obtiene con log2(512) que resulta en 9, 9 bits
    	- Por lo tanto la dirección virtual para este caso es de 19 bits

    - Sabiendo que la DF consiste en No.Marco + Desplazamiento
    	- El número de bits de desplazamiento sigue siendo de 10, 10 bits
	    - El número de bits para el indizado de marcos se obtiene con log2(32) que resulta en 5, 5 bits
    	- Por tanto la dirección física para este caso es de 15 bits

- Suponga que la dirección virtual ingresada sea 33362, cuyo número de página es 32 y el desplazamiento es 594
    - Se tendría que ingresar en su forma binaria, que se vería de la siguiente forma: 1000001001010010
		- Con 19 bits es: 0001000001001010010
	    - Se guarda una copia de la dirección virtual en una variable auxiliar para poder tratar con los bits
    - El número de página es: 32, se obtiene con el corrimiento a la izquierda de bits de desplazamiento, o sea, 10
        - En forma binaria es 100000, con los 9 bits es: 000100000
- El valor de desplazamiento se obtiene con corrimiento a la derecha de bits de desplazamiento poniendo los bits del número de página en su estado original
  -	 Se crea una máscara aplicando el operador XOR (^) sobre el número anterior que debería ser 32768 con el valor máximo de uint32 (65535)
            que tiene todos los bits encendidos, y se obtiene el siguiente número 594, este último es el valor del desplazamiento

### Obteniendo la dirección física
- Se necesita conocer el número de marcos y el desplazamiento
- El desplazamiento ya se tiene de los pasos anteriores, es 594
- Para obtener el número de marco solo se debe de acceder a la entrada de la página y leer el campo **n_frame**
- Suponiendo que el número de marco en la página fuese 22
    * En forma binaria es 10110
    * Entonces se forma la dirección física de la siguiente forma
        + Se aplica corrimiento a la izquierda al número de marco, se mueve el número de bits de desplazamiento, para dejarlas en su posición
        + Después se realiza enmascaramiento con OR (|) con el valor de desplazamiento, para encender los bits correspondientes obteniendo finalmente la dirección física que es la siguiente: 101 1010 0101 0010
        + En decimal es 23122
 #### Resultados finales
Para este caso particular:
- Dado que se ingresó la siguiente dirección virtual:  $33362_{10}$ ; $1000001001010010_{2}$
- Se obtiene como resultado la siguiente dirección física:

$23122_{10}$ ; $101101001010010_{2}$
