/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "interface1.h"
#include "interface2.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

void formatearVectorAlertas(notificacion notificacion){
	for(int i=0; i<5; i++){
		notificacion.vecUltimasAlertas[i].puntuacion = -1;
	}
}

void guardarAlertaEnVector(alerta alerta, notificacion	notificacion){

	for(int i=0; i<5; i++){
		if(notificacion.vecUltimasAlertas[i].puntuacion == -1){
			alerta.puntuacion = notificacion.puntuacion;
			strcpy(alerta.fechaAlerta,notificacion.fechaAlerta);
			strcpy(alerta.horaAlerta,notificacion.horaAlerta);
			notificacion.vecUltimasAlertas[i] = alerta;
			break;
		}
	}
}

char *generarFechaAlerta(struct tm *fecha_hora) {
	// Asignamos la memoria para la cadena
	char *cadena = malloc(11 * sizeof(char));

	// Formateamos la fecha
	sprintf(cadena, "%04d/%02d/%02d", fecha_hora->tm_year + 1900, fecha_hora->tm_mon + 1, fecha_hora->tm_mday);

	// Devolvemos la cadena
	return cadena;
}

char * generarHoraAlerta(struct tm * fecha_hora){
	// Asignamos la memoria para la cadena
	char *cadena = malloc(6 * sizeof(char));

	// Formateamos la hora
	sprintf(cadena, "%02d:%02d", fecha_hora->tm_hour, fecha_hora->tm_min);

	// Devolvemos la cadena
	return cadena;
}

// Para las funciones de determinar el rango, retornarán 0 si hay anomalías en el valor del sensor
// Retornará 1 si todo esta correcto.

int determinarRangoNormalFrecuenciaCardiaca(paciente_C_SA *paciente, notificacion notificacion){
	
	int edad = paciente->edad;
	int latidoMinuto = paciente->valoresPaciente.frecuencia_cardiaca;

	if(edad < 1 && ((latidoMinuto < 120) || (latidoMinuto > 140))){ //Infante y RN
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 1 && edad < 2 && ((latidoMinuto < 100) || (latidoMinuto > 120))){ //Lactante mayor
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 2 && edad < 6 && ((latidoMinuto < 80) || (latidoMinuto > 120))){ //Pre-escolar
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 6 && edad < 13 && ((latidoMinuto < 80) || (latidoMinuto > 100))){ //Escolar
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 13 && edad < 16 && ((latidoMinuto < 70) || (latidoMinuto > 80))){ //Adolescente
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 16 && ((latidoMinuto < 60) || (latidoMinuto > 80))){ //Adulto
		notificacion.puntuacion += 1;
		return 0;
	}
	return 1;
}

int determinarRangoNormalTensionArterial(paciente_C_SA *paciente, notificacion notificacion){
	int edad = paciente->edad;
	//Posicion 0 vecTension Sistólica
	//Posicion 1 vecTension Diastólica
	int sistolica = paciente->valoresPaciente.tension_arterial[0];
	int diastolica = paciente->valoresPaciente.tension_arterial[1];
	
	if(edad < 1 && (((sistolica < 70) || (sistolica > 106)) && ((diastolica < 50) || (diastolica > 70)))){ //Infante y RN
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 1 && edad <= 2 && (((sistolica < 98) || ( sistolica > 106)) && ((diastolica < 58) || (diastolica > 70)))){ //Lactante mayor
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 2 && edad < 6  && (((sistolica < 99) || ( sistolica > 112)) && ((diastolica < 64) || (diastolica > 70)))){ //Pre-escolar
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 6 && edad < 13 && (((sistolica < 104) || ( sistolica > 124)) && ((diastolica < 64) || (diastolica > 86)))){ //Escolar
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 13 && edad < 16 && (((sistolica < 118) || ( sistolica > 132)) && ((diastolica < 70) || (diastolica > 82)))){ //Adolescente
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 16 && (((sistolica < 110) || ( sistolica > 140)) && ((diastolica < 70) || (diastolica > 90)))){ //Adulto
		notificacion.puntuacion += 1;
		return 0;
	}
	return 1;
}

int determinarRangoNormalFrecuenciaRespiratoria(paciente_C_SA *paciente, notificacion notificacion){
	int edad = paciente->edad;
	int ventilacionesMinuto = paciente->valoresPaciente.frecuencia_respiratoria;

	if(edad < 1 && ((ventilacionesMinuto < 20) || (ventilacionesMinuto > 45))){ //Infante y RN
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 1 && edad < 6 && ((ventilacionesMinuto < 20) || (ventilacionesMinuto > 30))){ //Lactante mayor y pre-escolar
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 6 && ((ventilacionesMinuto < 12) || (ventilacionesMinuto > 20))){ //Escolar, adolescente y adulto
		notificacion.puntuacion += 1;
		return 0;
	}
	return 1;
}

