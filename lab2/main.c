#include "ContactsLib.h"

int main()
{
    Contacts *C;
    C = (Contacts *) malloc(sizeof(Contacts));

//    addContact(C, "Bcanas", "123123123");
//    addContact(C, "Abanas", "321321321");
//    addContact(C, "Cerifraz", "228228228");

//    delContact(C, 1);
//    changeContact(C, 1, "Karkas", "909909909");


//    printSorted(C);
//    export(C, "contacts.save");
    import(C, "contacts.save");
    printContact(C);
//    printf("%s\n", getByName(C, "Kaasfs"));
    return 0;
}
