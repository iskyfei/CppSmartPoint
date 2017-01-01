//
//  smartPtr1.h
//  test
//
//  Created by sky on 2017/1/1.
//  Copyright © 2017年 sky. All rights reserved.
//

#ifndef smartPtr1_h
#define smartPtr1_h

template<typename T>
class CRefPtr
{
public:
    T* operator->() const
    {
        return m_refObj->m_obj;
    }
    
    T& operator()() const
    {
        assert(m_refObj->m_obj != NULL);
        return *m_refObj->m_obj;
    }
    
    T& operator*() const
    {
        assert(m_refObj->m_obj != NULL);
        return *m_refObj->m_obj;
    }
    
    T* GetPtr() const
    {
        return m_refObj->m_obj;
    }
    
    bool IsNull() const
    {
        return m_refObj->m_obj == NULL;
    }
    
    explicit CRefPtr(T* p = NULL)
    {
        m_refObj = new CRefObject();
        if(m_refObj != NULL)
        {
            m_refObj->m_obj = p;
            m_refObj->AddRefCount();
        }
    }
    
    CRefPtr(const CRefPtr& ref)
    {
        m_refObj = ref.m_refObj;
        if(m_refObj != NULL)
        {
            m_refObj->AddRefCount();
            
        }
    }
    
    ~CRefPtr()
    {
        if(m_refObj != NULL && m_refObj->SubRefCount() == 0)
        {
            delete m_refObj;
        }
    }
    
    CRefPtr& operator = (const CRefPtr& ref)
    {
        if(this != &ref)
        {
            if(m_refObj != NULL
               && m_refObj->SubRefCount() == 0)
            {
                delete m_refObj;
            }
            
            m_refObj = ref.m_refObj;
            
            if(m_refObj != NULL)
            {
                m_refObj->AddRefCount();
            }
        }
        
        return *this;
    }
    
    bool operator == (const CRefPtr& ref) const
    {
        return m_refObj == ref.m_pRawObj;
    }
    
    int get_ref_count()
    {
        return m_refObj->GetRefCount();
    }
    
    class CRefObject
    {
    public:
        T* m_obj;
        CRefObject()
        {
            m_nRefCount = 0;
        }
        
        ~CRefObject()
        {
            if (m_obj) {
                delete m_obj;
            }
        }
        
        inline int GetRefCount() const
        {
            return m_nRefCount;
        }
        
        inline int AddRefCount()
        {
            return ++m_nRefCount;
        }
        
        inline int SubRefCount()
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
    
    
private:
    
    CRefObject *m_refObj;
    
    
};
#endif /* smartPtr1_h */
