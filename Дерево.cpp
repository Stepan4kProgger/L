#include <iostream>
#include <conio.h>
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;

struct Tree {
    int info;
    Tree* left, * right;
};

void CreateLeaf(Tree** tree, int value) {
    if (*tree == NULL) {
        *tree = new Tree;
        (*tree)->info = value;
        (*tree)->left = (*tree)->right = NULL;
        return;
    }
    else {
        if ((*tree)->info == value) {
            cout << "Дерево не может содержать одинаковые элементы\n";
            return;
        }
        else {
            if (value > (*tree)->info)
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
        cout << tree->info << '\n';
        ShowTree(tree->left, level + 1);
    }
}

int TreeSearch(Tree* tree, int key, int& found) {
    if ((tree) && (found == 0)) {
        if (tree->info != key) {
            TreeSearch(tree->right, key, found);
            TreeSearch(tree->left, key, found);
        }
        else found = 1;
    }
    return found;
}

void BalanceTree(Tree** root, int* arr, int left, int right) {
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

int* ConvertToArray(Tree* root) {
    static int* arr = new int[DefineTreeSize(root)];
    static int i = 0;
    if (root) {
        arr[i++] = root->info;
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

Tree* DeleteFromTree(Tree* root, int key) {
    Tree* toDelete, * parent, * r, * parent_r;
    toDelete = root;
    parent = NULL;
    while (toDelete && toDelete->info != key) {
        parent = toDelete;
        if (toDelete->info > key) toDelete = toDelete->left;
        else toDelete = toDelete->right;
    }
    if (toDelete == NULL) {
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
        if (toDelete->info < parent->info)
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
    cout << tree->info << " ";
    if (tree->right != NULL)
        LeftRootRight(tree->right);
}

void RootLeftRight(Tree* tree) {
    cout << tree->info << " ";
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
    cout << tree->info << " ";
}

void FindLevelCount(Tree* tree, int* mass, int level) {
    if (tree) {
        FindLevelCount(tree->left, mass, level + 1);
        FindLevelCount(tree->right, mass, level + 1);
        mass[level]++;
    }
}

int FindMaxDeepness(Tree* tree, int level) {
    if (tree != NULL) {
        int l, r;
        l = r = level;
        if (tree->left != NULL)
            l = FindMaxDeepness(tree->left, level + 1);
        if (tree->right != NULL)
            r = FindMaxDeepness(tree->right, level + 1);
        if (l > r)
            return l;
        else
            return r;
    }
    return level;
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
    int choice, count, deep, found = 0;
    while (true) {
        system("cls");
        cout << "Выберите действие:\n\n"
            << "\t1 - Добавить элементы в дерево\n"
            << "\t2 - Отобразить дерево\n"
            << "\t3 - Найти элемент в дереве\n"
            << "\t4 - Балансировка дерева\n"
            << "\t5 - Удалить элемент из дерева\n"
            << "\t6 - Опциональное отображение дерева\n"
            << "\t7 - Количество узлов(негфнеывнфеыв)\n"
            << "\tESC - Выйти\n";
        cin >> choice;
        cout << endl;
        if (root == NULL && choice > 1 && choice < 8) {
            cout << "Перед работой, создайте дерево.\n";
            continue;
        }
        switch (choice) {
        default:
            cout << "Куда ты клацаешь, тут такого нет!";
            break;
        case 1:
            cout << "Введите количество элементов, которых вы хотите добавить\n";
            cin >> count;
            for (int i = 0; i < count; i++)
            {
                cout << "Введите значение [" << i + 1 << "] элемента: ";
                cin >> choice;
                CreateLeaf(&root, choice);
            }
            break;
        case 2:
            ShowTree(root, 0);
            break;
        case 3:
        {
            cout << "Введите элемент, который необходимо найти";
            cin >> choice;
            found = TreeSearch(root, choice, found);
            if (found == 1)
            {
                cout << choice << " обнаружен в дереве";
                found = 0;
            }
            else
                cout << choice << " НЕ находится в дереве";
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
            break;
        }
        case 5:
        {
            cout << "Введите элемент для удаления";
            cin >> choice;
            root = DeleteFromTree(root, choice);
            break;
        }
        case 6:
            cout << "Каким образом отобразить дерево?\n 1 - Лево->Корень->Право\n 2 - Корень->Лево->Право\n 3 Лево->Право->Корень\n  ";
            cin >> choice;
            switch (choice)
            {
            default:
                cout << "Выбрана ошибочная опция\n";
                break;
            case 1:
                LeftRootRight(root);
                break;
            case 2:
                RootLeftRight(root);
                break;
            case 3:
                LeftRightRoot(root);
                break;
            }
            break;
        case 7:
            deep = FindMaxDeepness(root, 0);
            int newarr[20];
            for (int i = 0; i < 20; i++)
                newarr[i] = 0;
            FindLevelCount(root, newarr, 0);
            for (int i = 0; i <= deep; i++)
                cout << i + 1 << " уровень. " << newarr[i] << '\n';
            break;
        case 8:
            if (root != NULL)
                DeleteTree(root);
            return;
        }
        system("pause");
    }
}
