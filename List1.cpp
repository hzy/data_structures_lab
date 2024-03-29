/* Linear Table On Sequence Structure */
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;  //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

struct SqList {  //顺序表（顺序结构）的定义
  ElemType* elem;
  size_t length;
  size_t listSize;
};

/*-----page 19 on textbook ---------*/
status InitList(SqList&);
status DestroyList(SqList&);
status ClearList(SqList&);
bool ListEmpty(SqList);
size_t ListLength(SqList);
status GetElem(SqList, size_t i, ElemType& e);
size_t LocateElem(SqList, ElemType e);
status PriorElem(SqList, ElemType cur, ElemType& pre_e);
status NextElem(SqList, ElemType cur, ElemType& next_e);
status ListInsert(SqList&, size_t i, ElemType e);
status ListDelete(SqList&, size_t i, ElemType& e);
status ListTraverse(SqList);  //简化过
/*--------------------------------------------*/
int main(void) {
  int i = 0;
  vector<SqList> Lists = {SqList()};
  int op = 1;
  while (op) {
    system("cls");
    printf("\n\n");
    printf("Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("      1. InitList         7. LocateElem\n");
    printf("      2. DestroyList      8. PriorElem\n");
    printf("      3. ClearList        9. NextElem \n");
    printf("      4. ListEmpty       10. ListInsert\n");
    printf("      5. ListLength      11. ListDelete\n");
    printf("      6. GetElem         12. ListTraverse\n");
    printf("      0. Exit            13. ReadList\n");
    printf("                         14. WriteList\n");
    printf("                         15. AddList\n");
    printf("                         16. ChangeList\n");
    printf("                         17. CurrentList\n");
    printf("-------------------------------------------------\n");
    printf("请选择你的操作[0~17]:");
    scanf("%d", &op);
    switch (op) {
      case 1:
        //printf("\n----InitList功能待实现！\n");
        if (InitList(Lists[i]) == OK)
          printf("线性表创建成功！\n");
        else
          printf("线性表创建失败！\n");
        getchar();
        getchar();
        break;
      case 2:
        DestroyList(Lists[i]);
        getchar();
        getchar();
        break;
      case 3:
        ClearList(Lists[i]);
        getchar();
        getchar();
        break;
      case 4:
        printf("列表是否为空：%s", ListEmpty(Lists[i]) ? "是" : "否");
        getchar();
        getchar();
        break;
      case 5:
        printf("列表长度：%d", ListLength(Lists[i]));
        getchar();
        getchar();
        break;
      case 6: {
        if (ListEmpty(Lists[i])) {
          printf("列表为空！");
          getchar();
          getchar();
          break;
        }
        int __i;
        printf("输入 index：\n");
        scanf("%u", &__i);
        ElemType e;
        GetElem(Lists[i], __i, e);
        printf("值：%d", e);
        getchar();
        getchar();
        break;
      }
      case 7: {
        ElemType e;
        scanf("%d", &e);
        printf("值：%d", LocateElem(Lists[i], e));
        getchar();
        getchar();
        break;
      }
      case 8: {
        ElemType e;
        ElemType p_e;
        printf("输入值：");
        scanf("%d", &e);
        PriorElem(Lists[i], e, p_e);
        printf("前驱：%d", p_e);
        getchar();
        getchar();
        break;
      }
      case 9: {
        ElemType e;
        ElemType n_e;
        printf("输入值：");
        scanf("%d", &e);
        NextElem(Lists[i], e, n_e);
        printf("后继：%d", n_e);
        getchar();
        getchar();
        break;
      }
      case 10: {
        ElemType e;
        size_t __i;
        printf("先后输入 index 和 item：\n");
        while (scanf("%u", &__i) && scanf("%d", &e) && __i <= Lists[i].length - 1) {
          if (ListInsert(Lists[i], __i, e))
            printf("成功在%d插入%d\n", __i, e);
          printf("先后输入 index 和 item：\n");
        }
        getchar();
        getchar();
        break;
      }
      case 11: {
        size_t __i;
        printf("输入 index：\n");
        while (scanf("%u", &__i)) {
          ElemType e;
          if (ListDelete(Lists[i], __i, e))
            printf("删除的值为：%d\n", e);
          printf("输入 index：\n");
        }
        getchar();
        getchar();
        break;
      }
      case 12:
        if (!ListTraverse(Lists[i]))
          printf("线性表是空表！\n");
        getchar();
        getchar();
        break;
      case 13: {
        FILE* fp;
        char filename[30];
        printf("Input file name: ");
        scanf("%s", filename);

        Lists[i].length = 0;
        if ((fp = fopen(filename, "r")) == NULL) {
          printf("File open error\n");
          return 1;
        }
        while (fread(&Lists[i].elem[Lists[i].length], sizeof(ElemType), 1, fp))
          Lists[i].length++;
        break;
      }
      case 14: {
        FILE* fp;
        char filename[30];
        printf("Input file name: ");
        scanf("%s", filename);

        if ((fp = fopen(filename, "w")) == NULL) {
          printf("File open error\n");
          getchar();
          getchar();
          break;
        }
        fwrite(Lists[i].elem, sizeof(ElemType), Lists[i].length, fp);
        fclose(fp);
        getchar();
        getchar();
        break;
      }

      case 15: {
        SqList l;
        InitList(l);
        // l.elem = new int();
        Lists.push_back(l);
        printf("添加一张空表成功！\n");
        getchar();
        getchar();
        break;
      }
      case 16: {
        int __i;
        printf("输入表编号(0~%d):", Lists.size() - 1);
        while (!(scanf("%u", &__i) && (__i <= Lists.size() - 1))) {
          printf("输入表编号(0~%d):", Lists.size() - 1);
        }
        i = __i;
        printf("切换到表%d成功！\n", __i);
        getchar();
        getchar();
        break;
      }
      case 17: {
        printf("当前是表%d\n", i);

        getchar();
        getchar();
        break;
      }

      case 0:
        break;
    }
  }
  printf("欢迎下次再使用本系统！\n");
  getchar();
}  //end of main()

/*--------page 23 on textbook --------------------*/
status InitList(SqList& L) {
  L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L.elem)
    exit(OVERFLOW);
  L.length = 0;
  L.listSize = LIST_INIT_SIZE;
  return OK;
}
status ListTraverse(SqList L) {
  size_t i;
  printf("\n-----------all elements -----------------------\n");
  for (i = 0; i < L.length; i++)
    printf("%d ", L.elem[i]);
  printf("\n------------------ end ------------------------\n");
  return L.length;
}
status DestroyList(SqList& L) {
  free(L.elem);
  L.length = 0;
  return OK;
}
status ClearList(SqList& L) {
  free(L.elem);
  L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L.elem)
    exit(OVERFLOW);
  L.length = 0;
  return OK;
}
bool ListEmpty(SqList L) {
  if (L.elem != nullptr)
    return L.length == 0;
  else
    return false;
}
size_t ListLength(SqList L) {
  if (L.elem != nullptr)
    return L.length;
  return -1;
}
status GetElem(SqList L, size_t i, ElemType& e) {
  if (L.elem != nullptr)
    if (i >= 0 && i < ListLength(L)) {
      e = L.elem[i];
      return OK;
    }
  return ERROR;
}
size_t LocateElem(
    SqList L,
    ElemType e)
