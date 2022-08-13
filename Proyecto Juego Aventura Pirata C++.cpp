#include <iostream>
#include <string.h>
//Librerias necesarias para el funcionamiento de valores aleatorios
#include <stdlib.h>
#include <time.h>

using namespace std;

//Definicion de constantes
const int MAX1 = 25, MAX2 = 30;

//Definicion de los tipos de datos que se utilizaran en el programa
typedef char pal[MAX2];
struct jugador {
  pal nombre,apellido,nickname;
  bool turno;
  int puntaje;
};
struct casillero{
	int num;
	bool sol,sirena,kraken,tifon;
};

//Definicion de nodo simple
typedef struct nodo_s *pnodo_s;
struct nodo_s {
  jugador dato;
  pnodo_s sig;
};
//Definicion de lista simple
struct tlistas {
  pnodo_s inicio,final;
  int cont;
};

//Definicion de nodo doble
typedef struct nodo_d *pnodo_d;
struct nodo_d {
	casillero dato;
	pnodo_d sig,ant;
};
//Definicion de lista doble
struct tlistad{
	pnodo_d inicio,final;
};

//Definicion de arbol binario
typedef struct nodo_a *pnodo_a;
struct nodo_a{
	jugador dato;
	pnodo_a der,izq;
};

//Inicializador de lista simple
void iniciar_lista(tlistas &lista);

//Esta funcion devuelve la cadena ingresada en mayusculas
char mayuscula(char p);

//Este procedimiento carga los caracteres del contenido en cada posicion del contenedor
void cargar_cadena(pal contenido, pal &contenedor);

//Esta funcion verifica si los datos ingresados existen en la lista, de ser asi devuelve false
bool verificar_jugador(tlistas lista, pal nombre, pal apellido, pal nickname);

//Procedimiento que agrega un nodo a la lista simple
void agregar_jugador(tlistas &lista, pnodo_s nuevo);

//Procedimiento que crea un nuevo nodo simple
void crear_nodo(tlistas &lista);

//Procedimiento que permite buscar un jugador, al encontrarlo muestra sus datos
void buscar_jugador(tlistas lista);

//Procedimiento que muestra todos los jugadores registrados
void listar_jugador(tlistas lista);

//procedimiento que muestra todos los jugadores registrados menos el jugador 1
void listar_jugador_dos(tlistas lista,pnodo_s excep);

//Procedimiento que permite modificar los datos de un jugador registrado
void modificar_jugador(tlistas &lista);

//Procedimiento que permite eliminar un jugador registrado
void eliminar_jugador(tlistas &lista);

//Menu de Gestion de Jugadores de la lista simple
void menu_jugadores(tlistas &lista);


//Inicializador de lista doble
void iniciar_tablero(tlistad &tablero);

//Procedimiento que crea un nuevo nodo doble
void crear_casilla(pnodo_d &casilla, int valor);

//Procedimiento que agrega un nodo a la lista doble
void agregar_casilla(tlistad &tablero, pnodo_d casilla);

//Procedimiento que agrega las casillas al tablero jusnto a sus datos
void cargar_tablero(tlistad &tablero);

//Procedimiento que permite seleccionar un jugador
void seleccionar_jugador(tlistas jugadores, pnodo_s &jugador,pal nickname);


//Inicializador de arbol binario
void iniciar_ranking(pnodo_a &arbol);

//Funcion que cuenta la cantidad de nodos que tiene el arbol binario
int contar_ranks(pnodo_a arbol);

//Procedimiento que inserta un nodo al arbol binario
void insertar_rank(pnodo_a &arbol,pnodo_a nuevo);

//Procedimiento que crea un nuevo nodo del arbol binario
void crear_rank(pnodo_a &nuevo,pnodo_s &nuevor);

//Procedimiento que muestra el rankings de jugadores
void mostrar_ranking(pnodo_a arbol);

//Procedimiento que restringe el numero de nodos del arbol
void restringir_ranking(pnodo_a &ranking);


//Procedimiento inicializador de la partida
void iniciar_partida(tlistad tablero, tlistas &jugadores,pnodo_a &ranking);

