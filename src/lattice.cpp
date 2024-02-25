#include "lattice.h"
#include <fstream>

// Implementación del constructor de Lattice
Lattice::Lattice(int N, int M) {

  rows = N;
  cols = M;

  // Crear las células en memoria dinámica y establecer su estado inicial a "muerta" (false)
  for (int i = 0; i < N; ++i) {
    std::vector<Cell*> row;
    for (int j = 0; j < M; ++j) {
      row.push_back(new Cell(std::make_pair(i, j), false));
    }
    cells_.push_back(row);
  }

  // Solicitar por teclado las posiciones de las células vivas en la configuración inicial
  askForLiveCells();
}

// Constructor por archivo
Lattice::Lattice(const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
    return;
  }

  // Leer las dimensiones de la retícula del archivo
  file >> rows >> cols;
  // Reservar espacio para las células
  cells_.resize(rows, std::vector<Cell*>(cols));

  // Leer las cadenas de caracteres del archivo para inicializar las células
  for (int i = 0; i < rows; ++i) {
    std::string rowString;
    file >> rowString;
    for (int j = 0; j < cols; ++j) {
      // Crear una célula viva si el carácter es 'X', de lo contrario, crear una célula muerta
      bool isAlive = (rowString[j] == 'X');
      cells_[i][j] = new Cell(std::make_pair(i, j), isAlive);
    }
  }

  // Cerrar el archivo
  file.close();
}


// Destructor de Lattice
Lattice::~Lattice() {
  // Liberar la memoria de las células
  for (auto& row : cells_) {
    for (auto& cell : row) {
      delete cell;
    }
  }
}

// getter frontera
std::string Lattice::getFrontera() const {
    return frontera_;
}

// setter frontera
void Lattice::setFrontera(const std::string& frontera) {
    frontera_ = frontera;
}

// Método privado para solicitar por teclado las posiciones de las células vivas en la configuración inicial
void Lattice::askForLiveCells() {
  char choice = 's';
  std::cout << "Ingrese las posiciones de las células vivas (fila columna):" << std::endl;
  
  while (choice == 's') {
    int row, col;
    std::cout << "Fila: ";
    std::cin >> row;
    std::cout << "Columna: ";
    std::cin >> col;

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
      // Establecer el estado de la célula en vivo (true)
      cells_[row][col]->setState(true);
    } else {
      std::cout << "Posición inválida. Por favor, ingrese una posición dentro del retículo." << std::endl;
    }

    std::cout << "¿Desea añadir otra célula viva? (s/n): ";
    std::cin >> choice;
    if (choice == 's')
    {
      continue;
    } else if (choice == 'n')
    {
      break;
    } else
    {
      std::cout << "Opción inválida. Saliendo del ingreso de células vivas." << std::endl;
      break;
    }
  }
}

// Implementación del método para calcular la población actual (número de células vivas)
std::size_t Lattice::Population() const {
    std::size_t aliveCount = 0;
    for (const auto& row : cells_) {
        for (const auto& cell : row) {
            if (cell->getState()) { // Si el estado de la célula es verdadero (viva)
                ++aliveCount;
            }
        }
    }
    return aliveCount;
}

// Sobrecarga del operador [] para acceder a las células por su posición en el retículo
Cell& Lattice::operator[](const Position& pos) const {
    // Obtener las coordenadas de la posición
    int x = pos.first;
    int y = pos.second;

    // Verificar que las coordenadas estén dentro de los límites del retículo
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        // Devolver la referencia a la célula en la posición dada
        return *cells_[x][y];
    } else {
        // Si las coordenadas están fuera de los límites, lanzar una excepción o devolver una referencia nula
        // Aquí se elige lanzar una excepción
        throw std::out_of_range("Posición fuera de los límites del retículo.");
    }
}

