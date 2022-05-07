#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

struct Tree {
    int key;
    Tree* left, * right;
};

void CreateLeaf(Tree** tree, int value) {
    if (*tree == NULL) {
        *tree = new Tree;
        (*tree)->key = value;
        (*tree)->left = (*tree)->right = NULL;
        return;
    }
    else {
        if ((*tree)->key == value) {
            cout << "Дерево не может содержать одинаковые элементы! Добавление пропущено\n";
            return;
        }
        else {
            if (value > (*tree)->key)
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
        cout << tree->key << endl;
        ShowTree(tree->left, level + 1);
    }
}

bool TreeSearch(Tree* tree, int key, bool& found) {
    if ((tree) && (found == 0)) {
        if (tree->key != key) {
            TreeSearch(tree->right, key, found);
            TreeSearch(tree->left, key, found);
        }
        else {
            found = 1;
        }
    }
    return found;
}


void BalanceTree(Tree** root, int* arr, int left, int right) {
    if (right < left)
        *root = NULL;
    else {
        int m = (right + left) / 2;
        *root = new Tree;
        (*root)->key = arr[m];
        BalanceTree(&(*root)->left, arr, left, m - 1);
        BalanceTree(&(*root)->right, arr, m + 1, right);
    }
}

int DefineTreeSize(Tree* root) {
    if (root)
        return 1 + DefineTreeSize(root->right) + DefineTreeSize(root->left);
    return 0;
}

int* ConvertToArray(Tree* root) {
    static int* arr = new int[DefineTreeSize(root)];
    static int i = 0;
    if (root) {
        arr[i++] = root->key;
        ConvertToArray(root->left);
        ConvertToArray(root->right);
    }
    return arr;
}

void SortValues(int* arr, int count) {
    int min, buff;
    for (int i = 0; i < count - 1; i++) {
        min = i;
        for (int j = i + 1; j < count; j++)
            if (arr[j] < arr[min])
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
    while (toDelete && toDelete->key != key) {
        parent = toDelete;
        if (toDelete->key > key) toDelete = toDelete->left;
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
        if (toDelete->key < parent->key)
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
    cout << tree->key << endl;
    if (tree->right != NULL)
        LeftRootRight(tree->right);
}

void RootLeftRight(Tree* tree) {
    cout << tree->key << endl;
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
    cout << tree->key << endl;
}

Tree* getParent(Tree* root, int key) {
    if (root == NULL) return NULL;
    else if (root->right->key == key || root->left->key == key) return root;
    else if (root->key > key) return getParent(root->left, key);
    else return getParent(root->right, key);
}

int findMax(Tree* root) {
    if (root == NULL)
        return INT_MIN;
    int res = root->key;
    int left = findMax(root->left);
    int right = findMax(root->right);
    if (left > res)
        res = left;
    if (right > res)
        res = right;
    return res;
}

Tree* DelIndivid(Tree* root, int target) {
    Tree* parent = getParent(root, target), * maxel;
    int val[4];
    val[0] = parent->key;
    val[1] = target;
    if (parent->left && parent->left->key == target)
        maxel = parent->left;
    else maxel = parent->right;
    if (maxel->left)
        val[2] = maxel->left->key;
    if (maxel->right)
        val[3] = maxel->right->key;
    for (int i = 0; i < 4; i++) {
        if (val[i] == INT_MIN) continue;
        root = DeleteFromTree(root, val[i], false);
    }
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
    SetConsoleOutputCP(1251);
    Tree* root = NULL;
    while (true) {
        int sw, key, count, max, elem;
        bool found = false;
        Tree* target = NULL;
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
        system("cls");
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
                cin >> elem;
                CreateLeaf(&root, elem);
            }
            cout << "Добавление завершено\n";
            break;
        case 2:
            ShowTree(root, 0);
            cout << "\nДерево (от корня к крайним элементам - от левого края окна к правой стороне)\n";
            break;
        case 3:
        {
            cout << "Введите числовое значение элементa, которое необходимо найти\n";
            cin >> key;
            
            if (TreeSearch(root, key, found))
                cout << '\"' << key << "\" обнаружен в дереве\n";
            else
                cout << "Элемент со значением " << key << " НЕ находится в дереве\n";
            break;
        }
        case 4:
        {
            Tree* newRoot = NULL;
            int* arr = ConvertToArray(root);
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
            max = findMax(root->left);
            if (TreeSearch(root->left, max, found)) {
                cout << "Не удалось найти элемент\n";
                break;
            }
            root = DelIndivid(root, max);
            cout << "Операция произведена успешно\n";
            break;
        case 0:
            if (root)
                DeleteTree(root);
            return;
        }
        cout << endl;
        system("pause");
    }
}
