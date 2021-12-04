# curses
## a c++ class based on curses
### 主要真针对linux terminal 的ui库curses进行了c++封装。
### 使用之前先安装curses库
### 编译时请添加链接：
### cmake中：
```cpp 
target_link_libraries(test "ncurses")
target_link_libraries(test "panel")
target_link_libraries(test "menu")
//target_link_libraries(test "form") 表单库没有添加
Example:
```
```cpp 
int main(int argc, char** argv)
{
    char data[256];
    BaseWindow base;
    Newwin inputbar(&base, 3,COLS,LINES - 3, 0);
    base.mcbreak();
    base.mecho();
    base.mbox(0,0);
    base.minit_pair(1,COLOR_YELLOW,COLOR_BLUE);
    base.mmvprintw(1,1,COLOR_PAIR(1),"Tony Terminal");
    base.mwrefresh();
    inputbar.mkeypad(true);
    inputbar.mbox(0,0);
    inputbar.mwrefresh();
    inputbar.mmove(1, 2);
    while(true)
    {
        inputbar.mgetstr(data);
        inputbar.mwclear();
        inputbar.mmove(1, 2);
        inputbar.mwrefresh();
        inputbar.getbasewin()->mmvprintw(2,1,"                                                                                                                                  ");
        inputbar.getbasewin()->mmvprintw(2,1,COLOR_PAIR(1),"input msg: %s",data);
        inputbar.getbasewin()->mwrefresh();
        inputbar.mbox(0,0);
        memset(data, 0, sizeof(data));
    }
    base.mwgetch();
    return 0;
 }
```