//Menu principal
int main() {
  tlistas jugadores;
  tlistad tablero;
  pnodo_a ranking;
  int opc,cont=0;
  bool band1=false,band2=false;

  iniciar_lista(jugadores);
  iniciar_tablero(tablero);
  iniciar_ranking(ranking);
  do {
    cout << "*********** AVENTURA PIRATA *************\n" << endl;
    cout << "Elija una opcion: " << endl;
    cout << "1) Administar jugadores." << endl;
    cout << "2) Generar tablero de juego." << endl;
    cout << "3) Iniciar la partida." << endl;
    cout << "4) Ranking jugadores." << endl;
    cout << "5) Salir." << endl;
    cout << "*********** ************** ************" << endl;
    cin >> opc;

    switch (opc) {

    case 1:
      menu_jugadores(jugadores);
      break;

    case 2:
    	if(jugadores.inicio!=NULL && jugadores.inicio->sig!=NULL)
    		cargar_tablero(tablero);
    	else
    		cout << "No hay jugadores registrados, por favor registre al menos 2 jugadores" << endl;
  			system("pause");
  			system("cls");
      break;

    case 3:
    	if(jugadores.inicio!=NULL){
    	  if(jugadores.inicio->sig!=NULL && tablero.inicio!=NULL)
    	  	iniciar_partida(tablero,jugadores,ranking);
		  else
			cout << "Cantidad de jugadores insuficiente o tablero no iniciado" << endl;
		} else
			cout << "No hay jugadores registrados, por favor registre al menos 2 jugadores" << endl;
  			system("pause");
  			system("cls");
      break;

    case 4:
    	if(ranking!=NULL)
          mostrar_ranking(ranking);
        else
          cout << "No hay Partidas jugadas" << endl;
  			system("pause");
  			system("cls");
      break;

    case 5:
	  iniciar_lista(jugadores);
	  iniciar_tablero(tablero);
	  iniciar_ranking(ranking);
      cout << "\nFIN DEL JUEGO" << endl;
      break;

    default:
      cout << "Error en el ingreso." << endl;
      break;
    }

  } while (opc != 5);
}

//Desarrolo de Procedimientos y funciones

