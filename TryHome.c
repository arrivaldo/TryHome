//Integrantes: Alexandra Rodriguez, Diego Trejo y Erick B�rcena
//Fecha: 11/05/2016

/* @Tryhome.c 
   @brief Este sistema de venta de zapatos para damas permite la administracion y la venta de prestamo de zapatos a usuarios/clientes, la seleccion de calzado en venta y la generacion de reportes de ventas
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena
   @date 04/05/2015*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tm Tm; // define una estructura como un tipo de variable

struct usuario{ //estrutura para el registro de usuarios
  char usuario[50];
  char password[50];
  int activo;
  char nombre[50];
  Tm nacimiento;// se usa tm_mday, tm_mom tm_year
  char direccion[100];
  char correo[50];
  int prestamos[3];
  Tm fPrestamos;//fecha de los prestamos
  int *historial;
};

struct zapato{ //estructura del catalogo
  int id;
  int precio;
  char nombre[50];
  char colores [100];
  
};

struct admin{ // estructura para el ingreso al sistema 
  char usuario[50];
  char password[50];
  char **reporte;
};

typedef struct usuario Usuario;// define una estructura como un tipo de variable
typedef struct zapato Zapato;// define una estructura como un tipo de variable
typedef struct admin Admin;// define una estructura como un tipo de variable

void leer();/* Esta funcion lee todos los archivos y los coloca en la funcion correspondiente
               @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena */
void guardar();/* Esta funcion guarda todos los archivos
                  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/

//catalogo
void catalogo();
void imprimirCatalogo();
void opcionesUsuarios();
void verCarrito();
void buscar();
void buscarModelo();
void buscarPrecio();
void seleccionarBusqueda(Zapato z[], int n);
void agregarCarrito();

void login();
void registro();
void agregarUsuario(Usuario u);
void masUsuarios();

void hacerPedido();
void eliminarCarrito();

//opciones usuario
void historialCompra();
void prestamos();
void confirmarDatos();

void imprimirPrestamos();
void comprarZapato();
void regresarZapato();

void ayuda();


Usuario *usuarios;
Zapato *zapatos;
Admin admin;

// Variables Globales
char archivoUsuarios[15]="usuarios.txt";
char archivoAdmin[15]="admin.txt";
char archivoZapatos[15]="zapatos.txt";
char archivoAyuda[15]="ayuda.txt";

int maxTamUsuarios=0;
int contUsuarios=0;

int maxAdmin=0;
int contAdmin=0;

int maxZapatos=0;
int contZapatos=0;

int contCatalogo=0;

int usuario=-1;

int carrito[3];
int contCarrito=0;
/*Esta funcion manda llamar las funciones leer, catalogo y guardar
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena  */
int main(void){
  int i,j;

  leer();

  carrito[0]=-1;
  carrito[1]=-1;
  carrito[2]=-1;

  system("clear");
  catalogo();

  guardar(); 

  return 0;
}
/*Esta funcion incrementa el tama�o del arreglo donde se guardan los usuarios
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena */
void masUsuarios(){
  Usuario aux[maxTamUsuarios+20];
  int i;

  for(i=0; i<maxTamUsuarios; i++){
    aux[i]=usuarios[i];
  }

  usuarios=aux;
  maxTamUsuarios+=20;
}
/*Esta funcion permite agregar usuarios infinitamente, compara si ya existe un usuario con el mismo nombre y los muestra por orden alfabetico
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void agregarUsuario(Usuario u){
  int i;
  Usuario aux;
  
  if(contUsuarios>=maxTamUsuarios-1)
    masUsuarios();

  if(contUsuarios==0){
    usuarios[0]=u;
  }
  
  for(i=0; i<contUsuarios; i++){
    if(strcmp(usuarios[i].nombre,u.nombre)>0){
      aux=usuarios[i];
      usuarios[i]=u;
      u=aux;
    }
  }
  
  usuarios[contUsuarios]=u;
  contUsuarios++;
  
}
/*Esta funcion permite el registro de usuarios validando su informacion clave y comprueba si es mayor de 18 a�os
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena   */
void registro(){
  Usuario aux;
  int salir=-1, a,m,d;
  Tm *edad;
  time_t tiempo;
  char pass[50];

  //Inicializacion de variables
  aux.prestamos[0]=-1;
  aux.prestamos[1]=-1;
  aux.prestamos[2]=-1;

  aux.fPrestamos.tm_mday=0;  
  aux.fPrestamos.tm_mon=0;
  aux.fPrestamos.tm_year=0;
  
  aux.historial=malloc(20*sizeof(int));//reserva un espacio de memoria
  aux.historial[0]=0;

  aux.activo=1;

  printf("Registro.\n\n");

  printf("Ingresa tu nombre: ");
  gets(aux.nombre);
  printf("\nIngresa tu correo electronico: ");
  gets(aux.correo);
  printf("\nIngresa tu direccion postal: ");
  gets(aux.direccion);

  printf("\nIngresa tu fecha de nacimiento\n\nDia: ");
  scanf(" %d", &d);
  getchar();
  printf("\nMes: ");
  scanf(" %d", &m);
  getchar();
  printf("\nA�o(aaaa): ");
  scanf(" %d", &a);
  getchar();
  
  time(&tiempo);
  edad=localtime(&tiempo);
  
  if((*edad).tm_year-(a-1900)>=18){
    if((*edad).tm_year-(a-1900)==18){
      if((*edad).tm_mon-m<=0)                 //tm es una estructura que guarda d�a, mes y a�o
	if((*edad).tm_mon-m==0){
	  if((*edad).tm_mday-d<=0)
	    salir=1;
	}else
	  salir=1;
    }else
      salir=1;
    aux.nacimiento.tm_mday=d;
    aux.nacimiento.tm_mon=m;
    aux.nacimiento.tm_year=a;
  }

  if(salir>0){
    salir=-1;
    while(salir<0){
      printf("\nIngresa el nombre de usario que deseas: ");
      gets(aux.usuario);
      d=-1;
      a=0;
      while(d<0 && a<contUsuarios){
	if(strcmp(usuarios[a].usuario,aux.usuario)==0)
	  d=1;
	a++;
      }
      if(d>0){
	system("clear");
	printf("\nEl usario que ingresaste ya esta ocupado, vuelve a intentar.\n ");
      }else
	salir=1;
    }
    
    salir=-1;
    while(salir<0){
      printf("\nIngresa tu contrase�a: ");
      gets(aux.password);
      printf("\nConfirma la contrase�a: ");
      gets(pass);
      
      if(strcmp(aux.password,pass)==0){
	salir=1;
      }else{
	system("clear");
	printf("\nLas contrase�as no concuerdan, vuelve a intentar.\n");
      }
    }
    
    system("clear");
    printf("\nRegistro exitoso.\n");
    
    agregarUsuario(aux);
    
    opcionesUsuarios();
  }else{
    system("clear");
    printf("Debes de ser mayor de 18 a�os para registrarte.\n");
    opcionesUsuarios();
  }
}
/* Esta funcion permite ingresar al sistema como usuario validando si los datos ingresados son correctos 
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void login(){
  char usuario1[50], password[50];
  int encontrado=-1, i;
  
  printf("\nUsuario: ");
  gets(usuario1);
  printf("\nContrase�a: ");
  gets(password);
  
  if(strcmp(admin.usuario, usuario1)==0)
    if(strcmp(admin.password,password)==0){
      usuario=0;
      encontrado=1;
      system("clear");
      opcionesUsuarios();
    }
  
  i=0;
  while(encontrado<0 && i<contUsuarios){
    if(strcmp(usuarios[i].usuario, usuario1)==0)
      if(strcmp(usuarios[i].password, password)==0 && usuarios[i].activo>0){
	usuario=i+1;
	encontrado=1;
	system("clear");
	opcionesUsuarios();
      }
    
    i++;
  }

  if(encontrado<0){
    system("clear");
    printf("El usuario y/o contrase�a son incorrectas.\n");
    opcionesUsuarios();
  }
    
}
/* Esta funcion muestra en pantalla el historial de compra de cada usuario por modelo y por precio
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void historialCompra(){
  int i,n=0;
  
  system("clear");

  for(i=0; i<usuarios[usuario-1].historial[0]; i++){
    printf("\n-Modelo: %s\tPrecio: %d", zapatos[usuarios[usuario-1].historial[i+1]].nombre,zapatos[usuarios[usuario-1].historial[i+1]].precio);
    n+=zapatos[usuarios[usuario-1].historial[i+1]].precio;
  }
  
  printf("\n\nSaldo total: %d", n);
  
  opcionesUsuarios();
  
}
/* Esta funcion permite tomar prestados  zapatos asi como regresarlos y comprobar si tiene prestamos pendientes
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena  */
void prestamos(){
  int i,n=0;

  for(i=0; i<3; i++){
    if(usuarios[usuario-1].prestamos[i]>0){
      printf("\n-Modelo: %s\tPrecio: %d",zapatos[usuarios[usuario-1].prestamos[i]-1].nombre, zapatos[usuarios[usuario-1].prestamos[i]-1].precio);
      n++;
    }
  }
  if(n==0){
    system("clear");
    printf("No tienes prestamos\n\n");
    opcionesUsuarios();
  }
  else
    {
      printf("\n 1 - Comprar zapato\n");
      printf(" 2 - Regresar zapato\n");
      printf(" 3 - Regresar a opciones de usuario\n\n");
      scanf("%d",&n);
      getchar();
      switch(n)
	{
	case 1:
	  comprarZapato();
	  break;

	case 2:
	  regresarZapato();
	  break;

	case 3:
	  system("clear");
	  opcionesUsuarios();
	  break;
	
	default:
	  system("clear");
	  printf("La opcion que ingresaste no es valida.\n\n");
	  opcionesUsuarios();
	  break;
	}
    }
}
/* Un vez comprobados los prestamos que tienes esta funcion te los imprime en pantalla 
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void imprimirPrestamos(){
  int i;

  for(i=0; i<3; i++){
    if(usuarios[usuario-1].prestamos[i]>0){
      printf("\n%d-Modelo: %s\tPrecio: %d", i+1, zapatos[usuarios[usuario-1].prestamos[i]-1].nombre,zapatos[usuarios[usuario-1].prestamos[i]-1].precio);
    }
  }
}
/* Esta funcion permite la seleccion y compra de zapatos 
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void comprarZapato(){
  int i, j;

  imprimirPrestamos();

  printf("\n\n�Que zapato quieres comprar?(ingrasa el indice)  ");
  scanf(" %d", &i);
  getchar();

  if(i<4 && i>0){
    usuarios[usuario-1].historial[usuarios[usuario-1].historial[0]+1]=usuarios[usuario-1].prestamos[i-1];
    usuarios[usuario-1].historial[0]++;
    i--;
    for(j=i; j<2; j++){
      usuarios[usuario-1].prestamos[j]=usuarios[usuario-1].prestamos[j+1];
      usuarios[usuario-1].prestamos[j+1]=-1;
    }
    usuarios[usuario-1].prestamos[2]=-1;
  }
}
/* Esta funcion permite regresar los zapatos que no quieres comprar
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void regresarZapato(){
  int i,j;
  
  imprimirPrestamos();

  printf("�Que zapato quieres regresar?(ingresa el indice)  ");
  scanf(" %d", &i);
  getchar();
  if(i<4 && i>0){
    i--;
    for(j=i; j<2; j++){
      usuarios[usuario-1].prestamos[j]=usuarios[usuario-1].prestamos[j+1];
      usuarios[usuario-1].prestamos[j+1]=-1;
    }
    usuarios[usuario-1].prestamos[2]=-1;
  }
}
/* Esta funcion permite al usuario confirmar si sus datos son correctos
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void confirmarDatos(){
  int i;
  printf("\nSu direccion actual: %s", usuarios[usuario-1].direccion);

  printf("\n\n1-Cambiar direccion");
  printf("\n2-Regresar a Opciones de usuario");

  scanf(" %d", &i);
  getchar();
  
  if(i==1){
    
    printf("\ningrese la nueva direccion: ");
    gets(usuarios[usuario-1].direccion);
    system("clear");
    printf("operacion exitosa\n\n");
  }else
    system("clear");
  opcionesUsuarios();
  
}
/* Esta funcion permite al usuario ver el catalogo , que seleccione los zapatos que desea agregar a su carrito y salir del sitema
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena */
void imprimirCatalogo(){
  
  if(usuario<0)
    printf("Log in (1)");
  else
    printf("Opciones de usuario (1)");
  
  printf("\t\t\t\tCarrito(%d/3) (2)",contCarrito);
  printf("\n\t\t\t\t\t   Buscar (3)");

  printf("\n\tModelo: %s",zapatos[contCatalogo].nombre);
  printf("\n\tPrecio: %d",zapatos[contCatalogo].precio);
  printf("\n\tColores: %s",zapatos[contCatalogo].colores);
  printf("\n\tTalla: 3-10");
  printf("\n\tnAgregar a carrito (4)");
  printf("\n\nAnterior (5)\t\t Siguiente (6)");
  printf("\n\nComo funciona TryAtHome (7)");
  printf("\nSalir (8)\n\n");
}
/* Esta funcion muestra el menu principal del usuario
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void opcionesUsuarios(){
  int menu;
  
  if(usuario>0){
    printf("\nOpciones de Usuario");
    printf("\n1-Ver historial de compra");
    printf("\n2-Ver prestamos");
    printf("\n3-Ver carrito");
    printf("\n4-Confirmar direccion de envio");
    printf("\n5-Regresar a catalogo");
    printf("\n6-Reglas de prestamo/compra");
    printf("\n7-Cerrar sesion");
    printf("\n8-Salir\n\n");
    
    scanf(" %d", &menu);
    getchar();
    
    switch(menu){
    case 1:
      historialCompra();
      break;
    case 2:
      system("clear");
      prestamos();
      break;
    case 3:
      system("clear");
      verCarrito();
      break;
    case 4:
      system("clear");
      confirmarDatos();
      break;
    case 5:
      system("clear");
      catalogo();
      break;
    case 6: 
      system("clear");
      ayuda();
      break;
    case 7:
      usuario=-1;
      system("clear");
      catalogo();
      break;
    case 8:
      break;
    default:
      system("clear");
      printf("La opcion que ingreso no es valida.\n\n");
      opcionesUsuarios();
      break;
    }
  }else if(usuario==0){
    //opciones admin
  }else{
    printf("\n1-Ingresar con una cuenta existente");
    printf("\n2-Registrarse");
    printf("\n3-Regresar a catalogo\n\n");

    scanf(" %d",&menu);
    getchar();
    switch(menu){
    case 1:
      system("clear");
      login();
      break;
    case 2:
      system("clear");
      registro();
      break;
    case 3:
      system("clear");
      catalogo();
      break;
    default:
      system("clear");
      printf("La opcion que ingreso no es valida.\n\n");
      opcionesUsuarios();
      break;
    }
  }
}
/*Esta funcion permite eliminar zapatos del carrito
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void eliminarCarrito(){
  int i,j;

  for(i=0; i<3; i++){
    printf("\n%d-Modelo: %s\tPrecio: %d",i+1,zapatos[carrito[i]-1].nombre,zapatos[carrito[i]-1].precio);
  }
  
  printf("\n\n�Que zapato quieres elimiar?(ingresa el indice) ");
  scanf(" %d", &i);
  getchar();

  if(i<4 && i>0){
    i--;
    for(j=i; j<2; j++){
      carrito[j]=carrito[j+1];
      carrito[j+1]=-1;
    }
    carrito[2]=-1;
    system("clear");
  }else{
    system("clear");
    printf("El valor ingresado no es valido\n\n");
  }  
}
/*Esta funcion permite hacer un pedido tomando los zapatos que el usuario coloco en su carrito, el usuario solo podra hacer un pedido cada dias
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena  */
void hacerPedido(){

  time_t tiempo;
  Tm *fecha;

  if(usuario>0){
    if(usuarios[usuario].prestamos[0]<0){
      system("clear");
      printf("Solo puedes hacer un pedido cada 5 dias.");
      verCarrito();
    }else{
      usuarios[usuario].prestamos[0]=carrito[0];
      usuarios[usuario].prestamos[1]=carrito[1];
      usuarios[usuario].prestamos[2]=carrito[2];
      
      carrito[0]=-1;
      carrito[1]=-1;
      carrito[2]=-1;
      contCarrito=0;

      time(&tiempo);
      fecha=localtime(&tiempo);
      usuarios[usuario].fPrestamos=*fecha;
      system("clear");
      printf("Se ha hecho el pedido exitosamente.");
      opcionesUsuarios();
    }
  }else{
    system("clear");
    printf("Debe de iniciar sesion para hacer un pedido\n");
    opcionesUsuarios();
  }
}
/* Esta funcion muestra en pantalla los zapatos selecciones del catalogo en la opcion carrito
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void verCarrito(){
  int i, precio=0;

  for(i=0; i<3; i++){
    printf("\n-");
    if(carrito[i]>0){
      printf("Modelo: %s\tPrecio: %d", zapatos[carrito[i]-1].nombre,zapatos[carrito[i]-1].precio);
      precio+=zapatos[carrito[i]-1].precio;
    }
  }

  printf("\n\nPrecio total: %d\n",precio);

  printf("\n1-Eliminar zapato");
  printf("\n2-Hacer pedido");
  printf("\n3-Regresar a catalogo\n\n");
  
  scanf(" %d", &i);

  switch(i){
  case 1:
    system("clear");
    eliminarCarrito();
    break;
  case 2:
    hacerPedido();
    break;
  case 3:
    system("clear");
    catalogo();
    break;
  default:
    system("clear");
    verCarrito();
    break;
  }
}
/*Esta funcion permite buscar en el catalogo zapatos por modelo y rango de precio
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void buscar(){
  int menu;
  
  printf("Buscar zapatos\n");
  printf("\n1-Buscar zapato por modelo");
  printf("\n2-Buscar zapato por rango de precio");
  printf("\n3-Regresar al catalogo\n\n");

  scanf(" %d", &menu);
  getchar();

  switch(menu){
  case 1:
    system("clear");
    buscarModelo();
    break;
  case 2: 
    system("clear");
    buscarPrecio();
    break;
  case 3:
    system("clear");
    catalogo();
    break;
  default:
    system("clear");
    printf("La opcion que ingreso no es valida\n\n");
    buscar();
    break;
  }
}
/*Esta funcion te permite buscar los zapatos por modelo, seleccionarlos, hacer otra busqueda y/o regresar de nuevo al catalogo
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void buscarModelo(){
  char linea[50];
  Zapato encontrados[contZapatos];
  int i, n=0;
  
  printf("\nIngresa el nombre del modelo que deseas buscar: ");
  gets(linea);
  
  printf("\n");
  for(i=0; i<contZapatos; i++){
    if(strcasestr(zapatos[i].nombre,linea)!=NULL){
      printf("-Modelo: %s\tPrecio: %d", zapatos[i].nombre, zapatos[i].precio);
      encontrados[n]=zapatos[i];
      n++;
    }
  }
  
  printf("\n\n1-seleccionar");
  printf("\n2-buscar");
  printf("\n3-regresar a catalogo\n\n");
  
  scanf(" %d", &i);
  getchar();

  switch(i){
  case 1:
    system("clear");
    seleccionarBusqueda(encontrados,n);
    break;
  case 2:
    system("clear");
    buscar();
    break;
  case 3:
    system("clear");
    catalogo();
    break;
  default:
    system("clear");
    buscar();
    break;
  }
}
/*Esta funcion permite buscar los zapatos por rango de precio, seleccionarlos, hacer otra busqueda y/o regresar de nuevo al catalogo
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena */
void buscarPrecio(){
 Zapato encontrados[contZapatos];
 int i, n=0, max=0;
  
  printf("\nIngresa el precio maximo que deseas: ");
  scanf(" %d", &max);
  getchar();
  
  for(i=0; i<contZapatos; i++){
    if(zapatos[i].precio<=max){
      printf("-Modelo: %s\tPrecio: %d", zapatos[i].nombre, zapatos[i].precio);
      encontrados[n]=zapatos[i];
      n++;
    }
  }
  
  printf("\n1-seleccionar");
  printf("\n2-buscar");
  printf("\n3-regresar a catalogo\n\n");
  
  scanf(" %d", &i);
  getchar();

  switch(i){
  case 1:
    system("clear");
    seleccionarBusqueda(encontrados,n);
    break;
  case 2:
    system("clear");
    buscar();
    break;
  case 3:
    system("clear");
    catalogo();
    break;
  default:
    system("clear");
    buscar();
    break;
  }
}
/*Esta funcion permite agregar a carrito los zapatos seleccionados por su indice, solo puedes tener un maximo de 3 zapatos por carrito
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena   */
void seleccionarBusqueda(Zapato z[], int n){
  int i,x;
  int listo=-1;

  for(i=0; i<n;i++){
    printf("\n%d-Modelo: %s\tPrecio: %d", i+1,z[i].nombre, z[i].precio);
  }

  printf("\n\nIngrese el indice del que desea agregar al carrito: ");
  scanf(" %d", &i);
  getchar();
  
  x=0;
  while(listo<0 && x<3){
    if(carrito[x]<0){
      carrito[x]=zapatos[contCatalogo].id;
      listo=1;
      contCarrito++;
    }else
      x++;
  }

  if(x>=3){
    system("clear");
    printf("El carrito esta lleno\n\n");
    catalogo();
  }else{
    system("clear");
    buscar();
  }
}
/* Esta funcion valida si el carrito esta lleno
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void agregarCarrito(){

  if(contCarrito>=3){
    system("clear");
    printf("El carrito esta lleno\n\n");
    catalogo();
  }else{
    carrito[contCarrito]=contCatalogo+1;
    contCarrito++;
    system("clear");
    catalogo();
  }
}
/*Esta funcion muestra el manual de ayuda en pantalla
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena */
void ayuda(){
  FILE *archivo;
  char linea [100];
  archivo=fopen(archivoAyuda, "rt");
  
  if(archivo!=NULL){
    while(!feof(archivo)){
      fgets(linea, 100,archivo);
      if(feof(archivo)) break;
      puts(linea);
    }
    fclose(archivo);
  }
  
  opcionesUsuarios();
}
/* Esta funcion manda llamar a las funciones anteriores
   @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena  */
