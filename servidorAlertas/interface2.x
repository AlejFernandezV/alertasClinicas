

/*Declaracion de datos a transferir entre el servidor de alertas y el servidor de notificaciones*/

/*Declaracion de constantes*/
const MAXNOM = 20;
const MAXAPEL = 20;


/*Declaracion de la estructura que permite almacenar los datos de una notificacion*/
struct paciente_SA_SN{
	int numeroHabitacion;
	char nombre[MAXNOM];
	char apellido[MAXAPEL];
	int edad;
};

struct indicadores_SA_SN{
	int frecuencia_cardiaca;
	int tension_arterial[2];
	int frecuencia_respiratoria;
	int saturacion_oxigeno;
	float temperatura;
};

struct alerta{
	char horaAlerta[50];
	char fechaAlerta[50];
	int puntuacion;
};

struct notificacion{
	char horaAlerta[50];
	char fechaAlerta[50];
	alerta vecUltimasAlertas[5];
	int cantidadAlertas;
	int puntuacion;
	indicadores_SA_SN objIndicadores;
	paciente_SA_SN objPaciente;
};

/*Definicion de las operaciones que se pueden realizar*/
program enviar_notificacion{
	version enviar_notificacion_1{
		bool enviarNotificacion(notificacion objNotificacion)=1;		
	}=2;
}=0x20000002;
