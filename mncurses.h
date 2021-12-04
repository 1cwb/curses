#pragma once
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <panel.h>
#include <menu.h>
#include <vector>


class Twindow
{
protected:
    void setWINDOWID(WINDOW* win)
    {
        mwind = win;
    }
public:
    Twindow():mwind(nullptr)
    {
    }
    ~Twindow()
    {
        //delwin(mwind);
        mwind = nullptr;
    }
    Twindow(const Twindow& win)
    {
        mwind = win.mwind;
    }
    Twindow& operator=(Twindow&win)
    {
        mwind = win.mwind;
        return *this;
    }
    int mbox(int y, int x)//y 和 x分别是画行和列的字符
    {
        return box(mwind,y,x);
    }
    int mprintw(const char* fmt, ...)
    {
        int result = 0;
        va_list vp;
        va_start(vp, fmt);
        result =  ::vw_printw(mwind,fmt,vp);
        va_end(vp);
        return result;
    }
    int mprintw(attr_t type, const char* fmt, ...)
    {
        int result = 0;
        va_list vp;
        va_start(vp, fmt);
        mattron(type);
        result =  ::vw_printw(mwind,fmt,vp);
        mattroff(type);
        va_end(vp);
        return result;
    }
    int mwrefresh()
    {
        return ::wrefresh(mwind);
    }

    int mkeypad(bool benable)
    {
        return ::keypad(mwind,benable);//允许使用功能键，如F1,F2,方向键等
    }
    int mhalfdelay(int time)
    {
        return ::halfdelay(time);//启用半延时模式，参数以整型0.1s为单位，在该时间内等待输入，
                                //如果没有有效输入则返回ERR
    }
    int mattron(attr_t type)
    {
        return ::wattron(mwind,type);//修饰与mattroff之间的字符
    }
    int mattroff(attr_t type)
    {
        return ::wattroff(mwind,type);
    }
    int mattrset(attr_t arg)
    {
        return ::wattrset(mwind, arg);//该函数是设置全局修饰的
    }
    int mattrget(attr_t * res, NCURSES_PAIRS_T *pairs, void * p)
    {
        return ::wattr_get(mwind, res,pairs,p);//获取修饰
    }
    int mstandout()
    {
        return ::wattrset (mwind, A_STANDOUT);
    }
    int mstandend()
    {
        return ::wattrset (mwind, A_NORMAL);//去除所有修饰
    }
    int mchgat(int line, attr_t type, NCURSES_PAIRS_T pairs, const void * p)
    {
        return ::wchgat (mwind, line, type, pairs, p);
    }
    //窗口：
    //初始化时会默认创建一个80行，25列的窗口（根据显示环境的不同创建的窗口大小可能不同），id为stdscr。
    int maddch(const chtype ch)
    {
        return::waddch(mwind,ch);//在当前光标处输入单个字符，可以添加修饰
                                 //addch(ch | A_BOLD | A_UNDERLINE);
    }
    int maddstr(const char* str)
    {
        return ::waddnstr(mwind,str,-1);//打印字符串
    }
    int mmvaddch(int y,int x,const chtype ch)
    {
        return  (wmove((mwind),(y),(x)) == ERR ? ERR : waddch((mwind),(ch)));//将光标移动到指定位置输出字符
    }
    int mwaddch(const chtype ch)
    {
        return ::waddch(mwind,ch);//将字符输出到指定窗口
    }
    int mmvwaddch(int y,int x,const chtype ch)
    {
        return mvwaddch(mwind,y,x,ch);//移动光标到指定窗口指定坐标输出字符
    }
    int mmvprintw(int y, int x, const char* fmt,...)
    {
        int result = 0;
        va_list vp;
        if(wmove((mwind),(y),(x)) == ERR)
        {
            return ERR;
        }
        va_start(vp, fmt);
        result =  ::vw_printw(mwind,fmt,vp);
        va_end(vp);
        return result;
    }
    int mmvprintw(int y, int x, attr_t type, const char* fmt, ...)
    {
        int result = 0;
        va_list vp;
        if(wmove((mwind),(y),(x)) == ERR)
        {
            return ERR;
        }
        va_start(vp, fmt);
        mattron(type);
        result =  ::vw_printw(mwind,fmt,vp);
        mattroff(type);
        va_end(vp);
        return result;
    }
    int mgetmaxyx(int& row, int& col)
    {
        return getmaxyx(mwind,row,col);
    }
    int mwgetch()
    {
        return ::wgetch(mwind);//读取一个字符
    }
    int mscanw(const char *fmt,...)
    {
        int result = 0;
        va_list vp;
        va_start(vp, fmt);
        result = vw_scanw(mwind, fmt,vp);
        va_end(vp);
        return result;
    }
    int mmvscanw(int y, int x, const char* fmt, ...)
    {
        int result = 0;
        va_list vp;
        if(wmove((mwind),(y),(x)) == ERR)
        {
            return ERR;
        }
        va_start(vp, fmt);
        result =  ::vw_scanw(mwind,fmt,vp);
        va_end(vp);
        return result;
    }
    int mgetstr(char* res)//获取字符串
    {
        return ::wgetnstr(mwind, res, -1);
    }
    int mmove(int y, int x) //移动光标到指定坐标
    {
        return wmove((mwind),(y),(x));
    }
    int mgetyx(int& row, int& col)//获取当前光标的位置
    {
        return getyx(mwind, row, col);
    }
    int mgetparyx(int& row, int& col)//取得子窗口相对主窗口的起始坐标
    {
        return getparyx(mwind, row, col);
    }
    int mgetbegyx(int& row, int& col)
    {
        return getbegyx(mwind, row, col);
    }
    int mwborder(char ml, char mr, char tp, char bt, char c1, char c2, char c3, char c4)
    {
        return ::wborder(mwind, ml, mr, tp, bt, c1,c2,c3,c4);
    }
    int mmvhline(int y, int x, chtype type, int n)//画线 h方向，type是字符 n是长度
    {
        return (wmove((mwind),(y),(x)) == ERR ? ERR : whline((mwind),(type),(n)));
    }
    int mmvvline(int y, int x, chtype type, int n)//画线 v方向，type是字符 n是长度
    {
        return (wmove((mwind),(y),(x)) == ERR ? ERR : wvline((mwind),(type),(n)));
    }

