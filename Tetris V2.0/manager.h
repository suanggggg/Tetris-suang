#ifndef _MANAGER_H_
#define _MANAGER_H_

// �������ģʽ

template <typename T>

class Manager
{
public:
	// ���û��ʵ���򴴽�ʵ������ʵ���򷵻�ʵ��ָ��
	static T* instance()
	{
		if (!manager)
			manager = new T();

		return manager;
	}

private:
	static T* manager;

protected:
	// �����캯���Լ�������������������ȷ���������й�����ֻ��һ��ʵ��
	Manager() = default;
	~Manager() = default;
	// ���������캯�������صĸ�ֵ�����ɾ��
	Manager(const Manager&) = delete;
	Manager& operator = (const Manager&) = delete;

};

template <typename T>
T* Manager<T>::manager = nullptr;

#endif // !_MANAGER_H_
