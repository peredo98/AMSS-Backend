# AMSS-Backend

## Descripción de Proyecto
Crear una base de datos que reciba la informacion biometrica de una persona y regrese su foto e informacion. Asi como su nombre, matricula, edad, y una pequeña descripción.

### Requerimientos Funcionales
- El sistema será capaz de guardar información biométrica, personal (nombre, matrícula, edad y descripción) y foto de un usuario.
- El sistema regresará la información personal y foto del usuario que tenga la mayor similitud a la persona que acaba de ingresar.
- El sistema deberá guardar los miles de perfiles mediante la agrupación de características físicas.
- El sistema deberá comparar el perfil biométrico del usuario que acaba de entrar con base en la agrupación de los perfiles.
- El sistema deberá ser capaz de hacer búsquedas filtradas tomando en cuenta un porcentaje de similitud.
- El sistema podrá agregar, editar o eliminar los perfiles.

### Requerimientos No Funcionales
- El sistema solo acpeta datos biometricos.
- El porcentaje de error en el sistema debe de ser menor o igual al 10%.
- El tiempo de respuesta del sistema debe de ser igual o menor a un segundo.
- La base de datos debe tener la capacidad de guardad 100,000 perfiles.
- La base de datos funcionará tanto en MongoDB como en Firebase.
- La API rest funcionará en C++.
- El sistema debera de ser accessado mediante peticiones HTTP.
- El sistema deberá restrigingir a un solo perfil por persona. Por lo tanto, no se deberá aceptar repetidos.
- El sistema debe contar con manuales de usuario estructurados adecuadamente.

## Instalar

## Pruebas
