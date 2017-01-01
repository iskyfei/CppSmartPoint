//
//  SmartPtr2.h
//  test
//
//  Created by sky on 2017/1/1.
//  Copyright © 2017年 sky. All rights reserved.
//

#ifndef SmartPtr2_h
#define SmartPtr2_h
template<typename T> class CRefPtr;

template<typename T>
class U_Ptr
{
private:
    
    friend class CRefPtr<T>;
    
    U_Ptr(T *ptr) :p(ptr), count(0)
    {
    }
    ~U_Ptr() { delete p; }
    
    int count;
    T *p;
};

template<typename T>
class CRefPtr
{
public:
    T* operator->() const
    {
        return rp->p;
    }
    
    T& operator()() const
    {
        assert(rp->p != NULL);
        return *(rp->p);
    }
    
    T& operator*() const
    {
        assert(rp->p != NULL);
        return *(rp->p);
    }
    
    T* GetPtr() const
    {
        return (rp->p);
    }
    
    bool IsNull() const
    {
        return (rp->p) == NULL;
    }
    
    explicit CRefPtr(T* p = NULL)
    {
        rp = new U_Ptr<T>(p);
        
        if(rp != NULL)
        {
            rp->count ++;
        }
    }
    
    CRefPtr(const CRefPtr& ref)
    {
        rp = ref.rp;
        if(rp != NULL)
        {
            rp->count++;
        }
    }
    
    ~CRefPtr()
    {
        
        if(rp != NULL && --(rp->count) == 0)
        {
            delete rp;
        }
    }
    
    CRefPtr& operator = (const CRefPtr& ref)
    {
        if(this != &ref)
        {
            if(rp != NULL
               && --(rp->count) == 0)
            {
                delete rp;
            }
            
            rp = ref.rp;
            
            if(rp != NULL)
            {
                rp->count++;
            }
        }
        
        return *this;
    }
    
    bool operator == (const CRefPtr& ref) const
    {
        return rp == ref.rp;
    }
    
    int get_ref_count() const
    {
        return rp->count;
    }
    
private:
    CRefPtr();
    U_Ptr<T> *rp;
};


#endif /* SmartPtr2_h */