void iniciar_lista(tlistas &lista) {
  lista.inicio = NULL;
  lista.final = NULL;
  lista.cont = 0;
}
char mayuscula(char p){
  if(p>=97 && p<=122){
  	p-=32;
  }
  return p;
}
void cargar_cadena(pal contenido, pal &contenedor) {
  for (int i = 0; i < MAX2; i++) {
    contenedor[i] = mayuscula(contenido[i]);
  }
}
bool verificar_jugador(tlistas lista, pal nombre, pal apellido, pal nickname) {
  bool diferentes = true;
  if (lista.inicio != NULL) {
    if (lista.inicio->sig == NULL) {
      if (strcmp(lista.inicio->dato.nombre, nombre) == 0 ||
          strcmp(lista.inicio->dato.apellido, apellido) == 0 ||
          strcmp(lista.inicio->dato.nickname, nickname) == 0)
        diferentes = false;
    } else {
      if (lista.inicio->sig == lista.final) {
        if (strcmp(lista.inicio->dato.nombre, nombre) == 0 ||
            strcmp(lista.inicio->dato.apellido, apellido) == 0 ||
            strcmp(lista.inicio->dato.nickname, nickname) == 0) {
          diferentes = false;
        } else {

          if (strcmp(lista.final->dato.nombre, nombre) == 0 ||
              strcmp(lista.final->dato.apellido, apellido) == 0 ||
              strcmp(lista.final->dato.nickname, nickname) == 0) {
            diferentes = false;
          }
        }
      } else {

        pnodo_s p;
        while (p != NULL && strcmp(p->dato.nombre, nombre) != 0 &&
               strcmp(p->dato.apellido, apellido) != 0 &&
               strcmp(p->dato.nickname, nickname) != 0) {
          p = p->sig;
        }

        if (p != NULL) {
          diferentes = false;
        }
      }
    }
  }
  return diferentes;
}
void agregar_jugador(tlistas &lista, pnodo_s nuevo) {

  if (lista.inicio == NULL) {
    lista.inicio = nuevo;
    lista.final = nuevo;
  } else {

    if (lista.inicio == lista.final) {

      if (strcmp(nuevo->dato.nickname, lista.inicio->dato.nickname) < 0) {

        nuevo->sig = lista.inicio;
        lista.inicio = nuevo;
      } else {

        lista.final->sig = nuevo;
        lista.final = nuevo;
      }
    } else {

      if (lista.inicio->sig == lista.final) {

        if (strcmp(nuevo->dato.nickname, lista.inicio->dato.nickname) < 0) {

          nuevo->sig = lista.inicio;
          lista.inicio = nuevo;
        } else {

          if (strcmp(nuevo->dato.nickname, lista.final->dato.nickname) < 0) {

            nuevo->sig = lista.final;
            lista.inicio->sig = nuevo;
          } else {

            lista.final->sig = nuevo;
            lista.final = nuevo;
          }
        }
      } else {

        if (strcmp(nuevo->dato.nickname, lista.inicio->dato.nickname) < 0) {

          nuevo->sig = lista.inicio;
          lista.inicio = nuevo;
        } else {
          pnodo_s p = lista.inicio;
          while (p->sig != NULL &&
                 (strcmp(nuevo->dato.nickname, p->sig->dato.nickname) > 0))
            p = p->sig;
          nuevo->sig = p->sig;
          p->sig = nuevo;
        }
      }
    }
  }

  lista.cont++;
}
void crear_nodo(tlistas &lista) {
	if(lista.cont<MAX1){
	  pnodo_s nuevo = new nodo_s;
	  if (nuevo != NULL) {
	    pal nombre, apellido, nickname;
	    char r;
	    do {
	      cout << "Ingrese Nombre del jugador " << endl;
	      cin >> nombre;
	      cout << "Ingrese Apellido del jugador " << endl;
	      cin >> apellido;
	      cout << "Ingrese Nickname del jugador " << endl;
	      cin >> nickname;
	      if (verificar_jugador(lista, nombre, apellido, nickname)) {
	
	        cargar_cadena(nombre, nuevo->dato.nombre);
	        cargar_cadena(apellido, nuevo->dato.apellido);
	        cargar_cadena(nickname, nuevo->dato.nickname);
	        nuevo->dato.puntaje = 0;
	        nuevo->dato.turno=true;
	        nuevo->sig = NULL;
	        agregar_jugador(lista, nuevo);
	  		system("cls");
	        cout << "Carga exitosa!" << endl;
			system("pause");
			system("cls");
	        r = 'n';
	      } else {
	        cout << "Los datos del Jugador coinciden con otro jugador registrado!"
	             << endl;
	        cout << "Desea ingresar los datos nuevamente? [S/n]:" << endl;
	        cin >> r;
	      }
	    } while (r == 's' || r == 'S');
	    if (r != 's' || r != 'S') {
	      nuevo = NULL;
	    }
	  } else {
	    cout << "memoria insuficiente" << endl;
	  }
	} else {
	  cout << "Se lleno la agenda de jugadores" <<endl;
	}
}
void buscar_jugador(tlistas lista) {

  pal nbusc;
  pnodo_s p;

  pnodo_s encontrado = NULL;

  if (lista.inicio != NULL) {

    if (lista.inicio == lista.final) {
      cout << "Unico Jugador Registrado:" << endl;
      cout << "Nombre: " << lista.inicio->dato.nombre << endl;
      cout << "Apellido: " << lista.inicio->dato.apellido << endl;
      cout << "Nickname: " << lista.inicio->dato.nickname << endl;

    } else {

      cout << "Nombre del jugador que busca: " << endl;
      cin >> nbusc;
	  cargar_cadena(nbusc,nbusc);
	  
      p = lista.inicio;

      while (p != NULL && strcmp(p->dato.nombre, nbusc) != 0)
        p = p->sig;

      if (p == NULL) {
		
  		system("cls");
        cout << "El jugador no existe" << endl;

      } else {

        cout << "Nombre: " << p->dato.nombre << endl;
        cout << "Apellido: " << p->dato.apellido << endl;
        cout << "Nickname: " << p->dato.nickname << endl;
        cout << "Puntaje: " << p->dato.puntaje << endl;
      }
    }

  } else {

  	system("cls");
    cout << "lista vacia intente nuevamente" << endl;
  }
  system("pause");
  system("cls");
}
void listar_jugador(tlistas lista) {

  pnodo_s k;
  k = lista.inicio;

  while (k != NULL) {

    cout << "Nickname: " << k->dato.nickname << endl;
    cout << "	Nombre: " << k->dato.nombre << endl;
    cout << "	Apellido: " << k->dato.apellido << endl << endl;

    k = k->sig;
  }
}
void listar_jugador_dos(tlistas lista,pnodo_s excep) {

  pnodo_s k;
  k = lista.inicio;

  while (k != NULL && k!=excep) {

    cout << "Nickname: " << k->dato.nickname << endl;
    cout << "	Nombre: " << k->dato.nombre << endl;
    cout << "	Apellido: " << k->dato.apellido << endl << endl;

    k = k->sig;
  }
}
void modificar_jugador(tlistas &lista) {

  if (lista.inicio != NULL) {

    pal nbusc, nombre, apellido, nickname;
    pnodo_s p;

    cout << "Nombre del jugador a modificar: " << endl;

    listar_jugador(lista);

    cin >> nbusc;
    cargar_cadena(nbusc,nbusc);

    bool encontrado = false;

    p = lista.inicio;

    while (p != NULL && strcmp(p->dato.nombre, nbusc))
      p = p->sig;

    if (p != NULL) {

      cout << "Nuevo nombre:" << endl;
      cin >> nombre;
      cout << "Nuevo apellido:" << endl;
      cin >> apellido;
      cout << "Nuevo nickname:" << endl;
      cin >> nickname;

      if (verificar_jugador(lista, nombre, apellido, nickname)) {

        cargar_cadena(nombre, p->dato.nombre);
        cargar_cadena(apellido, p->dato.apellido);
        cargar_cadena(nickname, p->dato.nickname);
  		system("cls");
        cout << "Modificacion exitosa!" << endl;
        cout << endl;
      } else {

  		system("cls");
        cout << "No se pudo modificar, datos no validos" << endl;
        cout << endl;
      }

    } else {

  	  system("cls");
      cout << "El jugador no existe" << endl;
      return;
    }

  } else {

	system("cls");
    cout << "La lista se encuentra vacia intente nuevamente" << endl;
  }
  system("pause");
  system("cls");
}
void eliminar_jugador(tlistas &lista) {
  char r;
  if (lista.inicio != NULL) {
    if (lista.inicio->sig == NULL) {
      cout << "Desea eliminar al unico jugador de la lista? [S/n]:" << endl;
      cin >> r;
      if (r == 's' || r == 'S') {

        lista.inicio = NULL;
        lista.final = NULL;
        lista.cont--;
  		system("cls");
        cout << "Jugador eliminado exitosamente!" << endl;

      } else {
  		system("cls");
        cout << "Se cancelo la eliminacion de jugadores" << endl;
      }
    } else {

      if (lista.inicio->sig == lista.final) {

        pal opc;
        do {
          cout <<"Cual desea Eliminar?:" << endl;
          cout <<	"Jugador 1: " << lista.inicio->dato.nombre << endl;
          cout <<	"Jugador 2: " << lista.final->dato.nombre << endl;
          cout <<"Ingrse el nombre del jugador a eliminar: ";
          cin >> opc;
          cargar_cadena(opc,opc);
          if (strcmp(opc, lista.inicio->dato.nombre) == 0) {

            lista.inicio = lista.final;
            lista.cont--;
            r = 'n';
  			system("cls");
            cout << "Jugador eliminado exitosamente!" << endl;
          } else {

            if (strcmp(opc, lista.final->dato.nombre) == 0) {

              lista.inicio->sig = NULL;
              lista.final = lista.inicio;
              lista.cont--;
              r = 'n';
  			  system("cls");
              cout << "Jugador eliminado exitosamente!" << endl;
            } else {

              cout << "Jugador no encontrado o no existe. Desea intentar "
                      "nuevamente? [S/n]: "
                   << endl;
              cin >> r;
            }
          }
        } while (r == 's' || r == 'S');
      } else {
            
        pnodo_s p = lista.inicio, aux;
        pal nelim;

        do {
          listar_jugador(lista);
          cout << "Ingrese el nombre del Jugador a Eliminar: ";
          cin >> nelim;
          cargar_cadena(nelim,nelim);
		  if (strcmp(lista.inicio->dato.nombre,nelim) == 0){
			lista.inicio=lista.inicio->sig;
            lista.cont--;
            r = 'n';
  			system("cls");
            cout << "Jugador eliminado exitosamente!" << endl;
		  } else {
	        while (p->sig != NULL && strcmp(p->sig->dato.nombre, nelim) != 0)
	          p = p->sig;

          	if (p->sig == NULL) {

              cout << "Jugador no encontrado o no existe. Desea intentar "
                      "nuevamente? [S/n]: "
                   << endl;
              cin >> r;

          	} else {
              aux = p->sig;
              p->sig = aux->sig;
              lista.cont--;
              r = 'n';
  			  system("cls");
              cout << "Jugador eliminado exitosamente!" << endl;
          	}
		  }
        } while (r == 's' || r == 'S');
      }
    }
  } else {

  	system("cls");
    cout << "La lista se encuentra vacia intente nuevamente" << endl;
  }
  system("pause");
  system("cls");
}
void menu_jugadores(tlistas &lista) {

  int opc;

  do {
    cout << "*********** Submenu de jugadores. ***********\n" << endl;
    cout << "Elija una opcion: " << endl;
    cout << "1) Registrar un jugador." << endl;
    cout << "2) Consultar un jugador." << endl;
    cout << "3) Modificar un jugador." << endl;
    cout << "4) Eliminar un jugador." << endl;
    cout << "5) Listar jugadores." << endl;
    cout << "6) Retroceder." << endl;
    cout << "*********** ************** ************" << endl;
    cin >> opc;

    switch (opc) {

    case 1:
      crear_nodo(lista);
      cout << endl;
      break;

    case 2:
      buscar_jugador(lista);
      cout << endl;
      break;

    case 3:
      modificar_jugador(lista);
      cout << endl;
      break;

    case 4:
      eliminar_jugador(lista);
      cout << endl;
      break;

    case 5:
      listar_jugador(lista);
      cout << endl;
      break;

    case 6:
      system("cls");
      return;
      break;

    default:
      cout << "Error en el ingreso." << endl;
      break;
    }

  } while (opc != 6);
}