void catalogo(){
  int menu;

  imprimirCatalogo();

  scanf(" %d", &menu);
  getchar();
  switch (menu){
  case 1:
    system("clear");
    opcionesUsuarios();
    break;
  case 2:
    system("clear");
    verCarrito();
    break;
  case 3:
    system("clear");
    buscar();
    break;
  case 4:
    system("clear");
    agregarCarrito();
    break;
  case 5:
    if(contCatalogo+1<contZapatos)
      contCatalogo+=1;
    else
      contCatalogo=0;
    system("clear");
    catalogo();
    break;
  case 6:
    if(contCatalogo-1>=0)
      contCatalogo-=1;
    else
      contCatalogo=contZapatos-1;
    system("clear");
    catalogo();
    break;
  case 7:
    system("clear");
    ayuda();
    break;
  case 8:
    puts("Gracias por usar TryAtHome.\n");
    break;
  default:
    system("clear");
    printf("La opcion que ingreso no es valida.\n\n");
    catalogo();
    break;
  }
}
/*Esta funcion lee la informacion de los usuarios, del administrador y de los zapatos
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena */
void leer(){

  FILE *archivo;
  char linea[100];
  int i;


  //leer usuarios
  archivo=fopen(archivoUsuarios, "rt");
  
  if(archivo!=NULL){
    
    if(!feof(archivo)){
      
      fgets(linea,50, archivo);
      if(feof(archivo)) return;
      sscanf(linea, "%d", &maxTamUsuarios);
      
      maxTamUsuarios+=20;
      
      usuarios=malloc(maxTamUsuarios*sizeof(Usuario));
    }
    while(!feof(archivo)){
      
      fgets(linea,50,archivo);
      if(feof(archivo)) break;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(usuarios[contUsuarios].usuario,linea);
  
      fgets(linea,50,archivo);
      if(feof(archivo))break;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(usuarios[contUsuarios].password,linea);

      fgets(linea,50,archivo);
      if(feof(archivo)) break;
      sscanf(linea, "%d", &usuarios[i].activo);

      fgets(linea,50,archivo);
      if(feof(archivo)) break;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(usuarios[contUsuarios].nombre, linea);
      
      fgets(linea, 50, archivo);
      if(feof(archivo)) break;
      sscanf(linea, "%d %d %d", &usuarios[contUsuarios].nacimiento.tm_mday, &usuarios[contUsuarios].nacimiento.tm_mon, &usuarios[contUsuarios].nacimiento.tm_year);

      fgets(linea,100,archivo);
      if(feof(archivo)) break;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(usuarios[contUsuarios].direccion,linea);

      fgets(linea,50,archivo);
      if(feof(archivo))break;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(usuarios[contUsuarios].correo,linea);
      
      fgets(linea, 50, archivo);
      if(feof(archivo))break;
      sscanf(linea, "%d %d %d", &usuarios[contUsuarios].prestamos[0], &usuarios[contUsuarios].prestamos[1], &usuarios[contUsuarios].prestamos[2]);
      
      
      fgets(linea, 50, archivo);
      if(feof(archivo))break;
      sscanf(linea,"%d %d %d", &usuarios[contUsuarios].fPrestamos.tm_mday, &usuarios[contUsuarios].fPrestamos.tm_mon, &usuarios[contUsuarios].fPrestamos.tm_year);

      fgets(linea, 50, archivo);
      if(feof(archivo)) break;
      sscanf(linea, "%d", &i);
      
      usuarios[contUsuarios].historial=malloc((i+50)*sizeof(int));
      usuarios[contUsuarios].historial[0]=i;
      
      for(i=0; i<usuarios[contUsuarios].historial[0]; i++){
	fgets(linea, 50, archivo);
	if(feof(archivo))break;
	sscanf(linea, "d", &usuarios[contUsuarios].historial[1+i]);
      }
      contUsuarios+=1;
    }
    fclose(archivo);
  }else{
    maxTamUsuarios=20;
    usuarios=malloc(maxTamUsuarios*sizeof(Usuario));
  }

  
  //leer admin

  archivo=fopen(archivoAdmin,"rt");
  if(archivo!=NULL){
    
   fgets(linea, 50, archivo);
    if(feof(archivo)) return;
    if(strlen(linea)>0)
      linea[strlen(linea)-1]='\0';
    strcpy(admin.usuario,linea);

    fgets(linea, 50, archivo);
    if(feof(archivo)) return;
    if(strlen(linea)>0)
      linea[strlen(linea)-1]='\0';
    strcpy(admin.password,linea);

    fgets(linea, 50,archivo);
    if(feof(archivo)) return;
    sscanf(linea, "%d", &contAdmin);
    
    maxAdmin=contAdmin+20;
    admin.reporte=malloc(maxAdmin*sizeof(char*));
    for(i=0; i<20; i++)
      admin.reporte[i]=malloc(100*sizeof(char));

    for(i=0; i<contAdmin;i++){
      fgets(linea, 100,archivo);
      if(feof(archivo)) return;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(admin.reporte[i],linea);
    }
      
    fclose(archivo);
  }else{
    
    strcpy(admin.usuario,"Admin");
    strcpy(admin.password,"Admin1");

    admin.reporte=malloc(20*sizeof(char*));
    for(i=0; i<20; i++)
      admin.reporte[i]=malloc(100*sizeof(char));
    maxAdmin=20;
  }

  //leer zapatos
  
  archivo=fopen(archivoZapatos,"rt");

  if(archivo!=NULL){
    fgets(linea, 50, archivo);
    if(feof(archivo)) return;
    sscanf(linea, "%d", &contZapatos);
    
    maxZapatos=contZapatos+20;
    zapatos=malloc(maxZapatos*sizeof(Zapato));
    for(i=0;i<contZapatos;i++){
      fgets(linea, 50, archivo);
      if(feof(archivo)) break;
      sscanf(linea, "%d", &zapatos[i].id);

      fgets(linea, 50, archivo);
      if(feof(archivo)) break;
      sscanf(linea, "%d", &zapatos[i].precio);
      
      fgets(linea, 50, archivo);
      if(feof(archivo)) break;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(zapatos[i].nombre,linea);
      
      fgets(linea, 100, archivo);
      if(feof(archivo)) break;
      if(strlen(linea)>0)
	linea[strlen(linea)-1]='\0';
      strcpy(zapatos[i].colores,linea);

    }
    fclose(archivo);
  }else{
    zapatos=malloc(20*sizeof(Zapato));
    
  }
}
/*Esta funcion guarda toda la informacion de los usuarios que se registren, del administrador y de los zapatos
  @autor Alexandra Rodriguez, Diego Trejo y Erick B�rcena*/
