# Resumen del Temario

### Estructuras para solidos por fronteras
Hay distintas formas de representar un sólido por fronteras que serían:
  - **Lista de triángulos aislados**: La malla es una lista de triangulos, cada uno formado por 3 vertices
  - **Tiras de triángulos**: Cada triangulo de la tira comparte una arista y dos vertidos que en principio no hay que repetir.
  - **Lista de vértices y triángulos**: Información de la geometria por un lado (vertices) y de la topología por otro (conectividad de vertices)
    - Lista de vertices que no se repiten.
    - Lista de caras una entrada por triangulo compuesto por indices a los vertices anteriores.
  - **Lista de vértices, aristas y triángulos**
    - Lista de vértices: una entrada por cada vértice, por tanto no se repiten
    - Lista de aristas: una entrada por arista que contiene los índices a los vértices extremos de la arista
    - Lista de caras: una entrada por triángulo que contiene los índices a los vértices correspondientes de la lista de vértices

### Generación de modelos por fronteras
Entre ellos podemos encontrar:
  - **Revolución**: Dado un perfil este se revoluciona.
  - **Barrido**: Dada la planta esta se superpone x veces.
  - **Operaciones booleanas**: Se usan sólidos, 2 o más, ya creados y usando las operaciones unión, intersección y diferencia se contruye un modelo nuevo como convinación de las figuras anteriores según la operación realizada.
  - **Geometría constructiva**: Se usan sólidos básicos para construir modelos jerarquicos, por ejemplo una la grua que contruí en practicas.

### Tipos de proyecciones
Hay que diferenciar entre dos tipos de proyecciones:
  - **Perspectivas** (1,2,3 puntos de fuga) pudiendo ser frontal, oblicua y cónica:
    - Produce la ilusión de disminución en el tamaño de los objetos cuando nos vamos alejando del centro de proyección.
    - No se pueden tomar medidas, ángulos y distancias exactas, salvo ángulos en caras paralelas al plano de proyección

  - **Paralelas** que se dividen en:
    - **Oblicua/Caballera**: Permite medir ángulos y distancias para las caras paralelas al plano de proyección y solamente distancias con un cierto factor de escala para las restantes caras.
    - **Triédricas**: Permiten medir tanto ángulos como distancias directamente sobre los dibujos, pero es difícil de deducir las características 3D de los objetos. (Alzado, planta y perfil)
    - **Isometrica**: Tiene la ventaja de permitir la representación a escala, y la desventaja de no reflejar la disminución aparente de tamaño -proporcional a la distancia- que percibe el ojo humano. Los 3 ejes forman angulos de 120º respectivamentete.
    - **Dimétrica**: Variante de la isometrica, solo dos angulos respecto a los ejes son iguales.
    - **Trimétrica**: Ningún ángulo que formen los ejes dos a dos son iguales.

### Transformación de proyección
La matriz de transformación para un punto de fuga se puede calcular de dos formas.
  - PP en z=d, CP en z=0
  - PP en z=0, CP en z=-d

La matriz de un punto del PP se definirá como una regular de 4x4. Si en la posición última, (3,3) hay un 0 nos referiremos a la opción 1), sin embargo si hay un 1 nos estaremos refiriendo a la opción 2).

  Para más puntos de fuga 2 o 3, usaremos rotaciones sobre la matriz 4x4 nombrada anteriormente.

### Proceso de síntesis de una imagen en 3D
Para ver un objeto tridimensional lo que usaremos será una cámara. A la hora de definirla deberemos saber:
  - ¿Desde dónde miramos? (situación o ubicación de la cámara en el espacio).
  - ¿Hacia dónde miramos? (centro de atención o punto de mira).
  - ¿Cuánto ángulo abarcamos? (cantidad de escena que podemos ver).
  - Tipo de proyección (paralela o perspectiva).

