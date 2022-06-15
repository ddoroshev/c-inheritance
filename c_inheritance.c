#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "object.h"

typedef struct Person Person;
typedef struct Bird Bird;

struct Person {
    OBJECT(Person)
    char *first_name;
    char *last_name;
};

void Person_Repr(Person *person, char *buf) {
    sprintf(buf, "<Person: first_name='%s' last_name='%s'>", person->first_name, person->last_name);
}

void Person_Str(Person *person, char *buf) {
    sprintf(buf, "%s %s", person->first_name, person->last_name);
}

Person *New_Person(char *first_name, char *last_name) {
    Person *person = malloc(sizeof(Person));
    INIT_OBJECT(person, Person);

    person->first_name = first_name;
    person->last_name = last_name;

    return person;
}


void Del_Person(Person *person) {
    free(person);
}

struct Bird {
    OBJECT(Bird)
    char *name;
    Person *owner;
};

void Bird_Repr(Bird *bird, char* buf) {
    char owner_repr[80];
    bird->owner->Repr(bird->owner, owner_repr);
    sprintf(buf, "<Bird: name='%s' owner=%s>", bird->name, owner_repr);
}

void Bird_Str(Bird *bird, char* buf) {
    sprintf(buf, "%s", bird->name);
}

Bird *New_Bird(char *name, Person *owner) {
    Bird *bird = malloc(sizeof(Bird));
    INIT_OBJECT(bird, Bird);

    bird->name = name;
    bird->owner = owner;
    return bird;
}

void Del_Bird(Bird *bird) {
    free(bird);
}

int main(void) {
    Person *person = New_Person("Oleg", "Olegov");
    Bird *bird = New_Bird("Kukushka", person);

    person->Print_Repr(person);
    bird->Print_Repr(bird);

    person->Print_Str(person);
    bird->Print_Str(bird);

    Del_Bird(bird);
    Del_Person(person);
}
