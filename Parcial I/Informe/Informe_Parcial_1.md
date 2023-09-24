# Informe Primer Parcial Informática II 

## Observación acerca del integrado 74hc595

Nos hemos documentado acerca del funcionamiento del 74hc595, y hemos notado que se puede utilizar en modo cascading o cascada, de esta manera necesitaremos solamente 3 pínes digitales para controlar los 64 leds, ya que sin importar la
cantidad de 74hc595 que usemos la cantidad de pines necesarios sigue siendo constante. Esto nos lleva a la primera propuesta de la solución, utilizar 8 integrados.


### Nota

Para iniciar con el proceso de construcción de la solución, primero tuvimos que familiarizarnos con el funcionamiento a nivel de hardware, y software; por lo que tuvimos que hacer un entorno de pruebas para comprender cómo se programa y qué podiamos plantear. En pocas palabras en esta etapa estudiamos Arduino y nos documentamos acerca de todo lo necesario para plantear correctamente la solución.


```c++

//Nos familiarizamos acerca de como se programa el arduino tomando como base lo aprendido en c++

void setup(){

}

void loop(){
    
}

```
## Aplicación e Interpretación del código para el 74hc595

Para darnos una dirección en como empezar, primero analizamos el comportamiento de nuestro microcontrolador con respecto a su código, indagamos para encontrar la aplicación y modo de controlar este mismo, la manera de hacer el setup y como hacer que el procesamiento de información para este fuera eficaz y legible a lo largo de nuestro ensamblado.


