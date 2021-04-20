#include <Python.h>
#include "startClusterThread.h"
#include "PyThreadStateLock.h"

#include <QDebug>

startClusterThread::startClusterThread(QObject* par):QThread(par)
{
}
startClusterThread::~startClusterThread()
{
    qDebug() << "startClusterThread::~startClusterThread()";
}

void startClusterThread::run()
{
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();
    qDebug() << "进入run函数......";
    PyObject* pModule = PyImport_ImportModule("start");
    if(pModule)
    {
        // 获取模块属性字典pDict
        PyObject* pDict = PyModule_GetDict(pModule);
        if (!pDict)
        {
            printf("Cant find dictionary./n");
        }
        PyObject* pClassCalc = PyDict_GetItemString(pDict,"startCluster");
        if (!pClassCalc){
            printf("Cant find cal calss./n");
        }
        // 得到构造函数而不是类实例
        PyObject* pConstruct = PyInstanceMethod_New(pClassCalc);
        if (!pConstruct){
            printf("Cant find calc construct./n");
        }
        // 构建类构造函数的参数
        char* infilename = c_transition_python(in_filepath);
        char* gender = c_transition_python(selgender);
        char* stroke = c_transition_python(selstroke);
        char* stroketype = c_transition_python(selstroketype);

        PyObject* args = PyTuple_New(4);
        PyObject* in_filename = PyUnicode_FromString(infilename);
        PyObject* in_gender = PyUnicode_FromString(gender);
        PyObject* in_stroke = PyUnicode_FromString(stroke);
        PyObject* in_stroketype = PyUnicode_FromString(stroketype);
        PyTuple_SetItem(args,0,in_filename);
        PyTuple_SetItem(args,1,in_gender);
        PyTuple_SetItem(args,2,in_stroke);
        PyTuple_SetItem(args,3,in_stroketype);

        // 实例化类得到类对象
        PyObject* pInstance = PyObject_CallObject(pConstruct,args);

        // 调用对象的成员函数
        PyObject* pRet1 = PyObject_CallMethod(pInstance,"k_means","");
        if (!pRet1)
        {
            printf("不能找到 pRet");
        }
        // 解析python调用结果
        if (PyTuple_Check(pRet1))
        {
            qDebug()<<"python脚本返回结果元素个数= "<< PyTuple_Size(pRet1)<<endl;
            PyObject* item1 = PyTuple_GetItem(pRet1,1);
            char info;
            PyArg_Parse(item1,"s",&info);
            qDebug()<<info;
        }
    }
    else{
        qDebug() << "导入python模块失败";
    }
    PyGILState_Release(gstate);
}

char* startClusterThread::c_transition_python(QString in_c_obj)
{
    QByteArray curobj = in_c_obj.toUtf8();
    char* input_obj= curobj.data();
    return input_obj;
}