### Proceso de síntesis de una imagen en 3D (perspectiva)
Parametros para la perspectiva de un volumen para la vista en 3D por prespectiva:

  - **PO**, punto en el plano de proyección. Punto inicial dosde donde se observa.
  - **PM**, punto de mira (o altura de la cámara). A donde se va a mirar desde PO.
  - **PM**-**PO**, normal al plano (PP) que contiene a PO. Vector resultande de unir PM-PO.
  - **VI**, vector de inclinación de la cámara.
  - **CP**, centro de posición (posición de la cámara).
  - **F** y **T**, planos de recorte frontal y trasero.
  - **Wxmin**, **Wxmax**, **Wymin**, **Wymax**: Ventana en el plano de proyección.

Para que un objeto se vea tiene que estar delante del plano PP y detrás de T y evidenetemente delante del CP. El vector VI no coicide con el eje Y. CP es desde donde miramos, nuestro punto de fuga.

Con **Parapela** y no perspectiva: mismos parametros que antes pero ahora CP se cambia por DP, vector de dirección de proyección.

### Tipos de angulos y planos
  - **Tipos de ángulos**:
    - **Normal**: Aproximadamente 46o. Se corresponde con el ángulo de un ojo humano.
    - **Angular**: Cuando es mayor de 46o. Al abarcar más campo de visión, los objetos parecen más pequeños. Para sacarlos al mismo tamaño nos tenemos que acercar a ellos obteniendo grandes distorsiones.
    - **Tele**: Cuando es menor de 46o. Los objetos parecen más grandes. Para sacarlos al mismo tamaño nos tenemos que alejar comprimiendo los planos.
  - **Tipos de planos**:
    - **Frontal**: Proporciona una visión neutra y objetiva de la escena.
    - **Picado**: Hace que los personajes parezcan pequeños y débiles (cámara a 45o).
    - **Contrapicado**: Hace que los personajes parezcan grandes y heroicos (cámara a -45o).
    - **Subjetivo**: Sitúa la cámara en el punto de vista de un personaje.
    - **Cenital**: Cámara a 90o.
    - **Supina**: Cámara a -90o

### Proceso Transformación de vista en 3D
Los pasos son, partiendo de una escena con un objeto y los datos: PM, PO, VI y los vectores X0, Y0 y Z0:
  1. Inversión del eje Z0
  2. Traslación al origen del sistema de coordenadas del observador al origen del sistema de coordenadas mundial.
  3. Rotación del eje Z0 con respecto a X
  4. Rotación del eje Z0 con respecto a Y
  5. Rotación del eje Y0 con respecto a Z

### Rasterización
También llamado discretización. Los elementos geométricos son continuos, pero si los queremos visualizar en un dispositivo raster se tienen que representar por puntos discretos que corresponderán a pixeles.

Esto es que aparentemente los objetos vectoriales habrá que asignarle, para poder verlos por pantalla una serie de pixeles.

### ¿Que es el z-buffer?
Es un algoritmo para la eliminación de caras ocultas, el máx extendido. Puede ser facilemnte implementado por hardware, necesita almacenar los valores de profundidad de cada pixel de ahí su nombre.

Devuelve para cada pixel el color del ojeto más cerno al observador. Puede aplicarse a cualquier tipo de objeto. La profundida de los puntos de una cara se determina interpolando las coordenada z de los vértices.

      void Z-Buffer (...){
        int pz, y, x;
        for (y=0; y<YMAX; y++)
          for (x=0; x<XMAX; x++){
            put-pixel(x,y,color_fondo);
            put_z_buffer(x,y,ZMAX);
          }
        for (cada polígono Q de la escena)
          for (cada pixel (x,y) de la rasterización de Q){
            pz= valor de z del polígono Q en el pixel (x,y);
            if (pz<=read_z_buffer(x,y)){
              put_pixel(x,y,color del polígono Q en el pixel (x,y));
              put_z_b(x,y,pz);
            }
          }
      }


### Modelos de iluminación local
Luz como partícula:
  - Explica la absorción y emisión de luz
  - Explica la reflexión especular. Los partículas luminosas son elásticas y en la reflexión se produce un choque elástico
  - Explica de forma incompleta la transmisión

Luz como onda:
  - Explica la transmisión, incluyendo que en medios con mayor índice de refracción la velocidad de la luz es menor
  - Explica las interferencias y la difracción

