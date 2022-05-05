#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
using namespace std;

struct info {
    int num;
    string name;
};

struct Tree {
    info info;
    Tree* left, * right;
};

void CreateLeaf(Tree** tree, info value) {
    if (*tree == NULL) {
        *tree = new Tree;
        (*tree)->info = value;
        (*tree)->left = (*tree)->right = NULL;
        return;
    }
    else {
        if ((*tree)->info.num == value.num) {
            cout << "Дерево не может содержать одинаковые элементы! Добавление пропущено\n";
            return;
        }
        else {
            if (value.num > (*tree)->info.num)
                CreateLeaf(&(*tree)->right, value);
            else
                CreateLeaf(&(*tree)->left, value);
        }
    }
}

void ShowTree(Tree* tree, int level) {
    if (tree) {
        ShowTree(tree->right, level + 1);
        for (int i = 0; i < level; i++)
            cout << "   ";
        cout << tree->info.num << " - " << tree->info.name << endl;
        ShowTree(tree->left, level + 1);
    }
}

Tree* TreeSearch(Tree* tree, int key, Tree* found) {
    if ((tree) && (found == NULL)) {
        if (tree->info.num != key) {
            TreeSearch(tree->right, key, found);
            TreeSearch(tree->left, key, found);
        }
        else found = tree;
    }
    return found;
}

void BalanceTree(Tree** root, info* arr, int left, int right) {
    if (right < left)
        *root = NULL;
    else {
        int m = (right + left) / 2;
        *root = new Tree;
        (*root)->info = arr[m];
        BalanceTree(&(*root)->left, arr, left, m - 1);
        BalanceTree(&(*root)->right, arr, m + 1, right);
    }
}

int DefineTreeSize(Tree* root) {
    if (root)
        return 1 + DefineTreeSize(root->right) + DefineTreeSize(root->left);
    return 0;
}

info* ConvertToArray(Tree* root) {
    static info* arr = new info[DefineTreeSize(root)];
    static int i = 0;
    if (root) {
        arr[i++] = root->info;
        ConvertToArray(root->left);
        ConvertToArray(root->right);
    }
    return arr;
}

void SortValues(info* arr, int count) {
    int min;
    info buff;
    for (int i = 0; i < count - 1; i++) {
        min = i;
        for (int j = i + 1; j < count; j++)
            if (arr[j].num < arr[min].num)
                min = j;
        buff = arr[i];
        arr[i] = arr[min];
        arr[min] = buff;
    }
}

Tree* DeleteFromTree(Tree* root, int key, bool no_check = true) {
    Tree* toDelete, * parent, * r, * parent_r;
    toDelete = root;
    parent = NULL;
    while (toDelete && toDelete->info.num != key) {
        parent = toDelete;
        if (toDelete->info.num > key) toDelete = toDelete->left;
        else toDelete = toDelete->right;
    }
    if (toDelete == NULL && no_check) {
        cout << "Данное значение не найдено\n";
        return root;
    }
    if (toDelete->right == NULL)
        r = toDelete->left;
    else {
        if (toDelete->left == NULL)
            r = toDelete->right;
        else {
            parent_r = toDelete;
            r = toDelete->left;
            while (r->right) {
                parent_r = r;
                r = r->right;
            }
            if (parent_r == toDelete)
                r->right = toDelete->right;
            else {
                r->right = toDelete->right;
                parent_r->right = r->left;
                r->left = parent_r;
            }
        }
    }
    if (toDelete == root)
        root = r;
    else {
        if (toDelete->info.num < parent->info.num)
            parent->left = r;
        else
            parent->right = r;
    }
    delete toDelete;
    return root;
}

void LeftRootRight(Tree* tree) {
    if (tree->left != NULL)
        LeftRootRight(tree->left);
    cout << tree->info.num + ", " + tree->info.name << endl;
    if (tree->right != NULL)
        LeftRootRight(tree->right);
}

void RootLeftRight(Tree* tree) {
    cout << tree->info.num + ", " + tree->info.name << endl;
    if (tree->left != NULL)
        RootLeftRight(tree->left);
    if (tree->right != NULL)
        RootLeftRight(tree->right);
}

