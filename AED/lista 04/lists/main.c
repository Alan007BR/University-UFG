#include "list.c"


int main(){

    int x;
    List *list;

    list = createNewList();

    for(int i = 0; i < 10; i++){
        addInListFInal(list, i);
    }

    print(list);

    freeList(list);
    return 0;
}