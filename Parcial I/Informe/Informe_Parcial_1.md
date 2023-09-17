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

Por otra parte también podemos indicar que leds encendemos con el valor entero del byte apropiado.

Ejemplo:

Si se usa 255 se encienden todos.
Si se usa 128 se enciende el más significativo.
Si se usa 1 se enciende el menos significativo.

También cabe decir que será necesario usar la función shiftout para enviar los datos seriados bit a bit.