/*Declaracion de datos a transferir entre el cliente y el servidor de alertas*/

/*Declaracion de constantes*/
const MAXNOM = 20;
const MAXAPEL = 20;

/*Declaracion de la estructura que permite almacenar los datos de los pacientes */
struct sensores{
	int frecuencia_cardiaca;
	int tension_arterial[2];
	int frecuencia_respiratoria;
	int saturacion_oxigeno;
	float temperatura;
};

struct paciente_C_SA{
	int numeroHabitacion;
	char nombre[MAXNOM];
	char apellido[MAXAPEL];
	int edad;
	sensores valoresPaciente;
};

/*Definicion de las operaciones que se pueden realizar*/

program enviar_datos_pacientes{
	version enviar_datos_pacientes_1{
		bool enviarDatosPacientes(paciente_C_SA objPaciente)=1;	
	}=2;
}=0x20000001;


