#include "interactor.h"
#include "status.h"
#include "avl_tree.h"
#include "linked_list.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void clearScreen() {
#ifdef _WIN32
    system("cls"); // Windows 平台
#else
    system("clear"); // Linux/Unix 平台
#endif
}

// 判断字符串是否为数字
Status Interactor_IsNumber(const char *str) {
    if (str == NULL || *str == '\0') {
        return STATUS_FALSE; // 空字符串或 NULL 非法
    }
    while (*str) {
        if (!isdigit(*str)) {
            return STATUS_FALSE; // 非数字字符
        }
        str++;
    }
    return STATUS_TRUE;
}

Status Helper_CharInputAndOutputInt(int *output) {
    char input_num[MAX_INPUT];
    if (fgets(input_num, sizeof(input_num), stdin) != NULL) {
        // 去掉换行符
        input_num[strcspn(input_num, "\n")] = '\0';
    }
    // 检查输入是否为纯数字
    if (Interactor_IsNumber(input_num) == STATUS_FALSE) {
        return STATUS_OVERFLOW; // 输入中有非数字字符
    }
        if (strlen(input_num) > 5) {
        return STATUS_OVERFLOW; // 输入超过范围
    }
    // 将输入字符串转换为数字
    int number = strtol(input_num, NULL, 10);
    *output = number;
    return STATUS_TRUE;
}


Status HandlerContext_Init(HandlerContext *handler_context, Menu *now_menu, Menu *top_menu, Menu *tree_menu, Menu *control_tree_menu, Menu *more_menu, LinkedList *avl_list, int *now_avl) {
    if(!handler_context || !top_menu || !avl_list || !now_avl || !tree_menu || !control_tree_menu || !more_menu) {
        return STATUS_FALSE;
    }
    handler_context->top_menu = top_menu;
    handler_context->now_menu = now_menu;
    handler_context->tree_menu = tree_menu;
    handler_context->control_tree_menu = control_tree_menu;
    handler_context->more_menu = more_menu;
    handler_context->avl_list = avl_list;
    handler_context->now_avl = now_avl;
    return STATUS_TRUE;
}

void Test_MenuDisplay(Menu *top_menu, Menu *tree_menu, Menu *control_tree_menu, Menu *more_menu) {
    Menu_Display(top_menu);
    Menu_Display(tree_menu);
    Menu_Display(control_tree_menu);
}

Status top_menu_handler0(void *context) {
    exit(0);
}

Status top_menu_handler1(void *context) {
    HandlerContext *handler_context = (HandlerContext*)context;
    // AvlTree new_avl = NULL;
    // Status init_status = Avl_Init(&new_avl);
    // AvlTree *new_avl_posi = &new_avl;
    // Status output_status = List_Append(handler_context->avl_list, &new_avl);
    Status output_status = List_Append(handler_context->avl_list, NULL);
    if(output_status == STATUS_TRUE) {
        printf("创建成功\n");
        return output_status;
    }
    else {
        printf("创建失败\n");
        return output_status;
    }
}

Status top_menu_handler2(void *context) {
    HandlerContext *handler_context = (HandlerContext*)context;
    handler_context->now_menu = handler_context->tree_menu;
    return STATUS_TRUE;
}

Status top_menu_handler3(void *context) {
    printf("暂时不设计");
    getchar();
    clearScreen();
    return STATUS_TRUE;
}

Status control_tree_menu_handler0(void *context) {
    if(!context) {
        return STATUS_FALSE;
    }
    HandlerContext *handler_context = (HandlerContext*)context;
    handler_context->now_menu = handler_context->top_menu;
    return STATUS_TRUE;
}

Status control_tree_menu_handler1(void *context) {
    HandlerContext *handler_context = (HandlerContext*)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin)) {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    int insert_value = 0;
    if (Helper_CharInputAndOutputInt(&insert_value) != STATUS_TRUE) {
        printf("输入不是纯数字\n");
        return STATUS_OVERFLOW;
    }
    if (abs(insert_value) > 65533) {
        printf("输入数字绝对值过大\n");
        return STATUS_OVERFLOW;
    }
    AvlTree avl_tree = (AvlTree)get_avl_tree_origin;
    if (get_avl_tree_origin == NULL) {
        AvlTree purpose = NULL;
        Avl_Init(&purpose);
        avl_tree = purpose;
    }
    Avl_Insert(&avl_tree, insert_value);
    if (get_avl_tree_origin == NULL) {
        ListElementType curr = (ListElementType*)avl_tree;
        List_Change(handler_context->avl_list, *handler_context->now_avl, &curr);
    }
    return STATUS_TRUE;
}

