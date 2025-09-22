#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <pwd.h>
#include <unistd.h>

const std::string nomFich = "/home/usuario/notas";   /* ruta del fichero de notas */

/** @brief Obtiene la nota del usuario que ejecuta el programa del fichero indicado
 *  @pre El fichero tiene líneas de la forma: usuario:nota:
 *  @pre Los valores decimales deben ir separados por un punto. e.g. 8.5
 *  @example ./consulta 
*/
int main(int argc, char *argv[]) {

  struct passwd *usuario = nullptr;

  std::string nombre; /* nombre del usuario que ejecutó el programa */
  std::string login;  /* nombre del usuario en cada línea del fichero de datos */
  float nota=0;       /* nota del usuario en cada línea del fichero de datos */

  std::ifstream fs;

  bool encontrado = false;  /* ¿ se encontró el usuario en el fichero ? */
  std::string linea;        /* línea actual procesada del fichero */
  
  usuario = getpwuid(getuid()); //obtenemos el uid del usuario que ejecuta el programa y recuperamos su información
  
  nombre=usuario->pw_name; // Nos interesa solo el login del usuario

  fs.open(nomFich);

  if ( !fs.good() ) {
    std::cerr << argv[0] << ": no se pudo abrir "<< nomFich << std::endl;
    return 1; //salida con código de error
  }
  
  std::stringstream ss;  // lo usaremos para trocear cada línea del fichero

  while ( !encontrado && std::getline(fs,linea) ) {
      ss.str(linea);      // cargamos la línea en el stringstream
      std::getline(ss,login,':');
      if ( nombre == login ) {        
        encontrado=true;
        ss >> nota;
      }
  }

  if (!encontrado)   
    std::cout << "No se encontro la nota de " << nombre << std::endl;
  else {
    std::cout << "la nota de " << nombre << " es " << nota << std::endl;
  }
  
  fs.close();

  return 0;
}

 

