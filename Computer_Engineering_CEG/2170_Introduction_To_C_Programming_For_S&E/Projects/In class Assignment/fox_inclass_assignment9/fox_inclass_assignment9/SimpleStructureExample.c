#include <stdio.h>
#include <string.h>
#include "example.h"

int main() {
  struct Employee employee1;

  employee1.id = 12345;
  strcpy( employee1.name, "Sally Smith");
  employee1.salary = 85755.50;

  printf( "ID: %d\n", employee1.id);
  printf( "Name: %s\n", employee1.name);
  printf( "Salary: $%0.2f\n", employee1.salary);
  return 0;
}

