#ifndef _MANAGER_H_
#define _MANAGER_H_

// 单例设计模式

template <typename T>

class Manager
{
public:
	// 如果没有实例则创建实例，有实例则返回实例指针
	static T* instance()
	{
		if (!manager)
			manager = new T();

		return manager;
	}

private:
	static T* manager;

protected:
	// 将构造函数以及析构函数保护起来，确保程序运行过程中只有一个实例
	Manager() = default;
	~Manager() = default;
	// 将拷贝构造函数和重载的赋值运算符删除
	Manager(const Manager&) = delete;
	Manager& operator = (const Manager&) = delete;

};

template <typename T>
T* Manager<T>::manager = nullptr;

#endif // !_MANAGER_H_
