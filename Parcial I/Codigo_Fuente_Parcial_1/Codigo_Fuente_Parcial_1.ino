// Definición de pines
int pinData = 2;
int pinLatch = 3;
int pinClock = 4;

// Variables Globales
bool mensajeMostrado = false;

//Prototipos de Funciones

int pow2(int);
int leerMonitorSerial();
int input(int&, String);
void inputOneLine(int(&)[2]);

int** genMatriz(int,int);
void fillMatriz(int**,int,int);
void mostrar(int**,int,int);
void borrarMatriz(int**,int);

int& translateByte(int**,int,int&);
void writeByte(int**,int&,int&,int&,int&,int&,int&,int&,int&);
void ledWrite(int,int,int,int,int,int,int,int);

void genPatron1(int**,int&,int&,int&,int&,int&,int&,int&,int&);
void genPatron2(int**,int&,int&,int&,int&,int&,int&,int&,int&);
void genPatron3(int**,int&,int&,int&,int&,int&,int&,int&,int&);
void genPatron4(int**,int&,int&,int&,int&,int&,int&,int&,int&);

void verificacion(int tiempoSeg,int nSecuencias);
void personalizar(int**);
void patrones(int**,int);
void publik();

void setup() {

  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
  Serial.begin(9600);
 
}

void loop() {
  publik();

}

// Funciones

//Funcionalidades

int pow2(int exponente){
  
  // Función que calcula la potencia de 2 dada por exponente.
 
  int resultado = 1 << exponente;
  
  return resultado;
}

int leerMonitorSerial(){

  // Función que lee y retorna un número entero del monitor serial.

  int numeroIngresado = 0;
  if (Serial.available() > 0) {
    numeroIngresado = Serial.parseInt();
  }
  
  return numeroIngresado;
}

int input(int& variable, String mensaje){

  // Función que recibe una variable y un string para imprimir un mensaje y pedir al usuario que ingrese por el monitor serial un número.
  
  int valorIngresado = 0;
  Serial.println(mensaje);

  while (true) {
    valorIngresado = leerMonitorSerial();
    if (valorIngresado != 0) {
      variable = valorIngresado;
      break;
    }
  }
  
  while (Serial.available()) {
    Serial.read();
  }
  
  return variable;
}

void inputOneLine(int (&arraY)[2]){

    // Función diseñada para solicitar un número entero de 2 digitos y almacenar en un arreglo cada digito del número.
    
    int numero = 0;
    int pos = 1;
    Serial.println("Nota: si ingresa 99 se interrumpira el proceso y se imprimira la matriz personalizada.");
    input(numero,"Ingrese la posicion que desea editar de la forma fila|columna donde 11 significa [0][0].");
   

    while (numero != 0) {
        arraY[pos] = numero % 10;
        numero /= 10;
        pos --;
    }
    
}

// Arreglo Dinámico

int** genMatriz(int filas,int columnas){

    // Función diseñada para reservar en memoria una matriz de orden filas x columnas.
  
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new int[columnas];
    }
    
    return matriz;
}

void fillMatriz(int** matriz, int filas, int columnas){

    // Función diseñada para rellenar un arreglo dinámico con ceros.
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 1;
            if((i + j)%2 == 0){
                matriz[i][j] = 0;
            }
            else{
                matriz[i][j] = 0;
            }
        }
    }
}

