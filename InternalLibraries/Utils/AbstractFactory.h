#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QMap>
#include <QHash>
//#include <>
//#include <>
//#include <>

//#include ""
//#include ""
//------------------------------------------------------------------------------------
//! http://habrahabr.ru/post/229993/
//! Фабрика объектов с шаблонными типами идентификатора объекта,
//! базового класса создаваемых объектов и переменным списком аргументов создаваемых классов
//! ID          - тип ключа
//! Base        - тип базового(для создаваемых) класса
//! ... Args    - аргументы для создаваемого класса
//!
template< typename ID, class BaseItem, class ... Args>
class AbstractFactory      
{
    public:
        //! Тип указателя на функцию, создающую конкретный объект
        typedef BaseItem* (*fInstantiator)(Args ...);

        //! Шаблонная функция создания классов, наследников Base,
        //! с переменным колличеством аргументов по ID
        template<class DerivedItem>
        static BaseItem* instantiator(Args ... args)
            { return new DerivedItem(args ...); }

    private:
        //! Тип хранилища соответствий идентификатор объекта - функция, создающая объект
        //typedef QMap<ID, fInstantiator> InstantiatorMap;
        typedef QHash<ID, fInstantiator> InstantiatorMap;

    public:
        explicit AbstractFactory()
            {  }
        virtual ~AbstractFactory()
            {  }

        //! Регистрация нового класса объектов Derived по идентификатору ID
        //! factory.addType<DerivedItem>("newObject");
        template<class DerivedItem>
        void addType(const ID &itemId)
            { m_createCallbackMap.insert(itemId, &instantiator<DerivedItem>); }

        //! Регистрация новой функции создания объекта по идентификатору
        //! m_factory.addTypeFunction<NewItemForm>("NewItem", ...arg);
        inline void addTypeFunction(const ID &itemId, fInstantiator createFn)
            { m_createCallbackMap.insert(itemId, createFn); }

        //! Дерегистрация функциии создания по идентификатору
        inline fInstantiator unregisteredItem(const ID &itemId)
            { return m_createCallbackMap.take(itemId); }

        //! Создать объект по идентификатору
        //! factory.createInstance("Id", "args");
        virtual BaseItem* createInstance(const ID &itemId, Args ... args)
            {
                fInstantiator createFn = m_createCallbackMap.value(itemId, NULL);
                if(createFn != NULL)
                    return createFn(args ...);
                return NULL;
            }

    private:
        //! Хранилище идентификатор объекта - функция, создающая объект
        InstantiatorMap m_createCallbackMap;
};
//------------------------------------------------------------------------------------
/*
    //! Пример применения
    AbstractFactory<QString, ModbusCore, ModbusDeviceAddress> modbusCoreFactory;

    modbusCoreFactory.addType<ModbusRTU>  ("RTU");
    modbusCoreFactory.addType<ModbusASCII>("ASCII");
    modbusCoreFactory.addType<ModbusISI>  ("ISI");
    modbusCoreFactory.addType<ModbusTCP>  ("TCP");

    ModbusDeviceAddress modbusDeviceAddress;

    ModbusRTU   *rtu    = modbusCoreFactory.createInstance("RTU")  (modbusDeviceAddress);
    ModbusASCII *ascii  = modbusCoreFactory.createInstance("ASCII")(modbusDeviceAddress);
    ModbusISI   *cat    = modbusCoreFactory.createInstance("ISI")  (modbusDeviceAddress);
    ModbusTCP   *tcp    = modbusCoreFactory.createInstance("TCP")  (modbusDeviceAddress);
*/
//------------------------------------------------------------------------------------
#endif // ABSTRACTFACTORY_H
