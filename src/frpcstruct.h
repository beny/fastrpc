/*
 * FILE          $Id: frpcstruct.h,v 1.1 2005-07-19 13:02:54 vasek Exp $
 *
 * DESCRIPTION   
 *
 * AUTHOR        
 *              Miroslav Talasek <miroslav.talasek@firma.seznam.cz>
 *
 * Copyright (C) Seznam.cz a.s. 2005
 * All Rights Reserved
 *
 * HISTORY
 *       
 */
#ifndef FRPCFRPCSTRUCT_H
#define FRPCFRPCSTRUCT_H

#include <frpcvalue.h>
#include "frpctypeerror.h"
#include <map>
#include <string>


namespace FRPC
{
class Pool_t;

/**
@brief Srtruct type
@author Miroslav Talasek
*/
class FRPC_DLLEXPORT Struct_t : public Value_t
{
    friend class Pool_t;
public:
    /**
        @brief Struct_t iterator
    */
    typedef std::map<std::string,Value_t*>::iterator        iterator;
    /**
         @brief Struct_t const_iterator
    */
    typedef std::map<std::string,Value_t*>::const_iterator  const_iterator;
    /**
         @brief Struct_t size_type
    */
    typedef std::map<std::string,Value_t*>::size_type       size_type;
    /**
        @brief Struct_t key_type
    */
    typedef std::map<std::string,Value_t*>::key_type        key_type;
    /**
         @brief Struct_t value_type
    */
    typedef std::map<std::string,Value_t*>::value_type      value_type;
    /**
        @brief Struct_t pair
    */
    typedef std::pair<std::string,Value_t*>                 pair;


    enum{TYPE = 0x0A};
    /**
    `   @brief Default destructor
    */
    virtual ~Struct_t();
    /**
        @brief Method to clone/copy Struct_t 
        @param newPool is pointer of Pool_t which is used for allocate objects
    */
    virtual Value_t& clone(Pool_t& newPool) const;
    /**
        @brief Getting type of value
        @return  @b unsigned @b short always 
        @li @b Struct_t::TYPE - identificator of struct value
    */
    virtual unsigned short getType()
    {
        return TYPE;
    }
    /**
        @brief Getting typename of value
        @return @b const @b char* always
        @li @b "Struct" - typename of Struct_t
    */
    virtual const char* getTypeName()
    {
        return "struct";
    }
    /**
        @brief Getting info if Struct_t has key
        @param key searched key
        @return @b bool
        @li @b TRUE - if struct has key 'key'
        @li @b FALSE - if struct hasn't key 'key'
    */
    bool has_key(const key_type &key);
    /**
        @brief Inserting a new item with key
        @param key is reference to Struct_t::key_type
        @param value is reference to new Value_t 
        @return  std::pair<iterator, bool> as std::map<>::insert(..)
    */
    std::pair<iterator, bool> insert(const key_type &key, Value_t &value);
    /**
        @brief Inserting a new item with key
        @param value is new pair Struct_t::pair(std::string key, Value_t* value)
        @return  std::pair <iterator, bool> as std::map<>::insert(..)
    */
    std::pair<iterator, bool> insert(pair value);
    /**
        @brief Delete all items in Struct_t
    */
    void clear();
    /**
        @brief Checking if Struct_t is empty
        @return bool
        @li @b TRUE if the Struct_t is empty @n
        @li @b FALSE if the Struct_t isn't empty   
    */
    bool empty();
    /**
        @brief getting number of items in Struct_t
        @return  Struct_t::size_type -  number of items in Struct_t
    */
    size_type size();
    
    /**
        @brief Getting iterator to first item
        @return Struct_t::iterator - position to first item
    */
    iterator begin();
    /**
        @brief Getting iterator to last item
        @return Struct_t::iterator - position to last item
    */
    iterator end();
    /**
        @brief Insert Value_t to Struct_t with key
        @param value is is new pair Struct_t::pair(std::string key, Value_t* value)
        @return Struct_t& reference with apended value 
    */
    Struct_t& append(pair value);
    /**
        @brief Insert Value_t to Struct_t with key
        @param key is reference to Struct_t::key_type
        @param value is reference to new Value_t 
        @return Struct_t& reference with apended value
    */
    Struct_t& append(const key_type &key, Value_t &value);
    /**
        @brief operator []
        @return reference to Value_t or exeption KeyError_t if key isn't exist
    */
    Value_t& operator[] (const key_type &key);
    
private:
    /**
        @brief Default constructor is disabled
    */
    Struct_t();
    /** 
        @brief Costructor empty Struct_t 
        @param pool is a reference to Pool_t used for allocating
    */
    Struct_t(Pool_t &pool);
    /**          1
        @brief Costructor of Struct_t with one item
        @param pool is a reference to Pool_t used for allocating
        @param key is reference to Struct_t::key_type
        @param value is reference to new Value_t 
    */
    Struct_t(Pool_t &pool, const std::string &key, Value_t &value);
    /** 
        @brief Costructor of Struct_t  with one item
        @param pool is a reference to Pool_t used for allocating
        @param value is new pair Struct_t::pair(std::string key, Value_t* value)
    */  
    Struct_t(Pool_t &pool,pair value );
    
    
    
    std::map<std::string,Value_t*> structData; ///internal Struct_t data


};
/**
    @brief Inline method
    
    Used to retype Value_t to Struct_t 
    @return  If Value_t  can  retype to Struct_t return reference to  Struct_t
    @n If Value_t can't retype to Struct_t: throw exception TypeError_t
    
*/
inline FRPC_DLLEXPORT Struct_t& Struct(Value_t &value)
{
    Struct_t *struct_v = dynamic_cast<Struct_t*>(&value);

    if(!struct_v)
        throw TypeError_t("Type is %s but not struct",value.getTypeName());
    return *struct_v;

}

}

#endif
