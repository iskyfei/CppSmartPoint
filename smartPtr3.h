//
//  smartPtr3.h
//  test
//
//  Created by sky on 2017/1/1.
//  Copyright © 2017年 sky. All rights reserved.
//

#ifndef smartPtr3_h
#define smartPtr3_h

class CRefObject
{
public:
    CRefObject()
    {
        m_nRefCount = 0;
    }
    
    int GetRefCount() const
    {
        return m_nRefCount;
    }
    
    int AddRefCount()
    {
        return ++m_nRefCount;
    }
    
    int SubRefCount()
    {
        return --m_nRefCount;
    }
    
    void ResetRefCount()
    {
        m_nRefCount = 0;
    }
    
private:
    int    m_nRefCount;
};


//T should inherit from CRefObject
template<typename T>
class CRefPtr
{
public:
    T* operator->() const
    {
        return m_pRawObj;
    }
    
    T& operator()() const
    {
        assert(m_pRawObj != NULL);
        return *m_pRawObj;
    }
    
    T& operator*() const
    {
        assert(m_pRawObj != NULL);
        return *m_pRawObj;
    }
    
    T* GetPtr() const
    {
        return m_pRawObj;
    }
    
    bool IsNull() const
    {
        return m_pRawObj == NULL;
    }
    
    explicit CRefPtr(T* p = NULL)
    {
        m_pRawObj = p;
        if(p != NULL)
        {
            p->AddRefCount();
        }
    }
    
    CRefPtr(const CRefPtr& ref)
    {
        m_pRawObj = ref.m_pRawObj;
        if(m_pRawObj != NULL)
        {
            m_pRawObj->AddRefCount();
        }
    }
    
    ~CRefPtr()
    {
        if(m_pRawObj != NULL && m_pRawObj->SubRefCount() == 0)
        {
            delete m_pRawObj;
        }
    }
    
    CRefPtr& operator = (const CRefPtr& ref)
    {
        if(this != &ref)
        {
            if(m_pRawObj != NULL
               && m_pRawObj->SubRefCount() == 0)
            {
                delete m_pRawObj;
            }
            
            m_pRawObj = ref.m_pRawObj;
            
            if(m_pRawObj != NULL)
            {
                m_pRawObj->AddRefCount();
            }
        }
        
        return *this;
    }
    
    bool operator == (const CRefPtr& ref) const
    {
        return m_pRawObj == ref.m_pRawObj;
    }
    
private:
    T* m_pRawObj;
};

#endif /* smartPtr3_h */
