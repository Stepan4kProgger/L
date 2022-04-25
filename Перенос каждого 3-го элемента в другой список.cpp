int task(List2*& b, List2*& e) {
    cout << "--List2-before--\n";
    ViewList(1, b);

    List2* t = b, * t2 = t, * b2 = NULL, * e2 = NULL;
    bool first = true;
    if (!b->next || !b->next->next) return -1;
    t = b->next;
    while (t && t->next && t->next != e) {
        t = t->next;
        t2 = t;
        t->next->prev = t->prev;
        t->prev->next = t->next;
        t = t->next->next;
        t2->prev = NULL;
        if (first) {
            t2->next = NULL; //создание первого элемента списка
            b2 = e2 = t2;
            first = false;
        }
        else {
            t2->next = b2;
            b2->prev = t2;
            b2 = t2;
        }
    }
    if (t && t->next) {
        t2 = t->next;
        t->next = NULL;
        e = t;
        t2->prev = NULL;
        if (first) {
            t2->next = NULL; //создание первого элемента списка
            b2 = e2 = t2;
        }
        else {
            t2->next = b2;
            b2->prev = t2;
            b2 = t2;
        }
    }
    cout << "\n--Now-List2-is--\n";
    ViewList(1, b);
    cout << "\nEjected-Elements\n";
    ViewList(1, b2);
    Del_All(&b2);
    cout << endl;

    return 0;
}
