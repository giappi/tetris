/*
 * File:   Function.h
 * Author: Giappi
 *
 * Created on 16 October 2018, 12:50
 */

#ifndef FUNCTION_H
#define FUNCTION_H
#include "cpp/lang/Object.h"
#include "cpp/memory/Memory.h"

#define extend :

template <class Fx>
class Function;

template <class ReturnType, class... Args>
class Function<ReturnType(Args...)>
    extend public Object
{

private:

    /**
     * Generic Function
     */
    class Fn
    {

    public:
        /**
         * Operator call function
         * @param args arguments
         * @return ReturnType
         */
        virtual ReturnType operator()(Args... args) = 0;
        /**
         * Make another Fn from this
         * @return an other Fn as pointer
         */
        virtual Fn* clone() = 0;

    };

    /**
     * Specific Function
     */
    template <class T>
    class Fx
        extend public Fn
    {

    public:

        /**
         * Create a specific function
         * @param function
         */
        Fx(T function): _fx_with_args(function)
        {
        };

        /**
         * Operator call funtion(args...)
         * @param args arguments
         * @return ReturnType
         */
        ReturnType operator()(Args... args) override
        {
            return _fx_with_args(args...);
        }
        /**
         * Make a duplicate version of this Fx
         * @return an other Fn as pointer
         */
        Fn* clone() override
        {
            return Memory::allocate<Fx<T>>(*this);
            //return new Fx<T>(*this);
        };


    private:

        T _fx_with_args;

    };

public:

    /**
     * Create a Function that is callable
     * @param function
     */
    template <class CallableType>
    Function(CallableType function)
    {
        this->_fx = Memory::allocate<Fx<CallableType>>(function);
        //this->_fx = new Fx<CallableType>(function);
    }

    /**
     * Create new Function by copy from another: `Function b = a;`
     * @param __fx another Function
     */
    Function(const Function<ReturnType(Args...)>& __fx)
    {
        Fn* fx1 = __fx._fx;
        if(fx1 != null)
        {
            this->_fx = fx1->clone();
        }
        else
        {
            this->_fx = null;
        }
    }

    Function&   operator =(const Function& __another)
    {
        if(&__another != this)
        {
            Fn*    fx1 = __another._fx;
            if(fx1 != null && this->_fx != null)
            {
                Memory::unallocate(this->_fx);
                this->_fx = fx1->clone();
            }
            else
            {
                this->_fx = null;
            }
        }
        return *this;
    }

    /**
     * Operator for call Funtion(args...)
     * @param args arguments
     * @return ReturnType
     */
    ReturnType  operator()(Args... args)
    {
        ReturnType tmp;
        if(_fx != null)
        {
            tmp = _fx->operator ()(args...);
        }
        else
        {
            tmp = ReturnType();
        }
        return tmp;
    }

    /**
     * Default contructor
     */
    Function(){}

    /**
     * Destroy and clean up everything
     */
    virtual ~Function()
    {
        if(_fx != null)
        {
            Memory::unallocate(this->_fx);
            _fx = null;
        }
    }

private:

    Fn* _fx = null;

};


#endif /* FUNCTION_H */

