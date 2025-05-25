# GraphQuest - Tarea 3

**Alumno:** Luis Ignacio  

---

## 1. Cómo compilar y ejecutar la tarea

###  Requisitos
- Sistema operativo: Windows, Linux o Mac.
- Compilador de C: GCC (MinGW en Windows o `gcc` en Linux/macOS).

###  Archivos necesarios
Todos los archivos deben estar en la **misma carpeta**:
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
###2. Opciones que funcionan correctamente y las que no
Funcionalidades implementadas y funcionando:
Carga del laberinto desde archivo CSV.

Representación de los escenarios como grafo con conexiones.

Menú principal: cargar laberinto, iniciar partida, salir.
Menú del juego:

Ver estado actual (nombre, descripción, ítems, inventario, tiempo).

Recoger ítems del escenario.

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
 