// Condicion abierta, temp es si caliente o fria (true o false)
void Lattice::openFrontier(const bool temp) {
  // Añadir columnas a los lados con células en el estado dado
  for (int i = 0; i < rows; ++i) {
    // Izquierda
    cells_[i].insert(cells_[i].begin(), new Cell(std::make_pair(i, 0), temp));
    // Derecha
    cells_[i].push_back(new Cell(std::make_pair(i, cols), temp));
  }
  cols += 2; // Se añaden dos columnas nuevas

  // Añadir filas arriba y abajo con células en el estado dado
  // Fila arriba
  cells_.insert(cells_.begin(), std::vector<Cell*>(cols, new Cell(std::make_pair(0, 0), temp)));
  // Fila abajo
  cells_.push_back(std::vector<Cell*>(cols, new Cell(std::make_pair(rows, 0), temp)));
  rows += 2; // Se añaden dos filas nuevas

  // Ajustar las esquinas
  // Esquina superior izquierda
  cells_[0].insert(cells_[0].begin(), new Cell(std::make_pair(0, 0), temp));
  // Esquina superior derecha
  cells_[0].push_back(new Cell(std::make_pair(0, cols), temp));
  // Esquina inferior izquierda
  cells_[rows - 1].insert(cells_[rows - 1].begin(), new Cell(std::make_pair(rows, 0), temp));
  // Esquina inferior derecha
  cells_[rows - 1].push_back(new Cell(std::make_pair(rows, cols), temp));

  // Ajustar las posiciones de las células existentes
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells_[i][j]->setPosition(i, j);
    }
  }
}

// Condicion de frontera periodica
void Lattice::periodicFrontier() {
  // Expansión de la frontera periódica
  std::vector<std::vector<Cell*>> tempCells = cells_; // Variable temporal para almacenar las células originales

  // Expansión hacia los lados
  for (int i = 0; i < rows; ++i) {
    // Izquierda
    cells_[i].insert(cells_[i].begin(), tempCells[i][cols - 1]);
    // Derecha
    cells_[i].push_back(tempCells[i][0]);
  }
  cols += 2; // Se añaden dos columnas nuevas

  // Expansión hacia arriba y abajo
  // Expansión hacia arriba con una copia de la última fila
  cells_.insert(cells_.begin(), tempCells[rows - 1]);
  // Expansión hacia abajo con una copia de la primera fila
  cells_.push_back(tempCells[0]);
  ++rows; // Se añaden dos filas nuevas

  // Esquina superior izquierda
  cells_[0].insert(cells_[0].begin(), tempCells[rows - 1][cols - 1]);
  // Esquina superior derecha
  cells_[0].push_back(tempCells[rows - 1][0]);
  // Esquina inferior izquierda
  cells_[rows - 1].insert(cells_[rows - 1].begin(), tempCells[0][cols - 1]);
  // Esquina inferior derecha
  cells_[rows - 1].push_back(tempCells[0][0]);

  // Ajustar las posiciones de las células existentes
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells_[i][j]->setPosition(i, j);
    }
  }
}

