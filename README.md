# 005Threads

Analizador de archivos de registro HTTP implementado en C usando **pthreads**. Divide el archivo entre múltiples hilos para procesarlo en paralelo y combina los resultados al final.

---

## Estructura del proyecto

```
├── main_linux.c                        # Programa principal, manejo de hilos
├── log_processor.h                     # Structs y prototipos
├── log_processor.c                     # Lógica: hash table, parseo, merge
├── Makefile                            # Compilación
├── run.sh                              # Script de compilación y ejecución
├── access_log_file_generator.py        # Archivo generador de log de prueba
└── access.log                          # Archivo de log de prueba

```

---

## Compilar y ejecutar

```bash
make        # solo compilar
make run    # compilar y ejecutar
make clean  # borrar ejecutable
```

O con el script:
```bash
chmod +x run.sh
./run.sh
```

---

## ¿Cómo funciona?

### 1. División del archivo
El archivo se divide en partes iguales según el número de hilos:
```
Hilo 0: byte 0      → 75199
Hilo 1: byte 75199  → 150398
Hilo 2: byte 150398 → 225597
Hilo 3: byte 225597 → 300796
```

### 2. Procesamiento en paralelo
Cada hilo trabaja de forma independiente con sus propias tablas hash, sin compartir datos con los otros hilos (evita race conditions).

### 3. Merge
Cuando todos los hilos terminan, el hilo principal combina los resultados en tablas globales y calcula los totales.

```
args[0].ip_table ─┐
args[1].ip_table ─┤ merge → global_ip → count_unique()
args[2].ip_table ─┤
args[3].ip_table ─┘

args[0].error_count ─┐
args[1].error_count ─┤ suma → total_errors
args[2].error_count ─┤
args[3].error_count ─┘
```

---

## Salida

```
--- RESULT ---
Total Unique IPs: 5
Most Visited URL: /contact (850 veces)
HTTP Errors: 3783
```

---

## Configuración

En `log_processor.h`:

```c
#define NUM_THREADS  4      // número de hilos
#define HASH_SIZE    10007  // tamaño de la tabla hash
```

---

## Conceptos clave

| Concepto | Uso en el proyecto |
|---|---|
| `pthread_create` | Crear cada hilo |
| `pthread_join` | Esperar que terminen |
| `fseek` | Posicionar cada hilo en su byte de inicio |
| `Hash table` | Contar IPs y URLs eficientemente O(1) |
| `ThreadArgs` | Pasar datos a cada hilo y recibir resultados |