    int mgetwein(FILE* filep)//将窗口存储到一个指定的文件中
    {
        return mwind ==::getwin(filep);
    }
    int mputwin(FILE* filep)
    {
        return ::putwin(mwind,filep);
    }
    int mcopywin(WINDOW* dst, int sminrow, int smincol, int dminrow, int dmincol, int dmaxrow, int dmaxcol, bool over)
    {
        // dst 目标窗口， sminrow源窗口所选矩形区域最小行数，smincol源窗口所选矩形区域最小列数， over 覆盖目的窗口true false
        return ::copywin(mwind , dst, sminrow, smincol, dminrow, dmincol, dmaxrow,  dmaxcol, over);
    }
    int mmvwin(int y, int x)
    {
        return ::mvwin(mwind, y, x);
    }
    int mwclear()
    {
        return ::wclear(mwind);
    }
    WINDOW* getWINDOW(){return mwind;}
private:
    WINDOW* mwind;//stdscr
};

class BaseWindow : public Twindow
{
public:
    BaseWindow()
    {
        if(mwind == nullptr)
        {
            mwind = ::initscr();
            start_color();
        }
       Twindow:: setWINDOWID(mwind);
    }
    ~BaseWindow()
    {
        mendwin();//退出NCURSES 模式
    }
    void mendwin()
    {
        if(mwind != nullptr)
        { 
            endwin();
            mwind = nullptr;
        }
    }
    BaseWindow(const BaseWindow&) = delete;
    BaseWindow& operator=(const BaseWindow&) = delete;
    //临时离开curses模式,调用endwin退出,想再次返回curses则要调用reset_prog_mode(),之后再refresh
    int mdef_prog_mode()
    {
        return ::def_prog_mode();
    }
    int mraw()
    {
        return ::raw();//raw()函数用来禁止终端缓存
    }
    int mnoraw()
    {
        return ::noraw();
    }
    int mcbreak()
    {
        return ::cbreak();//cbreak用来禁止终端缓存
    }
    int mnocbreak()
    {
        return ::nocbreak();
    }
    int mecho()
    {
        return ::echo();//终端显示键盘输入的字符
    }
    int mnoecho()
    {
        return ::noecho();//终端不显示键盘输入的字符
    }
        bool mcan_change_color()
    {
        return ::can_change_color();
    }
    int minit_color(NCURSES_COLOR_T COLOR, NCURSES_COLOR_T R, NCURSES_COLOR_T G, NCURSES_COLOR_T B)//改变颜色设置，R/G/B范围(0-1000)
    {
        return ::init_color(COLOR, R, G, B);
    }
    int minit_pair(NCURSES_COLOR_T colorID,NCURSES_COLOR_T fcolor,NCURSES_COLOR_T background)//colorID，fcolor前景色，background背景色
    {
        return ::init_pair(colorID, fcolor, background);//该函数用来生成pair id，方便后面调用
    }
    int mgetmouse(MEVENT* event)
    {
        return ::getmouse(event);
    }
    int mmouseinterval(int n = 200)//返回值获取鼠标点击的时间，默认时间间隔为1/5s
    {
        return ::mouseinterval(n);
    }
    int mscr_dump(const char* file)//把当前屏幕内容存入指定文件
    {
        return ::scr_dump(file);
    }
    int mscr_restore(const char* file)//调用屏幕文件数据来恢复屏幕
    {
        return ::scr_restore(file);
    }
    int mcurs_set(int visiable)//设置光标是否可见，0不可见，1可见，2完全可见
    {
        return ::curs_set(visiable);
    }
private:
    static WINDOW* mwind;
};
WINDOW* BaseWindow::mwind = nullptr;

