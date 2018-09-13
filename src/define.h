#pragma once

#define WM_COMMAND		0x0111


#define REGISTER(class_name) \
	private: \
		const std::string name = #class_name; \
	public: \
		std::string get_name(){ return name; } 

#define REGISTER_CLASS(class_name) \
class class_name##Register { \
public: \
	static void * NewInstance() { return new class_name; } \
private: \
	static Register reg; \
}; \
Register class_name##Register::reg(#class_name, class_name##Register::NewInstance);


#define DECLARE_MESSAGE_MAP() \
	static AFX_MSGMAP messageMap;\
	static std::vector<AFX_MSGMAP_ENTRY> messageEntries; \
	virtual AFX_MSGMAP* GetMessageMap() const;


#define IMPLEMENT_MESSAGE_MAP(theClass, baseClass) \
	AFX_MSGMAP* theClass::GetMessageMap() const { return &theClass::messageMap; } \
	std::vector<AFX_MSGMAP_ENTRY> theClass::messageEntries = {{0, 0, 0, 0, 0, 0 }}; \
	AFX_MSGMAP theClass::messageMap = {&(baseClass::messageMap), &(theClass::messageEntries)};


#define ON_COMMAND(id,memberFxn){WM_COMMAND,0,(int)id,(int)id,AfxSig_vv,(AFX_PMSG)memberFxn}