En general, un modelo de iluminación determina que intensidad luminosa ha de asignarse a cada punto de una superficie. Los modelos de iluminación local son llamados modelos empíricos locales. Empíricos porque están basados en la óptica geométrica y locales porque se considera que la única luz que puede iluminar una superficie procede de las fuentes de luz de la escena (luz directa). Los objetos no producen sombreas a otros objetos. Se usan las tres longitudes del modelo RGB. **El modelo más simple es el ambiental** que aproxima toda la iluminación indirecta. Asignar un valor constante de intensidad a cada punto de una cara

La iluminación tiene tres componentes en los modelos locales, que son:
  - Difusa
  - Especular
  - Ambiental

### Pasos para la iluminación.
  1. Definir las luces (características). Una luz es un objeto más de la escena.
  2. Habilitar la iluminación (glEnable (GL_LIGHTING)
  3. Usar normales a las caras o a los vértices según el modo de suavizado
  4. Definir los materiales de los objetos
  5. Cambiar el modelo de iluminación

### Texturas, que son.
Con las transformaciones de textura se añaden detalles a la superficie de los objetos sin aumentar su número de caras. Una textura se puede relacionar con los trampantojos en bellas artes, es decir, el pintar en superficie plana una representación tridimensional dotandola de aparentes detalles que sería muy costoso usando otras técnicas.

Los parámetros de para dar impresión a una textura son:
  - Coeficientes de reflexión (difusa y especular)
  - Perturvación del vector normal.
  - Transparencia

La asignación de texturas se puede hacer de 3 formas:
  1. **Manual**: para objetos muy simples se asigna una coordenada de textura a cada vértice
  2. **Procedural**: para objetos sencillos y objetos complejos donde no importe que se pueda deformar la textura
  3. **Asistida**: para objetos muy complejos. Se usan herramientas CAD

### Pasos para las texturas
  1. Cargar la imagen. OpenGL no dispone de funciones para ello. Habría que usar una librería externa que dejará los datos en la memoría de la gráfica.
  2. Habilitar uso de texturas. glEnable (GL_TEXTURE_2D)
  3. Especificar la imagen usada como textura de OpenGL. glTexImage2D()
  4. Indicar como la textura se aplica (filtros, repetición). glTexParameteri()
  5. Especificar las coordenadas de textura (texels) para los vértices de los objetos (explícita y procedural) glTexCoord2()

### La selección y sus tipos
La selección permite identificar interactivamente elementos del modelo geométrico, permite al usuario referenciar componentes de un modelo geométrico através de identificadores o etiquetas. Estas se asocian a distinto nivel pudiendo controlar diferentes ambitos en la selección: vertive, primitiva, objeto...

  - Intersección rayo escena
  - Identificando los objetos incluidos en un subvolumen de visión centrado en la posición dada (OpenGL)
  - Codificando el identificador de objeto como color y leyendo del frame buffer

### Pasos para una selección
  1. Indicar un “buffer de selección” contendrá el resultado de la selección, glSelectBuffer().
  2. Entrar en modo selección, glRenderMode(GL_SELECT).
  3. Inicializar la pila de nombres de los elementos a seleccionar. glInitNames() y glPushName().
  4. Definir el volumen de vista, de modo que haya una pequeña ventana de selección (mínimo un píxel):
    - Se tiene que calcular una matriz de proyección restringida a una pequeña región del viewport alrededor del cursor usado en la selección
    - En el modo de selección solo se hace el dibujado de la escena para esta pequeña región del viewport
    - Esta matriz de proyección se llama matriz de selección (picking)
    - En la selección se determina que elementos gráficos están más cerca del cursor
    - Se realiza la transformación de coordenadas de dispositivo (región del viewport) a coordenadas de vista (región de selección)
    - Se usa la función gluPickMatrix() para calcular la matriz de selección
  5. Dibujar la escena asignado nombres a los elementos que se quieran seleccionar.
  6. Salir del modo de selección y procesar el “buffer de selección”.

### Ray tracing
Es un algoritmo para calcular las direcciones de los rayos que se lanzan a la
escena.

Lo que conseguimos con este algoritmo es generar efectos como sombras, hacer objetos translucidos, endefinitiva superficies difusas y especulares, sombras arrojadas,
transmisión y reflexión.
