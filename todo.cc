#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
//clang-format off
int ID;

struct todo {
  int id;
  std::string task;
};
//clang-format off
void addtodo() {
  system("clear");
  std::cout << "\n\t┌────────────────────────────────────────────────────────────────────┐\n";
  std::cout << "  \t│                      TO-DO LIST APPLICATION                        │\n"; 
  std::cout << "  \t└────────────────────────────────────────────────────────────────────┘\n\n";
  
  todo todo;
  std::cout << "\n\tEnter new task: ";
  std::cin.ignore();
  std::getline(std::cin, todo.task);
  ID++;

  std::ofstream write;
  write.open("todo.txt", std::ios::app);
  write << "\n" << ID;
  write << "\n" << todo.task;
  write.close();

  write.open("id.txt");
  write << ID;
  write.close();

  char ch;
  std::cout << "\n\tDo you want to add more tasks? (y/n): ";
  std::cin >> ch;

  if (ch == 'y') {
    addtodo();
  } else {
    std::cout << "\n\tTask has been added successfully\n";
    return;
  }
}

void print(todo s) {
  std::cout << "\n\tID: " << s.id;
  std::cout << "\n\tTask: " << s.task << "\n";
}

void readData() {
  system("clear");
  std::cout << "\n\t┌────────────────────────────────────────────────────────────────────┐\n";
  std::cout << "  \t│                      TO-DO LIST APPLICATION                        │\n";
  std::cout << "  \t└────────────────────────────────────────────────────────────────────┘\n\n";
  
  todo todo;
  std::ifstream read;
  read.open("todo.txt");
  std::cout << "\n\t------------------ Your Current Tasks ------------------\n";

  while (read >> todo.id) {
    read.ignore();
    std::getline(read, todo.task);
    print(todo);
  }
  read.close();
}

int searchData() {
  system("clear");
  std::cout << "\n\t┌────────────────────────────────────────────────────────────────────┐\n";
  std::cout << "  \t│                      TO-DO LIST APPLICATION                        │\n";
  std::cout << "  \t└────────────────────────────────────────────────────────────────────┘\n\n";
  
  int id;
  std::cout << "\n\tEnter task ID: ";
  std::cin >> id;
  todo todo;
  std::ifstream read;
  read.open("todo.txt");

  while (read >> todo.id) {
    read.ignore();
    std::getline(read, todo.task);
    if (todo.id == id) {
      print(todo);
      return id;
    }
  }
  std::cout << "\n\tTask not found!\n";
  return -1;
}

void deleteData() {
  system("clear");
  std::cout << "\n\t┌────────────────────────────────────────────────────────────────────┐\n";
  std::cout << "  \t│                      TO-DO LIST APPLICATION                        │\n";
  std::cout << "  \t└────────────────────────────────────────────────────────────────────┘\n\n";
  
  int id = searchData();
  if (id == -1) return;
  
  std::cout << "\n\tDo you want to delete this task? (y/n): ";
  char choice;
  std::cin >> choice;
  if (choice == 'y') {
    todo todo;
    std::ofstream tempFile;
    tempFile.open("temp.txt");
    std::ifstream read;
    read.open("todo.txt");

    while (read >> todo.id) {
      read.ignore();
      std::getline(read, todo.task);
      if (todo.id != id) {
        tempFile << "\n" << todo.id;
        tempFile << "\n" << todo.task;
      }
    }
    read.close();
    tempFile.close();
    remove("todo.txt");
    rename("temp.txt", "todo.txt");
    std::cout << "\n\tTask deleted successfully\n";
  } else {
    std::cout << "\n\tTask not deleted\n";
  }
}

void updateData() {
  system("clear");
  std::cout << "\n\t┌────────────────────────────────────────────────────────────────────┐\n";
  std::cout << "\t  │                      TO-DO LIST APPLICATION                        │\n";
  std::cout << "\t  └────────────────────────────────────────────────────────────────────┘\n\n";
  
  int id = searchData();
  if (id == -1) return;
  
  std::cout << "\n\tDo you want to update this task? (y/n): ";
  char choice;
  std::cin >> choice;
  if (choice == 'y') {
    todo newData;
    std::cout << "\n\tEnter updated task: ";
    std::cin.ignore();
    std::getline(std::cin, newData.task);
    todo todo;
    std::ofstream tempFile;
    tempFile.open("temp.txt");
    std::ifstream read;
    read.open("todo.txt");

    while (read >> todo.id) {
      read.ignore();
      std::getline(read, todo.task);
      if (todo.id != id) {
        tempFile << "\n" << todo.id;
        tempFile << "\n" << todo.task;
      } else {
        tempFile << "\n" << todo.id;
        tempFile << "\n" << newData.task;
      }
    }
    read.close();
    tempFile.close();
    remove("todo.txt");
    rename("temp.txt", "todo.txt");
    std::cout << "\n\tTask updated successfully\n";
  } else {
    std::cout << "\n\tTask not updated\n";
  }
}

int main() {
  system("clear");
  std::cout << "\n\t┌────────────────────────────────────────────────────────────────────┐\n";
  std::cout << "\t  │                      TO-DO LIST APPLICATION                        │\n";
  std::cout << "\t  └────────────────────────────────────────────────────────────────────┘\n\n";
  
  std::ifstream read;
  read.open("id.txt");
  if (read >> ID) {
    // ID read successfully
  } else {
    ID = 0;
  }
  read.close();

  while (true) {
    std::cout << "\n\t1. Add Task";
    std::cout << "\n\t2. Display Tasks";
    std::cout << "\n\t3. Search Task"; 
    std::cout << "\n\t4. Delete Task";
    std::cout << "\n\t5. Update Task";
    std::cout << "\n\t6. Exit";

    int choice;
    std::cout << "\n\n\tEnter choice: ";
    std::cin >> choice;
    switch (choice) {
      case 1:
        addtodo();
        break;
      case 2:
        readData();
        break;
      case 3:
        searchData();
        break;
      case 4:
        deleteData();
        break;
      case 5:
        updateData();
        break;
      case 6:
        std::cout << "\n\tExiting...\n";
        return 0;
      default:
        std::cout << "\n\tInvalid choice. Please try again.\n";
    }
  }
}