int determinarRangoNormalTemperatura(paciente_C_SA *paciente, notificacion notificacion){
	int edad = paciente->edad;
	float gradosC = paciente->valoresPaciente.temperatura;

	if(edad < 1 && ((gradosC < 37.5) || (gradosC > 37.8))){ //Infante y RN
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 1 && edad < 6 && ((gradosC < 37.5) || (gradosC > 37.8))){ //Lactante mayor
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 6 && edad < 13 && ((gradosC < 37.0) || (gradosC > 37.5))){ //Escolar
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 13 && edad < 16 && (gradosC != 37)){ //Adolescente
		notificacion.puntuacion += 1;
		return 0;
	}
	else if(edad >= 16 && ((gradosC < 36.2) || (gradosC > 37.2))){ //Adulto
		notificacion.puntuacion += 1;
		return 0;
	}
	return 1;
}

int determinarRangoNormalSaturacionOxigeno(paciente_C_SA *paciente, notificacion notificacion){
	if(paciente->valoresPaciente.saturacion_oxigeno < 90){
		notificacion.puntuacion += 1;
		return 0;
	}
	return 1;
}

void calcularPuntuacion(paciente_C_SA * paciente, notificacion notificacion){
	if(determinarRangoNormalFrecuenciaCardiaca(paciente, notificacion) == 1){
		notificacion.objIndicadores.frecuencia_cardiaca = -1;
	}
	if(determinarRangoNormalTensionArterial(paciente, notificacion) == 1){
		notificacion.objIndicadores.tension_arterial[0] = -1;
		notificacion.objIndicadores.tension_arterial[1] = -1;
	}
	if(determinarRangoNormalFrecuenciaRespiratoria(paciente, notificacion) == 1){
		notificacion.objIndicadores.frecuencia_respiratoria = -1;
	}
	if(determinarRangoNormalTemperatura(paciente, notificacion) == 1){
		notificacion.objIndicadores.temperatura = -1;
	}
	if(determinarRangoNormalSaturacionOxigeno(paciente, notificacion)== 1){
		notificacion.objIndicadores.saturacion_oxigeno = -1;
	}
}

void cambiarTipoPaciente(paciente_C_SA *pacienteLlegada, paciente_SA_SN pacienteNotificacion){
	pacienteNotificacion.numeroHabitacion = pacienteLlegada->numeroHabitacion;
	strcpy(pacienteNotificacion.nombre,pacienteLlegada->nombre);
	strcpy(pacienteNotificacion.apellido,pacienteLlegada->apellido);
	pacienteNotificacion.edad = pacienteLlegada->edad;
}

void cambiarTipoIndicadores(paciente_C_SA * paciente, indicadores_SA_SN indicadores){
	indicadores.frecuencia_cardiaca = paciente->valoresPaciente.frecuencia_cardiaca;
	indicadores.frecuencia_respiratoria = paciente->valoresPaciente.frecuencia_respiratoria;
	indicadores.saturacion_oxigeno = paciente->valoresPaciente.saturacion_oxigeno;
	indicadores.temperatura = paciente->valoresPaciente.temperatura;

	for(int i=0; i<2; i++){
		indicadores.tension_arterial[i] = paciente->valoresPaciente.tension_arterial[i];
	}
	
}

bool_t *
enviardatospacientes_2_svc(paciente_C_SA *argp, struct svc_req *rqstp)
{
	static bool_t  result;
	CLIENT *clnt;
	bool_t  *result_1;
	notificacion  objNotificacion;

	//Declaración de la variable de tiempo
	// Obtenemos el valor de tiempo Unix
	time_t tiempo_unix = time(NULL);
	// Convertimos el valor de tiempo Unix en una fecha y hora UTC
	struct tm *fecha_hora = gmtime(&tiempo_unix);

#ifndef	DEBUG
	clnt = clnt_create ("localhost", enviar_notificacion, enviar_notificacion_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror ("localhost");
		exit (1);
	}
#endif	/* DEBUG */
	objNotificacion.puntuacion = 0;
	printf("CLIENTE CONECTADO\n");

	//Formateo del vector de alertas dentro del objNotificacion
	formatearVectorAlertas(objNotificacion);

	//Almacena la información que llega del cliente en el nuevo tipo de indicadores
	cambiarTipoIndicadores(argp, objNotificacion.objIndicadores);

	//Verificacion de los valores de los sensores
	calcularPuntuacion(argp, objNotificacion);

	//Almacena la información que llegó del paciente en el nuevo tipo de paciente que manejan los servidores
	cambiarTipoPaciente(argp, objNotificacion.objPaciente);

	//Le da la fecha y la hora a la notificación
	strcpy(objNotificacion.fechaAlerta,generarFechaAlerta(fecha_hora));
	strcpy(objNotificacion.horaAlerta,generarHoraAlerta(fecha_hora));

	//Pendiente de guardar la información del paciente en un txt
	//TO DO
	

	//Verificación de la cantidad de puntuaciones para los sensores
	if(objNotificacion.puntuacion >= 2){
		printf("Alerta detectada!\n");
		printf("Enviando notificacion...\n");
		//Si la puntuacion es mayor a 2 se enviará una notificación
		result_1 = enviarnotificacion_2(&objNotificacion, clnt);
		if (result_1 == (bool_t *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	}
	
	//free(objNotificacion.fechaAlerta);
	//free(objNotificacion.horaAlerta);
	
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */

	return &result;
}
