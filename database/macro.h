#ifndef MACRO_H
#define MACRO_H
/*
 * Macro khai bao Q_PROPERTY de su dung metaobject
*/
#define OBJECT_PROPERTY(type,name)\
Q_PROPERTY(type name READ get##name WRITE set##name)\
    private:\
    type name;\
    public:\
    type get##name()\
    {\
        return name;\
    }\
    void set##name(type input_##name)\
        {\
            name=input_##name;\
        }


#endif // MACRO


