#ifndef __VSN_OBJECT_INTERNAL_H
#define __VSN_OBJECT_INTERNAL_H


//-----------------------------------------------------------------------------
// signal & slot method ptr
// ---
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
bool VSN::Object::Connect(const Sender* pSender, void (SignalClass::*signalMethod)(SignalArgs...),
    const Receiver* receiver, SlotReturn (SlotClass::*slotMethod)(SlotArgs...), VSN::ConnectionType type)
{      
   if (pSender == nullptr)
   {
      vsnWarning("Object::Connect() Can not connect, because sender is null.");
      return false;
   }

   if (receiver == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, receiver is null");
      return false;
   }

   if (signalMethod == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, signal is null");
      return false;
   }

   if (slotMethod == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, slot is null");
      return false;
   }
   
   // получить сигнал MetaMethod
   const MetaObject* pSenderMetaObject = pSender->GetMetaObject();
   MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);

   const char* pSenderClass = pSenderMetaObject->GetMetaClassName();

   String signature = signalMetaMethod.MethodSignature();
   const char* signalName = signature.c_str();

   if (signature.IsEmpty())  
   {
      vsnWarning("%s%s%s", "Object::Connect() ", pSenderClass, "::<Invalid Signal> ");
      return false;
   }

   // является ли signalMethod сигналом
   if (signalMetaMethod.GetMethodType() != MetaMethod::Signal ) 
   {
      vsnWarning("%s%s%s%s%s", "Object::Connect() ", pSenderClass, "::", signalName, "was not a valid signal");
      return false;
   }  

   ConnectionInner typeConnect;
   bool uniqueConnection = false;

   if (type & UniqueConnection)
      uniqueConnection = true;

   typeConnect = static_cast<ConnectionInner>(type & ~UniqueConnection);

   PrivateConnect(*pSender, signalMethod, *receiver, slotMethod, typeConnect, uniqueConnection);
   pSender->OnConnectNotify(signalMetaMethod);
   return true;
}

// signal method ptr, slot lambda
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
bool VSN::Object::Connect(const Sender *sender, void (SignalClass::*signalMethod)(SignalArgs...), 
    const Receiver* receiver, T slotLambda, VSN::ConnectionType type)
{
   static_assert(std::is_base_of<Object, Sender>::value, "Sender must inherit from Object");  
   if (sender == nullptr) 
   {
      vsnWarning("Object::connect() Can not connect, sender is null");
      return false;
   }

   if (receiver == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, receiver is null");
      return false;
   }

   if (signalMethod == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, signal is null");
      return false;
   }

   // получить сигнал MetaMethod
   const MetaObject* pSenderMetaObject = sender->GetMetaObject();
   MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);

   const char* pSenderClass = pSenderMetaObject->GetMetaClassName();

   String signature = signalMetaMethod.MethodSignature();
   const char* signalName  = signature.c_str();

   if (signature.IsEmpty())
   {
      vsnWarning("%s%s%s", "Object::Connect() ", pSenderClass, "::<Invalid Signal> ");
      return false;
   }

   // является ли сигналом для сигнала
   if (signalMetaMethod.GetMethodType() != MetaMethod::Signal ) 
   {
      vsnWarning("%s%s%s%s%s", "Object::Connect() ", pSenderClass, "::", signalName, "was not a valid signal");
      return false;
   }  
   
   ConnectionInner typeConnect;
   bool uniqueConnection = false;

   if (type & UniqueConnection)
      uniqueConnection = true;

   // преобразовать тип
   typeConnect = static_cast<ConnectionInner>(type & ~UniqueConnection);
   PrivateConnect(*sender, signalMethod, *receiver, slotLambda, typeConnect, uniqueConnection);
   sender->OnConnectNotify(signalMetaMethod);
   return true;
}

// 
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
bool VSN::Object::Disconnect(const Sender* pSnder, void (SignalClass::*signalMethod)(SignalArgs...), 
    const Receiver* pReceiver, SlotReturn (SlotClass::*slotMethod)(SlotArgs...))
{
   static_assert(std::is_base_of<Object, Sender>::value, "Sender must inherit from Object");  
   if (pSnder == nullptr || (pReceiver == nullptr && slotMethod != nullptr))
   {
      vsnWarning("Object::Disconnect() Unexpected null parameter");
      return false;
   }
   bool retval = PrivateDisconnect(*pSnder, signalMethod, *pReceiver, slotMethod);
   if (retval) 
   {
      if (const MetaObject* pSenderMetaObject = pSnder->GetMetaObject())
      {
          MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);
          const_cast<Sender *>(pSnder)->OnDisconnectNotify(signalMetaMethod);
      } 
   }
   return retval;
}

template<class Sender, class SignalClass, class ...SignalArgs, class Receiver>
bool VSN::Object::Disconnect(const Sender* sender, void (SignalClass::* signalMethod)(SignalArgs...),
    const Receiver* receiver, std::nullptr_t slotMethod)
{
    (void)slotMethod;

    static_assert(std::is_base_of<Object, Sender>::value, "Sender must inherit from Object");

    if (sender == nullptr) 
    {
        vsnWarning("Object::Disconnect() Unexpected null parameter");
        return false;
    }

    const MetaObject* senderMetaObject = sender->GetMetaObject();
    bool retval = false;

    if (senderMetaObject) 
    {
        MetaMethod signalMetaMethod = senderMetaObject->Method(signalMethod);
        const AbsStorage* signalMethod_Bento = signalMetaMethod.GetStorage();

        retval = PrivateDisconnect(*sender, signalMethod_Bento, receiver, nullptr);

        if (retval)
            const_cast<Sender*>(sender)->Object::OnDisconnectNotify(signalMetaMethod);
    }
    return retval;
}

// 
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
bool VSN::Object::Disconnect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), 
    const Receiver* pReceiver, T slotMethod)
{
    bool retval = PrivateDisconnect(*sender, signalMethod, *pReceiver, slotMethod);
    if (retval)
    {
        if (const MetaObject* pSenderMetaObject = sender->GetMetaObject())
        {
            MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);
            const_cast<Sender *>(sender)->OnDisconnectNotify(signalMetaMethod);
        }
    }
    return retval;
}
#endif // __VSN_OBJECT_INTERNAL_H
