# GraphQuest - Tarea 3

**Alumno:** Luis Ignacio  

---

## 1. Cómo compilar y ejecutar la tarea

###  Archivos necesarios:
- `tarea3.c`
- `extra.c`
- `extra.h`
- `list.c`
- `list.h`
- `graphquest.csv` 

###  Instrucciones para compilar y ejecutar

```bash
gcc tarea3.c extra.c list.c -o graphquest <-(para compilar)
./graphquest  <-(para ejecutar)
```
##2. Opciones que funcionan correctamente y las que no
Funcionalidades implementadas y funcionando:
Carga del laberinto desde archivo CSV.

Representación de los escenarios como grafo con conexiones.

Menú principal: cargar laberinto, iniciar partida, salir.
Menú del juego:

Ver estado actual (nombre, descripción, ítems, inventario, tiempo).

Recoger ítems del escenario(al recogerlo escribirlo exactamente como te lo muestra).

Descartar ítems del inventario.

Avanzar en direcciones disponibles (arriba, abajo, izquierda, derecha).

Reiniciar partida.

Salir del juego.

Victoria si se alcanza la salida (esFinal = 1).

Derrota si el tiempo llega a 0.

###Funcionalidades no implementadas:
 Guardar/cargar partidas desde archivo.
 Ranking de puntajes.
 Validación de errores avanzada (como entradas inválidas del usuario).
 algunos prints se ven mal por las tildes


 Ejemplo de uso

==== MENU PRINCIPAL ====
1) Cargar Laberinto
2) Iniciar Partida
3) Salir
Opcion: 1
Laberinto cargado correctamente.
==== MENU PRINCIPAL ====
1) Cargar Laberinto
2) Iniciar Partida
3) Salir
Opcion: 2

=== ESCENARIO ACTUAL: Entrada principal ===
Una puerta rechinante abre paso a esta mansion olvidada por los dioses y los conserjes. El aire huele a humedad y a misterios sin resolver.
Items disponibles:

TIEMPO RESTANTE: 20
INVENTARIO:
Peso total: 0 kg | Puntaje: 0
Conexiones disponibles:
2) Abajo
5) Recoger item
6) Descartar item
7) Reiniciar
8) Salir
Accion: 2

=== ESCENARIO ACTUAL: Cocina ===
Restos de una batalla culinaria. Cuchillos por aqui, migajas por alla. Alguien cocinoÔÇª o fue cocinado.
Items disponibles:
- Cuchillo (3 pts, 1 kg)
- Pan (2 pts, 1 kg)

TIEMPO RESTANTE: 19
INVENTARIO:
Peso total: 0 kg | Puntaje: 0
Conexiones disponibles:
1) Arriba
2) Abajo
4) Derecha
5) Recoger item
6) Descartar item
7) Reiniciar
8) Salir
Accion: Cuchillo

=== ESCENARIO ACTUAL: Cocina ===
Restos de una batalla culinaria. Cuchillos por aqui, migajas por alla. Alguien cocinoÔÇª o fue cocinado.
Items disponibles:
- Cuchillo (3 pts, 1 kg)
- Pan (2 pts, 1 kg)

TIEMPO RESTANTE: 18
INVENTARIO:
Peso total: 0 kg | Puntaje: 0
Conexiones disponibles:
1) Arriba
2) Abajo
4) Derecha
5) Recoger item
6) Descartar item
7) Reiniciar
8) Salir
Accion: 5
Ingrese el nombre del item a recoger: Cuchillo

=== ESCENARIO ACTUAL: Cocina ===
Restos de una batalla culinaria. Cuchillos por aqui, migajas por alla. Alguien cocinoÔÇª o fue cocinado.
Items disponibles:
- Pan (2 pts, 1 kg)

TIEMPO RESTANTE: 16
INVENTARIO:
- Cuchillo (3 pts, 1 kg)
Peso total: 1 kg | Puntaje: 3
Conexiones disponibles:
1) Arriba
2) Abajo
4) Derecha
5) Recoger item
6) Descartar item
7) Reiniciar
8) Salir
Accion: 2

=== ESCENARIO ACTUAL: Jardin ===
Mal cuidado y con plantas que parecen tener hambre. Un lugar perfecto para esconder cosas peque├▒as o a un cadaver elegante.
Items disponibles:
- Moneda (2 pts, 1 kg)

TIEMPO RESTANTE: 15
INVENTARIO:
- Cuchillo (3 pts, 1 kg)
Peso total: 1 kg | Puntaje: 3
Conexiones disponibles:
1) Arriba
2) Abajo
5) Recoger item
6) Descartar item
7) Reiniciar
8) Salir
Accion: 6
Ingrese el nombre del item a descartar: Cuchillo

=== ESCENARIO ACTUAL: Jardin ===
Mal cuidado y con plantas que parecen tener hambre. Un lugar perfecto para esconder cosas peque├▒as o a un cadaver elegante.
Items disponibles:
- Moneda (2 pts, 1 kg)

TIEMPO RESTANTE: 13
INVENTARIO:
Peso total: 0 kg | Puntaje: 0
Conexiones disponibles:
1) Arriba
2) Abajo
5) Recoger item
6) Descartar item
7) Reiniciar
8) Salir
Accion: 8
==== MENU PRINCIPAL ====
1) Cargar Laberinto
2) Iniciar Partida
3) Salir
Opcion: 3
 


