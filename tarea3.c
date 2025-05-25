#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "extra.h"

#define MAX_TIEMPO 20

typedef struct {
  char nombre[64];
  int valor;
  int peso;
} Item;

typedef struct Escenario {
  int id;
  char nombre[128];
  char descripcion[256];
  List *items;

  struct Escenario *arriba, *abajo, *izquierda, *derecha;
  int id_arriba, id_abajo, id_izquierda, id_derecha;

  int esFinal;
} Escenario;

typedef struct {
  Escenario *actual;
  List *inventario;
  int tiempo_restante;
  int puntaje;
} Jugador;

Escenario *mapa[100];

Escenario* get_escenario(int id) {
  return (id > 0 && id < 100) ? mapa[id] : NULL;
}

Escenario* cargar_laberinto(const char *archivo) {
  FILE *f = fopen(archivo, "r");
  if (!f) {
    perror("No se pudo abrir el archivo");
    return NULL;
  }

  char **campos;
  leer_linea_csv(f, ','); // encabezado

  while ((campos = leer_linea_csv(f, ',')) != NULL) {
    Escenario *e = malloc(sizeof(Escenario));
    e->id = atoi(campos[0]);
    strcpy(e->nombre, campos[1]);
    strcpy(e->descripcion, campos[2]);
    e->items = list_create();

    List *lista_items = split_string(campos[3], ";");
    for (char *item = list_first(lista_items); item != NULL; item = list_next(lista_items)) {
      List *info = split_string(item, ",");
      Item *nuevo = malloc(sizeof(Item));
      strcpy(nuevo->nombre, list_first(info));
      nuevo->valor = atoi(list_next(info));
      nuevo->peso = atoi(list_next(info));
      list_pushBack(e->items, nuevo);
      list_clean(info); free(info);
    }
    list_clean(lista_items); free(lista_items);

    // Guardar las conexiones como IDs
    e->id_arriba = atoi(campos[4]);
    e->id_abajo = atoi(campos[5]);
    e->id_izquierda = atoi(campos[6]);
    e->id_derecha = atoi(campos[7]);

    e->esFinal = atoi(campos[8]);
    mapa[e->id] = e;
  }

  fclose(f);

  // Segunda pasada: enlazar conexiones
  for (int i = 1; i < 100; i++) {
    if (mapa[i]) {
      mapa[i]->arriba = get_escenario(mapa[i]->id_arriba);
      mapa[i]->abajo = get_escenario(mapa[i]->id_abajo);
      mapa[i]->izquierda = get_escenario(mapa[i]->id_izquierda);
      mapa[i]->derecha = get_escenario(mapa[i]->id_derecha);
    }
  }

  return mapa[1];
}

int calcular_tiempo_movimiento(List *inventario) {
  int peso_total = 0;
  for (Item *item = list_first(inventario); item != NULL; item = list_next(inventario))
    peso_total += item->peso;
  return (peso_total + 1 + 9) / 10;
}

void mostrar_estado(Jugador *jugador) {
  Escenario *e = jugador->actual;
  printf("\n=== ESCENARIO ACTUAL: %s ===\n%s\n", e->nombre, e->descripcion);
  puts("Items disponibles:");
  for (Item *item = list_first(e->items); item != NULL; item = list_next(e->items))
    printf("- %s (%d pts, %d kg)\n", item->nombre, item->valor, item->peso);

  printf("\nTIEMPO RESTANTE: %d\n", jugador->tiempo_restante);
  puts("INVENTARIO:");
  int peso = 0;
  for (Item *item = list_first(jugador->inventario); item != NULL; item = list_next(jugador->inventario)) {
    printf("- %s (%d pts, %d kg)\n", item->nombre, item->valor, item->peso);
    peso += item->peso;
  }
  printf("Peso total: %d kg | Puntaje: %d\n", peso, jugador->puntaje);

  puts("Conexiones disponibles:");
  if (e->arriba) puts("1) Arriba");
  if (e->abajo) puts("2) Abajo");
  if (e->izquierda) puts("3) Izquierda");
  if (e->derecha) puts("4) Derecha");
  puts("5) Recoger item");
  puts("6) Descartar item");
  puts("7) Reiniciar");
  puts("8) Salir");
}