void iniciar_tablero(tlistad &tablero){
	tablero.inicio=NULL;
	tablero.final=NULL;
}
void crear_casilla(pnodo_d &casilla, int valor){
	casilla = new nodo_d;
	casilla->dato.num=valor;
	switch(valor){
		case 4:
			casilla->dato.sol=true;
			break;
			
		case 9:
			casilla->dato.kraken=true;
			break;
			
		case 10:
			casilla->dato.kraken=true;
			break;
			
		case 11:
			casilla->dato.kraken=true;
			break;
			
		case 13:
			casilla->dato.sol=true;
			break;
			
		case 18:
			casilla->dato.sirena=true;
			break;
			
		case 19:
			casilla->dato.sirena=true;
			break;
			
		case 20:
			casilla->dato.sirena=true;
			break;
			
		case 22:
			casilla->dato.sol=true;
			break;
			
		case 23:
			casilla->dato.tifon=true;
			break;
			
		case 24:
			casilla->dato.tifon=true;
			break;
			
		case 25:
			casilla->dato.tifon=true;
			break;
	}
	casilla->ant=NULL;
	casilla->sig=NULL;
}
void agregar_casilla(tlistad &tablero, pnodo_d casilla){
	if(tablero.inicio == NULL){
		tablero.inicio=casilla;
		tablero.final=casilla;
	} else {
		tablero.final->sig=casilla;
		tablero.final=casilla;
		if(tablero.inicio==tablero.final){
			tablero.inicio->sig=tablero.final;
			tablero.final->ant=tablero.inicio;
		}
	}
}
void cargar_tablero(tlistad &tablero){
	pnodo_d casilla;
	for(int i=0;i<MAX2;i++){
		crear_casilla(casilla,i+1);
		agregar_casilla(tablero,casilla);
	}
	system("cls");
    cout << "Tablero Creado Exitosamente!!" << endl;
}
void seleccionar_jugador(tlistas jugadores, pnodo_s &jugador,pal nickname){
  pnodo_s k;
  k = jugadores.inicio;

  while (k != NULL && strcmp(k->dato.nickname,nickname)!=0)
    k = k->sig;
	if(k!=NULL){
		jugador=k;
		jugador->sig=NULL;
		cout << "Jugador 1 Seleccionado correctamente!!" << endl;
	} else 
	  cout << "Jugador no encontrado, intente nuevamente" << endl;
}


