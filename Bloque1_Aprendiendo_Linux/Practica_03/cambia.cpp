#include <iostream>
#include <fstream>
#include <string>

/** @brief Cambia todas las ocurrencias de un carácter por otro carácter en un fichero
 *  @example ./cambia fichero c1 c2 
 */
int main(int argc, char *argv[]) {
    // 1. Validar el número de argumentos    
    if (argc != 4) {
        std::cerr << "Modo de uso: " << argv[0] << " <fichero> <caracter_original> <caracter_nuevo>" << std::endl;
        return 1; // Terminar con código de error
    }

    // 2. Asignar los argumentos a variables
    std::string nombreFichero = argv[1];
    char c1 = argv[2][0]; // El primer carácter del segundo argumento
    char c2 = argv[3][0]; // El primer carácter del tercer argumento

    // 3. Abrir el fichero en modo lectura y escritura
    std::fstream fichero(nombreFichero, std::ios::in | std::ios::out);

    // 4. Comprobar si el fichero se abrió correctamente
    if (!fichero.is_open()) {
        std::cerr << "Error: No se pudo abrir el fichero '" << nombreFichero << "'" << std::endl;
        return 1; // Terminar con código de error
    }

    // 5. Procesar el fichero
    char caracterActual;
    // Bucle que lee el fichero carácter a carácter hasta el final
    while (fichero.get(caracterActual)) {
        // Si el carácter leído es el que queremos reemplazar...
        if (caracterActual == c1) {
            // Retrocedemos el cursor de escritura una posición
            // para colocarnos justo donde estaba el carácter que acabamos de leer.
            fichero.seekp(-1, std::ios::cur);
            
            // Escribimos (reemplazamos) el nuevo carácter en esa posición.
            fichero.put(c2);

            // Es buena práctica asegurarse de que los punteros de lectura y escritura
            // estén sincronizados después de una escritura.
            fichero.seekg(fichero.tellp());
        }
    }

    // 6. Cerrar el fichero
    fichero.close();

    std::cout << "✅ Reemplazo completado con éxito en el fichero '" << nombreFichero << "'." << std::endl;

    return 0; // Terminar con éxito
}
