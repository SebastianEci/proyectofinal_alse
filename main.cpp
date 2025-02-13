#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

// Función para generar una marca de tiempo
std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Uso: ./aplicacion <path_base_datos>" << std::endl;
        return 1;
    }
    
    std::string dbPath = argv[1];
    
    // Apertura de la base de datos
    std::ofstream database(dbPath, std::ios::app);
    
    if (!database) {
        std::cout << "Error al abrir la base de datos." << std::endl;
        return 1;
    }
    
    float temperature = 0.0f;
    float humidity = 0.0f;
    float precipitation = 0.0f;
    float lightIntensity = 0.0f;
    
    // Ciclo principal para realizar las mediciones cada 5 segundos
    while (true) {
        // Simulación de obtención de valores de los sensores
        // Aquí puedes implementar la lógica real para leer los datos de los sensores
        temperature = -10.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (45.0f - (-10.0f))));
        humidity = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
        precipitation = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));
        lightIntensity = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2000.0f));
        
        // Cálculo del promedio cada minuto
        static int measurementCount = 0;
        static float temperatureSum = 0.0f;
        static float humiditySum = 0.0f;
        static float precipitationSum = 0.0f;
        static float lightIntensitySum = 0.0f;
        
        measurementCount++;
        temperatureSum += temperature;
        humiditySum += humidity;
        precipitationSum += precipitation;
        lightIntensitySum += lightIntensity;
        
        if (measurementCount == 12) { // 12 mediciones x 5 segundos = 1 minuto
            float temperatureAverage = temperatureSum / measurementCount;
            float humidityAverage = humiditySum / measurementCount;
            float precipitationAverage = precipitationSum / measurementCount;
            float lightIntensityAverage = lightIntensitySum / measurementCount;
            
            // Registro de los datos promedio en la base de datos
            database << "Promedio - Temperatura: " << temperatureAverage
                     << " - Humedad: " << humidityAverage
                     << " - Precipitación: " << precipitationAverage
                     << " - Intensidad de luz: " << lightIntensityAverage << std::endl;
            
            // Reiniciar los contadores y sumas
            measurementCount = 0;
            temperatureSum = 0.0f;
            humiditySum = 0.0f;
            precipitationSum = 0.0f;
            lightIntensitySum = 0.0f;
        }
        
        // Registro de la medición en la base de datos
        database << "Medición - Temperatura: " << temperature
                 << " - Humedad: " << humidity
                 << " - Precipitación: " << precipitation
                 << " - Intensidad de luz: " << lightIntensity << std::endl;
        
        // Registro de la fecha y hora de inicio de la ejecución
        if (measurementCount == 1) { // Solo registrar una vez por minuto
            database << "Inicio de ejecución - " << getCurrentTimestamp() << std::endl;
        }
        
        // Esperar 5 segundos antes de la próxima medición
        // Ten en cuenta que esta no es una forma precisa de lograr el intervalo de tiempo deseado
        // y podrías necesitar una lógica más precisa dependiendo del sistema operativo y otras consideraciones.
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    
    // Cierre de la base de datos
    database.close();
    
    return 0;
}
