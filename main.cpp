#include <iostream>
#include <fstream>
#include <string>
#include "lattice.h"

int main(int argc, char* argv[]) {
  // Variables para almacenar los argumentos de línea de comandos
  int size = 0;
  std::string borderType;
  std::string initFile = "";

  // Procesar los argumentos de línea de comandos
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-size") {
      if (i + 1 < argc) {
        size = std::stoi(argv[++i]);
      } else {
        std::cerr << "Error: Se espera un valor después de -size." << std::endl;
        return 1;
      }
    } 
    
    else if (arg == "-border") {
      if (i + 1 < argc) {
        borderType = argv[++i];

        if (borderType == "open") {
          if (i + 1 < argc) {
            std::string v = argv[++i];
            if (v != "0" && v != "1") {
              std::cerr << "Error: Valor inválido para -v. Debe ser 0 o 1." << std::endl;
              return 1;
            }
            if(v == "0") { borderType = "abiertaFria"; }
            else if(v == "1") { borderType = "abiertaCaliente"; }
          } else {
            std::cerr << "Error: Se espera un valor después de -border open." << std::endl;
            return 1;
          }
        } else if (borderType == "periodic") {
          borderType = "periodic";
        }
      } else {
        std::cerr << "Error: Se espera un tipo de frontera después de -border." << std::endl;
        return 1;
      }
    } else if (arg == "-init") {
      if (i + 1 < argc) {
        initFile = argv[++i];
      } else {
        std::cerr << "Error: Se espera un nombre de archivo después de -init." << std::endl;
        return 1;
      }
    }
  }

  // Verificar que se especificó el tamaño y el tipo de frontera
  if (size == 0 || borderType.empty()) {
    std::cerr << "Error: Debes especificar el tamaño y el tipo de frontera." << std::endl;
    return 1;
  }

  // Crear el retículo del autómata celular
  Lattice lattice(size, borderType);
  std::vector<char> initialConfig;

  // Cargar la configuración inicial si se proporciona un archivo
  if (!initFile.empty()) {
    std::ifstream file(initFile);
    if (file.is_open()) {
      std::string line;
      if (std::getline(file, line)) {
        for (char c : line){
          if (c == '0' || c == '1')
          {
            initialConfig.push_back(c);
          }
          
        }
      } else {
        std::cerr << "Error: El archivo de inicialización está vacío." << std::endl;
        return 1;
      }
    } else {
      std::cerr << "Error: No se pudo abrir el archivo de inicialización." << std::endl;
      return 1;
    }
  } else {
    // Usar la configuración inicial por defecto
    lattice.loadInitialConfiguration(initialConfig);
  }

  // Simular la evolución del autómata celular
  char stopChar;
  do {
    std::cout << lattice << std::endl; // Mostrar la configuración actual
    lattice.nextGeneration(); // Pasar a la siguiente generación
    
    std::cout << "Presiona 'q' para salir o cualquier otra tecla para continuar: ";
    std::cin >> stopChar;
  } while (stopChar != 'q');

  return 0;
}