void guardar(){
  FILE *archivo;
  int i,j;
  

  //guardar usuarios
  archivo=fopen(archivoUsuarios,"wt");
  fprintf(archivo,"%d\n", contUsuarios);
  
  for(i=0; i<contUsuarios; i++){
    fprintf(archivo, "%s\n", usuarios[i].usuario);
    fprintf(archivo, "%s\n", usuarios[i].password);
    fprintf(archivo, "%d\n", usuarios[i].activo);
    fprintf(archivo, "%s\n", usuarios[i].nombre);

    fprintf(archivo, "%d %d %d\n", usuarios[i].nacimiento.tm_mday, usuarios[i].nacimiento.tm_mon, usuarios[i].nacimiento.tm_year);

    fprintf(archivo, "%s\n", usuarios[i].direccion);
    fprintf(archivo, "%s\n", usuarios[i].correo);

    fprintf(archivo, "%d %d %d\n", usuarios[i].prestamos[0], usuarios[i].prestamos[1], usuarios[i].prestamos[2]);

    fprintf(archivo,"%d %d %d\n", usuarios[i].fPrestamos.tm_mday, usuarios[i].fPrestamos.tm_mon, usuarios[i].fPrestamos.tm_year);

    for(j=0; j<=usuarios[i].historial[0];j++)
      fprintf(archivo,"%d\n", usuarios[i].historial[j]);
  }


  //guardar admin

  archivo=fopen(archivoAdmin,"wt");

  fprintf(archivo, "%s\n", admin.usuario);
  fprintf(archivo, "%s\n", admin.password);
  fprintf(archivo, "%d\n", contAdmin);
  
  for(i=0; i<contAdmin; i++){
    fprintf(archivo, "%s\n", admin.reporte[i]);
  }
  fclose(archivo);


  //Guardar zapatos
  archivo=fopen(archivoZapatos,"wt");
  fprintf(archivo, "%d\n", contZapatos);

  for(i=0; i<contZapatos; i++){
    fprintf(archivo, "%d\n", zapatos[i].id);
    fprintf(archivo, "%d\n", zapatos[i].precio);
    fprintf(archivo, "%s\n", zapatos[i].nombre);
    fprintf(archivo, "%s\n", zapatos[i].colores);
  }

  fclose(archivo);
}