// Expand lattice para sin frontera
void Lattice::noFrontier(int row, int col) {

  // Expandir el retículo creando una nueva fila o columna con células muertas en la dirección correspondiente
  
  // Esquinas
  if (row == 0 && col == 0) {
    // Esquina superior izquierda
    // Insertar una nueva fila en la parte superior
    for (int i = 0; i < cols; ++i) {
      cells_[0].insert(cells_[0].begin(), new Cell(std::make_pair(0, 0), false)); // Agregar al principio
    }
    ++rows;

    // Ajustar las posiciones de todas las células existentes en las filas
    for (int i = 1; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        cells_[i][j]->setPosition(i, j);
      }
    }

    // Insertar una nueva columna en el lado izquierdo
    for (int i = 0; i < rows; ++i) {
      cells_[i].insert(cells_[i].begin(), new Cell(std::make_pair(i, 0), false)); // Agregar al principio
    }
    ++cols;

    // Ajustar las posiciones de todas las células existentes en las columnas
    for (int i = 0; i < rows; ++i) {
      for (int j = 1; j < cols; ++j) {
        cells_[i][j]->setPosition(i, j);
      }
    }
  } else if (row == 0 && col == cols - 1) {
    // Esquina superior derecha
    // Insertar una nueva fila en la parte superior
    for (int i = 0; i < cols; ++i) {
      cells_[0].push_back(new Cell(std::make_pair(0, cols), false)); // Agregar al final
    }
    ++rows;

    // Ajustar las posiciones de todas las células existentes en las filas
    for (int i = 1; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        cells_[i][j]->setPosition(i, j);
      }
    }
  } else if (row == rows - 1 && col == 0) {
    // Esquina inferior izquierda
    // Insertar una nueva fila en la parte inferior
    cells_.push_back(std::vector<Cell*>(cols, new Cell(std::make_pair(rows, 0), false)));
    ++rows;

    // Insertar una nueva columna en el lado izquierdo
    for (int i = 0; i < rows; ++i) {
      cells_[i].insert(cells_[i].begin(), new Cell(std::make_pair(i, 0), false)); // Agregar al principio
    }
    ++cols;

    // Ajustar las posiciones de todas las células existentes en las columnas
    for (int i = 0; i < rows; ++i) {
      for (int j = 1; j < cols; ++j) {
        cells_[i][j]->setPosition(i, j);
      }
    }
  } else if (row == rows - 1 && col == cols - 1) {
    // Esquina inferior derecha
    // Insertar una nueva fila en la parte inferior
    cells_.push_back(std::vector<Cell*>(cols, new Cell(std::make_pair(rows, cols), false)));
    ++rows;
    ++cols;
  }
  else if (row == 0) {
    // Expansión hacia arriba
    // Insertar una nueva fila de células muertas en la parte superior
    cells_.insert(cells_.begin(), std::vector<Cell*>(cols, new Cell(std::make_pair(0, 0), false)));
    ++rows;

    // Ajustar las posiciones de todas las células existentes en las filas
    for (int i = 1; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        cells_[i][j]->setPosition(i, j);
      }
    }
  } else if (row == rows - 1) {
    // Expansión hacia abajo
    // Insertar una nueva fila de células muertas en la parte inferior
    cells_.push_back(std::vector<Cell*>(cols, new Cell(std::make_pair(rows, 0), false)));
    ++rows;
  } 
  else if (col == 0) {
    // Expansión hacia la izquierda
    // Insertar una nueva columna de células muertas en el lado izquierdo
    for (int i = 0; i < rows; ++i) {
      cells_[i].insert(cells_[i].begin(), new Cell(std::make_pair(i, 0), false)); // Agregar al principio
    }
    ++cols;

    // Ajustar las posiciones de todas las células existentes en las columnas
    for (int i = 0; i < rows; ++i) {
      for (int j = 1; j < cols; ++j) {
        cells_[i][j]->setPosition(i, j);
      }
    }
  } else if (col == cols - 1) {
    // Expansión hacia la derecha
    // Insertar una nueva columna de células muertas en el lado derecho
    for (int i = 0; i < rows; ++i) {
      cells_[i].push_back(new Cell(std::make_pair(i, cols), false)); // Agregar al final
    }
    ++cols;
  }
}

// Restaurar tamaño original, para print
void Lattice::removeBorders() {
  // Eliminar las columnas adicionales en los lados
  for (int i = 0; i < rows; ++i) {
    cells_[i].erase(cells_[i].begin()); // Eliminar la primera célula en la fila (lado izquierdo)
    cells_[i].pop_back(); // Eliminar la última célula en la fila (lado derecho)
  }
  cols -= 2; // Se eliminan dos columnas

  // Eliminar las filas adicionales arriba y abajo
  cells_.erase(cells_.begin()); // Eliminar la primera fila (arriba)
  cells_.pop_back(); // Eliminar la última fila (abajo)
  rows -= 2; // Se eliminan dos filas

  // Restaurar las posiciones de las células existentes
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells_[i][j]->setPosition(i, j);
    }
  }
}