void jugar(Escenario *inicio) {
  Jugador jugador = {inicio, list_create(), MAX_TIEMPO, 0};
  char opcion[10];
  while (1) {
    mostrar_estado(&jugador);
    printf("Accion: ");
    scanf("%s", opcion);

    if (strcmp(opcion, "1") == 0 && jugador.actual->arriba) jugador.actual = jugador.actual->arriba;
    else if (strcmp(opcion, "2") == 0 && jugador.actual->abajo) jugador.actual = jugador.actual->abajo;
    else if (strcmp(opcion, "3") == 0 && jugador.actual->izquierda) jugador.actual = jugador.actual->izquierda;
    else if (strcmp(opcion, "4") == 0 && jugador.actual->derecha) jugador.actual = jugador.actual->derecha;
    else if (strcmp(opcion, "5") == 0) 
    {
      printf("Ingrese el nombre del item a recoger: ");
      char nombre[64]; scanf(" %63[^\n]", nombre);
      bool encontrado = false;
      for (Item *item = list_first(jugador.actual->items); item != NULL; item = list_next(jugador.actual->items)) {
        if (strcmp(item->nombre, nombre) == 0) {
          list_pushBack(jugador.inventario, item);
          jugador.puntaje += item->valor;
          list_popCurrent(jugador.actual->items);
          jugador.tiempo_restante--;
          encontrado = true;
          break;
        }
      }
      if (!encontrado) printf("Ese item no esta disponible aqui.\n");
    }
    else if (strcmp(opcion, "6") == 0) {
      printf("Ingrese el nombre del item a descartar: ");
      char nombre[64]; scanf(" %63[^\n]", nombre);
      for (Item *item = list_first(jugador.inventario); item != NULL; item = list_next(jugador.inventario)) {
        if (strcmp(item->nombre, nombre) == 0) {
          jugador.puntaje -= item->valor;
          list_popCurrent(jugador.inventario);
          jugador.tiempo_restante--;
          break;
        }
      }
    }
    else if (strcmp(opcion, "7") == 0) {
      jugador.actual = inicio;
      list_clean(jugador.inventario);
      jugador.inventario = list_create();
      jugador.puntaje = 0;
      jugador.tiempo_restante = MAX_TIEMPO;
    }
    else if (strcmp(opcion, "8") == 0) break;

    if (jugador.actual->esFinal) {
      printf("\n¡Llegaste a la salida!\nPuntaje final: %d\n", jugador.puntaje); break;
   }

jugador.tiempo_restante -= calcular_tiempo_movimiento(jugador.inventario);


    if (jugador.tiempo_restante <= 0) {
      puts("\n\u00a1Tiempo agotado! Has perdido.");
      break;
    }

    if (jugador.actual->esFinal) {
      printf("\n\u00a1Llegaste a la salida!\nPuntaje final: %d\n", jugador.puntaje);
      break;
    }
  }
}

int main() {
  Escenario *inicio = NULL;
  char opcion;
  do {
    puts("==== MENU PRINCIPAL ====");
    puts("1) Cargar Laberinto");
    puts("2) Iniciar Partida");
    puts("3) Salir");
    printf("Opcion: ");
    scanf(" %c", &opcion);
    if (opcion == '1') {
      inicio = cargar_laberinto("graphquest.csv");
      if (inicio) puts("Laberinto cargado correctamente.");
    } else if (opcion == '2' && inicio) {
      jugar(inicio);
    } else if (opcion == '2') {
      puts("Primero debes cargar el laberinto.");
    }
  } while (opcion != '3');

  return 0;
}