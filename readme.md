# DamasChinas
REGLAS:


Las mismas que un juego de damas chinas clasico, pero diferenciando en:

-Si tienes la opoortunidad de comerte una ficha oponente con una que ya seleccionaste, pero te mueves hacia otro lado sin comertela, tu ficha sera eliminada automaticamente.

-La reina solamente tiene el poder de, al llegar al otro extremo del tablero, poder moverse de reversa para comerse las fichas enemigas ahora por atras.

EXPLICACION DE LAS FUNCIONES:


--struct ficha guarda todos los datos necesarios para identificar una ficha, su posicion en x, en y, un id unico que lo diferencia de las demas, vida=1 si esta viva o vida=0 si ya se la comieron, la direccion es si va hacia abajo (dir=0) o si va hacia arriba (dir=1), un color (N para negras y B para blancas, y un apuntador a la siguiente ficha.

--struct Cuadro nos ayuda a saber si una ficha esta disponible diferenciando negras (Disponible=1), blancas (Disponible=2), o vacio (Disponible=0), una posicion x y y para represrntar las posiciones centrales de cada cuadro, y un entero Reina que sirve para saber si la ficha ya paso al lado contrario del tablero.

--struct tablero contiene un arreglo con la informacion de los cuadros y su capacidad.

--get_pos_arr recibe un tipo de ficha y el tablero, nos ayuda a identificar la pocision de una ficha en nuestro tablero, cosa que es util para funciones como comer ficha, o saber si hay amigas al rededor.

--isReina recibe un tipo de ficha y el tablero. Nos ayuda a clasificar una ficha como reina en su estructura si esta ya llego al lado contrario del tablero, pues nuestra funcion de reina lo que hace es que si llegaste al lado contrario solo cambia que puedes comer pero ahora de reversa.

--TableroDisplay, recibiendo como parametros un par de medidas que son la altura y el ancho de nuestro tablero, es la funcion que utilizamos para dibujar nuestros cuadros del tablero, asi como las lineas que delimitan un cuadro.

--addF recibe de parametros una ficha, posiciones en x y en y, id , una direccion y un color que es representado por un char, sirve para inicializar una ficha en su totalidad, agegandole valor a todos los atributos de su estructura (los de struct ficha) usando memoria dinamica.

--Crear_tab la usamos para reservar memoria dinamica y crear un tablero que contendra los datos de cada cuadro.

--new_cuadro recibe una posicion en x y una en y, reserva tambien memoria dinamica e inicializa un cuadro dandole valor a cada uno de sus atributos.

--Llenar_tab recibe como parametro un tablero, sirve para añadirle todos los cuadros a nuestro tablero, dejando su valor de disponible en 0 para todos y agragandole su posicion en x y en y dentro del tablero.

--Llenar_disponibles recibe como parametro el tablero y un tipo de fichas, la usamos para diferenciar las fichas negras y blancas dentro del tablero agregando el valor correcto de "Disponible" para cada una.

--Crear_fichas recibe como parametro un numero (1 para las negras y 2 para las blancas), que usando memoria dinamica crea las fichas, les agrega una posicion en x y en y, asi como su id unico, y usando estos datos obtenidos llamamos la funcion addF para crear las fichas, luego de eso retornamod la ficha.

--DibujarFichas recibe como parametro una ficha, su color y el tablero, es la funcion que se encarga de desplegar las fichas en la interfaz grafica, detecta si es una reina, y si ya se comieron la ficha la manda fuera del tablero para que ya no sea visible.

--DerectF recibe como parametros una posicion en x, una en y y (que son las posiciones donde se presiono el boton izquierdo del mouse), y un tipo de ficha (Blancas o Negras), y con estos datos es posible saber si el usuario esta presionando una ficha o no.

--MovBlancasSinComida recibe un tipo de ficha que es la seleccionada por el usuario, una direccion (1 a la derecha y 0 a la izquierda), y el tablero. Primero se obtiene la posicion del tablero donde se encuentra la ficha, y dependiendo su el movimiento sera a la derecha o izquierda, mueve la ficha en la interfaz grafica y cambia la disponibilidad de un cuadro dentro del tablero que antes creamos usando su posicion.

--MovBalncasConComida funciona de la misma manera que MovBlancasSinComida, pero ahora el movimiento que se hara en la interfaz grafica y el que se realizara en nuestro tablero implica el de dos fichas a la izquierda o derecha (segun la direccion), pues eso significa que ya se comio una ficha.

--MovNegrasSinComida y MovNegrasConComida funcionan igual que las funciones de las fichas blancas y reciben los mismos parametros.

--eliminarf recibe una ficha en especifico y el tablero, tomamos la posicion de dicha ficha dentro de nuestro tablero y cambiamos su disponibilidad a 0 (o sea que ya no hay nada), y cambia el atributo vida de la ficha a 0, con lo que se dejara de dibujar gracias a la funcion de 

--comerFNegraDerecha recibe las fichas del tipo que selecciono el usuario, las oponentes y el tablero, identificamos si que ficha habia cuando una ficha blanca hizo un movimiento de comida a la derecha, cambiamos su disponibilidad en el tablero y la eliminamos de la interfaz grafica.

--comerFNegraIzquierda funciona igual que comerFNegraDerecha recibiendo los mismos parametros, pero esta detecta la ficha negra a la que se comio una ficha blanca a la izquierda y la elimina.

--comerFBlancaDerecha funciona igual que comerFNegraDerecha, pero esta detecta una ficha blanca que sera comida al hacer un movimiento con nuestra ficha negra a la derecha.

--comerFBlancaIzquierda hace lo mismo que comerFBlancaDerecha, pero con un movimiento a la izquierda.

--colision es una funcion que recibe el tipo de fichas que fue seleccionada por el usuario, y el tablero. Detecta si se encuentra una ficha del oponente a nuestra izquierda o derecha, basandose en la direccion a la que va la ficha seleccionada, realizando una comparacion en las posiciones del tablero, tomando en cuenta si esa ficha es una reina que ahora viene de regreso o si tu ficha seleccionada es una reina. Toma en cuenta si estas en una orilla del tablero o en alguno de los extremos de arriba o abajo para solo realizar comparaciones cuendo es posible. Retorna 1 si hay una colision a la derecha, 2 si hay colision a la izquierda, 3 si hay colision a los dos lados, o 0 si no hay colision.

--comidaDisponible recibe el tipo de fichas seleccionadas por el usuario, y el tablero. Lo que hace es ver si tu ficha va hacia abajo, hacia arriba, es reina o no y nos dice si es posible comerse una ficha por la que le estaremos preguntando en una funcion que esta mas adelante, toma en cuenta si te estoba una ficha amiga o una oponente. Retorna 1 si la comida de la derecha esta tapada, 2 si la de la izquierda no se puede comer, 3 si ningun lado esta disponible para comer, y 0 si las dos se pueden comer. Claramente esta funcion esta ligada con colision para saber si esa colision se puede comer.

--isAmiga recibe el tipo de fichas seleccionadas por el usuario, y el tablero, lo que hace es verificar si tu ficha va hacia arriba o hacia abajo y si es reina o no, se obtiene su posicion en el arreglo y se hace una comparacion para saber si existe una amiga a nuestra derecha o izquierda. Retorna 1 si tienes una amiga a la derecha, 2 si la tienes a la derecha, 3 si tienes amigas a los dos lados, y 0 si no tienes amigas. Valida la posicion de nuestra fichas para solo hacer comparaciones validas.

--isAmigaLejana recibe el tipo de fichas seleccionadas por el usuario, y le tablero, al igual que la funciones anteriores detecta si tu direccion es hacia arriba o hacia abajo, y si eres una reina o no. hace una comparacion en las posiciones del arreglo, y si se encuentra una ficha donde pudiera moverse la nuestra para comer (o sea a dos posiciones) retorna 1 si hay una a la derecha, 2 si hay una a la izquierda, 3 si hay a los dos lados, o 0 si no tienes amigas lejanas. Tambien valida la posicon de nuestra ficha para solo realizar comparaciones validas.

--SinEnemigos recibe las posiciones x y y del mouse de nuestro usuario para, si no tenemos colisiones o amigas cercanas podamos validar que este pulso una posicion valida a la izquierda o derecha, y asi realizar el movimiento de su ficha. Retorna 1 si se pudo realizar un movimiento valido, 0 si no fue asi.

--EnemigoDerecha recibe las posiciones x y y del mouse del usuario, el tipo de fichas seleccionadas con anterioridad (la que se quiere mover), el tablero y las fichas oponentes.

--Lo que hace la funcion es validar que si se tiene un enemigo a la derecha, a este no le estorben otras fichas del oponente o una amiga lejana para poder comerselo, ademas de ver si hay una amiga del otro lado para poder hacer o no tambien un movimiento a la izquierda. Si tienes una oportunidad de comer a la derecha pero decides moverte hacien la izquierda porque nada te estorba tu ficha sera eliminada por no comerse una ficha que ya estaba a tu alcance. La funcion retorna 1 si se hizo un movimiento valido, 2 si solo se pudo mover sin comer a causa de su posicion en el tablero o si tu ficha fue eliminada, y 0 si no te comiste nada.

--EnemigoIzquierda recibe los mismos parametros que EnemigoDerecha, y retorno lo mismo en los mismos casos, pero aqui se valida que hay un enemigo a la izquierda de nuestra ficha. Estas funciones tambien tomas en cuenta si te encuentras hasta arriba, hasta abajo, a la derecha o a la izquerda del tablero para solo realizar comparaciones validas y no meternos en posiciones que no existen (nuestro muy temido segmentation fault).

--EnemigoSupremo realiza lo mismo que las dos funciones anteriores, pero sabiendo que se tiene enemigos a los dos lados de nuestra ficha.

--sinMovimiento recibe la posicion en x y y del mouse del usuario, la ficha seleccionada, el tablero y las fichas oponentes para, tomando en cuenta las funciones ya mencionadas, darnos cuenta de si una ficha ya no tiene mas comida disponible luego de haberse comido una ficha.

--MovimientoValido es la funcion en la que usamos las anteriores mencionadas, recibe las posiciones en x y y del mouse del usuario, la ficha seleccionada, las fichas oponentes y el tablero. Realizando comparaciones con lo que retornen nuestras funciones como colision, isAmiga, EnemigoDerecha, etc, podemos hacer el movimiento valido de fichas, y si se realizo un movimiento valido se retorna 1, numero que se utiliza para hacer posible el cambio de turno. Si no hubo movimientos validos se retorna 0.

--CirculosR toma como parametros la ficha seleccionada por el usuario, y le tablero, y haciendo uso de las funciones anteriores, podermos dibujar circulos rojos donde el usuario tenga opcion de mover su ficha.

--movimientosDisponibles recibe las fichas blancas y negras, y el tablero, haciendo uso de las fichas mencionadas anteriormente nos damos cuenta si una ficha ya no tiene un movimiento disponible, recorriendo todas las fichas guardamos el numero de fichas bloqueadas en un contador, y al final lo comparamos con otro contador que contiene el numero de fichas con vida. Si el total de fichas negras con vida estan bloqueadas, retornamos 2 (ganaron las blancas), si todas las blancas estan bloqueadas retornamos 1 (ganaron las negras), y si ninguna ha perdido retornamos 0.

--getWinner recibe tambien las fichas blancas, las fichas negras y el tablero, cuenta cuantas fichas aun tienen vida, y si todas las fichas negras estan muertas retornamos 2, si las fichas blancas estan muertas retornamos 1, y si no esta muerto el total de ninguna de las dos retornamos 0.

--menu no recibe ningun parametro, solo dibuja anuncios al inicio de una partida mostrando las opciones que se pueden realizar (juego nuevo, cargar juego).

--saveGame recibe como parametros las fichas blancas, las fichas negras, el turno y el tablero. Creamos varios arreglos donde guardamos todos los atributos de las estructuras de ficha de todas las fichas, ademas creamos un arreglo con el turno donde nos habiamos quedado, luego de eso fuimos guardando toda la informacion de las fichas una por una en el achivo.

--loadGame tambien recibe fichas blancas, negras , el turno y el tablero. Tambien se crea un arreglo donde se guardara toda la informacion de las fichas y el turno, luego de eso se lee una por una para poder añadirle la informacion a cada ficha del juego en el que se va a cargar.