![ensamblado](https://i.imgur.com/0f7lWXr.png)


```c++

//Como se plantea el definir nuestras variables y como hacerlas funcionar acorde a nuestro mc

int pinData  = 2; //Declarado acorde a nuestro ensamble (que en el caso del modelo de TK
int pinLatch = 3;
int pinClock = 4;

void ledWrite(int FLed){     //Nuestro declare para el estado del LED
   shiftOut(pinData, pinClock, LSBFIRST, FLed);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}

void setup(){
   pinMode(pinData, OUTPUT); //Declaramos como outputs (salidas) para que se registren durante la ejecución del loop
   pinMode(pinLatch, OUTPUT);
   pinMode(pinClock, OUTPUT);
}

void loop(){
   ledWrite(128); delay(TIEMPO); //Se prende fisicamente el LED
}

```

Tambien denotamos como se comporta el valor de FLed en nuestros LEDs, de modo que acorde a los bytes ingresados será el modo de que sea encendido estos, en el ensamblaje tenemos 3 disponibles de los cuales se prendian en la sumatoria de los bytes, o por valor de byte sera el LED que estara prendido, asumimos que este comportamiento estaba basado sea o por el reloj o por el data que se envia.


## Manejo de encendido de leds

A cada 74hc595 se le puede asignar un valor binario que podemos considerar un byte, dependiendo de la combinación de bits, se encenderán determinados leds, supongamos que tenemos la siguiente fila de led.

Si usamos el el byte 00000001 se encenderá el último led únicamente:
Si usamos el byte 1111111 se encenderán todos los leds.

Por otra parte el integrado 74hc595 puede programarse en dos modos LSB (Least Significant Bit) o MSB (Most Significant Bit).

En modo LSB: EL primer bit que se transmite es el último es decir el menos significativo.
En modo MSB: EL primer bit que se transmite es el primero es decir el más significativo.

Por otra parte también podemos indicar que leds encendemos con el valor entero del byte apropiado, gracias a su comportamiento con las operaciones genericas de la suma y como se comporta de manera jerarquica los bits.

Ejemplo:

Si se usa 255 se encienden todos los de la fila.                //
Si se usa 128 se enciende el más significativo de la fila.      //
Si se usa 1 se enciende el menos significativo de la fila.      //

Cabe aclarar que esto sera con una fila que tenga el alcance suficiente para llegar a 1 (que a veces no funcionaba en arregols más pequeños como de 3 leds).

Para esto será necesario usar la función shiftout para enviar los datos seriados bit a bit.

[- Demo -](https://imgur.com/a/hb3Cpd1)

## Propuesta Inicial

No será una tarea complicada usar una matriz dinamica para generar los bytes y después liberar la memoria reservada, en base a ella podemos generar las secuencias con ciclos y no hacer uso de una solución trivial.

A modo de nuestro workflow trabajamos con un arreglo dinamico el cual fuera modificable para tener un pequeño acercamiento a como se dirige el proposito de nuestra practica.

del mismo modo se vería graficamente como...

```c++
...
(0,0,0,1) //4x4 de leds.
(0,0,1,0)
(0,1,0,0)
(1,0,0,0)
...

```
Este seria para la representación de como se veria para nuestras filas si tuvieramos de basis solo el 0 para apagado el 1 para encendido, como basis para el momento de que tengamos la idea concretada con todo funcionando al unisono.

## Propuesta de tareas para implementar impresión de patrones

* Hacer montaje en tinkercad
* Implementar en software una matriz en la que se van a generar los patrones o figuras para después reflejarlas en los leds.
* Crear una función que "traduzca" las filas de la matriz a bytes.
* Crear una funcionalidad que permita encender los leds en base a la matriz, ya que los leds pueden ser encendidos con numeros enteros correspondientes al valor decimal de cada byte. 
* Trabajar en la interacción usuario - simulación
* Generación de patrones automáticos
* Implementación de menu
* Optimizar recursos usando memoria dinámica y tener en cuenta el uso de punteros,

En esta lista se descibre brevemente el paso a paso inicial que hemos planteado para comenzar con la 
implementación.

## Resumen de planteamiento para la solución

Primero que todo convertiremos las filas de las matrices a bytes que serán usados luego en una función creada para encender los leds en base al valor décimal de los bytes.

![solucion](https://i.imgur.com/yeXCpAJ.jpg)

Como fue mencionado anteriormente se usará una matriz para predefinir las secuencias, esto se puede hacer manual o mediante ciclos en el caso de las secuencias.

Se implementarán funciones como:

```c++
...

verificacion();
imagen();
publik();
traduccionByte();


*/
verificacion() pedirá al usuario el tiempo que pasará entre encendido y apagado y la cantidad de repeticiones, para luego
reflejar esto en los leds.
/*


/*
imagen() pedirá al usuario la posición de una fila y una columna para invertir el valor que esta posición tiene asignanado,
de esta manera si contamos con una matriz 4x4 con todos sus leds apagados y el usuario ingresa [1][1]. 
*/

...
// La matriz resultante será esta
(1,0,0,0) 
(0,0,0,0)
(0,0,0,0)
(0,0,0,0)
...

/*
En el caso que el usuario ingrese un número fuera de rango se validará o automáticamente se cancelará la ejecución imprimiendo
la matriz que se había personalizado hasta ese momento.
*/

/*
publik() menu para interacción usuario-simulación.

*/

//Esto para hacerlo más similar a las matrices fuera de la programación.

/*
traduccionByte() pedirá una fila de la matriz y una variable a la cuál le asignará su correspondiente valor décimal.

Si tenemos en cuenta la matriz anterior el resultado sería:

En byte: B10000000
En decimal: 128

*/

//El resto de funciones necesarias aún está por definir.

```

Nota: Como la matriz no se necesita durante todo el tiempo de ejecución y la memoria del Arduino es muy pequeña
probablemente se usará un arreglo dinámico.



## Proceso Solución del Problema

## Implementación del circuito 

Se utilizan 8 integrados 74hc595 con 3 pines digitales, cumpliendo de esta manera el requisito de usar máximo 7 pines del arduino.

![solucion](https://i.imgur.com/oSDhvOO.png)



## Implementación de funciones

Se define función de prueba para comprobar el estado de las conexiones:

```c++

void ledWrite(int F1,int F2,int F3,int F4, int F5, int F6, int F7, int F8){
   //Se toman definen 8 parametros que representan el valor entero de los bytes equivalentes a cada fila
   //Se usa shiftOut() para enviar datos en serie
   //Se activa en modo LSBFIST es decir bit menos significativo primero

   shiftOut(pinData, pinClock, LSBFIRST, F8); 
   shiftOut(pinData, pinClock, LSBFIRST, F7); 
   shiftOut(pinData, pinClock, LSBFIRST, F6); 
   shiftOut(pinData, pinClock, LSBFIRST, F5);
   shiftOut(pinData, pinClock, LSBFIRST, F4);
   shiftOut(pinData, pinClock, LSBFIRST, F3);
   shiftOut(pinData, pinClock, LSBFIRST, F2);
   shiftOut(pinData, pinClock, LSBFIRST, F1);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}

```

Se definió una función que permite encender y apagar los leds n veces durante cierto tiempo.

```c++
void verificacion(int tiempoSeg,int nSecuencias){
   //Se definen 2 parametros enteros que representan el tiempo en segundos entre cada repetición y la cantidad de secuencias.

   for(int i = 0; i < nSecuencias; i++){
      ledWrite(255, 255, 255, 255, 255, 255,255,255); //255 representa una fila de bits completamente encendida
      delay(tiempoSeg*1000);
      ledWrite(0,0,0,0,0,0,0,0); // 0 representa una fila de bits completamente encendida 
      Serial.print("Repeticion numero: ");
      Serial.println(i + 1 );
      delay(tiempoSeg*1000);
  }
  Serial.println("Verificacion Finalizada");
}
```

No fueron colocadas las utilidades que se usan para el funcionamiento de la función pero se implemento una opción de prueba para personalizar el patrón que se mostrará en pantalla.

```c++
void personalizar(int** matriz){
    int fila = 0;
    int columna = 0;
    Serial.println("Personalice la imagen de la matriz:" );
    mostrar(matriz,8,8);
    while(true){
        Serial.println("Nota: todo valor que no corresponda a los indices de una matriz 8x8 sera ignorado:");
        input(fila,"Ingrese el numero de la fila que desea cambiar o 65 para salir:"); 
        input(columna,"Ingrese la numero de la columna que desea cambiar o 65 para salir:");

        if(fila  == 65 || columna == 65 ){
            break;
        }

        if (matriz[fila-1][columna-1] == 1) {
            matriz[fila-1][columna-1] = 0;
        }
        else {
            matriz[fila-1][columna-1] = 1;
        }

        mostrar(matriz,8,8);

    }

    translateByte(matriz,0,ByteF1);
    translateByte(matriz,1,ByteF2);
    translateByte(matriz,2,ByteF3);
    translateByte(matriz,3,ByteF4);
    translateByte(matriz,4,ByteF5);
    translateByte(matriz,5,ByteF6);
    translateByte(matriz,6,ByteF7);
    translateByte(matriz,7,ByteF8);
    fillMatriz(matriz,8,8);
    
}
```

Para la implementación de nuestros patrones cerrados por la matriz definida

```c++

//Patrón 1

void genPatron1(int** matriz){
    fillMatriz(matriz, 8, 8);

    for (int i = 0; i < 8; i++) {
        for (int j = i; j < 8 - i; j++) {
            matriz[3-i][j] = 1; //3-i
            matriz[i+4][j] = 1; //i+4
        }
    }
}

//Patrón 2

void genPatron2(int matriz){
    fillMatriz(matriz,8,8);

    for(int i = 0 ; i<8;i++){
        for(int j = 0; j<8;j++)
            if(i == j || i+j == 7){
                matriz[i][j] = 1;
            }
        }
}

//Patrón 3

void genPatron3(int matriz){
    fillMatriz(matriz,8,8);


    for(int i = 0 ; i<8;i++){
        if(i == 0 i == 1  i == 4 || i == 5){
            for(int j = 0; j<8;j++){
                if(j != 2 && j != 5){
                    matriz[i][j] = 1;
                }
            }
        }
        else{
            for(int j = 0; j<8;j++){
                if(j != 0 && j!= 3 && j!=6){
                    matriz[i][j] = 1;
                }
            }
        }
    }

}

//Patrón 4

void genPatron4(int** matriz) {
    int init = 0;
    int aux = 0;
    int filas = 8;
    int columnas = 8;
    fillMatriz(matriz, 8, 8);

    for(int i = 0; i < filas/2; i++) {
        init = i % 8;
        for (int j = 0; j < columnas; j++) {
            if (j >= init && j < init + filas/2) {
                matriz[i][j] = 1;
            }
        }
    }

    aux = 3;
    for(int i = 4; i < filas; i++){
        init = aux%8;
        for(int j = 0; j<columnas;j++){
            if (j >= init && j < init + filas/2) {
                matriz[i][j] = 1;
            }
        }
        aux --;
    }
}
```
Varias de estas funciones predominaron muchas constantes ya que trabajamos bajo el mismo arreglo sin cambios, nuevamente revisaremos en estas mismas para cambiar las constantes por valores que tengan congruencia con lo que se busca imprimir.

Nota: Se colocó el enlace del proyecto tinkercad en el README y en el archivo del infome, se notan varios de los requisitos funcionales ya implementados, sin embargo aún resta pulir algunos aspectos del código; por otra parte el proceso de implementación tardó tan solo unas horas debido a que ya teníamos una planeación de por medio.

## Nota final

El 22/09/2023 se ha dado por concluida implementación de la solución del problema, como se mencionó anteriormente no se necesitó mucho tiempo para codificar ya que había un análisis de por medio y teniamos todo planificado. 

NOTA: El proyecto del parcial aparece como una mezcla de un proyecto original pero es porque teniamos dos versiones, una para pruebas y otra de implementación oficial.

## Enlaces Importantes

Enlace Directo: 
https://www.tinkercad.com/things/8rY4dTVhr0Q?sharecode=GsS3glwJ_Hnsqcyt_E2rV1LQWFPN1kUoiAVzaa1udYw

Hipervinculo:
[(Proyecto Tinkercad)](https://www.tinkercad.com/things/8rY4dTVhr0Q?sharecode=GsS3glwJ_Hnsqcyt_E2rV1LQWFPN1kUoiAVzaa1udYw)

Vídeo Youtube
[(Vídeo)](https://youtu.be/mOIkzRQvF-0)