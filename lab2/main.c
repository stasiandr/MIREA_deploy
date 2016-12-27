#include "ContactsLib.h"
#include <string.h>

int main()
{
    Contacts *C;
    C = (Contacts *) malloc(sizeof(Contacts));

    printf("Welcome home, nigga! What do ya need? If ya need help, type \"help\"\n");

    char input[20];
    char buff[20];
    int id;

    while(1)
    {
        scanf("%s", &input);
        if (!strcmp(input, "help"))
        {
            printf("Anytime, ma nigga\nType add to add dealer phone number\nType change if dealers number changed\nType delete if dealer has been busted\nType search if ya need to find contact\nType print if ya wanna to see your dealers list\nType save if ya need to conceal from police your list\nType load if smb gave ya his dealers contacts\nType close if ya wanna stop this sh**\n");
        }

        if (!strcmp(input, "add"))
        {
            printf("Enter name, nigga\n");
            scanf("%s", buff);
            printf("Mmm... Seams like I know that guy. He sells good stuff. Enter number too\n");
            scanf("%s", input);
            addContact(C, buff, input);
            printf("I've got it. Smth else?\n");
        }

        if (!strcmp(input, "delete"))
        {
            printf("So, who's done smth wrong to ya? A? Say his name, nigga\n");
            scanf("%s", input);
            id = getIdByName(C, input);
            if (id == -1)
            {
                printf("Maaan. Seams like I don't have it in ma list. Try smth else\n");
            }
            else
            {
                delContact(C, id);
                printf("Oh, you won't see that \"%s\" again. What's next?\n", input);
            }
        }

        if (!strcmp(input, "change"))
        {
            printf("Mmm... What's his name?\n");
            scanf("%s", input);
            id = getIdByName(C, input);
            printf("So enter new name for \"%s\"\n");
            scanf("%s", buff);
            printf("And number\n");
            scanf("%s", input);
            changeContact(C, id, buff, input);
        }

        if (!strcmp(input, "save"))
        {
            printf("F***, the police? Enter filename, and I'll conceal it as fast as i can\n");
            scanf("%s", input);
            export(C, input);
            printf("Huh, noone ever will find it, nigga\n");
        }

        if (!strcmp(input, "load"))
        {
            printf("Mmm, ma nigga brought wmth interesting. Let's see. Enter filename\n");
            scanf("%s", input);
            C = (Contacts *) malloc(sizeof(Contacts));
            import(C, input);
            printf("I've done it. What we'll do with such nice list?\n");
        }

        if (!strcmp(input, "print"))
        {
            printf("Yeah, I wanna see that, too\n");
            printSorted(C);
            printf("Reach list. What next we'll do?\n");
        }

        if (!strcmp(input, "close"))
        {
            printf("Good work, nigga. See ya next time\n");
            return 0;
        }
    }

    return 0;
}