class Newwin : public Twindow
{
public:
    Newwin(BaseWindow*base ,int hight, int weight, int y, int x):mwind(nullptr),mbase(base)
    {
        mwind = ::newwin(hight,weight,y,x);
        Twindow::setWINDOWID(mwind);
    }
    ~Newwin()
    {
        distoryWind();
    }
    Newwin(const Newwin&) = delete;
    Newwin& operator=(const Newwin&) = delete;
    void distoryWind()
    {
        if(mwind != nullptr)
        {
            ::delwin(mwind);
        }
    }
    BaseWindow* getbasewin()
    {
        return mbase;
    }
private:
    WINDOW* mwind;
    BaseWindow* mbase;
};

class Panel : public Newwin
{
public:
    Panel(BaseWindow*base ,int hight, int weight, int y, int x):Newwin(base ,hight, weight, y, x)
    {
        mpanle = new_panel(getWINDOW());
    }
    ~Panel()
    {
        if(mpanle != nullptr)
        {
            del_panel(mpanle);
            mpanle = nullptr;
        }
    }
    int mtop_panel()//将该panel置顶
    {
        return ::top_panel(mpanle);
    }
    int mshow_panel()
    {
        return ::show_panel(mpanle);
    }
    int mhide_panel()
    {
        return ::hide_panel(mpanle);
    }
    int mmove_panel(int y, int x)
    {
        return ::move_panel(mpanle, y, x);
    }
    static void mupdate_panels()
    {
        ::update_panels();
    }
    static int mdoupdate()
    {
        return ::doupdate();
    }
private:
    PANEL* mpanle;
};

class Item
{
public:
    Item():_Item(nullptr)
    {

    }
    void setItem(ITEM* item)
    {
        _Item = item;
    }
    Item(ITEM* item)
    {
        _Item = item;
    }
    Item(const Item& item)
    {
        this->_Item = item._Item;
    }
    Item& operator=(const Item& item)
    {
        this->_Item = item._Item;
        return *this;
    }
    Item(Item&& item)
    {
        this->_Item = item._Item;
        item._Item = nullptr;
    }
    Item& operator=(Item&& item)
    {
        this->_Item = item._Item;
        item._Item = nullptr;
        return *this;
    }
    ~Item()
    {}
    const char* mitem_name()//获取item name
    {
        return ::item_name(_Item);
    }
    const char * mitem_description ()//获取item 描述
    {
        return ::item_description(_Item);
    }
    Item_Options mitem_opts() //获取item opts
    {
        return ::item_opts(_Item);
    }
    int mitem_index()//获取item 的index
    {
        return ::item_index(_Item);
    }
    Item& mitem_opts_off(Item_Options opts, int* res = nullptr)
    {
        if(res != nullptr)
        {
            *res = ::item_opts_off(_Item, opts);
        }
        else
        {
            ::item_opts_off(_Item, opts);
        }
        return *this;
    }
    Item& mitem_opts_on(Item_Options opts, int* res = nullptr)
    {
        if(res != nullptr)
        {
            *res = ::item_opts_on(_Item, opts);
        }
        else
        {
            ::item_opts_on(_Item, opts);
        }
        return *this;
    }
    Item& mset_item_opts(Item_Options opts, int* res = nullptr)
    {
        if(res != nullptr)
        {
            *res = ::set_item_opts(_Item, opts);
        }
        else
        {
            ::set_item_opts(_Item, opts);
        }
        return *this;
    }
    Item& mset_item_value(bool b, int* res = nullptr)
    {
        if(res != nullptr)
        {
            *res = ::set_item_value(_Item, b);
        }
        else
        {
            ::set_item_value(_Item, b);
        }
        return *this;
    }
    bool mitem_value()
    {
        return ::item_value(_Item);
    }
    bool item_visible()
    {
        return ::item_visible(_Item);
    }
private:
    ITEM* _Item;
};

