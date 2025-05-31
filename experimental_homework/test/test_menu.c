#include "menu.h"
#include "status.h"
#include <stdio.h>

// 测试用的菜单处理函数
Status test_handler(void *context)
{
    printf("测试选项被成功调用！\n");
    return STATUS_TRUE;
}

void test_menu1()
{
    // 初始化菜单选项
    MenuOption options[3];
    char *description1 = "选项1: 测试功能1";
    char *description2 = "选项2: 测试功能2";
    char *description3 = "选项3: 测试功能3";

    // 创建菜单选项
    MenuOption_create(&options[0], 1, description1, test_handler);
    MenuOption_create(&options[1], 2, description2, test_handler);
    MenuOption_create(&options[2], 3, description3, test_handler);

    // 创建菜单
    Menu menu;
    char *title = "测试菜单";
    Menu_Create(&menu, &title, options, 3, 3);

    // 显示菜单
    printf("----- 测试菜单显示 -----\n");
    Menu_Display(&menu);

    // 更新菜单选项
    printf("----- 测试更新菜单选项 -----\n");
    char *new_description1 = "新选项1: 功能A";
    char *new_description2 = "新选项2: 功能B";
    MenuOption new_options[2];
    MenuOption_create(&new_options[0], 1, new_description1, test_handler);
    MenuOption_create(&new_options[1], 2, new_description2, test_handler);
    Menu_UpdateOption(&menu, new_options, 2);
    Menu_Display(&menu);

    // 测试处理输入
    printf("----- 测试菜单输入处理 -----\n");
    char input1[] = "1";
    char input2[] = "3";   // 超出范围的选项
    char input3[] = "abc"; // 非法输入
    char input4[] = "";    // 空输入

    printf("输入: %s\n", input1);
    if (Menu_HandlerInput(menu, input1, NULL) == STATUS_TRUE)
    {
        printf("选项1处理成功！\n");
    }
    else
    {
        printf("选项1处理失败！\n");
    }

    printf("输入: %s\n", input2);
    if (Menu_HandlerInput(menu, input2, NULL) == STATUS_TRUE)
    {
        printf("选项3处理成功！\n");
    }
    else
    {
        printf("选项3处理失败！\n");
    }

    printf("输入: %s\n", input3);
    if (Menu_HandlerInput(menu, input3, NULL) == STATUS_TRUE)
    {
        printf("非法输入处理成功！\n");
    }
    else
    {
        printf("非法输入处理失败！\n");
    }

    printf("输入: %s\n", input4);
    if (Menu_HandlerInput(menu, input4, NULL) == STATUS_TRUE)
    {
        printf("空输入处理成功！\n");
    }
    else
    {
        printf("空输入处理失败！\n");
    }
}

int main()
{
    test_menu1();
    return 0;
}
