# Traductor de Dirección Virtual a Física
- Este programa mostrará la dirección física resultante de acuerdo a la dirección virtual proporcionada

- Se define desde un archivo el número de páginas y el número de marcos
- Los elementos de la tabla de páginas se encuentran en el mismo archivo


## Comandos para instalar (Linux)
Instalar meson como sea posible considerando que sea la ultima version**Ultima version Usada 1.5.1**
```bash
pip install meson
```
```bash
pip install meson==1.5.1
```

***La version de `apt` puede estar desactualizada***

## Compilar con Meson
```bash
meson setup out
meson compile -C out/
```

### Ejecutar en Linux
```bash
./out/traductor {archivo usado}
```