class Menu
{
public:
    Menu(Twindow* win):curItem(nullptr),menu(nullptr),mwind(win)
    {

    }
    ~Menu()
    {
        while(!mitems.empty())
        {
            if(mitems.back() != nullptr)
            {
                free_item(mitems.back());
            }
            mitems.pop_back();
        }
        if(menu != nullptr)
        {
            unpost_menu(menu);
            free_menu(menu);
            menu = nullptr;
        }
    }
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    Item addItem(const char* n1, const char* n2)
    {
        ITEM* it = new_item(n1,n2);
        mitems.push_back(it);
        return Item(it);
    }
    /*
    void removeItem(const char* item)
    {

    }*/
    void drawmenu(int hight, int width, int y, int x)
    {
        if(menu != nullptr)
        {
            unpost_menu(menu);
            free_menu(menu);
            menu = nullptr;
        }
        menu = new_menu(&mitems[0]);
        set_menu_win(menu,mwind->getWINDOW());
        set_menu_sub(menu, derwin(mwind->getWINDOW(),hight,width,y,x));
        post_menu(menu);
    }
    int mmenu_drive(int action)
    {
        return ::menu_driver(menu,action);
    }
    const Twindow* getTwindow()
    {
        return mwind;
    }
    int mset_menu_mark(const char* mark)
    {
        return ::set_menu_mark(menu,mark);
    }
    int mset_menu_format(int itms, int nums)//itms参数显示多少行，nums显示多少列
    {
        return ::set_menu_format(menu, itms, nums);
    }
    Menu_Options mmenu_opts()//获取opts
    {
        return menu_opts(menu);
    }
    int mmenu_opts_on(Menu_Options opts)
    {
        return ::menu_opts_on(menu, opts);
    }
    int mmenu_opts_off(Menu_Options opts)
    {
        return ::menu_opts_off(menu, opts);
    }
    int mset_menu_opts(Menu_Options opts)
    {
        return ::set_menu_opts(menu, opts);
    }
    int mitem_count()
    {
        return ::item_count(menu);
    }

    int mset_menu_fore(chtype type)//改变选中菜单的颜色
    {
        return ::set_menu_fore(menu, type);
    }
    int mset_menu_back(chtype type)//改变未选中菜单的颜色
    {
        return ::set_menu_back(menu, type);
    }
    int mset_menu_grey (chtype type)
    {
        return ::set_menu_grey(menu, type);
    }
    int mpos_menu_cursor()
    {
        return ::pos_menu_cursor(menu);
    }
    chtype mmenu_back ()
    {
        return ::menu_back(menu);
    }
    chtype mmenu_fore ()
    {
        return ::menu_fore(menu);
    }
    chtype mmenu_grey ()
    {
        return ::menu_grey(menu);
    }

    Item& mcur_item()
    {
        curItem = current_item(menu);
        curItemref.setItem(curItem);
        return curItemref;
    }
    std::vector<ITEM*>* getItems()
    {
        return &mitems;
    }
private:
    std::vector<ITEM*> mitems;
    ITEM* curItem;
    MENU* menu;
    Twindow* mwind;
    Item curItemref;
};