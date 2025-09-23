#include <iostream>
#include <cstring>     // Módulo para manejo de cadenas en C, incluye strlen()
#include <sys/wait.h>  // Incluye waitpid() para sincronización entre procesos
#include <sys/types.h> // Definiciones de tipos como pid_t
#include <unistd.h>    // Módulo para llamadas al sistema como fork() y execlp()

int main() {

    std::string comando; // variable para línea de comando introducida por usuario
    pid_t pid = 0;       // variable para almacenar el ID del proceso hijo
    int status = 0;      // almacena el estado de finalización del proceso hijo

    std::cout << "> ";   // imprime el indicador >
    // Bucle lectura órdenes hasta el fin del archivo (Ctrl+D o un error de lectura)
    while (std::getline(std::cin, comando))
    {
        pid = fork(); // Crea un nuevo proceso hijo
        if (pid < 0)
        { // Si fork() devuelve valor negativo, error al crear el hijo
            std::cerr << "Error en fork" << std::endl;
            return 127; // Termina con un código de error usando exit(127)
        }
        else if (pid == 0)
        { // Si pid es 0, se está ejecutando el proceso hijo
            /* El hijo intenta ejecutar el comando ingresado
            execlp busca el ejecutable en el path del sistema.
            Requiere cadenas en C (vectores de char terminados en valor 0 */
            execlp(comando.c_str(), comando.c_str(), nullptr);
            // Si execlp falla, muestra error
            std::cerr << "No se pudo ejecutar " << comando << std::endl;
            return 126; // Termina con un código de error usando exit(126)
        }
        else
        { // Si pid > 0, estamos ejecutando el proceso padre
            // El padre espera que el hijo termine con waitpid()
            if ((pid = waitpid(pid, &status, 0)) < 0)
            {
                // Si waitpid falla, muestra error
                std::cerr << "Error en waitpid" << std::endl;
                return 125; // Termina con un código de error usando exit(125)
            }
            std::cout << "> "; // Vuelve a mostrar el prompt solicitar otro comando
        }
    }
    return 0; // Termina con un código de éxito usando exit(0)
}
