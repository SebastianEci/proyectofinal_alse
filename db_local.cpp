include "db_local.h"

#include "conteomedidas.h"
#include <string>

using namespace std;

DB_Local::DB_Local( string url ){
    database.exec("CREATE TABLE IF NOT EXISTS mediciones ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "fecha_hora TEXT,"
                  "temperatura REAL,"
                  "humedad REAL,"
                  "precipitacion REAL,"
                  "intensidad_luz REAL"
                  ")");
  
}

bool DB_Local::Abrir_DB(){
  return true;
}

bool DB_Local::Ingresar( const conteomedidas  ){
  return true;

}

bool DB_Local::Recuperar( conteomedidas  ){
  return true;

}

bool DB_Local::Cerar_DB(){
  return true;

}