void LeftRightRoot(Tree* tree) {
    if (tree->left != NULL)
        LeftRightRoot(tree->left);
    if (tree->right != NULL)
        LeftRightRoot(tree->right);
    cout << tree->info.num + ", " + tree->info.name << endl;
}

Tree* getParent(Tree* root, Tree* key) {
    if (root == NULL) return NULL;
    else if (root->right == key || root->left == key) return root;
    else if (root->info.num > key->info.num) return getParent(root->left, key);
    else return getParent(root->right, key);
}

Tree* DelIndivid(Tree* root, Tree* target) {
    Tree* parent = getParent(root, target);
    if (target->left)
        root = DeleteFromTree(root, target->left->info.num, false);
    if (target->right)
        root = DeleteFromTree(root, target->right->info.num, false);
    root = DeleteFromTree(root, target->info.num, false);
    if (parent)
        root = DeleteFromTree(root, parent->info.num, false);
    return root;
}

void DeleteTree(Tree* root) {
    if (root) {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
    }
}

void main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Tree* root = NULL;
    while (true) {
        int sw, key, count, deep;
        Tree* target = NULL, * found = NULL;
        info elem;
        system("cls");
        cout << "Выберите действие:\n\n"
            << "\t1 - Добавить элементы в дерево\n"
            << "\t2 - Отобразить дерево\n"
            << "\t3 - Найти элемент в дереве\n"
            << "\t4 - Балансировка дерева\n"
            << "\t5 - Удалить элемент из дерева\n"
            << "\t6 - Опциональное отображение дерева\n"
            << "\t7 - Удалить из левой ветви дерева узел с макс знач и все связные с ним узлы\n"
            << "\t0 - Выйти\n";
        cin >> sw;
        cout << endl;
        if (root == NULL && sw > 1 && sw < 8) {
            cout << "Перед работой необходимо сформировать дерево.\n";
            system("pause");
            continue;
        }
        switch (sw) {
        case 1:
            cout << "Введите количество элементов, которых вы хотите добавить\n";
            cin >> count;
            for (int i = 0; i < count; i++) {
                cout << "Введите числовое значение [" << i + 1 << "] элемента: ";
                cin >> elem.num;
                cout << "Теперь, введите его имя: ";
                cin.ignore(123, '\n');
                getline(cin, elem.name);
                CreateLeaf(&root, elem);
            }
            break;
        case 2:
            ShowTree(root, 0);
            break;
        case 3:
        {
            cout << "Введите числовое значение элементa, которое необходимо найти\n";
            cin >> key;
            Tree* found = NULL;
            found = TreeSearch(root, key, found);
            if (found)
                cout << '\"' << found->info.num << " - " << found->info.name << "\" обнаружен в дереве\n";
            else
                cout << "Элемент со значением " << key << " НЕ находится в дереве\n";
            break;
        }
        case 4:
        {
            Tree* newRoot = NULL;
            info* arr = ConvertToArray(root);
            SortValues(arr, DefineTreeSize(root));
            BalanceTree(&newRoot, arr, 0, DefineTreeSize(root) - 1);
            ShowTree(newRoot, 0);
            DeleteTree(newRoot);
            cout << "\nСбалансированное дерево (от корня к крайним элементам - от левого края окна к правой стороне)\n";
            break;
        }
        case 5:
        {
            cout << "Введите значение элемента для удаления: ";
            cin >> key;
            root = DeleteFromTree(root, key);
            break;
        }
        case 6:
            cout << "Каким образом отобразить дерево?\n 1 - Лево->Корень->Право\n 2 - Корень->Лево->Право\n 3 Лево->Право->Корень\n  ";
            cin >> sw;
            if(sw == 1)
                LeftRootRight(root);
            else if (sw == 2)
                RootLeftRight(root);
            else if (sw == 3)
                LeftRightRoot(root);
            break;
        case 7:
            cout << "Введите значение элемента для операции: ";
            cin >> key;
            
            target = TreeSearch(root, key, target);
            if (target == NULL) {
                cout << "Не удалось найти элемент\n";
                break;
            }
            root = DelIndivid(root, target);
            cout << "Операция произведена успешно\n";
            break;
        case 0:
            if (root)
                DeleteTree(root);
            return;
        }
        system("pause");
    }
}
