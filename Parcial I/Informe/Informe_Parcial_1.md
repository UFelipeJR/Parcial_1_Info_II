# Informe Primer Parcial Informática II 

## Observación acerca del integrado 74hc595

Nos hemos documentado acerca del funcionamiento del 74hc595, y hemos notado que se puede utilizar en modo cascading o cascada, de esta manera necesitaremos solamente 3 pínes digitales para controlar los 64 leds, ya que sin importar la
cantidad de 74hc595 que usemos la cantidad de pines necesarios sigue siendo constante. Esto nos lleva a la primera propuesta de la solución, utilizar 8 integrados.


## Nota

Para iniciar con el proceso de construcción de la solución, primero tuvimos que familiarizarnos con el funcionamiento a nivel de hardware, y software; por lo que tuvimos que hacer un entorno de pruebas para comprender cómo se programa y qué podiamos plantear. En pocas palabras en esta etapa estudiamos Arduino y nos documentamos acerca de todo lo necesario para plantear correctamente la solución.


```c++

//Nos familiarizamos acerca de como se programa el arduino tomando como base lo aprendido en c++

void setup(){

}

void loop(){
    
}

```