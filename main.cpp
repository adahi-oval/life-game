// Incluye las bibliotecas necesarias
#include <iostream>
#include <string>
#include "lattice.h"
#include "cell.h"

// Función para imprimir el uso del programa
void printUsage() {
  std::cout << "Uso: programa -size <M> <N> [-init <file>] -border <b>\n"
            << "Donde:\n"
            << "  <M>: Número de filas\n"
            << "  <N>: Número de columnas\n"
            << "  <file>: Nombre del archivo con los valores iniciales\n"
            << "  <b>: Tipo de borde (periodic, noBorder, abiertaFria o abiertaCaliente)\n";
}

int main(int argc, char *argv[]) {
  if (argc < 5 || argc > 6) { // Verificar el número de argumentos
    std::cerr << "Número incorrecto de argumentos.\n";
    printUsage();
    return 1;
  }

  std::string sizeFlag = "-size";
  std::string initFlag = "-init";
  std::string borderFlag = "-border";
  std::string sizeFile;
  std::string initFile;
  std::string borderType;

  bool hasSizeFlag = false;
  bool hasBorderFlag = false;

  //Lattice lattice(0,0); // Variable lattice declarada fuera de los bloques if

  // Parsear los argumentos de la línea de comandos
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == sizeFlag) {
      // Verificar que no se haya utilizado previamente el flag -size
      if (hasSizeFlag) {
        std::cerr << "Error: El flag -size ya ha sido especificado.\n";
        printUsage();
        return 1;
      }
      // Obtener el tamaño del tablero
      if (i + 2 < argc) {
        sizeFile = argv[i + 1];
        initFile = argv[i + 2];
        i += 2;
        hasSizeFlag = true;
      } else {
        std::cerr << "Error: Se esperaban dos argumentos después de -size.\n";
        printUsage();
        return 1;
      }
    } else if (arg == initFlag) {

      if (hasSizeFlag) {
        std::cerr << "Error: El flag -size ya ha sido especificado.\n";
        printUsage();
        return 1;
      }
      
      // Obtener el nombre del archivo de inicialización
      if (i + 1 < argc) {
        initFile = argv[i + 1];
        ++i;
      } else {
        std::cerr << "Error: Se esperaba un argumento después de -init.\n";
        printUsage();
        return 1;
      }
    } else if (arg == borderFlag) {
      // Verificar que no se haya utilizado previamente el flag -border
      if (hasBorderFlag) {
        std::cerr << "Error: El flag -border ya ha sido especificado.\n";
        printUsage();
        return 1;
      }
      // Obtener el tipo de borde
      if (i + 1 < argc) {
        borderType = argv[i + 1];
        if (borderType != "periodic" && borderType != "noBorder" && borderType != "abiertaFria" && borderType != "abiertaCaliente") // Utiliza && en lugar de ||
        {
          std::cerr << "Error: Tipo de borde no válido.\n";
          printUsage();
          return 1;
        }
        ++i;
        hasBorderFlag = true;
      } else {
        std::cerr << "Error: Se esperaba un argumento después de -border.\n";
        printUsage();
        return 1;
      }
    } else {
      std::cerr << "Error: Argumento desconocido '" << arg << "'.\n";
      printUsage();
      return 1;
    }
  }
  /*
  if (hasSizeFlag) // si se ejecuta con size, initFile es las columnas
  {
    std::cout << sizeFile << std::endl << initFile << std::endl;
    lattice = Lattice(std::stoi(sizeFile), std::stoi(initFile)); // Asigna el valor de lattice aquí
  } else // si se ejecuta con init, initFile es el filename
  {
    lattice = Lattice(initFile.c_str()); // Asigna el valor de lattice aquí
  }
  */
  // Lattice lattice(std::stoi(sizeFile),std::stoi(initFile));
  Lattice lattice(initFile.c_str());
  lattice.setFrontera(borderType);
  char stopChar;
  std::string targetFile;
  std::cout << lattice << std:: endl;
  do
  { 
    std::cout << "Presiona 'x' para salir, o cualquiera de estas otras teclas para seleccionar opción: " << std::endl;
    std::cout << "'n' - Siguiente generación" << std::endl;
    std::cout << "'L' - Siguientes cinco generaciones" << std::endl;
    std::cout << "'c' - Modo población" << std::endl;
    std::cout << "'s' - Guarde el tablero actual a un fichero" << std::endl;
    std::cin >> stopChar;
    std::cout << std::endl;

    // Ejecutar opción
    if (stopChar == 'n')
    {
      lattice.nextGeneration();
    } else if (stopChar == 'L')
    {
      for (int i = 0; i < 5; i++)
      {
        lattice.nextGeneration();
      }
    } else if (stopChar == 's')
    {
      std::cout << "Escriba el nombre del archivo de salida:" << std::endl;
      std::cin >> targetFile;
      lattice.saveToFile(targetFile.c_str());
      std::cout << "Desea continuar?(s/n)" << std::endl;
      std::cin >> stopChar;
      if (stopChar == 's')
      {
        lattice.nextGeneration();
      } else
      {
        break;
      }
    } else if (stopChar == 'x')
    {
      break;
    } else if (stopChar == 'c')
    {
      lattice.setPopMode(true); // entra en popmode
    } else
    {
      std::cout << "Ingrese una opción válida: " << std::endl;
      std::cin >> stopChar;
    }
  } while (stopChar != 'x');
  

  return 0;
}
