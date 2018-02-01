#include "cmainwindow.h"
#include "compilepreprocessor.h"

#include <QApplication>

#ifdef test
    #include <qstringlist.h>
    #include <iostream>
    using namespace std;
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef  test //测试代码,已测试通过.
    QApplication::addLibraryPath("/home/gorf999/Music");
    QStringList sl;
    sl=QApplication::libraryPaths();
    for(int i=0; i<sl.size(); i++)
    {
        cout<<sl.at(i).toLocal8Bit().constData()<<endl;
    }
#endif

    CMainWindow w;
    w.show();

    return a.exec();
}