// std::function<bool(ElemType, ElemType)> compare =
// 	[](ElemType e1, ElemType e2) -> bool { return e1 == e2; })
{
  for (size_t i = 0; i < ListLength(L); i++) {
    ElemType _e;
    GetElem(L, i, _e);
    if (e == _e) {
      return i;
    }
  }
  return -1;
}
status PriorElem(SqList L, ElemType cur, ElemType& pre_e) {
  size_t l = LocateElem(L, cur);
  if (l != 0)
    return GetElem(L, l - 1, pre_e);
  return ERROR;
}
status NextElem(SqList L, ElemType cur, ElemType& next_e) {
  size_t l = LocateElem(L, cur);
  if (l != ListLength(L) - 1)
    return GetElem(L, l + 1, next_e);
  return ERROR;
}
status ListInsert(SqList& L, size_t i, ElemType e) {
  if (i < 0 || i >= L.length + 1) {
    return ERROR;
  }
  ElemType *p, *q;
  q = &(L.elem[i]);
  for (p = &(L.elem[L.length - 1]); p >= q; --p)
    *(p + 1) = *p;
  *q = e;
  ++L.length;
  return OK;
}

status ListDelete(SqList& L, size_t i, ElemType& e) {
  if (i < 0 || i >= L.length)
    return ERROR;

  int *p, *q;

  p = &(L.elem[i]);
  e = *p;
  q = L.elem + L.length - 1;
  for (++p; p <= q; ++p) {
    *(p - 1) = *p;
  }
  --L.length;
  return OK;
}