void iniciar_ranking(pnodo_a &arbol){
	arbol=NULL;
}
int contar_ranks(pnodo_a arbol){
	int cont;
	if(arbol==NULL)
		return 0;
	else
		return contar_ranks(arbol->izq)+contar_ranks(arbol->der)+1;
}
void insertar_rank(pnodo_a &arbol,pnodo_a nuevo){
	if(arbol==NULL)
		arbol=nuevo;
	else
		if(nuevo->dato.nickname==arbol->dato.nickname){
			cargar_cadena(nuevo->dato.apellido,arbol->dato.apellido);
			cargar_cadena(nuevo->dato.nombre,arbol->dato.nombre);
			cargar_cadena(nuevo->dato.nickname,arbol->dato.nickname);
			arbol->dato.puntaje=nuevo->dato.puntaje;
			arbol->dato.turno=nuevo->dato.turno;
			arbol->izq=NULL;
			arbol->der=NULL;
			return;
		} else
			if(nuevo->dato.puntaje<arbol->dato.puntaje)
				insertar_rank(arbol->izq,nuevo);
			else
				insertar_rank(arbol->der,nuevo);
}
void crear_rank(pnodo_a &nuevo,pnodo_s &nuevor){
	nuevo = new nodo_a;
	if(nuevo!=NULL){
		cargar_cadena(nuevor->dato.apellido,nuevo->dato.apellido);
		cargar_cadena(nuevor->dato.nickname,nuevo->dato.nickname);
		cargar_cadena(nuevor->dato.nombre,nuevo->dato.nombre);
		nuevo->dato.puntaje=nuevor->dato.puntaje;
		nuevo->dato.turno=true;
		nuevo->izq=NULL;
		nuevo->der=NULL;
	} else
		cout << "Memoria Insuficiente" << endl;
}
void mostrar_ranking(pnodo_a arbol){
	if(arbol!=NULL){
		mostrar_ranking(arbol->der);
		cout << "Jugador: " << arbol->dato.nickname << "	Puntaje: " << arbol->dato.puntaje;
		mostrar_ranking(arbol->izq);
	}
}
void restringir_ranking(pnodo_a &ranking){
	if(ranking->izq==NULL && ranking->der==NULL){
		ranking=NULL;
	} else {
		restringir_ranking(ranking->izq);
	}
}