Status control_tree_menu_handler2(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler3(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler4(void *context) {
    HandlerContext *handler_context = (HandlerContext*)context;
    ListElementType get_avl_tree_origin;
    if (STATUS_FALSE == List_Get(handler_context->avl_list, *handler_context->now_avl, &get_avl_tree_origin)) {
        control_tree_menu_handler0(context);
        *handler_context->now_avl = -1;
        return STATUS_FALSE;
    }
    AvlTree avl_tree = ((AvlTree)get_avl_tree_origin);
    Avl_PrintTree(avl_tree);
    return STATUS_TRUE;
}

Status control_tree_menu_handler5(void *context) {

    return STATUS_TRUE;
}

Status control_tree_menu_handler6(void *context) {

    return STATUS_TRUE;
}

Status tree_menu_handler0(void *context) {
    HandlerContext *handler_context = (HandlerContext*)context;
    handler_context->now_menu = handler_context->top_menu;
    return STATUS_TRUE;
}

Status tree_menu_handler1(void *context) {
    HandlerContext *handler_context = (HandlerContext*)context;
    printf("输入您要查看的二叉树对应的序号: ");
    int number = -1;
    if (Helper_CharInputAndOutputInt(&number) != STATUS_TRUE) {
        printf("输入不是纯数字\n");
        return STATUS_OVERFLOW;
    }
    if (number < 1 || number > List_Size(handler_context->avl_list)) {
        printf("输出超出范围");
        return STATUS_OVERFLOW; // 输入不合法
    }
    *handler_context->now_avl = number - 1;
    handler_context->now_menu = handler_context->control_tree_menu;
    return STATUS_TRUE;
}

Status tree_menu_handler2(void *context) {
    HandlerContext *handler_context = (HandlerContext*)context;
    printf("当前共有二叉树数量为 %d \n", List_Size(handler_context->avl_list));
    return STATUS_TRUE;
    return STATUS_TRUE;
}

Status Top_Menu_Init(Menu *top_menu, MenuOption *top_menu_option) {
    MenuOption_create(&top_menu_option[0], 0, "退出程序", top_menu_handler0);
    MenuOption_create(&top_menu_option[1], 1, "创建一棵新平衡二叉树", top_menu_handler1);
    MenuOption_create(&top_menu_option[2], 2, "选择二叉树进行调整", top_menu_handler2);
    MenuOption_create(&top_menu_option[3], 3, "更多功能", top_menu_handler3);
    char *top_menu_title = "顶级菜单展示";
    Menu_Create(top_menu, &top_menu_title, top_menu_option, TOP_MENU_COUNT, TOP_MENU_COUNT);
}

Status Control_Tree_Menu_Init(Menu *control_tree_menu, MenuOption *control_tree_menu_option) {
    MenuOption_create(&control_tree_menu_option[0], 0, "返回顶级目录", control_tree_menu_handler0);
    MenuOption_create(&control_tree_menu_option[1], 1, "插入数值", control_tree_menu_handler1);
    MenuOption_create(&control_tree_menu_option[2], 2, "删除数值", control_tree_menu_handler2);
    MenuOption_create(&control_tree_menu_option[3], 3, "查找数值", control_tree_menu_handler3);
    MenuOption_create(&control_tree_menu_option[4], 4, "打印二叉树", control_tree_menu_handler4);
    MenuOption_create(&control_tree_menu_option[5], 5, "中序遍历", control_tree_menu_handler5);
    MenuOption_create(&control_tree_menu_option[6], 6, "以某值为界限拆分二叉树", control_tree_menu_handler6);
    char *control_tree_menu_title = "单棵平衡二叉树调整菜单";
    Menu_Create(control_tree_menu, &control_tree_menu_title, control_tree_menu_option, CONTROL_TREE_MENU_COUNT, CONTROL_TREE_MENU_COUNT);
}

Status Tree_Menu_Init(Menu *tree_menu, MenuOption *tree_menu_option) {
    MenuOption_create(&tree_menu_option[0], 0, "返回顶级目录", tree_menu_handler0);
    MenuOption_create(&tree_menu_option[1], 1, "跳转到指定序号平衡二叉树调整菜单", tree_menu_handler1);
    MenuOption_create(&tree_menu_option[2], 2, "查看当前二叉树数量", tree_menu_handler2);
    char *tree_menu_title = "选择二叉树进行调整菜单";
    Menu_Create(tree_menu, &tree_menu_title, tree_menu_option, TREE_MENU_COUNT, TREE_MENU_COUNT);
};