void mostrar(int** matriz,int filas, int columnas){

    // Función que imprime la matriz en pantalla.
    
    for(int i = 0; i<8;i++){
        for(int j = 0; j <8; j++){
            Serial.print(matriz[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
}

void borrarMatriz(int** matriz, int filas){

    // Libera la memoria dinámica reservada en tiempo de ejecución.
    
    for (int i = 0; i < filas; ++i){
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Complemento de requisitos funcionales

int& translateByte(int** matriz,int fila,int& byteF){

    // Función que lleva una fila de una matriz (byte) a su correspondiente valor entero.
    
    int ex = 0;
    int byteAux = 0;
    for(int i = 7; i >= 0; i--){
        byteAux += pow2(ex)*matriz[fila][i];
        ex ++;
    }
    byteF = byteAux;
    return byteF;
}

void writeByte(int** matriz,int& var1, int& var2, int& var3, int& var4, int& var5, int& var6, int& var7, int& var8){

    // Función que asigna el valor entero correspondiente de los bytes al mismo tiempo.
    
    int* ptr1 = &var1;
    int* ptr2 = &var2;
    int* ptr3 = &var3;
    int* ptr4 = &var4;
    int* ptr5 = &var5;
    int* ptr6 = &var6;
    int* ptr7 = &var7;
    int* ptr8 = &var8;

    *ptr1 = translateByte(matriz,0,var1);
    *ptr2 = translateByte(matriz,1,var2);
    *ptr3 = translateByte(matriz,2,var3);
    *ptr4 = translateByte(matriz,3,var4);
    *ptr5 = translateByte(matriz,4,var5);
    *ptr6 = translateByte(matriz,5,var6);
    *ptr7 = translateByte(matriz,6,var7);
    *ptr8 = translateByte(matriz,7,var8);
}

void ledWrite(int F1,int F2,int F3,int F4, int F5, int F6, int F7, int F8){

   // Función que envia a cada fila bit por bit el byte.
   
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

// Requisitos Funcionales

void genPatron1(int** matriz, int& b1, int& b2, int& b3, int& b4, int& b5, int& b6, int& b7,int& b8){

    // Función que genera el patrón número 1

    int filas = 8;
    int columnas = 8;
    
    for (int i = 0; i < filas; i++) {
        for (int j = i; j < columnas - i; j++) {
            matriz[3-i][j] = 1;
            matriz[i+4][j] = 1;
        }
    }

    writeByte(matriz,b1,b2,b3,b4,b5,b6,b7,b8);
    
}

void genPatron2(int** matriz, int& b1, int& b2, int& b3, int& b4, int& b5, int& b6, int& b7, int& b8){

    // Función que genera el patrón número 2

    int filas = 8;
    int columnas = 8;
    
    for(int i = 0 ; i<filas;i++){
        for(int j = 0; j<columnas;j++)
            if(i == j || i+j == filas-1){
                matriz[i][j] = 1;
            }
        }

    writeByte(matriz,b1,b2,b3,b4,b5,b6,b7,b8);
}

void genPatron3(int** matriz, int& b1, int& b2, int& b3, int& b4, int& b5, int& b6, int& b7,int& b8){

    // Función que genera el patrón número 3

    int filas = 8;
    int columnas = 8;
    
    for(int i = 0 ; i<filas;i++){
        if(i == 0 ||i == 1 || i == 4 || i == 5){
            for(int j = 0; j<columnas;j++){
                if(j != 2 && j != 5){
                    matriz[i][j] = 1;
                }
            }
        }
        else{
            for(int j = 0; j<filas;j++){
                if(j != 0 && j!= 3 && j!=6){
                    matriz[i][j] = 1;
                }
            }
        }
    }

    writeByte(matriz,b1,b2,b3,b4,b5,b6,b7,b8);
}

void genPatron4(int** matriz, int& b1, int& b2, int& b3, int& b4, int& b5, int& b6, int& b7,int& b8){

    // Función que genera el patrón número 4
    
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

    writeByte(matriz,b1,b2,b3,b4,b5,b6,b7,b8);
}

void verificacion(int tiempoSeg,int nSecuencias){

  // Función diseñada para verificar el funcionamiento de los leds.
  
  for(int i = 0; i < nSecuencias; i++){
    ledWrite(255, 255, 255, 255, 255, 255,255,255);
    delay(tiempoSeg*1000.0);
    ledWrite(0,0,0,0,0,0,0,0);
    Serial.print("Repeticion numero: ");
    Serial.println(i + 1 );
    delay(tiempoSeg*1000.0);
  }
  Serial.println("Verificacion Finalizada");
}

void personalizar(int** matriz){

    // Función diseñada para personalizar qué leds se encienden y cuáles no.

    int ByteF1 = 0;
    int ByteF2 = 0;
    int ByteF3 = 0;
    int ByteF4 = 0;
    int ByteF5 = 0;
    int ByteF6 = 0;
    int ByteF7 = 0;
    int ByteF8 = 0;
    int opcion = 0;
    int fc[2];
    
    Serial.println("Personalice la imagen de la matriz:" );
    mostrar(matriz,8,8);
    while(true){
       Serial.println("Nota: todo valor que no corresponda a los indices de una matriz 8x8 provocara errores en la matriz de leds.");
       inputOneLine(fc);

        if(fc[0]  == 9 || fc[1] == 99 ){
            break;
        }
        

        if((fc[1] >= 0 && fc[1] <=64) && (fc[0] >= 0 && fc[0] <=64)){
          if (matriz[fc[0]-1][fc[1]-1] == 1) {
              matriz[fc[0]-1][fc[1]-1] = 0;
          }
          else {
              matriz[fc[0]-1][fc[1]-1] = 1;
          }   
        }

        mostrar(matriz,8,8);

    }

    writeByte(matriz,ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    fillMatriz(matriz,8,8);
    ledWrite(ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
}

void patrones(int** matriz, int tiempoSeg){

  // Función itera idenfinidamente durante cierto tiempo entre cuatro patrones generados por secuencias.
  
  int ByteF1 = 0;
  int ByteF2 = 0;
  int ByteF3 = 0;
  int ByteF4 = 0;
  int ByteF5 = 0;
  int ByteF6 = 0;
  int ByteF7 = 0;
  int ByteF8 = 0;
  
  while(true){
    genPatron1(matriz,ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    fillMatriz(matriz,8,8);
    ledWrite(ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    delay(tiempoSeg*1000);
    genPatron2(matriz,ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    fillMatriz(matriz,8,8);
    ledWrite(ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    delay(tiempoSeg*1000);
    genPatron3(matriz,ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    fillMatriz(matriz,8,8);
    ledWrite(ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    delay(tiempoSeg*1000);
    genPatron4(matriz,ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    fillMatriz(matriz,8,8);
    ledWrite(ByteF1,ByteF2,ByteF3,ByteF4,ByteF5,ByteF6,ByteF7,ByteF8);
    delay(tiempoSeg*1000);
    
    if(Serial.available() > 0){
      break;
    }
  }
  ledWrite(0,0,0,0,0,0,0,0);
}

void publik(){

  // Función que sirve como menu principal.
  
  int nSecuencias = 0;
  int tiempoSeg = 0;
  int ByteF1 = 0;
  int ByteF2 = 0;
  int ByteF3 = 0;
  int ByteF4 = 0;
  int ByteF5 = 0;
  int ByteF6 = 0;
  int ByteF7 = 0;
  int ByteF8 = 0;
  int opcion = 0;
  int** matriz = genMatriz(8,8);
  
  if (!mensajeMostrado) {
    Serial.println("*************************************************************************");
    Serial.println("*                          Menu Principal                               *");
    Serial.println("*************************************************************************");
    
    Serial.println("1. Verificar Funcionamiento de leds:");
    Serial.println("2. Crear y Mostrar Imagen de Prueba:");
    Serial.println("3. Alternar Patrones Predeterminados:");
    
    mensajeMostrado = true;    
    
  }

  opcion = leerMonitorSerial();
  switch(opcion){
  case 1:
      Serial.println("Verificando Funcionamiento de Leds:");
      input(nSecuencias,"Ingrese la cantidad de repeticiones:");
      input(tiempoSeg,"Ingrese la cantidad de segundos entre cada repeticion:");
      verificacion(tiempoSeg,nSecuencias);
      mensajeMostrado = false;
      break;
    
    case 2:
      Serial.println("Modo de Patron Personalizado:");
      personalizar(matriz);
      mensajeMostrado = false;
      break;
    
    case 3:
      Serial.println("Alternando Entre Patrones Conocidos:");
      input(tiempoSeg,"Ingrese la cantidad de tiempo entre cada secuencia:");
      patrones(matriz,tiempoSeg);
      mensajeMostrado = false;
      
    }
  borrarMatriz(matriz,8);
}