void iniciar_partida(tlistad tablero, tlistas &jugadores,pnodo_a &ranking){
	pal nickname;
	pnodo_s jugadorU, jugadorD;
	pnodo_a nrank;
	int barcosU=0, barcosD=0,cont1=1,cont2=1,dado;
	srand(time(NULL));
	do{
		cout << "Seleccione Jugador 1: "<<endl;
		cout<<"escriba su nickname..."<<endl;
		listar_jugador(jugadores);
		cin>>nickname;
		cargar_cadena(nickname,nickname);
		seleccionar_jugador(jugadores,jugadorU,nickname);
	}while(jugadorU==NULL);
	do{
	  	cout << "Seleccione Jugador 2: "<<endl;
	  	cout<<"escriba su nickname..."<<endl;
	  	listar_jugador_dos(jugadores,jugadorU);
	  	cin >> nickname;
	  	cargar_cadena(nickname,nickname);
	  	if(strcmp(nickname,jugadorU->dato.nickname)==0)
	  		cout<<"El jugaddor ya esta en la salida, seleccione otro jugador..."<<endl;
	  	seleccionar_jugador(jugadores,jugadorD,nickname);
	}while(strcmp(nickname,jugadorU->dato.nickname)==0 || jugadorD==NULL);
	do{
		if(cont1<tablero.final->dato.num){
			if(jugadorU->dato.turno==true){
				dado=1+rand()%(7-1);
				cout << jugadorU->dato.nickname << " saco un " << dado << endl;
				cont1+=dado;
				pnodo_d p=tablero.inicio;
				while(p!=NULL && p->dato.num!=cont1) p=p->sig;
				if(p!=NULL){
					if(!p->dato.kraken && !p->dato.sirena && !p->dato.sol && !p->dato.tifon)
						jugadorU->dato.puntaje+=5;
					else {
						if(p->dato.sol){
							cout << jugadorU->dato.nickname << " cayo en un sol, avanza 4 casillas." << endl;
							jugadorU->dato.puntaje+=6;
							cont1+=4;
						}
						if(p->dato.sirena){
							cout << jugadorU->dato.nickname << "se quedo escuchando el canto de las sirenas, pierde un turno." << endl;
							jugadorU->dato.puntaje-=3;
							jugadorU->dato.turno=false;
						}
						if(p->dato.kraken){
							cout << "Un kraken deboro la embarcacion, " << jugadorU->dato.nickname << "vuelve a comenzar." << endl;
							jugadorU->dato.puntaje-=3;
							cont1=1;
						}
						if(p->dato.tifon){
							cout << jugadorU->dato.nickname << " cayo en un tifon, retrocede 3 casillas" << endl;
							jugadorU->dato.puntaje-=3;
							cont1-=3;
						}
					}
				}
			} else {
				cout << jugadorU->dato.nickname << " no juega este turno" << endl;
				jugadorU->dato.turno=true;
			}
		} else {
			if(cont1==MAX2){
				jugadorU->dato.turno=false;
				jugadorD->dato.turno=false;
				barcosU++;
				cout<<" el barco "<<barcosU<<" del jugador"<<jugadorU->dato.nickname<<" llego al tesoro"<<endl;
				if(barcosU==1)
					cout<<"Faltan 2 barcos!!"<<endl;
				else
					if(barcosU==2)
						cout<<"Falta 1 barco!!"<<endl;
					else
						if(barcosU==3)
							cout<<"Llegaron los 3 barcos al tesoro!!"<<endl;
			}
		}
		if(cont1<tablero.final->dato.num){
			if(jugadorD->dato.turno==true){
				dado=1+rand()%(7-1);
				cout << jugadorD->dato.nickname << " saco un " << dado << endl;
				cont2+=dado;
				pnodo_d p=tablero.inicio;
				while(p!=NULL && p->dato.num!=cont2) p=p->sig;
				if(p!=NULL){
					if(!p->dato.kraken && !p->dato.sirena && !p->dato.sol && !p->dato.tifon)
						jugadorD->dato.puntaje+=5;
					else {
						if(p->dato.sol){
							cout << jugadorD->dato.nickname << " cayo en un sol, avanza 4 casillas." << endl;
							jugadorD->dato.puntaje+=6;
							cont1+=4;
						}
						if(p->dato.sirena){
							cout << jugadorD->dato.nickname << "se quedo escuchando el canto de las sirenas, pierde un turno." << endl;
							jugadorD->dato.puntaje-=3;
							jugadorD->dato.turno=false;
						}
						if(p->dato.kraken){
							cout << "Un kraken deboro la embarcacion, " << jugadorD->dato.nickname << "vuelve a comenzar." << endl;
							jugadorD->dato.puntaje=0;
							cont1=1;
						}
						if(p->dato.tifon){
							cout << jugadorD->dato.nickname << " cayo en un tifon, retrocede 3 casillas" << endl;
							jugadorD->dato.puntaje-=3;
							cont1-=3;
						}
					}
				}				
			} else {
				cout << jugadorD->dato.nickname << " no juega este turno" << endl;
				jugadorD->dato.turno=true;
			}
		} else {
			if(cont2==MAX2){
				jugadorU->dato.turno=false;
				jugadorD->dato.turno=false;
				barcosD++;
				cout<<" el barco "<<barcosD<<" del jugador"<<jugadorD->dato.nickname<<" llego al tesoro"<<endl;
				if(barcosD==1)
					cout<<"Faltan 2 barcos!!"<<endl;
				else
					if(barcosD==2)
						cout<<"Falta 1 barco!!"<<endl;
					else
						if(barcosD==3)
							cout<<"Llegaron los 3 barcos al tesoro!!"<<endl;
			}
		}
	}while(barcosU!=3 || barcosD!=3);
	if(barcosU==3){
		cout << "Felicidades " << jugadorU->dato.nickname << " eres el sucesor de Barba Negra!!!"<< endl;
		crear_rank(nrank,jugadorU);
	}
	else{
		cout << "Felicidades " << jugadorD->dato.nickname << " eres el sucesor de Barba Negra!!!"<< endl;
		crear_rank(nrank,jugadorD);
	}
	insertar_rank(ranking,nrank);
	if(contar_ranks(ranking)>5){
		restringir_ranking(ranking);
	}
	
}

